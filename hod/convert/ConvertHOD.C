#include "header.h"
TEnv *env = new TEnv("configConvertHOD.prm");
const static int NUMBER_OF_HOD = 40;
class PlasticRaw{
	private:
	public:
		int ID;
		int timeUpRaw ;
		int timeDownRaw ;
		int energyUpRaw ;
		int energyDownRaw;

		PlasticRaw(){
		}
		void initialize(){
			ID            = -1;
			timeUpRaw     = -1;
			timeDownRaw   = -1;
			energyUpRaw   = -1;
			energyDownRaw = -1;
		}
		void print(){
			cout<<"\t ID ="<< ID<<"\t timeUpRaw ="<< timeUpRaw<<"\t timeDownRaw = "<<timeDownRaw<<" \t energyUpRaw = "<<energyUpRaw<<"\t energyDownRaw = "<<energyDownRaw<<endl;

		}
		void load(TArtHODPla *HODPla){
			if(HODPla->GetID()>=1 && HODPla->GetID()<=NUMBER_OF_HOD) { 
				ID = HODPla->GetID();
				//check which HOD fired: HODP:24~40, HODF:24~1
				//define the intraID as 1~40, 1 from the lower momentum side one by one (HODF No.24 as intraID 1)
				//
				if(ID<25){   //HODF
					ID=24-ID; //1~24 			 
				} else {
					ID=64-ID;
				}
				timeUpRaw = HODPla->GetTURaw();
				timeDownRaw = HODPla->GetTDRaw();
				energyUpRaw = HODPla->GetQURaw();
				energyDownRaw = HODPla->GetQDRaw();

			}
		}
		int getID(){
			return ID;

		}
		int getTimeUpRaw(){
			return timeUpRaw;
		}
		int getTimeDownRaw(){
			return timeDownRaw;
		}
		int getEnergyUpRaw(){
			return energyUpRaw;
		}
		int getEnergyDownRaw(){
			return energyDownRaw;
		}
};
class HODPlasticRaw{

	private:
	public:

		int timeUpRaw[40];
		int timeDownRaw[40];
		int energyUpRaw[40];
		int energyDownRaw[40];
		HODPlasticRaw(){
			initialize();
		}
		void setBranch(TTree *tree){
			tree->Branch("timeUpRaw",timeUpRaw,"timeUpRaw[40]/I");
			tree->Branch("timeDownRaw",timeDownRaw,"timeDownRaw[40]/I");
			tree->Branch("energyUpRaw",energyUpRaw,"energyUpRaw[40]/I");
			tree->Branch("energyDownRaw",energyDownRaw,"energyDownRaw[40]/I");
		}
		void initialize(){
			for(int i=0;i<NUMBER_OF_HOD;i++){
				timeUpRaw[i] = -1;
				timeDownRaw[i] = -1;
				energyUpRaw[i] = -1;
				energyDownRaw[i] = -1;
				//cout<<i<<" time"<<timeUpRaw[i]<<endl;
			}
		}
		void readRaw(TClonesArray *HODPlaHit){

			int nHits = HODPlaHit->GetEntriesFast();

			//cout<<"Event nHit = "<<HODPlaHit->GetEntriesFast()<<endl;
			if(nHits != 0)
			{
				PlasticRaw *plastic =new PlasticRaw();
				for(Int_t i=0; i<nHits; i++)
				{
					plastic->initialize();
					TArtHODPla *HODPla = (TArtHODPla*)HODPlaHit->At(i);
					plastic->load(HODPla);
					//plastic->print();
					readOneHit(plastic);
				}
				delete plastic;
			}

		}

		void readOneHit(PlasticRaw *plastic){
			int ID = plastic->getID();
			timeUpRaw[ID] = plastic->getTimeUpRaw();
			timeDownRaw[ID] = plastic->getTimeDownRaw();
			energyUpRaw[ID] = plastic->getEnergyUpRaw();
			energyDownRaw[ID] = plastic->getEnergyDownRaw();

		}

		int getEnergyUpRaw(int ID){
			return energyUpRaw[ID];
		}

		int getEnergyDownRaw(int ID){
			return energyDownRaw[ID];
		}

};
class PlasticEnergyCal{
	private:
	public:
		int ID;
		bool isUpBar;
		int rawADC;
};
class HODPlasticPedestal{
	private:
	public:

        ifstream in;
        TString inputName;
	double pedestal[NUMBER_OF_HOD];
	double sigmaPed[NUMBER_OF_HOD];
	double adcThreshold[NUMBER_OF_HOD];

	HODPlasticPedestal(TString input){
		inputName = input;
		loadPedestal();
	}

	void loadPedestal(){
		in.open(inputName);
		int id;
		double mean;
		double sigma;
		double threshold;
		while (1)
		{
			if (!in.good()) break;
			in >>id>>mean>>sigma>>threshold;
			pedestal[id] = mean;
			sigmaPed[id] = sigma;
			adcThreshold[id] = threshold;
		}
	}
	double getPedestal(int id){
		return pedestal[id];
	}
};

class HODPlasticCal{
	private:
	public:
		HODPlasticRaw *rawData;
		HODPlasticPedestal *pedestalUp;
		HODPlasticPedestal *pedestalDown;

		double timeUpCal[40];
		double timeDownCal[40];
		double energyUpCal[40];
		double energyDownCal[40];
		double energyUpLnCal[40];
		double energyDownLnCal[40];



		void setBranch(TTree *tree){
			tree->Branch("timeUpCal",timeUpCal,"timeUpCal[40]/D");
			tree->Branch("timeDownCal",timeDownCal,"timeDownCal[40]/D");
			tree->Branch("energyUpCal",energyUpCal,"energyUpCal[40]/D");
			tree->Branch("energyDownCal",energyDownCal,"energyDownCal[40]/D");

			tree->Branch("energyUpLnCal",energyUpLnCal,"energyUpLnCal[40]/D");
			tree->Branch("energyDownLnCal",energyDownLnCal,"energyDownLnCal[40]/D");
	
		}
		void loadPedestalParameters(){
			pedestalUp = new HODPlasticPedestal("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/hod/pedestal/HOD_UP_Pedestal.txt");
			pedestalDown = new HODPlasticPedestal("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/hod/pedestal/HOD_DOWN_Pedestal.txt");
		}
		void initialize(){
			for(int i=0;i<NUMBER_OF_HOD;i++){
				timeUpCal[i] = -9999;
				timeDownCal[i] = -9999;
				energyUpCal[i] = -9999;
				energyDownCal[i] = -9999;

				energyUpLnCal[i] = -9999;
				energyDownLnCal[i] = -9999;
				
				//cout<<i<<" time"<<timeUpCal[i]<<endl;
			}
		}

		HODPlasticCal(){
			initialize();
			loadPedestalParameters();
		}
		void loadRawData(HODPlasticRaw *inputData){
			rawData = inputData;
		}
		void substractPedestal(){
			for(int i=0;i<NUMBER_OF_HOD;i++){
				if(getEnergyUpRaw(i)!=-1) energyUpCal[i] = getEnergyUpRaw(i) - getPedestalUp(i);
				if(getEnergyDownRaw(i)!=-1) energyDownCal[i] = getEnergyDownRaw(i) - getPedestalDown(i);
			}
		}
		void transformLnEnergy(){
			for(int i=0;i<NUMBER_OF_HOD;i++){
				if(energyUpCal[i]>0) energyUpLnCal[i] = log(energyUpCal[i]);
				if(energyDownCal[i]>0) energyDownLnCal[i] = log(energyDownCal[i]);
			}
		}
		int getEnergyUpRaw(int ID){
			return rawData->getEnergyUpRaw(ID);
		}
		int getEnergyDownRaw(int ID){
			return rawData->getEnergyDownRaw(ID);
		}
		double getPedestalUp(int ID){
			return pedestalUp->getPedestal(ID);
		}
		double getPedestalDown(int ID){
			return pedestalDown->getPedestal(ID);
		}
};
//class HODF:public HOD{
//};
//class HODP:public HOD{
//};

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
			hodPlasticRaw->setBranch(tree);
			hodPlasticCal->setBranch(tree);
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
				hodPlasticCal->substractPedestal();
				hodPlasticCal->transformLnEnergy();
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
	//      Long64_t maxEventNumber = 30;
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
