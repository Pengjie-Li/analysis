#include "header.h"
#include "distance.h"
#include "DCRaw.h"
#ifdef __MAKECINT__ 
#pragma link C++ class 
std::vector < std::vector<int> >+;
std::vector < std::vector<std::vector<int>> >+;
#endif


TEnv *env = new TEnv("configTDCSpectrum.prm");
class TDCSpectrum{

	private:
		static const bool isEventByEvent=false;
		static const bool kBDC=true;
		static const bool kFDC=true;
		static const bool kSaveTree = false;

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;


	public :

		int runNumber;
		int eventNumber;
		Long64_t maxEventNumber;

		TArtEventStore *EventStore;
		TArtStoreManager *sman;

		// Output
		TFile *fout;
		TTree *tree;

		TH1* hbdc1tdc[8];
		TH1* hbdc2tdc[8];
		TH1* hfdc0tdc[8];
		TH1* hfdc2tdc[14];

		TH2* hBDC1TDC[8];
		TH2* hBDC2TDC[8];
		TH2* hFDC0TDC[8];
		TH2* hFDC2TDC[14];

		TH2* hBDC1Layer[4];
                TH2* hBDC2Layer[4];
		TH2* hFDC0Layer[4];
                TH2* hFDC2Layer[7];

		// Head Variables

		DCRaw *BDC1RawData;
		DCRaw *BDC2RawData;
		DCRaw *FDC0RawData;
		DCRaw *FDC2RawData;


//		BDC1Raw *BDC1RawData;
//		BDC2Raw *BDC2RawData;
//		FDC0Raw *FDC0RawData;
//		FDC2Raw *FDC2RawData;

		// DC Raw Data
		// Each Drift Chamber raw Data 
		// * hit1 (layerid,wireid,TDC)
		// * hit2
		// * hit3
		// * ...
		Int_t BDC1_nhits;
		vector<int> BDC1_TDC;// for each hits, no matter layer, wireid
		vector<double> BDC1_layerid;// for each hits, no matter layer, wireid
		vector<double> BDC1_wireid;// for each hits, no matter layer, wireid


		Int_t BDC2_nhits;
		vector<int> BDC2_TDC;// for each hits, no matter layer, wireid
		vector<double> BDC2_layerid;// for each hits, no matter layer, wireid
		vector<double> BDC2_wireid;// for each hits, no matter layer, wireid

		Int_t FDC0_nhits;
		vector<int> FDC0_TDC;// for each hits, no matter layer, wireid
		vector<double> FDC0_layerid;// for each hits, no matter layer, wireid
		vector<double> FDC0_wireid;// for each hits, no matter layer, wireid

		Int_t FDC2_nhits;
		vector<int> FDC2_TDC;// for each hits, no matter layer, wireid
		vector<double> FDC2_layerid;// for each hits, no matter layer, wireid
		vector<double> FDC2_wireid;// for each hits, no matter layer, wireid


		// how many hits in each layer(layer: 16 wire)
		vector<int> BDC1_layer_hits;
		vector<int> BDC2_layer_hits;
		vector<int> FDC0_layer_hits;
		vector<int> FDC2_layer_hits;


		// Hits in each layer
		vector<vector<int> > BDC1_layer_TDC;
		vector<vector<int> > BDC2_layer_TDC;
		vector<vector<int> > FDC0_layer_TDC;
		vector<vector<int> > FDC2_layer_TDC;



		// Load Drift Chambers
		TArtCalibDCHit   *CalibBDC1Hit   ; 
		TArtCalibDCHit   *CalibBDC2Hit   ; 
		TArtCalibDCHit   *CalibFDC0Hit   ; 
		TArtCalibDCHit   *CalibFDC2Hit   ; 

		// In each event
		TClonesArray *BDC1Hit   ;

		TClonesArray *BDC2Hit   ;

		TClonesArray *FDC0Hit   ;

		TClonesArray *FDC2Hit   ;


		void loadAnarootDecoder(){
			//////////////////// Load anaroot decode class ////////////////////      
			gSystem->Load("libanacore.so");
			gSystem->Load("libanasamurai.so");
			gSystem->Load("libXMLParser.so");


		}
		void loadAnarootDatabase(){
			// ====================== ANAROOT Parameters =======================
			TArtBigRIPSParameters *BigRIPSPara = TArtBigRIPSParameters::Instance();
			TArtSAMURAIParameters *SamuraiPara = new TArtSAMURAIParameters();

			BigRIPSPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIPlastic.xml"); //F3 F7 and SBT plastic
			SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIBDC1.xml");
			SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIBDC2.xml");
			SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIFDC0.xml");
			SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIFDC2.xml");
		}

