#include "header.h"
TEnv *env = new TEnv("configConvertDC.prm");
#include "DCReadRaw.h"
#include "DCTracking.h"

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
		TArtCalibDCHit   *CalibBDC2Hit   ; 
		TArtCalibDCHit   *CalibFDC0Hit   ; 

		// In each event
		TClonesArray *BDC1Hit   ;
		TClonesArray *BDC2Hit   ;
		TClonesArray *FDC0Hit   ;

		DCReadRaw *bdc1ReadRaw    ;
		DCReadRaw *bdc2ReadRaw    ;
		DCReadRaw *fdc0ReadRaw    ;

		DCTracking *bdc1Track;
		DCTracking *bdc2Track;
		DCTracking *fdc0Track;

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
			CalibBDC2Hit   = new TArtCalibBDC2Hit();
			CalibFDC0Hit   = new TArtCalibFDC0Hit();

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
			TString outputSuffix = env->GetValue("outputSuffix","_DC.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}

		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreeDC","Convert Raw Cal Sync");

			bdc1ReadRaw    = new BDC1ReadRaw();
			bdc2ReadRaw    = new BDC2ReadRaw();
			fdc0ReadRaw    = new FDC0ReadRaw();

			bdc1Track	= new BDC1Tracking();
			bdc2Track	= new BDC2Tracking();
			fdc0Track	= new FDC0Tracking();
		}

		void setOutputBranch(){
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);

			bdc1ReadRaw->setBranch(tree);
			bdc2ReadRaw->setBranch(tree);
			fdc0ReadRaw->setBranch(tree);

			bdc1Track->setBranch(tree);
			bdc2Track->setBranch(tree);
			fdc0Track->setBranch(tree);

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

				//cout<<"EventNumber = "<<EventNumber<<endl;
				EventNumber++;
				getRawData();
				readDCRawData();
				trackingDCData();

				if(maxEventNumber<100) print();
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
		void print(){
			cout<<"EventNumber = "<<EventNumber<<endl;
			//bdc1ReadRaw->print();
			//bdc1Track->print();

		//	bdc2ReadRaw->print();
		//	bdc2Track->print();

			fdc0ReadRaw->print();
			fdc0Track->print();

		}

		void getRawData(){
			clearDCObject();
			reconstructDCObject();

			clearDCDataContainer();
			getDCDataContainer();
		}
		void clearDCDataContainer(){
			BDC1Hit   = NULL ; 

			BDC2Hit   = NULL ; 

			FDC0Hit   = NULL ; 

		}
		void getDCDataContainer(){
			// ======================= Obtain event =============================//
			BDC1Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");

			BDC2Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");

			FDC0Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Hit");

		}

		void readDCRawData(){
			bdc1ReadRaw->readRaw(BDC1Hit);
			bdc2ReadRaw->readRaw(BDC2Hit);
			fdc0ReadRaw->readRaw(FDC0Hit);
		}
		void trackingDCData(){
				bdc1Track->calibrate(bdc1ReadRaw);
				bdc2Track->calibrate(bdc2ReadRaw);
				fdc0Track->calibrate(fdc0ReadRaw);
		}
		void clearDCObject(){
			CalibBDC1Hit->ClearData();

			CalibBDC2Hit->ClearData();

			CalibFDC0Hit->ClearData();

		}
		void reconstructDCObject(){
			CalibBDC1Hit->ReconstructData();

			CalibBDC2Hit->ReconstructData();

			CalibFDC0Hit->ReconstructData();
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
			outputFile->cd();
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
