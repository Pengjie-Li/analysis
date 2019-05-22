#include "header.h"
TEnv *env = new TEnv("configConvertESPRI.prm");
class ConvertESPRI{
	private:

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;

		int runNumber;
		Long64_t maxEventNumber;

		TArtStoreManager *sman;
		TArtEventStore *EventStore;

		TFile *outputFile;
		TTree *tree;
		int EventNumber;
		int RunNumber;


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
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			//teleReadRaw->setBranch(tree);
			//teleConvertCal->setBranch(tree);
		}

		void preSetting(){
			start = std::clock();
			clock0 = std::clock();

			EventNumber = 0;
			RunNumber = runNumber;
		}
		void analysisLoop(){
			while(EventStore->GetNextEvent()
					&& EventNumber < maxEventNumber
			     )
			{

				showAnalysisProgress();

				EventNumber++;
				if(maxEventNumber<100) cout<<EventNumber<<endl;

				//	initOutput();
				//	clearTELEObject();
				//	reconstructTELEObject();

				//	clearTELEDataContainer();
				//	getTELEDataContainer();

				//	if(CalibSILICONS){
				//		readTELERawData();
				//		convertTELECalData();
				//	}
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
