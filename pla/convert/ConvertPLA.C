#include "header.h"
TEnv *env =new TEnv("configConvertPLA.prm");
#include "PLARead.h"
#include "PLAConvert.h"
class ConvertPLA{
	private:

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;

		int runNumber;
		Long64_t maxEventNumber;

		int EventNumber;
		int RunNumber;

		TArtStoreManager *sman;
		TArtEventStore *EventStore;
		TArtCalibPlastic *CalibPlastic;

		TArtPlastic *PlasticF3  ; 
		TArtPlastic *PlasticF7  ; 
		TArtPlastic *PlasticSBT1;
		TArtPlastic *PlasticSBT2;
		TArtPlastic *PlasticSBV ;


		TFile *outputFile;
		TTree *tree;
		PLARead *plaRead;
		PLAConvert *plaConvert;

		TString getInputName(){
			TString inputPath=env->GetValue("inputPath","./rootfile/");
			TString inputPrefix = env->GetValue("inputPrefix","run0");
			TString inputSuffix = env->GetValue("inputSufffix",".ridf.gz");
			return inputPath+inputPrefix+Form("%d",runNumber)+inputSuffix;

		}

		TString getOutputName(){
			TString outputPath=env->GetValue("outputPath","./rootfile/");
			TString outputPrefix = env->GetValue("outputPrefix","run0");
			TString outputSuffix = env->GetValue("outputSuffix","_PLA.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}
		void setOutputBranch(){
			tree->AutoSave("SaveSelf");
			tree->SetAutoSave(1e5);

			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			plaRead->setBranch(tree);
			plaConvert->setBranch(tree);
		}
		void preSetting(){
			start = std::clock();
			clock0 = std::clock();

			EventNumber = 0;
			RunNumber = runNumber;
			reconstructDataHolder();
		}
		void reconstructDataHolder(){

			// Load BigRIPS Plastic detector
			CalibPlastic = new TArtCalibPlastic();


		}
		void analysisLoop(){
			while(EventStore->GetNextEvent()
					&& EventNumber < maxEventNumber
			     )
			{

				showAnalysisProgress();

				EventNumber++;

				getRawData();
				readData();
				//readRawData();
				convertData();
				tree->Fill();
				if(maxEventNumber<100) print();
			}
		}
		void print(){
			cout<<"EventNumber = "<<EventNumber<<endl;
			printF3();
			printF7();
			printSBT1();
			printSBT2();
			printF13();
			printSBV();
		}
		void printF3(){
			plaRead->printF3();
			plaConvert->printF3();
		}
		void printF7(){
			plaRead->printF7();
			plaConvert->printF7();
		}
		void printSBT1(){
			plaRead->printSBT1();
			plaConvert->printSBT1();
		}
		void printSBT2(){
			plaRead->printSBT2();
			plaConvert->printSBT2();
		}
		void printF13(){
			plaConvert->printF13();
		}
		void printSBV(){
			plaRead->printSBV();
			plaConvert->printSBV();
		}

		void showAnalysisProgress(){
			if (EventNumber%DISPLAY_EVERY_EVENT == 0)
			{
				double duration =  int(10*((std::clock()-start)/ (double) CLOCKS_PER_SEC))/10. ;
				Double_t rate = DISPLAY_EVERY_EVENT/((std::clock()-clock0)/ (double) CLOCKS_PER_SEC) ;
				Int_t color = rate<100?33:31 ;//int(TMath::Log(rate)/TMath::Ln10())+31;
				std::clog << "\e[1;" << color << "m  ANALYSIS-Info : " << EventNumber/1000 << "k events treated in "
					<< duration << "s. Instantaneous rate = "
					<< rate << "evt/s\e[0m             \r";
				clock0 = std::clock();
			}

		}
                void getRawData(){
                        clearReconstructedData();
                        reconstructData();
                        //getDataContainer();

                }
                void clearReconstructedData(){

			CalibPlastic->ClearData();

                }
                void reconstructData(){
			CalibPlastic->ReconstructData();

                }
                void getDataContainer(){
			PlasticF3 = CalibPlastic->FindPlastic((char*)"F3pl");
			PlasticF7 = CalibPlastic->FindPlastic((char*)"F7pl");
			PlasticSBT1 = CalibPlastic->FindPlastic((char*)"F13pl-1");
			PlasticSBT2 = CalibPlastic->FindPlastic((char*)"F13pl-2");
			PlasticSBV = CalibPlastic->FindPlastic((char*)"SBV");

		}
		void readData(){
			plaRead->read(CalibPlastic);
		}
		void convertData(){
			plaConvert->convert(plaRead);
		}

	public:
		ConvertPLA(int rn,Long64_t men){
			runNumber = rn;
			maxEventNumber = men;
		}
		void load(){

			loadAnarootDecoder();
			openAnarootStoreManager();
			loadAnarootDataBase();

		}
		void openAnarootStoreManager(){
			sman = TArtStoreManager::Instance();
		}
		void loadAnarootDecoder(){
			//////////////////// Load anaroot decode class ////////////////////      
			gSystem->Load("libanacore.so");
			gSystem->Load("libanasamurai.so");
			gSystem->Load("libXMLParser.so");
		}
		void loadAnarootDataBase(){

			TArtBigRIPSParameters* BigRIPSPara = TArtBigRIPSParameters::Instance();

			TString dbFolder = env->GetValue("dbFolder",".");
			TString plasXml = env->GetValue("plasXml","SAMURAIPlastic.xml");
			plasXml = dbFolder + plasXml;
			cout<<plasXml<<endl;
			BigRIPSPara->LoadParameter((char *)plasXml.Data()); //F3 F7 and SBT plastic

		}
		void openRawData(){
			///////////////////// Open Raw Data ///////////////////////////////

			EventStore = new TArtEventStore;

			TString inputName=getInputName();
			cout<<inputName<<endl;

			if(!EventStore->Open(inputName))
			{
				std::cout << "\e[34m " << "cannot open " <<inputName<< "\e[37m" << std::endl;
				exit(0);
			}

		}

		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreePLA","Convert Raw Cal Sync");

			plaRead = new PLARead();
			plaConvert = new PLAConvert();

			setOutputBranch();

		}
		void analysis(){
			preSetting();
			analysisLoop();
		}
		void saveOutputFile(){
                        tree->Write();
                        outputFile->Close();
		}
};

int main(int argc, char *argv[]){
	int runNumber=-1;
	Long64_t maxEventNumber = 10000000;
	//Long64_t maxEventNumber = 30;
	//cout<<maxEventNumber<<endl;
	if(argc==2) runNumber=atoi(argv[1]);
	else if(argc==3) { runNumber=atoi(argv[1]); maxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./ConvertPLA  runNumberber"<<endl;
		cout<<" USAGE: ./ConvertPLA  runnumber maxevtnumber"<<endl;
	}

	ConvertPLA *convertPLA =new ConvertPLA(runNumber, maxEventNumber);

	convertPLA->load();
	convertPLA->openRawData();
	convertPLA->createOutput();
	convertPLA->analysis();
	convertPLA->saveOutputFile();

	return 0;
}
