#include "header.h"
#include "distance.h"

//void loadTDCDistribution(TFile *dcin, TArtCalibDCTrack *);
//void loadTDCDistribution(int runnum,TArtCalibDCTrack *CalibBDC1Track,TArtCalibDCTrack *CalibBDC2Track,TArtCalibDCTrack *CalibFDC0Track);

class ConvertDC{

	private:
		static const bool isEventByEvent=false;
		static const bool kBDC=true;
		static const bool kFDC=true;

		static const int DISPLAY_EVERY_EVENT = 1000 ;
		std::clock_t start  ;
		std::clock_t clock0 ;





		int runnum;
		Long64_t MaxEventNumber;

		TArtEventStore *EventStore;
		TArtStoreManager *sman;

		// Input
		TFile *dcin; // dc calibrated file from anaroot dc folder
		// Output
		TFile *fout_BDC ;
		TTree *tree_BDC ;

		TFile *fout_FDC ;
		TTree *tree_FDC ;




	public :


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


		//DC Possible Track Data
		Int_t BDC1_nlayerx;
		Int_t BDC1_nlayery;
		vector<double> BDC1_Track_dl;
		vector<double> BDC1_Track_XY;
		vector<double> BDC1_Track_Z;
		vector<double> BDC1_Track_dXY;

		Int_t BDC2_nlayerx;
		Int_t BDC2_nlayery;
		vector<double> BDC2_Track_dl;
		vector<double> BDC2_Track_XY;
		vector<double> BDC2_Track_Z;
		vector<double> BDC2_Track_dXY;


		Int_t FDC0_nlayerx;
		Int_t FDC0_nlayery;
		vector<double> FDC0_Track_dl;
		vector<double> FDC0_Track_XY;
		vector<double> FDC0_Track_Z;
		vector<double> FDC0_Track_dXY;


		// Analysis Result 
		Double_t BDC1_X,BDC1_Y,BDC2_X,BDC2_Y,FDC0_X,FDC0_Y;
		Double_t BDC1_ThetaX,BDC1_ThetaY,BDC2_ThetaX,BDC2_ThetaY,FDC0_ThetaX,FDC0_ThetaY;
		Double_t FDC2_X,FDC2_Y,FDC2_ThetaX,FDC2_ThetaY;

		Double_t BDC1_Chi2x,BDC2_Chi2x,FDC0_Chi2x;
		Double_t BDC1_Chi2y,BDC2_Chi2y,FDC0_Chi2y;

		// Load Drift Chambers
		TArtCalibDCHit   *CalibBDC1Hit   ; 
		TArtCalibDCTrack *CalibBDC1Track ; 
		TArtCalibDCHit   *CalibBDC2Hit   ; 
		TArtCalibDCTrack *CalibBDC2Track ; 
		TArtCalibDCHit   *CalibFDC0Hit   ; 
		TArtCalibDCTrack *CalibFDC0Track ; 
		TArtCalibDCHit   *CalibFDC2Hit   ; 
		TArtCalibDCTrack *CalibFDC2Track ; 

		// In each event
		TClonesArray *BDC1Hit   ;
		TClonesArray *BDC1Track ;

		TClonesArray *BDC2Hit   ;
		TClonesArray *BDC2Track ;

		TClonesArray *FDC0Hit   ;
		TClonesArray *FDC0Track ;


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
			CalibBDC1Track = new TArtCalibBDC1Track();
			CalibBDC2Hit   = new TArtCalibBDC2Hit();
			CalibBDC2Track = new TArtCalibBDC2Track();
			CalibFDC0Hit   = new TArtCalibFDC0Hit();
			CalibFDC0Track = new TArtCalibFDC0Track();
			CalibFDC2Hit   = new TArtCalibFDC2Hit();
			CalibFDC2Track = new TArtCalibFDC2Track();
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