		void createDCObject(){
			////////////////////Create ANAROOT Reconstruction classes////////////////////   

			CalibBDC1Hit   = new TArtCalibBDC1Hit();
			CalibBDC2Hit   = new TArtCalibBDC2Hit();
			CalibFDC0Hit   = new TArtCalibFDC0Hit();
			CalibFDC2Hit   = new TArtCalibFDC2Hit();
		}
		void clearDCObject(){

			CalibBDC1Hit->ClearData();

			CalibBDC2Hit->ClearData();

			CalibFDC0Hit->ClearData();

			CalibFDC2Hit->ClearData();
	
		}


		void reconstructDCObject(){
			CalibBDC1Hit->ReconstructData();

			CalibBDC2Hit->ReconstructData();

			CalibFDC0Hit->ReconstructData();

			CalibFDC2Hit->ReconstructData();

		}


		void openRawData(){
			///////////////////////////////////////////////////////////////////
			///////////////////// Open Raw Data ///////////////////////////////
			///////////////////////////////////////////////////////////////////

			EventStore = new TArtEventStore;

			TString inputpath="/media/Rawdata/RIKEN_Cluster_2018/";
			TString inputfilename=Form("run0%d.ridf.gz",runNumber);
			TString inputname=inputpath+inputfilename;

			//EventStore->Open(inputname);
			if(!EventStore->Open(inputname)) 
			{
				std::cout << "\e[34m " << "cannot open " <<inputname<< "\e[37m" << std::endl;
				exit(0);
			}
		}

		void createOutput(){
			///////////////////////////////////////////////////////////////////
			///////////////////// Create TFile and TTree  /////////////////////
			///////////////////////////////////////////////////////////////////


			TString treeName="tree";
			fout = NULL;
			tree = NULL;

			fout = new TFile(Form("./rootfiles/run0%d_tdcSpectrum.root",runNumber),"recreate");
			tree = new TTree(treeName,"TDC Spectrum");
			tree->AutoSave("SaveSelf");
			tree->SetAutoSave(1e5);

			///////////////////////////////////////////////////////////////////
			///////////////////// Create Histograms  /////////////////////
			///////////////////////////////////////////////////////////////////

			for (int ilayer=0;ilayer<8;++ilayer){
				hbdc1tdc[ilayer] = new TH1I(Form("hbdc1tdc%d",ilayer),
						Form("BDC1 TDC layer=%d",ilayer),200,1700,1900);
				hBDC1TDC[ilayer] = new TH2I(Form("hBDC1TDC%d",ilayer),
						Form("BDC1 TDC layer=%d",ilayer),200,1700,1900,16,-0.5,15.5);
	
			}


			for (int ilayer=0;ilayer<8;++ilayer){                   
				hbdc2tdc[ilayer] = new TH1I(Form("hbdc2tdc%d",ilayer),
						Form("BDC2 TDC layer=%d",ilayer),200,1700,1900);
				hBDC2TDC[ilayer] = new TH2I(Form("hBDC2TDC%d",ilayer),
						Form("BDC2 TDC layer=%d",ilayer),200,1700,1900,16,-0.5,15.5);
			}
			for (int ilayer=0;ilayer<8;++ilayer){
				hfdc0tdc[ilayer] = new TH1I(Form("hfdc0tdc%d",ilayer),
						Form("FDC0 TDC layer=%d",ilayer),300,1600,1900);
				hFDC0TDC[ilayer] = new TH2I(Form("hFDC0TDC%d",ilayer),
						Form("FDC0 TDC layer=%d",ilayer),300,1600,1900,32,-0.5,31.5);
			}
			for (int ilayer=0;ilayer<14;++ilayer){
				hfdc2tdc[ilayer] = new TH1I(Form("hfdc2tdc%d",ilayer),
						Form("FDC2 TDC layer=%d",ilayer),900,1000,1900);
				hFDC2TDC[ilayer] = new TH2I(Form("hFDC2TDC%d",ilayer),
						Form("FDC2 TDC layer=%d",ilayer),900,1000,1900,112,-0.5,111.5);
			}

			for(int i=0; i<4;i++){
				hBDC1Layer[i] = new TH2I(Form("hBDC1Layer%d%d",2*i,2*i+1),Form("BDC1 TDC Layer %d vs %d",2*i,2*i+1),200,1700,1900,200,1700,1900);
			}
	
			for(int i=0; i<4;i++){
				hBDC2Layer[i] = new TH2I(Form("hBDC2Layer%d%d",2*i,2*i+1),Form("BDC2 TDC Layer %d vs %d",2*i,2*i+1),200,1700,1900,200,1700,1900);
			}
	
			for(int i=0; i<4;i++){
				hFDC0Layer[i] = new TH2I(Form("hFDC0Layer%d%d",2*i,2*i+1),Form("FDC0 TDC Layer %d vs %d",2*i,2*i+1),300,1600,1900,300,1600,1900);
			}
	
			for(int i=0; i<7;i++){
				hFDC2Layer[i] = new TH2I(Form("hFDC2Layer%d%d",2*i,2*i+1),Form("FDC2 TDC Layer %d vs %d",2*i,2*i+1),900,1000,1900,900,1000,1900);
			}

		}

