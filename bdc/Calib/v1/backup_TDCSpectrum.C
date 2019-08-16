#include "header.h"
#include "distance.h"


TEnv *env = new TEnv("configTDCSpectrum.prm");
class TDCSpectrum{

	private:
		static const bool isEventByEvent=false;
		static const bool kBDC=true;
		static const bool kFDC=true;

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;





	


	public :

		int runnum;
		Long64_t MaxEventNumber;

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
                TH2* hFDC2Layer[4];

		// Head Variables
		Long64_t EventNumber;
		Int_t RunNumber ;



		// DC Raw Data
		// Each Drift Chamber raw Data 
		// * hit1 (layerid,wireid,TDC)
		// * hit2
		// * hit3
		// * ...
		Int_t BDC1_nhits;
		vector<double> BDC1_TDC;// for each hits, no matter layer, wireid
		vector<double> BDC1_layerid;// for each hits, no matter layer, wireid
		vector<double> BDC1_wireid;// for each hits, no matter layer, wireid

		Int_t BDC2_nhits;
		vector<double> BDC2_TDC;// for each hits, no matter layer, wireid
		vector<double> BDC2_layerid;// for each hits, no matter layer, wireid
		vector<double> BDC2_wireid;// for each hits, no matter layer, wireid

		Int_t FDC0_nhits;
		vector<double> FDC0_TDC;// for each hits, no matter layer, wireid
		vector<double> FDC0_layerid;// for each hits, no matter layer, wireid
		vector<double> FDC0_wireid;// for each hits, no matter layer, wireid

		Int_t FDC2_nhits;
		vector<double> FDC2_TDC;// for each hits, no matter layer, wireid
		vector<double> FDC2_layerid;// for each hits, no matter layer, wireid
		vector<double> FDC2_wireid;// for each hits, no matter layer, wireid


		// how many hits in each layer(layer: 16 wire)
		vector<int> BDC1_layer_hits;
		vector<int> BDC2_layer_hits;
		vector<int> FDC0_layer_hits;
		vector<int> FDC2_layer_hits;


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
			TString inputfilename=Form("run0%d.ridf.gz",runnum);
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

