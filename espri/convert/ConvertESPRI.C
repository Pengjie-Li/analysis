#include "header.h"

TEnv *env = new TEnv("configConvertESPRI.prm");
#include "ESPRIReadRaw.h"
#include "ESPRIConvertCal.h"
#include "ESPRIHit.h"

class ConvertESPRI{
	private:

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;

		int runNumber;
		Long64_t maxEventNumber;

		TArtStoreManager *sman;
		TArtEventStore *EventStore;

		TArtCalibCoin	 *calibCoin;
		TArtCalibRNaI	 *calibESPRINaI ;
		TArtCalibTDCHit	 *calibESPRITdc ;
		TArtCalibRDC	 *calibESPRIRdc ; 
		TArtCalibPlas	 *calibESPRIPlas;

		TClonesArray *rdcDataContainer ;
		TClonesArray *tdcDataContainer ;
		TClonesArray *naiDataContainer ;
		TClonesArray *plasDataContainer;

		TFile *outputFile;
		TTree *tree;
		int EventNumber;
		int RunNumber;
		ESPRIReadRaw *espriReadRaw;
		ESPRIConvertCal *espriConvertCal;
		ESPRIHit *espriHit;


		//////// Load anaroot decode class ////////
		void loadAnarootDecoder(){
			gSystem->Load("libanacore.so");
			gSystem->Load("libanasamurai.so");
			gSystem->Load("libXMLParser.so");

		}
		void openAnarootStoreManager(){
			sman = TArtStoreManager::Instance();
		}

		// ==== ANAROOT Parameters ====//
		void loadAnarootDatabase(){

			TArtESPRIParameters *ESPRIPara = new TArtESPRIParameters();
			TArtUserParameters *ESPRIUserPara = TArtUserParameters::Instance();

			TString dbFolder = env->GetValue("dbFolder",".");
			TString TDCXml = env->GetValue("dbESPRITDC","ESPRITDC.xml");
			TString NaIXml = env->GetValue("dbESPRINaI","ESPRINaI.xml");
			TString PlasXml = env->GetValue("dbESPRIPlas","ESPRIPlas.xml");
			TString UserXml = env->GetValue("dbESPRIUser","ESPRIUser.xml");
			TDCXml  = dbFolder + TDCXml  ;
			NaIXml  = dbFolder + NaIXml  ;
			PlasXml = dbFolder + PlasXml ;
			UserXml = dbFolder + UserXml ;

			ESPRIPara->LoadParameter(TDCXml.Data());
			ESPRIPara->LoadParameter(NaIXml.Data());
			ESPRIPara->LoadParameter(PlasXml.Data());
			ESPRIUserPara->LoadParameter(UserXml.Data());
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
			TString outputSuffix = env->GetValue("outputSuffix","_ESPRI1.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}
		void setOutputBranch(){
			tree->AutoSave("SaveSelf");
			tree->SetAutoSave(1e5);

			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			espriReadRaw->setBranch(tree);
			espriConvertCal->setBranch(tree);
			espriHit->setBranch(tree);
		}

		void preSetting(){
			start = std::clock();
			clock0 = std::clock();

			EventNumber = 0;
			RunNumber = runNumber;
			reconstructDataHolder();
		}
		void reconstructDataHolder(){

			calibCoin	 = new TArtCalibCoin;
			calibCoin->SetAddress(85);
			calibESPRINaI  = new TArtCalibRNaI();
			calibESPRITdc  = new TArtCalibTDCHit;
			calibESPRIRdc  = new TArtCalibRDC();
			calibESPRIPlas = new TArtCalibPlas();

		}
		void analysisLoop(){
			while(EventStore->GetNextEvent()
					&& EventNumber < maxEventNumber
			     )
			{

				showAnalysisProgress();

				EventNumber++;
				getRawData();
				readRawData();
				convertRawData();
				extractHit();
				tree->Fill();

				if(maxEventNumber<100) print();
				//print();
			}
		}
		void print(){
			cout<<"EventNumber = "<<EventNumber<<endl;
			//espriReadRaw->printTDC();
			//espriReadRaw->printPlas();
			espriConvertCal->printRdc();
			espriConvertCal->printPlas();
			espriConvertCal->printNai();
			espriHit->print();

		}
		void getRawData(){
			clearReconstructedData();
			reconstructData();
			getDataContainer();

		}
		void clearReconstructedData(){

			calibESPRINaI->ClearData();
			calibESPRITdc->ClearData();
			calibESPRIRdc->ClearData();
			calibESPRIPlas->ClearData();

		}
		void reconstructData(){
			calibESPRINaI->ReconstructData();
			calibESPRITdc->ReconstructData();
			calibESPRIRdc->ReconstructData();
			calibESPRIPlas->ReconstructData();

		}
		void getDataContainer(){
			tdcDataContainer = NULL;
			rdcDataContainer = NULL;
			naiDataContainer = NULL;
			plasDataContainer = NULL;

			tdcDataContainer = (TClonesArray *)sman->FindDataContainer("ESPRITDC");
			rdcDataContainer = (TClonesArray *)sman->FindDataContainer("ESPRIRDC");
			naiDataContainer = (TClonesArray *)sman->FindDataContainer("ESPRINaI");
			plasDataContainer = (TClonesArray *)sman->FindDataContainer("ESPRIPLAS");
		}
		void readRawData(){
			espriReadRaw->readRaw(tdcDataContainer,naiDataContainer,plasDataContainer);
		}
		void convertRawData(){
			espriConvertCal->updateRunNumber(runNumber);
			espriConvertCal->convertCal(espriReadRaw);
			espriConvertCal->readReconstructedData(rdcDataContainer);
		}
		void extractHit(){
			espriHit->hitEvent(espriConvertCal);
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




	public:
		ConvertESPRI(int rn,Long64_t men){
			runNumber = rn;
			maxEventNumber = men;
		}
		void load(){
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

		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreeESPRI","Convert Raw Cal Sync");

			espriReadRaw = new ESPRIReadRaw();
			espriConvertCal = new ESPRIConvertCal();
			espriHit = new ESPRIHit();

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
	//      Long64_t maxEventNumber = 30;
	//cout<<maxEventNumber<<endl;
	if(argc==2) runNumber=atoi(argv[1]);
	else if(argc==3) { runNumber=atoi(argv[1]); maxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./ConvertESPRI  runNumberber"<<endl;
		cout<<" USAGE: ./ConvertESPRI  runnumber maxevtnumber"<<endl;
	}


	ConvertESPRI *convertESPRI =new ConvertESPRI(runNumber, maxEventNumber);

	convertESPRI->load();
	convertESPRI->openRawData();
	convertESPRI->createOutput();
	convertESPRI->analysis();
	convertESPRI->saveOutputFile();

	return 0;
}
