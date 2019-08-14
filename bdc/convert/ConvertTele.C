#include "header.h"
TEnv *env = new TEnv("configConvertDC.prm");
#include "DCReadRaw.h"
#include "DCConvertCal.h"

class ConvertDC{
	private:
		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;

		int runNumber;
		Long64_t maxEventNumber;	

		TArtStoreManager *sman;
		TArtEventStore *EventStore;

		// Load Drift Chambers
		TArtCalibDCHit   *CalibBDC1Hit   ; 
		TArtCalibDCTrack *CalibBDC1Track ; 
		TArtCalibDCHit   *CalibBDC2Hit   ; 
		TArtCalibDCTrack *CalibBDC2Track ; 
		TArtCalibDCHit   *CalibFDC0Hit   ; 
		TArtCalibDCTrack *CalibFDC0Track ; 

		// In each event
		TClonesArray *BDC1Hit   ;
		TClonesArray *BDC1Track ;
		TClonesArray *BDC2Hit   ;
		TClonesArray *BDC2Track ;
		TClonesArray *FDC0Hit   ;
		TClonesArray *FDC0Track ;

		DCReadRaw *dcReadRaw;
		DCConvertCal *dcConvertCal;

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
			TArtBigRIPSParameters *BigRIPSPara = TArtBigRIPSParameters::Instance();
			TArtSAMURAIParameters *SamuraiPara = new TArtSAMURAIParameters();

			BigRIPSPara->LoadParameter((char*)env->GetValue("plaDataBase","./db/SAMURAIPlastic.xml")); //F3 F7 and SBT plastic
			SamuraiPara->LoadParameter((char*)env->GetValue("bdc1DataBase","./db/SAMURAIBDC1.xml"));
			SamuraiPara->LoadParameter((char*)env->GetValue("bdc2DataBase","./db/SAMURAIBDC2.xml"));
			SamuraiPara->LoadParameter((char*)env->GetValue("fdc0DataBase","./db/SAMURAIFDC0.xml"));
			SamuraiPara->LoadParameter((char*)env->GetValue("fdc2DataBase","./db/SAMURAIFDC2.xml"));
		}
		void reconstructDataHolder(){
			////////////////////Create ANAROOT Reconstruction classes////////////////////   

			CalibBDC1Hit   = new TArtCalibBDC1Hit();
			CalibBDC1Track = new TArtCalibBDC1Track();
			CalibBDC2Hit   = new TArtCalibBDC2Hit();
			CalibBDC2Track = new TArtCalibBDC2Track();
			CalibFDC0Hit   = new TArtCalibFDC0Hit();
			CalibFDC0Track = new TArtCalibFDC0Track();

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
			TString outputSuffix = env->GetValue("outputSufffix","_DC.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}

		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreeDC","Convert Raw Cal Sync");

			dcReadRaw = new DCReadRaw();
			dcConvertCal = new DCConvertCal();
		}

		void setOutputBranch(){
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			dcReadRaw->setBranch(tree);
			dcConvertCal->setBranch(tree);
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
				readDCRawData();
				convertDCCalData();
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
			clearDCObject();
			reconstructDCObject();

			clearDCDataContainer();
			getDCDataContainer();
		}
		void clearDCDataContainer(){
			BDC1Hit   = NULL ; 
			BDC1Track = NULL ;

			BDC2Hit   = NULL ; 
			BDC2Track = NULL ;

			FDC0Hit   = NULL ; 
			FDC0Track = NULL ;


		}
		void getDCDataContainer(){
			// ======================= Obtain event =============================//
			BDC1Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");
			BDC1Track = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");

			BDC2Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");
			BDC2Track = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");

			FDC0Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Hit");
			FDC0Track = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Track");

		}

		void readDCRawData(){
			dcReadRaw->readRaw(DCDataContainer);
		}
		void convertDCCalData(){
			dcConvertCal->calibration(dcReadRaw);
		}
		void clearDCObject(){
			CalibBDC1Hit->ClearData();
			CalibBDC1Track->ClearData();

			CalibBDC2Hit->ClearData();
			CalibBDC2Track->ClearData();

			CalibFDC0Hit->ClearData();
			CalibFDC0Track->ClearData();


		}
		void reconstructDCObject(){
			CalibBDC1Hit->ReconstructData();
			CalibBDC1Track->ReconstructData();

			CalibBDC2Hit->ReconstructData();
			CalibBDC2Track->ReconstructData();

			CalibFDC0Hit->ReconstructData();
			CalibFDC0Track->ReconstructData();
		}




	public:


		ConvertDC(int rn, Long64_t men){
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
		cout<<" USAGE: ./ConvertDC  runNumberber"<<endl;
		cout<<" USAGE: ./ConvertDC  runnumber maxevtnumber"<<endl;
	}

	ConvertDC *convertDC =new ConvertDC(runNumber, maxEventNumber);

	convertDC->loadAnaroot();

	convertDC->openRawData();

	convertDC->setupOutput();

	convertDC->analysis();

	convertDC->saveOutputFile();

	return 0;
}
