#include"header.h"
#include"DSSDEnergy.h"

TEnv *env = new TEnv("configConvertTELE.prm");


class TELEReadRaw{
	private:
	public:
		/********************************
		 * Silicon: 0 = LF; 1 = LB; 2 = RF; 3 = RB; 
		 * CsI: 0 = LL; 1 = LRT; 2 = LRB; 3 = RLT; 4 = RLB; 5 =RRT; 6 = RRB;
		 ********************************/

		int dssdEnergyRaw[4][32];	
		int dssdTimeRaw[4][32];	
		int csiEnergyRaw[7];
		int csiTimeRaw[7];
		int RefTime1;// TDC 1
		int RefTime2;// TDC 2 corresponding to 2 moudle

		TELEReadRaw(){
			initialize();	
		}
		void initialize(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdEnergyRaw[i][j] = -1;
					dssdTimeRaw[i][j] = -1;
				}
			}
			for(int k = 0;k<7;k++){
				csiEnergyRaw[k] = -1;
				csiTimeRaw[k] = -1;
			}
			RefTime1 = -1;
			RefTime2 = -1;
		}
		void readRaw(TClonesArray *rawDataArray){
			for(int i=0;i<rawDataArray->GetEntries();i++){
				TArtSILICONS *rawDataHit = (TArtSILICONS *)rawDataArray->At(i);
				int teleId=rawDataHit->GetID();
				int adc=rawDataHit->GetRawADC();
				int tdc=rawDataHit->GetRawTDC();
				setRawDataHit(teleId,adc,tdc);
			}
		}
		void setRawDataHit(int teleId,int adc,int tdc){
			if(teleId>0&&teleId<33)   { dssdEnergyRaw[0][teleId-1 ]= adc;dssdTimeRaw[0][teleId-1 ]= tdc;}
			if(teleId>32&&teleId<65)  { dssdEnergyRaw[1][teleId-33]= adc;dssdTimeRaw[1][teleId-33]= tdc;}
			if(teleId>64&&teleId<97)  { dssdEnergyRaw[2][teleId-65]= adc;dssdTimeRaw[2][teleId-65]= tdc;}
			if(teleId>96&&teleId<129) { dssdEnergyRaw[3][teleId-97]= adc;dssdTimeRaw[3][teleId-97]= tdc;}
			if(teleId>=129&&teleId<=135) { csiEnergyRaw[teleId-129]=adc; csiTimeRaw[teleId-129]=tdc;}
			if(teleId==136) { RefTime1 = tdc;}
			if(teleId==137) { RefTime2 = tdc;}
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdEnergyRaw",dssdEnergyRaw,"dssdEnergyRaw[4][32]/I");
			tree->Branch("dssdTimeRaw",dssdTimeRaw,"dssdTimeRaw[4][32]/I");
			tree->Branch("csiEnergyRaw",csiEnergyRaw,"csiEnergyRaw[7]/I");
			tree->Branch("csiTimeRaw",csiTimeRaw,"csiTimeRaw[7]/I");
			tree->Branch("RefTime1",&RefTime1,"RefTime1/I");
			tree->Branch("RefTime2",&RefTime2,"RefTime2/I");

		}
		double getSiliconRawADC(int side,int id){
			return dssdEnergyRaw[side][id];
		}
		double getCsIRawADC(int id){
			return csiEnergyRaw[id];
		}

};
class DSSDTimeCal{

	public:
		void calibrate(TELEReadRaw *rawData){
		}
};

class CsIEnergyCalParameter{
	private:
	public:
		double kCsISlope[7];
		double kCsIOffset[7];

		CsIEnergyCalParameter(){
			double CsISlope[7] = {0.357925,0.40584 ,0.350254,0.350748,0.464291,0.306815,0.353228};
			double CsIOffset[7]= {-139.651,-137.378,-105.061,-108.566,-150.243,-101.453,-117.866};
			for(int i = 0;i<7;i++){
				kCsISlope[i] = CsISlope[i];
				kCsIOffset[i] = CsIOffset[i];
			}
		}
		double getCsISlope(int id){
			return kCsISlope[id];
		}
		double getCsIOffset(int id){
			return kCsIOffset[id];
		}
		
};
CsIEnergyCalParameter *csiEnergyCalParameter = new CsIEnergyCalParameter();
class CsIEnergyCal{
	private:
	public:
		double calibrate(int id,double raw){
				return getCsISlope(id)*raw+getCsIOffset(id);
		}
		double getCsISlope(int id){
			return csiEnergyCalParameter->getCsISlope(id);
		}
		double getCsIOffset(int id){
			return csiEnergyCalParameter->getCsIOffset(id);
		}
};
class CsITimeCal{

	public:
		void calibrate(TELEReadRaw *rawData){
		}
};
class TELEConvertCal{
	private:
	public:
		TELEReadRaw *teleReadRaw;	

		DSSDEnergyCal	*dssdEnergy;
		DSSDTimeCal	*dssdTime;
		CsIEnergyCal	*csiEnergy;
		CsITimeCal 	*csiTime;

		double dssdEnergyCal[4][32];	
		double dssdTimeCal[4][32];	
		double csiEnergyCal[7];
		double csiTimeCal[7];