		void setOutputBranch(){
			//Beam
			tree->Branch("runNumber",&runNumber);
			tree->Branch("eventNumber",&eventNumber);

			///////////////////////////////////////////////////////////////
			//
		
			BDC1RawData->setRawDataBranch(tree);
			BDC2RawData->setRawDataBranch(tree);
			FDC0RawData->setRawDataBranch(tree);
			FDC2RawData->setRawDataBranch(tree);
		}

		void openAnarootStoreManager(){
			sman = TArtStoreManager::Instance();
		}

		TDCSpectrum(int mode,int runnum,int maxevt){
			runNumber = runnum;
			maxEventNumber = maxevt;

			BDC1RawData = new BDC1Raw();
			BDC2RawData = new BDC2Raw();
			FDC0RawData = new FDC0Raw();
			FDC2RawData = new FDC2Raw();


			/**
			 * 
			 * TDC Spectrum: Generate good Calibration Spectrum
			 * 3 Modes: 1File1TDCSpectrum, 1Beam1TDCSpectrum, 1TDCSpectrumforAll
			 * Output: TDC 1D, 2D with Wireid, Correlation between adjcent layer
			 */
			switch(mode){
				case 1: oneFileTDCSpectrum();break;
				case 2: TDCSpectrumFromOneFileAndOneHitInEachLayer();break;
				case 3: break;
			}

		}
		void TDCSpectrumFromOneFileAndOneHitInEachLayer(){
		}
		void oneFileTDCSpectrum(){
			analysis();
		}
		void analysis(){

			loadAnarootDecoder();
			openAnarootStoreManager();
			loadAnarootDatabase();

			openRawData();
			createDCObject();

			createOutput();
			setOutputBranch();

			launchAnalysisLoop();

			saveTreeAndCloseOutputFile();
			releaseMemory();


		}

		void showAnalysisProgress(){
			if (eventNumber%DISPLAY_EVERY_EVENT == 0)
			{
				double duration =  int(10*((std::clock()-start)/ (double) CLOCKS_PER_SEC))/10. ;
				Double_t rate = DISPLAY_EVERY_EVENT/((std::clock()-clock0)/ (double) CLOCKS_PER_SEC) ;
				Int_t color = rate<100?33:31 ;//int(TMath::Log(rate)/TMath::Ln10())+31;
				std::clog << "\e[1;" << color << "m  ANALYSIS-Info : " << eventNumber/1000 << "k events treated in " 
					<< duration << "s. Instantaneous rate = " 
					<< rate << "evt/s\e[0m             \r";
				clock0 = std::clock();
			}

		}

		void clearDataContainer(){
			BDC1Hit   = NULL ; 

			BDC2Hit   = NULL ; 

			FDC0Hit   = NULL ; 

			FDC2Hit   = NULL ; 

		}
		void getDataContainer(){

			// ======================= Obtain event =============================//
			BDC1Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");

			BDC2Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");

			FDC0Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Hit");

			FDC2Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC2Hit");

		}