			fout = new TFile(Form("./rootfiles/run0%d_tdcSpectrum.root",runnum),"recreate");
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
						Form("FDC0 TDC layer=%d",ilayer),300,1600,1900,16,-0.5,15.5);
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
			tree->Branch("RunNumber",&RunNumber);
			tree->Branch("EventNumber",&EventNumber);

			///////////////////////////////////////////////////////////////
			//
			tree->Branch("BDC1_TDC",&BDC1_TDC);
			tree->Branch("BDC1_layerid",&BDC1_layerid);
			tree->Branch("BDC1_wireid",&BDC1_wireid);

			tree->Branch("BDC1_nhits",&BDC1_nhits);
			tree->Branch("BDC1_layer_hits",&BDC1_layer_hits);
	

			tree->Branch("BDC2_TDC",&BDC2_TDC);
			tree->Branch("BDC2_layerid",&BDC2_layerid);
			tree->Branch("BDC2_wireid",&BDC2_wireid);
			tree->Branch("BDC2_nhits",&BDC2_nhits);
			tree->Branch("BDC2_layer_hits",&BDC2_layer_hits);
	
			tree->Branch("FDC0_TDC",&FDC0_TDC);
			tree->Branch("FDC0_layerid",&FDC0_layerid);
			tree->Branch("FDC0_wireid",&FDC0_wireid);
			tree->Branch("FDC0_nhits",&FDC0_nhits);
			tree->Branch("FDC0_layer_hits",&FDC0_layer_hits);

			tree->Branch("FDC2_TDC",&FDC2_TDC);
			tree->Branch("FDC2_layerid",&FDC2_layerid);
			tree->Branch("FDC2_wireid",&FDC2_wireid);
			tree->Branch("FDC2_nhits",&FDC2_nhits);
			tree->Branch("FDC2_layer_hits",&FDC2_layer_hits);
	
		}

		void openAnarootStoreManager(){
			sman = TArtStoreManager::Instance();
		}

		TDCSpectrum(int mode){
			/**
			 * 
			 * TDC Spectrum: Generate good Calibration Spectrum
			 * 3 Modes: 1File1TDCSpectrum, 1Beam1TDCSpectrum, 1TDCSpectrumforAll
			 * Output: TDC 1D, 2D with Wireid, Correlation between adjcent layer
			 */
			switch(mode){
				case 1: oneFileTDCSpectrum();break;
				case 2: break;
				case 3: break;
			}

		}
		void oneFileTDCSpectrum(){
			int rn = env->GetValue("runNumber",595);
			Long64_t men = env->GetValue("maxEventNumber",1000);
			analysis(rn,men);
		}
		void analysis(int rn, Long64_t men){
			runnum=rn;
			MaxEventNumber=men;

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

			EventNumber = 0;
			RunNumber = runnum;

			////////////////////////////////Analysis  loop/////////////
			while(EventStore->GetNextEvent() 
					&& EventNumber < MaxEventNumber
			     )
			{

				EventNumber++;
				//cout<<EventNumber<<endl;
				showAnalysisProgress();
				clearDCObject();
				reconstructDCObject();

				clearDataContainer();
				getDataContainer();

				readBDC1Hit();
				if(MaxEventNumber<100) printBDC1();
				readBDC2Hit();
				readFDC0Hit();
				readFDC2Hit();

				fillHistograms();
				tree->Fill();
			}

		}
		void readBDC1Hit(){
			//BDC1
			// Initialize Array
			BDC1_nhits=-1;
			BDC1_layer_hits.clear();
			BDC1_layer_hits.resize(8,0);
			BDC1_TDC.clear();
			BDC1_layerid.clear();
			BDC1_wireid.clear();

//			vector<vector<int> > BDC1_layer_TDC;
//			BDC1_layer_TDC.resize(8);

			if(BDC1Hit){

				BDC1_nhits=BDC1Hit->GetEntries();
				for(int i=0;i<BDC1Hit->GetEntries();i++){
					TArtDCHit *hit = (TArtDCHit *)BDC1Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					BDC1_layer_hits[layer]=BDC1_layer_hits[layer]+1;
					if(BDC1_layer_hits[layer]>16) cout<< EventNumber<<"  "<<BDC1_layer_hits[layer]<<endl;
					//cout<< layer<<"  "<<wireid<<"  "<<val<<"  "<<BDC1_layer_hits[layer]<<endl;
					BDC1_TDC.push_back(val);
					BDC1_layerid.push_back(layer);
					BDC1_wireid.push_back(wireid);
					//BDC1_layer_TDC[layer].push_back(val);


				}
			//	for(int i=0;i<BDC1_layer_TDC.size();i++){
			//		for(int j=0;j<BDC1_layer_TDC[i].size();j++){
			//			cout<<"Layer ="<<i<<" val = "<<BDC1_layer_TDC[i][j]<<endl;
			//		}
			//	}
			}
		}


		void readBDC2Hit(){
			//BDC2
			// Initialize Array
			BDC2_nhits=-1;
			BDC2_layer_hits.clear();
			BDC2_layer_hits.resize(8,0);
			BDC2_TDC.clear();
			BDC2_layerid.clear();
			BDC2_wireid.clear();

			if(BDC2Hit){

				BDC2_nhits=BDC2Hit->GetEntries();
				for(int i=0;i<BDC2Hit->GetEntries();i++){
					TArtDCHit *hit = (TArtDCHit *)BDC2Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					BDC2_layer_hits[layer]++;
					//cout<<BDC2_layer_hits[layer]<<endl;
					BDC2_TDC.push_back(val);
					BDC2_layerid.push_back(layer);
					BDC2_wireid.push_back(wireid);


				}
			}
		}
		void readFDC0Hit(){
			//FDC0
			// Initialize Array
			FDC0_nhits=0;
			FDC0_layer_hits.clear();
			FDC0_layer_hits.resize(8,0);
			FDC0_TDC.clear();
			FDC0_layerid.clear();
			FDC0_wireid.clear();

			if(FDC0Hit){

				FDC0_nhits=FDC0Hit->GetEntries();
				for(int i=0;i<FDC0Hit->GetEntries();i++){
					TArtDCHit *hit = (TArtDCHit *)FDC0Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					FDC0_layer_hits[layer]++;
					//cout<<FDC0_layer_hits[layer]<<endl;
					FDC0_TDC.push_back(val);
					FDC0_layerid.push_back(layer);
					FDC0_wireid.push_back(wireid);

				}
			}
		}
		void readFDC2Hit(){
			//FDC2
			// Initialize Array
			FDC2_nhits=0;
			FDC2_layer_hits.clear();
			FDC2_layer_hits.resize(14,0);
			FDC2_TDC.clear();
			FDC2_layerid.clear();
			FDC2_wireid.clear();

			if(FDC2Hit){

				FDC2_nhits=FDC2Hit->GetEntries();
				for(int i=0;i<FDC2Hit->GetEntries();i++){
					TArtDCHit *hit = (TArtDCHit *)FDC2Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					FDC2_layer_hits[layer]++;
					//cout<<FDC2_layer_hits[layer]<<endl;
					FDC2_TDC.push_back(val);
					FDC2_layerid.push_back(layer);
					FDC2_wireid.push_back(wireid);

				}
			}
		}
		void fillHistograms(){
			fillBDC1Histograms();
			fillBDC2Histograms();
			fillFDC0Histograms();
			fillFDC2Histograms();
		}
		void fillBDC1Histograms(){
			for (int i=0;i<BDC1_nhits;i++){
				int layer = BDC1_layerid[i];
				hbdc1tdc[layer]->Fill(BDC1_TDC[i]);
				hBDC1TDC[layer]->Fill(BDC1_TDC[i],BDC1_wireid[i]);
			}
		}

		void fillBDC2Histograms(){
			for (int i=0;i<BDC2_nhits;i++){
				int layer = BDC2_layerid[i];
				hbdc2tdc[layer]->Fill(BDC2_TDC[i]);
				hBDC2TDC[layer]->Fill(BDC2_TDC[i],BDC2_wireid[i]);
			}
		}

		void fillFDC0Histograms(){

			for (int i=0;i<FDC0_nhits;i++){
				int layer = FDC0_layerid[i];
				hfdc0tdc[layer]->Fill(FDC0_TDC[i]);
				hFDC0TDC[layer]->Fill(FDC0_TDC[i],FDC0_wireid[i]);
			}
		}

		void fillFDC2Histograms(){
			for (int i=0;i<FDC2_nhits;i++){
				int layer = FDC2_layerid[i];
				hfdc2tdc[layer]->Fill(FDC2_TDC[i]);
				hFDC2TDC[layer]->Fill(FDC2_TDC[i],FDC2_wireid[i]);
			}
		}




		void saveTreeAndCloseOutputFile(){
			//std::clog << std::endl;
			tree->BuildIndex("RunNumber","EventNumber");
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
			cout<<"EventNumber = "<< EventNumber <<endl;
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
	int runnum=-1;
	Long64_t MaxEventNumber = LLONG_MAX;
	//Long64_t MaxEventNumber = 10000;
	//cout<<MaxEventNumber<<endl;
	if(argc==2) runnum=atoi(argv[1]);
	else if(argc==3) { runnum=atoi(argv[1]); MaxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./TDCSpectrum  runnumber"<<endl;
		cout<<" USAGE: ./TDCSpectrum  runnumber maxevtnumber"<<endl;
	}
	/**
	 * Mode 1: 1File1TDCSpectrum ; 2: 1Beam1TDCSpectrum ; 3: TDCSpectrum for all
	 */
	TDCSpectrum *tdcSpectrum =new TDCSpectrum(1);

	return 0;
}