		TELEConvertCal(){
			initialize();

			dssdEnergy = new DSSDEnergyCal();
			dssdTime   = new DSSDTimeCal();
			csiEnergy  = new CsIEnergyCal();
			csiTime    = new CsITimeCal();
		}

		void initialize(){
			teleReadRaw = NULL;
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdEnergyCal[i][j] = -9999;
					dssdTimeCal[i][j] = -9999;
				}
			}
			for(int k = 0;k<7;k++){
				csiEnergyCal[k] = -9999;
				csiTimeCal[k] = -9999;
			}

		}

		void setBranch(TTree *tree){
			tree->Branch("dssdEnergyCal",dssdEnergyCal,"dssdEnergyCal[4][32]/D");
			tree->Branch("dssdTimeCal",dssdTimeCal,"dssdTimeCal[4][32]/D");
			tree->Branch("csiEnergyCal",csiEnergyCal,"csiEnergyCal[7]/D");
			tree->Branch("csiTimeCal",csiTimeCal,"csiTimeCal[7]/D");
		}

		void calibration(TELEReadRaw *rawData){
			loadRawData(rawData);
			calibration();
		}
		void loadRawData(TELEReadRaw *rawData){
			teleReadRaw = rawData;
		}
		void calibration(){
			for(int side = 0;side<4;side++)
				for(int id=0;id<32;id++){

					dssdEnergyCal[side][id] = dssdEnergy->calibrate(side,id,getSiliconRawADC(side,id));
					//					dssdTime->calibrate(teleReadRaw);
				}

			for(int k = 0;k<7;k++){
				csiEnergyCal[k] = csiEnergy->calibrate(k,getCsIRawADC(k));
			}
			//csiTime->calibrate(teleReadRaw);
		}
		double getSiliconRawADC(int side, int id){
			return teleReadRaw->getSiliconRawADC(side,id);
		}
		double getCsIRawADC(int id){
			return teleReadRaw->getCsIRawADC(id);
		}

		~TELEConvertCal(){
			delete dssdEnergy;
			delete dssdTime;
			delete csiEnergy;
			delete csiTime;
		}



};
class ConvertTELE{
	private:
	public:
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


		ConvertTELE(int rn, Long64_t men){
			runNumber = rn;
			maxEventNumber = men;
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
			TArtSILICONSParameters *SILICONSPara = TArtSILICONSParameters::Instance();

			SILICONSPara->LoadParameter((char*)env->GetValue("dataBaseFile","./db/SILICONS.xml"));
		}
		void createAnarootReconstructionClass(){
			// Load TELEscope Holder
			CalibSILICONS = new TArtCalibSILICONS();

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
		TString getInputName(){
			TString inputPath=env->GetValue("inputPath","./rootfile/");
			TString inputPrefix = env->GetValue("inputPrefix","run0");
			TString inputSuffix = env->GetValue("inputSufffix",".ridf.gz");
			return inputPath+inputPrefix+Form("%d",runNumber)+inputSuffix;

		}
		void createOutput(){
			outputFile = new TFile(getOutputName(),"recreate");
			tree = new TTree("CalTreeTELE","Convert Raw Cal Sync");

			teleReadRaw = new TELEReadRaw();
			teleConvertCal = new TELEConvertCal();
		}
		TString getOutputName(){
			TString outputPath=env->GetValue("outputPath","./rootfile/");
			TString outputPrefix = env->GetValue("outputPrefix","run0");
			TString outputSuffix = env->GetValue("outputSufffix","_TELE.root");
			return outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
		}

		void setOutputBranch(){
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			teleReadRaw->setBranch(tree);
			teleConvertCal->setBranch(tree);
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
				clearTELEObject();
				reconstructTELEObject();

				clearTELEDataContainer();
				getTELEDataContainer();

				if(CalibSILICONS){
					readTELERawData();
					convertTELECalData();
				}
				tree->Fill();

			}
		}
		void readTELERawData(){
			teleReadRaw->readRaw(TELEDataContainer);
		}
		void convertTELECalData(){
			teleConvertCal->calibration(teleReadRaw);
		}

		void clearTELEDataContainer(){
			TELEDataContainer = NULL;
		}
		void getTELEDataContainer(){
			TELEDataContainer = (TClonesArray *)sman->FindDataContainer("SILICONS");
		}

		void initOutput(){
			teleReadRaw->initialize();
			teleConvertCal->initialize();
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
		void clearTELEObject(){

			CalibSILICONS->ClearData();
		}
		void reconstructTELEObject(){

			CalibSILICONS->ReconstructData();
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

	convertTELE->loadAnarootDecoder();
	convertTELE->openAnarootStoreManager();
	convertTELE->loadAnarootDatabase();

	convertTELE->createAnarootReconstructionClass();
	convertTELE->openRawData();
	//	//
	convertTELE->createOutput();
	convertTELE->setOutputBranch();
	//	//
	//	
	//	//convertTELE->loadPedestalParameters();
	convertTELE->launchAnalysisLoop();
	//	//
	convertTELE->saveOutputFile();

	return 0;
}