		void setAnarootTDCWindow(){
			/* before 20190219 using this range*/
			//CalibBDC1Track->SetTDCWindow(1700,1870);  
			//CalibBDC2Track->SetTDCWindow(1700,1870);  
			//CalibFDC0Track->SetTDCWindow(1700,1870);  
			//
		//	CalibBDC1Track->SetTDCWindow(1770,1860);  
		//	CalibBDC2Track->SetTDCWindow(1760,1860);  
		//	CalibFDC0Track->SetTDCWindow(1740,1850);  
			CalibBDC1Track->SetTDCWindow(1720,1880);  
			CalibBDC2Track->SetTDCWindow(1720,1880);  
			CalibFDC0Track->SetTDCWindow(1720,1880);  



		}


		void loadTDCDistribution(){
			setAnarootTDCWindow();
			cout << "   CALTREE-Info : Load TDC Distribution" << endl;

			//dcin = new TFile(Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/root/dcdist0%d_v6.root",runnum),"READ");
			//dcin = new TFile(Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/root/dcdist0%d.root",runnum),"READ");
			//dcin = new TFile(Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/root_v20190114/dcdist0%d.root",runnum),"READ");
			dcin = new TFile(Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/bdc/Calib/rootfiles/run0%d_tdcSpectrum.root",runnum),"READ");
			if(dcin->IsOpen()){
				loadTDCDistribution(CalibBDC1Track,"bdc1");
				loadTDCDistribution(CalibBDC2Track,"bdc2");
				loadTDCDistribution(CalibFDC0Track,"fdc0");
			}
		}

		void loadTDCDistribution(TArtCalibDCTrack *CalibDCTrack,TString name){
			//gROOT->cd();
			TH1* hist = NULL;
			TString hName="h"+name;
			for(Int_t ihist=0;ihist<8;ihist++){
				hist = (TH1D*)dcin->Get(hName+(TString)Form("tdc%d",ihist));
				CalibDCTrack->SetTDCDistribution(hist,ihist);
				delete hist;
				hist = NULL;
			}

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

		void createOutputFileAndTree(){
			///////////////////////////////////////////////////////////////////
			///////////////////// Create TFile and TTree  /////////////////////
			///////////////////////////////////////////////////////////////////


			TString treeName="CalTree";
			// BDC Tree
			fout_BDC = NULL;
			tree_BDC = NULL;
			if(kBDC){
				fout_BDC = new TFile(Form("./rootfiles/run0%d_BDC.root",runnum),"recreate");
				tree_BDC = new TTree(treeName+(TString)"BDC","Analysis Tree BDC");
				tree_BDC->AutoSave("SaveSelf");
				tree_BDC->SetAutoSave(1e5);
			}


			// FDC Tree
			fout_FDC = NULL;
			tree_FDC = NULL;
			if(kFDC){
				fout_FDC = new TFile(Form("./rootfiles/run0%d_FDCG.root",runnum),"recreate");
				tree_FDC = new TTree(treeName+(TString)"FDC","Analysis Tree FDC");
				tree_FDC->AutoSave("SaveSelf");
				tree_FDC->SetAutoSave(1e5);
			}

		}

		void setBDCBranch(){
			//Beam
			tree_BDC->Branch("RunNumber",&RunNumber);
			tree_BDC->Branch("EventNumber",&EventNumber);

			///////////////////////////////////////////////////////////////////
			//
			// Raw
			tree_BDC->Branch("BDC1_nhits",&BDC1_nhits);
			tree_BDC->Branch("BDC1_TDC",&BDC1_TDC);
			tree_BDC->Branch("BDC1_layerid",&BDC1_layerid);
			tree_BDC->Branch("BDC1_wireid",&BDC1_wireid);

			//Raw2
			tree_BDC->Branch("BDC1_layer_hits",&BDC1_layer_hits);
			tree_BDC->Branch("BDC1_nlayerx",&BDC1_nlayerx);
			tree_BDC->Branch("BDC1_nlayery",&BDC1_nlayery);
	

			//Track
			tree_BDC->Branch("BDC1_Track_dl",&BDC1_Track_dl);
			tree_BDC->Branch("BDC1_Track_XY",&BDC1_Track_XY);
			tree_BDC->Branch("BDC1_Track_Z",&BDC1_Track_Z);
			tree_BDC->Branch("BDC1_Track_dXY",&BDC1_Track_dXY);

			//Analysis Result
			tree_BDC->Branch("BDC1_X",&BDC1_X);
			tree_BDC->Branch("BDC1_Y",&BDC1_Y);
			tree_BDC->Branch("BDC1_ThetaX",&BDC1_ThetaX);
			tree_BDC->Branch("BDC1_ThetaY",&BDC1_ThetaY);

			//Raw
			tree_BDC->Branch("BDC2_nhits",&BDC2_nhits);
			tree_BDC->Branch("BDC2_TDC",&BDC2_TDC);
			tree_BDC->Branch("BDC2_layerid",&BDC2_layerid);
			tree_BDC->Branch("BDC2_wireid",&BDC2_wireid);

			//Raw2
			tree_BDC->Branch("BDC2_layer_hits",&BDC2_layer_hits);
			tree_BDC->Branch("BDC2_nlayerx",&BDC2_nlayerx);
			tree_BDC->Branch("BDC2_nlayery",&BDC2_nlayery);
	
			//Track
			tree_BDC->Branch("BDC2_Track_dl",&BDC2_Track_dl);
			tree_BDC->Branch("BDC2_Track_XY",&BDC2_Track_XY);
			tree_BDC->Branch("BDC2_Track_Z",&BDC2_Track_Z);
			tree_BDC->Branch("BDC2_Track_dXY",&BDC2_Track_dXY);

			// Analysed
			tree_BDC->Branch("BDC2_X",&BDC2_X);
			tree_BDC->Branch("BDC2_Y",&BDC2_Y);
			tree_BDC->Branch("BDC2_ThetaX",&BDC2_ThetaX);
			tree_BDC->Branch("BDC2_ThetaY",&BDC2_ThetaY);
		}
		void setFDCBranch(){
			tree_FDC->Branch("RunNumber",&RunNumber);
			tree_FDC->Branch("EventNumber",&EventNumber);

			//Raw
			tree_FDC->Branch("FDC0_nhits",&FDC0_nhits);
			tree_FDC->Branch("FDC0_TDC",&FDC0_TDC);
			tree_FDC->Branch("FDC0_layerid",&FDC0_layerid);
			tree_FDC->Branch("FDC0_wireid",&FDC0_wireid);

			//RawF
			tree_FDC->Branch("FDC0_layer_hits",&FDC0_layer_hits);
			tree_FDC->Branch("FDC0_nlayerx",&FDC0_nlayerx);
			tree_FDC->Branch("FDC0_nlayery",&FDC0_nlayery);
	
			//TraFk
			tree_FDC->Branch("FDC0_Track_dl",&FDC0_Track_dl);
			tree_FDC->Branch("FDC0_Track_XY",&FDC0_Track_XY);
			tree_FDC->Branch("FDC0_Track_Z",&FDC0_Track_Z);
			tree_FDC->Branch("FDC0_Track_dXY",&FDC0_Track_dXY);

			// AnFlysed
			tree_FDC->Branch("FDC0_X",&FDC0_X);
			tree_FDC->Branch("FDC0_Y",&FDC0_Y);
			tree_FDC->Branch("FDC0_ThetaX",&FDC0_ThetaX);
			tree_FDC->Branch("FDC0_ThetaY",&FDC0_ThetaY);

			tree_FDC->Branch("FDC2_X",&FDC2_X);
			tree_FDC->Branch("FDC2_Y",&FDC2_Y);
			tree_FDC->Branch("FDC2_ThetaX",&FDC2_ThetaX);
			tree_FDC->Branch("FDC2_ThetaY",&FDC2_ThetaY);
		}
		void setOutputBranch(){
			setBDCBranch();
			setFDCBranch();
		}

		void openAnarootStoreManager(){
			sman = TArtStoreManager::Instance();
		}

		ConvertDC(int rn, Long64_t men){
			runnum=rn;
			MaxEventNumber=men;

			loadAnarootDecoder();
			openAnarootStoreManager();
			loadAnarootDatabase();

			createDCObject();
			loadTDCDistribution();

			openRawData();

			createOutputFileAndTree();
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
			BDC1Track = NULL ;

			BDC2Hit   = NULL ; 
			BDC2Track = NULL ;

			FDC0Hit   = NULL ; 
			FDC0Track = NULL ;

		}
		void getDataContainer(){

			// ======================= Obtain event =============================//
			BDC1Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");
			BDC1Track = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");

			BDC2Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");
			BDC2Track = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");

			FDC0Hit   = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Hit");
			FDC0Track = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Track");

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

				//BDC1
				// Initialize Array
				BDC1_nhits=-1;
				BDC1_layer_hits.clear();
				BDC1_layer_hits.resize(8,0);
				BDC1_TDC.clear();
				BDC1_layerid.clear();
				BDC1_wireid.clear();

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


					}
				}


				BDC1_X = NAN;
				BDC1_Y = NAN;
				BDC1_ThetaX = NAN;
				BDC1_ThetaY = NAN;
				BDC1_nlayerx=0;
				BDC1_nlayery=0;
				BDC1_Track_dl.clear();
				BDC1_Track_dl.resize(8,-9999);
				BDC1_Track_XY.clear();
				BDC1_Track_XY.resize(8,-9999);
				BDC1_Track_Z.clear();
				BDC1_Track_Z.resize(8,-9999);
				BDC1_Track_dXY.clear();
				BDC1_Track_dXY.resize(8,-9999);
				if (BDC1Track)
				{
					Int_t BDC1NumberOfTracks = BDC1Track->GetEntries();
					Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 

					if (BDC1NumberOfTracks > 0)
					{
						TArtDCTrack *TrackBDC1;

						for(Int_t i=0; i<BDC1NumberOfTracks; i++)
						{
							TrackBDC1 = (TArtDCTrack *)BDC1Track->At(i);

							if(TrackBDC1)
							{

								TempXPosition = TrackBDC1->GetPosition(0);
								Temp_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
								TempYPosition = TrackBDC1->GetPosition(1);
								Temp_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
								TempChi2 = TrackBDC1->GetChi2();
								TempNDF = TrackBDC1->GetNDF();

								if(TempChi2 > 0 ){

									if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
										MinChi2x = TempChi2;
										BDC1_X = TempXPosition;
										BDC1_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
										BDC1_Chi2x=MinChi2x;

										BDC1_nlayerx=TrackBDC1->GetNumHitLayer();
										for(int st=0;st<BDC1_nlayerx;st++)
										{
											Int_t planeid=TrackBDC1->GetHitPlaneID(st)-21;
											BDC1_Track_dl[planeid]=TrackBDC1->GetDriftLength(st);
											BDC1_Track_XY[planeid]=TrackBDC1->GetHitXPosition(st);
											BDC1_Track_Z[planeid]=TrackBDC1->GetHitZPosition(st);
											BDC1_Track_dXY[planeid]=TrackBDC1->GetAngle(0)*BDC1_Track_Z[planeid]+TrackBDC1->GetPosition(0)-BDC1_Track_XY[planeid];
											if(isEventByEvent) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC1_Track_dl[planeid]<<" xpos="<<BDC1_Track_XY[planeid]<<" zpos="<<BDC1_Track_Z[planeid]<<" dx="<<BDC1_Track_dXY[planeid]<<endl;

										}


									}

									if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
										BDC1_Y = TempYPosition;
										BDC1_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
										MinChi2y = TempChi2;
										BDC1_Chi2y=MinChi2y;

										BDC1_nlayery=TrackBDC1->GetNumHitLayer();
										for(int st=0;st<BDC1_nlayery;st++)
										{
											Int_t planeid=TrackBDC1->GetHitPlaneID(st)-21;
											BDC1_Track_dl[planeid]=TrackBDC1->GetDriftLength(st);
											BDC1_Track_XY[planeid]=TrackBDC1->GetHitXPosition(st);
											BDC1_Track_Z[planeid]=TrackBDC1->GetHitZPosition(st);
											BDC1_Track_dXY[planeid]=TrackBDC1->GetAngle(1)*BDC1_Track_Z[planeid]+TrackBDC1->GetPosition(1)-BDC1_Track_XY[planeid];
											if(isEventByEvent) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC1_Track_dl[planeid]<<" xpos="<<BDC1_Track_XY[planeid]<<" zpos="<<BDC1_Track_Z[planeid]<<" dx="<<BDC1_Track_dXY[planeid]<<endl;

										}


									}
								}
							}
						}
					}
				}

				if(MaxEventNumber<100) printBDC1();

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

				BDC2_X = NAN;
				BDC2_Y = NAN;
				BDC2_ThetaX = NAN;
				BDC2_ThetaY = NAN;
				BDC2_nlayerx=0;
				BDC2_nlayery=0;
				BDC2_Track_dl.clear();
				BDC2_Track_dl.resize(8,-9999);
				BDC2_Track_XY.clear();
				BDC2_Track_XY.resize(8,-9999);
				BDC2_Track_Z.clear();
				BDC2_Track_Z.resize(8,-9999);
				BDC2_Track_dXY.clear();
				BDC2_Track_dXY.resize(8,-9999);
				if (BDC2Track)
				{
					Int_t BDC2NumberOfTracks = BDC2Track->GetEntries();
					Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 

					if (BDC2NumberOfTracks > 0)
					{
						TArtDCTrack *TrackBDC2;

						for(Int_t i=0; i<BDC2NumberOfTracks; i++)
						{
							TrackBDC2 = (TArtDCTrack *)BDC2Track->At(i);

							if(TrackBDC2)
							{

								TempXPosition = TrackBDC2->GetPosition(0);
								Temp_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
								TempYPosition = TrackBDC2->GetPosition(1);
								Temp_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
								TempChi2 = TrackBDC2->GetChi2();
								TempNDF = TrackBDC2->GetNDF();

								if(TempChi2 > 0 ){

									if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
										MinChi2x = TempChi2;
										BDC2_X = TempXPosition;
										BDC2_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
										BDC2_Chi2x=MinChi2x;

										BDC2_nlayerx=TrackBDC2->GetNumHitLayer();
										for(int st=0;st<BDC2_nlayerx;st++)
										{
											Int_t planeid=TrackBDC2->GetHitPlaneID(st)-31;
											BDC2_Track_dl[planeid]=TrackBDC2->GetDriftLength(st);
											BDC2_Track_XY[planeid]=TrackBDC2->GetHitXPosition(st);
											BDC2_Track_Z[planeid]=TrackBDC2->GetHitZPosition(st);
											BDC2_Track_dXY[planeid]=TrackBDC2->GetAngle(0)*BDC2_Track_Z[planeid]+TrackBDC2->GetPosition(0)-BDC2_Track_XY[planeid];
											if(isEventByEvent) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC2_Track_dl[planeid]<<" xpos="<<BDC2_Track_XY[planeid]<<" zpos="<<BDC2_Track_Z[planeid]<<" dx="<<BDC2_Track_dXY[planeid]<<endl;

										}


									}

									if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
										BDC2_Y = TempYPosition;
										BDC2_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
										MinChi2y = TempChi2;
										BDC2_Chi2y=MinChi2y;

										BDC2_nlayery=TrackBDC2->GetNumHitLayer();
										for(int st=0;st<BDC2_nlayery;st++)
										{
											Int_t planeid=TrackBDC2->GetHitPlaneID(st)-31;
											BDC2_Track_dl[planeid]=TrackBDC2->GetDriftLength(st);
											BDC2_Track_XY[planeid]=TrackBDC2->GetHitXPosition(st);
											BDC2_Track_Z[planeid]=TrackBDC2->GetHitZPosition(st);
											BDC2_Track_dXY[planeid]=TrackBDC2->GetAngle(1)*BDC2_Track_Z[planeid]+TrackBDC2->GetPosition(1)-BDC2_Track_XY[planeid];
											if(isEventByEvent) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC2_Track_dl[planeid]<<" xpos="<<BDC2_Track_XY[planeid]<<" zpos="<<BDC2_Track_Z[planeid]<<" dx="<<BDC2_Track_dXY[planeid]<<endl;

										}


									}
								}
							}
						}
					}
				}
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

				FDC0_X = NAN;
				FDC0_Y = NAN;
				FDC0_ThetaX = NAN;
				FDC0_ThetaY = NAN;
				FDC0_nlayerx=0;
				FDC0_nlayery=0;
				FDC0_Track_dl.clear();
				FDC0_Track_dl.resize(8,-9999);
				FDC0_Track_XY.clear();
				FDC0_Track_XY.resize(8,-9999);
				FDC0_Track_Z.clear();
				FDC0_Track_Z.resize(8,-9999);
				FDC0_Track_dXY.clear();
				FDC0_Track_dXY.resize(8,-9999);
				if (FDC0Track)
				{
					Int_t FDC0NumberOfTracks = FDC0Track->GetEntries();
					Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 

					//cout<<"Number of Tracks="<<FDC0NumberOfTracks<<endl;

					if (FDC0NumberOfTracks > 0)
					{
						TArtDCTrack *TrackFDC0;

						for(Int_t i=0; i<FDC0NumberOfTracks; i++)
						{
							TrackFDC0 = (TArtDCTrack *)FDC0Track->At(i);

							if(TrackFDC0)
							{

								TempXPosition = TrackFDC0->GetPosition(0);
								Temp_ThetaX = TMath::ATan(TrackFDC0->GetAngle(0));
								TempYPosition = TrackFDC0->GetPosition(1);
								Temp_ThetaY = TMath::ATan(TrackFDC0->GetAngle(1));
								TempChi2 = TrackFDC0->GetChi2();
								TempNDF = TrackFDC0->GetNDF();

								if(TempChi2 > 0 ){

									if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
										MinChi2x = TempChi2;
										FDC0_X = TempXPosition;
										FDC0_ThetaX = TMath::ATan(TrackFDC0->GetAngle(0));
										FDC0_Chi2x=MinChi2x;

										FDC0_nlayerx=TrackFDC0->GetNumHitLayer();
										for(int st=0;st<FDC0_nlayerx;st++)
										{
											Int_t planeid=TrackFDC0->GetHitPlaneID(st)-11;
											if(planeid>8||planeid<0) 
											{
												cout<<" CALTREE info: Error! Plane id readout wrong!"<<endl;
												exit(0);

											}
											FDC0_Track_dl[planeid]=TrackFDC0->GetDriftLength(st);
											FDC0_Track_XY[planeid]=TrackFDC0->GetHitXPosition(st);
											FDC0_Track_Z[planeid]=TrackFDC0->GetHitZPosition(st);
											FDC0_Track_dXY[planeid]=TrackFDC0->GetAngle(0)*FDC0_Track_Z[planeid]+TrackFDC0->GetPosition(0)-FDC0_Track_XY[planeid];
											//if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<FDC0_Track_dl[planeid]<<" xpos="<<FDC0_Track_XY[planeid]<<" zpos="<<FDC0_Track_Z[planeid]<<" dx="<<FDC0_Track_dXY[planeid]<<endl;

										}


									}

									if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
										FDC0_Y = TempYPosition;
										FDC0_ThetaY = TMath::ATan(TrackFDC0->GetAngle(1));
										MinChi2y = TempChi2;
										FDC0_Chi2y=MinChi2y;

										FDC0_nlayery=TrackFDC0->GetNumHitLayer();
										for(int st=0;st<FDC0_nlayery;st++)
										{
											Int_t planeid=TrackFDC0->GetHitPlaneID(st)-11;
											if(planeid>8||planeid<0) 
											{
												cout<<" CALTREE info: Error! Plane id readout wrong!"<<endl;
												exit(0);

											}
											FDC0_Track_dl[planeid]=TrackFDC0->GetDriftLength(st);
											FDC0_Track_XY[planeid]=TrackFDC0->GetHitXPosition(st);
											FDC0_Track_Z[planeid]=TrackFDC0->GetHitZPosition(st);
											FDC0_Track_dXY[planeid]=TrackFDC0->GetAngle(1)*FDC0_Track_Z[planeid]+TrackFDC0->GetPosition(1)-FDC0_Track_XY[planeid];
											//if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<FDC0_Track_dl[planeid]<<" xpos="<<FDC0_Track_XY[planeid]<<" zpos="<<FDC0_Track_Z[planeid]<<" dx="<<FDC0_Track_dXY[planeid]<<endl;

										}


									}
								}
							}
						}
					}
				}





				tree_BDC->Fill();

				tree_FDC->Fill();
				// END BEAM ANALYSIS


			}






		}
		void saveTreeAndCloseOutputFile(){
			//std::clog << std::endl;
			if(kBDC) { tree_BDC->BuildIndex("RunNumber","EventNumber"); fout_BDC->cd();  fout_BDC->Write(); fout_BDC->Close("R"); }
			if(kFDC) { tree_FDC ->BuildIndex("RunNumber","EventNumber"); fout_FDC ->cd(); fout_FDC ->Write();  fout_FDC ->Close("R"); }
		}
		void releaseMemory(){
			EventStore->ClearData();

			delete CalibBDC1Hit;
			delete CalibBDC1Track;
			delete CalibBDC2Hit;
			delete CalibBDC2Track;
			delete CalibFDC0Hit;
			delete CalibFDC0Track;
			delete CalibFDC2Hit;
			delete CalibFDC2Track;
			delete TArtStoreManager::Instance();
		}
		void printBDC1(){
			cout<<"EventNumber = "<< EventNumber <<endl;
			printBDC1Raw();
			printBDC1Track();
			cout<<endl;
		}
		void printBDC1Raw(){
			cout<<" Printing Raw Info:"<<endl;
			for(int i = 0; i<BDC1_layerid.size(); i++)
				cout<<"Layer = "<< BDC1_layerid[i]<<" wireid = "<<BDC1_wireid[i]<<" TDC = "<<BDC1_TDC[i]<<" nhit of layer ="<<BDC1_layer_hits[BDC1_layerid[i]]<<endl;
		}

		void printBDC1Track(){
			cout<<"Printing Track Info:"<<endl;
			for(int i = 0;i<BDC1_Track_Z.size(); i++)
			cout<<"Layer = "<<i<<" Drift length="<<setw(9)<<BDC1_Track_dl[i]<<" xypos="<<setw(9)<<BDC1_Track_XY[i]<<" zpos="<<setw(9)<<BDC1_Track_Z[i]<<" Residue dxy = "<<setw(9)<<BDC1_Track_dXY[i]<<endl;

		}

};

int main(int argc, char *argv[])
{
	int runnum=-1;
	Long64_t MaxEventNumber = LLONG_MAX;
//	Long64_t MaxEventNumber = 30;
	//cout<<MaxEventNumber<<endl;
	if(argc==2) runnum=atoi(argv[1]);
	else if(argc==3) { runnum=atoi(argv[1]); MaxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./ConvertDC  runnumber"<<endl;
		cout<<" USAGE: ./ConvertDC  runnumber maxevtnumber"<<endl;
	}

	ConvertDC *convertDC =new ConvertDC(runnum, MaxEventNumber);

	return 0;
}
