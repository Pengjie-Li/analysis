#include "header.h"
TEnv *env = new TEnv("configConvertHOD.prm");
const static int NUMBER_OF_HOD = 40;
#include "HODReadRaw.h"
#include "HODConvertCal.h"

class ConvertHOD{
	private :
	public : 

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;

		int runNumber;
		int maxEventNumber;
		TArtStoreManager *sman;
		TArtEventStore *EventStore;
		TArtCalibHODPla *CalibHODPla;
		TClonesArray *HODPlaHit;

		// Load Pedestal Parameters
		HODPlasticPedestal *pedestalUp;
		HODPlasticPedestal *pedestalDown;


		TFile *outputFile;
		TTree *tree;
		HODPlasticRaw *hodPlasticRaw;
		HODPlasticCal *hodPlasticCal;



		int EventNumber;
		int RunNumber;
		int hodID[40];
		ConvertHOD(int rn,int men){
			runNumber=rn;
			maxEventNumber=men;
		}
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
			TArtSAMURAIParameters *SamuraiPara = new TArtSAMURAIParameters();

			SamuraiPara->LoadParameter((char*)env->GetValue("dataBaseFile","./db/SAMURAIHOD.xml"));
		}
		void createAnarootReconstructionClass(){
			// Load Hodoscope
			CalibHODPla = new TArtCalibHODPla();

		}
		void openRawData(){
			///////////////////////////////////////////////////////////////////
			///////////////////// Open Raw Data ///////////////////////////////
			///////////////////////////////////////////////////////////////////

			EventStore = new TArtEventStore;

			TString inputName=getInputName();
			cout<<inputName<<endl;

			if(!EventStore->Open(inputName))
			{
				std::cout << "\e[34m " << "cannot open " <<inputName<< "\e[37m" << std::endl;
				exit(0);
			}
		}
		TString getInputName(){
			TString inputPath=env->GetValue("inputPath","./rootfile/");
			TString inputPrefix = env->GetValue("inputPrefix","run0");
			TString inputSuffix = env->GetValue("inputSufffix",".ridf.gz");
			return inputPath+inputPrefix+Form("%d",runNumber)+inputSuffix;

		}
		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreeHOD","Convert Raw Cal Sync");
			hodPlasticRaw = new HODPlasticRaw();
			hodPlasticCal = new HODPlasticCal();
		}
		TString getOutputName(){
			TString outputPath=env->GetValue("outputPath","./rootfile/");
			TString outputPrefix = env->GetValue("outputPrefix","run0");
			TString outputSuffix = env->GetValue("outputSufffix","_HOD.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}

		void setOutputBranch(){
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			setHodIDBranch();
			hodPlasticRaw->setBranch(tree);
			hodPlasticCal->setBranch(tree);
		}
		void setHodIDBranch(){
			for (int i = 0; i < NUMBER_OF_HOD; ++i) {
				hodID[i] = i ;
			}
			tree->Branch("hodID",hodID,"hodID[40]/I");
		}

		void launchAnalysisLoop(){
			start = std::clock();
			clock0 = std::clock();

			EventNumber = 0;
			RunNumber = runNumber;

			////////////////////////// Analysis  loop  /////////////

			while(EventStore->GetNextEvent()
					&& EventNumber < maxEventNumber
			     )
			{

				showAnalysisProgress();

				EventNumber++;
				if(maxEventNumber<100) cout<<EventNumber<<endl;

				initOutput();
				clearHODObject();
				reconstructHODObject();

				clearHODContainer();
				getHODContainer();

				if(CalibHODPla){
					readHODRawData();
					calibrateHODRaw();
				}
				tree->Fill();

			}
		}
		void initOutput(){
			// One Object alway keep using
			hodPlasticRaw->initialize(); 
			hodPlasticCal->initialize();
		}
		void clearHODContainer(){
			HODPlaHit = NULL; // In loop, get Pointer from Raw Data 
		}
		void getHODContainer(){
			HODPlaHit = (TClonesArray *)sman -> FindDataContainer("SAMURAIHODPla");
		}
		void readHODRawData(){
				hodPlasticRaw->readRaw(HODPlaHit);
		}
		void calibrateHODRaw(){
				hodPlasticCal->loadRawData(hodPlasticRaw);
				hodPlasticCal->calibQ();
				hodPlasticCal->calibT();
				hodPlasticCal->calculateBar();
		}

		void saveOutputFile(){
			tree->Write();
			outputFile->Close();
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
		void clearHODObject(){

			CalibHODPla->ClearData();
		}
		void reconstructHODObject(){

			CalibHODPla->ReconstructData();
		}
};
int main(int argc, char *argv[]){
	int runNumber=-1;
	Long64_t maxEventNumber = 10000000;
	//      maxEventNumber = 3000;
	//cout<<maxEventNumber<<endl;
	if(argc==2) runNumber=atoi(argv[1]);
	else if(argc==3) { runNumber=atoi(argv[1]); maxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./ConvertHOD  runNumberber"<<endl;
		cout<<" USAGE: ./ConvertHOD  runnumber maxevtnumber"<<endl;
	}

	ConvertHOD *convertHOD =new ConvertHOD(runNumber, maxEventNumber);

	convertHOD->loadAnarootDecoder();
	convertHOD->openAnarootStoreManager();
	convertHOD->loadAnarootDatabase();

	convertHOD->createAnarootReconstructionClass();
	//
	convertHOD->openRawData();
	//
	convertHOD->createOutput();
	convertHOD->setOutputBranch();
	//
	
	//convertHOD->loadPedestalParameters();
	convertHOD->launchAnalysisLoop();
	//
	convertHOD->saveOutputFile();

	return 0;
}