		void launchAnalysisLoop(){

			start = std::clock();
			clock0 = std::clock();

			eventNumber = 0;

			////////////////////////////////Analysis  loop/////////////
			while(EventStore->GetNextEvent() 
					&& eventNumber < maxEventNumber
			     )
			{

				eventNumber++;
				if(maxEventNumber<100) cout<<eventNumber<<endl;
				showAnalysisProgress();
				clearDCObject();
				reconstructDCObject();

				clearDataContainer();
				getDataContainer();
				
				readDCHit(BDC1RawData,BDC1Hit);
				readDCHit(BDC2RawData,BDC2Hit);
				readDCHit(FDC0RawData,FDC0Hit);
				readDCHit(FDC2RawData,FDC2Hit);

				if(maxEventNumber<100) BDC1RawData->printRaw();

				fillHistograms();
				if(kSaveTree) tree->Fill();
			}

		}

		void readDCHit(DCRaw* DCRawData,TClonesArray *DCHit){
			//DC
			// Initialize Array
		
			DCRawData->initialize();

			if(DCHit){

				int DC_nhits=DCHit->GetEntries();
				DCRawData->setNHits(DC_nhits);
				for(int i=0;i<DCHit->GetEntries();i++){
					TArtDCHit *hit = (TArtDCHit *)DCHit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					DCRawData->fillHit(layer,wireid,val);

				}

			}

			//DCRawData->printRaw();
	
		}

		void fillHistograms(){
			fillBDC1Histograms();
			fillBDC2Histograms();
			fillFDC0Histograms();
			fillFDC2Histograms();
		}
		void fillBDC1Histograms(){
			BDC1RawData->fillTDC(hbdc1tdc);
			BDC1RawData->fillTDCvsWire(hBDC1TDC);
			BDC1RawData->fillAdjcentLayerTDC(hBDC1Layer);
	
		}
		void fillBDC2Histograms(){
			BDC2RawData->fillTDC(hbdc2tdc);
			BDC2RawData->fillTDCvsWire(hBDC2TDC);
			BDC2RawData->fillAdjcentLayerTDC(hBDC2Layer);
	
		}
		void fillFDC0Histograms(){
			FDC0RawData->fillTDC(hfdc0tdc);
			FDC0RawData->fillTDCvsWire(hFDC0TDC);
			FDC0RawData->fillAdjcentLayerTDC(hFDC0Layer);
	
		}
		void fillFDC2Histograms(){
			FDC2RawData->fillTDC(hfdc2tdc);
			FDC2RawData->fillTDCvsWire(hFDC2TDC);
			FDC2RawData->fillAdjcentLayerTDC(hFDC2Layer);
	
		}

		void saveTreeAndCloseOutputFile(){
			//std::clog << std::endl;
			tree->BuildIndex("runNumber","eventNumber");
			fout->cd();
			fout->Write();
			fout->Close("R"); 
		}
		void releaseMemory(){
			EventStore->ClearData();

			delete CalibBDC1Hit;
			delete CalibBDC2Hit;
			delete CalibFDC0Hit;
			delete CalibFDC2Hit;
			delete TArtStoreManager::Instance();
		}
		void printBDC1(){
			cout<<"eventNumber = "<< eventNumber <<endl;
			printBDC1Raw();
			cout<<endl;
		}
		void printBDC1Raw(){
			cout<<" Printing Raw Info:"<<endl;
			for(int i = 0; i<BDC1_layerid.size(); i++)
				cout<<"Layer = "<< BDC1_layerid[i]<<" wireid = "<<BDC1_wireid[i]<<" TDC = "<<BDC1_TDC[i]<<" nhit of layer ="<<BDC1_layer_hits[BDC1_layerid[i]]<<endl;
		}

};

int main(int argc, char *argv[])
{
	int runNumber=-1;
	//Long64_t maxEventNumber = LLONG_MAX;
	Long64_t maxEventNumber = 10000000;
	//cout<<MaxeventNumber<<endl;
	if(argc==2) runNumber=atoi(argv[1]);
	else if(argc==3) { runNumber=atoi(argv[1]); maxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./TDCSpectrum  runNumberber"<<endl;
		cout<<" USAGE: ./TDCSpectrum  runNumberber maxevtnumber"<<endl;
	}
	/**
	 * Mode 1: 1File1TDCSpectrum ; 2: 1Beam1TDCSpectrum ; 3: TDCSpectrum for all
	 * Mode 1: 1File1TDCSpectrum without any condition
	 * Mode 2: Mode 1 + nhits = 1 in each layer 
	 */
	TDCSpectrum *tdcSpectrum =new TDCSpectrum(1,runNumber,maxEventNumber);

	return 0;
}
