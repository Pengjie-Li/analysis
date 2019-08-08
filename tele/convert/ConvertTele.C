#include "header.h"
#include "TELEReadRaw.h"
#include "TELEConvertCal.h"
TEnv *env = new TEnv("configConvertTELE.prm");

class ConvertTELE{
	private:
		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;

		int runNumber;
		Long64_t maxEventNumber;	

		TArtStoreManager *sman;
		TArtEventStore *EventStore;

		TArtCalibSILICONS *CalibSILICONS;
		TClonesArray *TELEDataContainer;
		TELEReadRaw *teleReadRaw;
		TELEConvertCal *teleConvertCal;

		TFile *outputFile;
		TTree *tree;
		int RunNumber;
		int EventNumber;

		void loadAnarootDecoder(){
			//////////////////// Load anaroot decode class ////////////////////
			gSystem->Load("libanacore.so");
			gSystem->Load("libanasamurai.so");
			gSystem->Load("libXMLParser.so");

		}
		void openAnarootStoreManager(){
			sman = TArtStoreManager::Instance();
		}
		void loadAnarootDatabase(){
			// ====================== ANAROOT Parameters =======================
			TArtSILICONSParameters *SILICONSPara = TArtSILICONSParameters::Instance();

			SILICONSPara->LoadParameter((char*)env->GetValue("dataBaseFile","./db/SILICONS.xml"));
		}
		void reconstructDataHolder(){
			// Load TELEscope Holder
			CalibSILICONS = new TArtCalibSILICONS();
		}


		TString getInputName(){
			TString inputPath=env->GetValue("inputPath","./rootfile/");
			TString inputPrefix = env->GetValue("inputPrefix","run0");
			TString inputSuffix = env->GetValue("inputSufffix",".ridf.gz");
			return inputPath+inputPrefix+Form("%d",runNumber)+inputSuffix;

		}
		TString getOutputName(){
			TString outputPath=env->GetValue("outputPath","./rootfile/");
			TString outputPrefix = env->GetValue("outputPrefix","run0");
			TString outputSuffix = env->GetValue("outputSufffix","_TELE.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}

		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreeTELE","Convert Raw Cal Sync");

			teleReadRaw = new TELEReadRaw();
			teleConvertCal = new TELEConvertCal();
		}

		void setOutputBranch(){
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			teleReadRaw->setBranch(tree);
			teleConvertCal->setBranch(tree);
		}


		void preSetting(){
                        start = std::clock();
                        clock0 = std::clock();

                        EventNumber = 0;
                        RunNumber = runNumber;
                        reconstructDataHolder();
                }
		void launchAnalysisLoop(){

			while(EventStore->GetNextEvent()
					&& EventNumber < maxEventNumber
			     )
			{

				showAnalysisProgress();

				EventNumber++;
				if(maxEventNumber<100) cout<<EventNumber<<endl;
				getRawData();
				readTELERawData();
				convertTELECalData();
				tree->Fill();

			}
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
			clearTELEObject();
			reconstructTELEObject();

			clearTELEDataContainer();
			getTELEDataContainer();
		}
		void clearTELEDataContainer(){
			TELEDataContainer = NULL;
		}
		void getTELEDataContainer(){
			TELEDataContainer = (TClonesArray *)sman->FindDataContainer("SILICONS");
		}

		void readTELERawData(){
			teleReadRaw->readRaw(TELEDataContainer);
		}
		void convertTELECalData(){
			teleConvertCal->calibration(teleReadRaw);
		}
		void clearTELEObject(){

			CalibSILICONS->ClearData();
		}
		void reconstructTELEObject(){

			CalibSILICONS->ReconstructData();
		}




	public:


		ConvertTELE(int rn, Long64_t men){
			runNumber = rn;
			maxEventNumber = men;
		}
		void loadAnaroot(){
			loadAnarootDecoder();
			openAnarootStoreManager();
			loadAnarootDatabase();
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
		void setupOutput(){
			createOutput();
			setOutputBranch();
		}

		void analysis(){
			preSetting();
			launchAnalysisLoop();
		}

		void saveOutputFile(){
			tree->Write();
			outputFile->Close();
		}	
};

int main(int argc, char *argv[]){
	int runNumber=-1;
	Long64_t maxEventNumber = 10000000;
	//      Long64_t maxEventNumber = 30;
	//cout<<maxEventNumber<<endl;
	if(argc==2) runNumber=atoi(argv[1]);
	else if(argc==3) { runNumber=atoi(argv[1]); maxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./ConvertTELE  runNumberber"<<endl;
		cout<<" USAGE: ./ConvertTELE  runnumber maxevtnumber"<<endl;
	}

	ConvertTELE *convertTELE =new ConvertTELE(runNumber, maxEventNumber);

	convertTELE->loadAnaroot();

	convertTELE->openRawData();

	convertTELE->setupOutput();

	convertTELE->analysis();

	convertTELE->saveOutputFile();

	return 0;
}
