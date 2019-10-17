#include "header.h"
#include "distance.h"
#include "LoadTDCDistribution.h"

int main(int argc, char *argv[])
{
	int runnum=-1;
	Int_t EventByEvent=0;
	Long64_t MaxEventNumber = LLONG_MAX;
	//cout<<MaxEventNumber<<endl;
	if(argc==2) runnum=atoi(argv[1]);
	else if(argc==3) { runnum=atoi(argv[1]); MaxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./beam runnumber"<<endl;
		cout<<" USAGE: ./beam runnumber maxevtnumber"<<endl;
	}
	//////////////////// Load anaroot decode class ////////////////////      
	gSystem->Load("libanacore.so");
	gSystem->Load("libanasamurai.so");
	gSystem->Load("libXMLParser.so");



	// ====================== ANAROOT Parameters =======================


	TArtStoreManager *sman = TArtStoreManager::Instance();
	TArtBigRIPSParameters *BigRIPSPara = TArtBigRIPSParameters::Instance();
	TArtSAMURAIParameters *SamuraiPara = new TArtSAMURAIParameters();

	BigRIPSPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIPlastic.xml"); //F3 F7 and SBT plastic
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIBDC1.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIBDC2.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIFDC0.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/SAMURAIFDC2.xml");

	////////////////////Create ANAROOT Reconstruction classes////////////////////   

	// Load Beamline Plastic
	TArtCalibPlastic* CalibPla = new TArtCalibPlastic;
	// Load Drift Chambers
	TArtCalibBDC1Hit   *CalibBDC1Hit   = new TArtCalibBDC1Hit();
	TArtCalibBDC1Track *CalibBDC1Track = new TArtCalibBDC1Track();
	TArtCalibBDC2Hit   *CalibBDC2Hit   = new TArtCalibBDC2Hit();
	TArtCalibBDC2Track *CalibBDC2Track = new TArtCalibBDC2Track();
	CalibBDC1Track->SetTDCWindow(1700,1870);  
	CalibBDC2Track->SetTDCWindow(1700,1870);  

	cout << "   CALTREE-Info : Load TDC Distribution" << endl;
	//TFile *dcin = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/root/dcdist.root","READ");
	TFile *dcin = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/root/dcdist0436.root","READ");
	if(dcin->IsOpen()){
		gROOT->cd();
		TH1* hist = NULL;
		// BDC1
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hbdc1tdc%d",ihist));
			CalibBDC1Track->SetTDCDistribution(hist,ihist);
			delete hist;
			hist = NULL;
		}

		// BDC2
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hbdc2tdc%d",ihist));
			CalibBDC2Track->SetTDCDistribution(hist,ihist);
			delete hist;
			hist = NULL;
		}
	}


	////////////////////Setup input and output files////////////////////       

	TString inputpath="/media/Rawdata/RIKEN_Cluster_2018/";
	TString inputfilename=Form("run0%d.ridf.gz",runnum);
	TString inputname=inputpath+inputfilename;

	TString outputpath="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/rootfiles/converted/";
	//TString outputfilename=Form("run0%d_Beamv1test.root",runnum);
	TString outputfilename=Form("run0%d_Beamv2.root",runnum);
	TString outputname=outputpath+outputfilename;



	TArtEventStore *EventStore = new TArtEventStore;

	//EventStore->Open(inputname);
	if(!EventStore->Open(inputname)) 
	{
		std::cout << "\e[34m " << "cannot open " <<inputname<< "\e[37m" << std::endl;
		exit(0);
	}


	// BEAM Tree

	TFile *fout_BEAM = NULL;
	TTree *tree_BEAM = NULL;
	fout_BEAM = new TFile(outputname,"recreate");
	tree_BEAM = new TTree("tree_BEAM","Analysis Tree BEAM");
	//  tree_BEAM->SetFile(fout_BEAM);
	tree_BEAM->AutoSave("SaveSelf");
	tree_BEAM->SetAutoSave(1e5);

	// Variables
	Long64_t EventNumber = 0;
	Int_t RunNumber = -1;

	// Plastics

	Double_t F3_Charge,F5_Charge,F7_Charge,F13_Charge,SBV_Charge;
	Double_t F3_Time,F5_Time,F7_Time,F13_Time,SBV_Time;
	////////////////////////////////////////////////////////
	Double_t F3_LTRaw,F7_LTRaw,SBT1_LTRaw,SBT2_LTRaw; //
	Double_t F3_RTRaw,F7_RTRaw,SBT1_RTRaw,SBT2_RTRaw; //
	Double_t F3_LQRaw,F7_LQRaw,SBT1_LQRaw,SBT2_LQRaw; //
	Double_t F3_RQRaw,F7_RQRaw,SBT1_RQRaw,SBT2_RQRaw; //
	Double_t TOFF3F7,TOFF7F13; //


	// BDC
	Int_t BDC1_nhits;
	vector<int> BDC1_layer_hits;
	vector<double> BDC1_TDC;// for each hits, no matter layer, wireid
	vector<double> BDC1_layerid;// for each hits, no matter layer, wireid
	vector<double> BDC1_wireid;// for each hits, no matter layer, wireid

	Int_t BDC2_nhits;
	vector<int> BDC2_layer_hits;
	vector<double> BDC2_TDC;// for each hits, no matter layer, wireid
	vector<double> BDC2_layerid;// for each hits, no matter layer, wireid
	vector<double> BDC2_wireid;// for each hits, no matter layer, wireid


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


	Double_t BDC1_X,BDC1_Y,BDC2_X,BDC2_Y;
	Double_t BDC1_ThetaX,BDC1_ThetaY,BDC2_ThetaX,BDC2_ThetaY;

	Double_t BDC1_Chi2x,BDC2_Chi2x;
	Double_t BDC1_Chi2y,BDC2_Chi2y;
	Double_t Target_X,Target_Y,Target_ThetaX,Target_ThetaY; // Value at the entrance

	//Beam
	tree_BEAM->Branch("RunNumber",&RunNumber);
	tree_BEAM->Branch("EventNumber",&EventNumber);

	tree_BEAM->Branch("F3_Charge",&F3_Charge);
	tree_BEAM->Branch("F3_Time",&F3_Time);
	tree_BEAM->Branch("F3_LTRaw",&F3_LTRaw);
	tree_BEAM->Branch("F3_RTRaw",&F3_RTRaw);
	tree_BEAM->Branch("F3_LQRaw",&F3_LQRaw);
	tree_BEAM->Branch("F3_RQRaw",&F3_RQRaw);

	tree_BEAM->Branch("F7_Charge",&F7_Charge);
	tree_BEAM->Branch("F7_Time",&F7_Time);
	tree_BEAM->Branch("F7_LTRaw",&F7_LTRaw);
	tree_BEAM->Branch("F7_RTRaw",&F7_RTRaw);
	tree_BEAM->Branch("F7_LQRaw",&F7_LQRaw);
	tree_BEAM->Branch("F7_RQRaw",&F7_RQRaw);

	tree_BEAM->Branch("SBT1_LTRaw",&SBT1_LTRaw);
	tree_BEAM->Branch("SBT1_RTRaw",&SBT1_RTRaw);
	tree_BEAM->Branch("SBT1_LQRaw",&SBT1_LQRaw);
	tree_BEAM->Branch("SBT1_RQRaw",&SBT1_RQRaw);


	tree_BEAM->Branch("SBT2_LTRaw",&SBT2_LTRaw);
	tree_BEAM->Branch("SBT2_RTRaw",&SBT2_RTRaw);
	tree_BEAM->Branch("SBT2_LQRaw",&SBT2_LQRaw);
	tree_BEAM->Branch("SBT2_RQRaw",&SBT2_RQRaw);


	tree_BEAM->Branch("F13_Charge",&F13_Charge);
	tree_BEAM->Branch("F13_Time",&F13_Time);
	tree_BEAM->Branch("SBV_Charge",&SBV_Charge);
	tree_BEAM->Branch("SBV_Time",&SBV_Time);

	tree_BEAM->Branch("TOFF3F7",&TOFF3F7);
	tree_BEAM->Branch("TOFF7F13",&TOFF7F13);

	///////////////////////////////////////////////////////////////////
	// Raw

	tree_BEAM->Branch("BDC1_nhits",&BDC1_nhits);
	tree_BEAM->Branch("BDC1_layer_hits",&BDC1_layer_hits);
	tree_BEAM->Branch("BDC1_nlayerx",&BDC1_nlayerx);
	tree_BEAM->Branch("BDC1_nlayery",&BDC1_nlayery);
	tree_BEAM->Branch("BDC1_TDC",&BDC1_TDC);
	tree_BEAM->Branch("BDC1_layerid",&BDC1_layerid);
	tree_BEAM->Branch("BDC1_wireid",&BDC1_wireid);

	tree_BEAM->Branch("BDC2_nhits",&BDC2_nhits);
	tree_BEAM->Branch("BDC2_layer_hits",&BDC2_layer_hits);
	tree_BEAM->Branch("BDC2_nlayerx",&BDC2_nlayerx);
	tree_BEAM->Branch("BDC2_nlayery",&BDC2_nlayery);
	tree_BEAM->Branch("BDC2_TDC",&BDC2_TDC);
	tree_BEAM->Branch("BDC2_layerid",&BDC2_layerid);
	tree_BEAM->Branch("BDC2_wireid",&BDC2_wireid);

	// Analysed

	tree_BEAM->Branch("BDC1_Track_dl",&BDC1_Track_dl);
	tree_BEAM->Branch("BDC1_Track_XY",&BDC1_Track_XY);
	tree_BEAM->Branch("BDC1_Track_Z",&BDC1_Track_Z);
	tree_BEAM->Branch("BDC1_Track_dXY",&BDC1_Track_dXY);
	tree_BEAM->Branch("BDC1_X",&BDC1_X);
	tree_BEAM->Branch("BDC1_Y",&BDC1_Y);
	tree_BEAM->Branch("BDC1_ThetaX",&BDC1_ThetaX);
	tree_BEAM->Branch("BDC1_ThetaY",&BDC1_ThetaY);

	tree_BEAM->Branch("BDC2_Track_dl",&BDC2_Track_dl);
	tree_BEAM->Branch("BDC2_Track_XY",&BDC2_Track_XY);
	tree_BEAM->Branch("BDC2_Track_Z",&BDC2_Track_Z);
	tree_BEAM->Branch("BDC2_Track_dXY",&BDC2_Track_dXY);
	tree_BEAM->Branch("BDC2_X",&BDC2_X);
	tree_BEAM->Branch("BDC2_Y",&BDC2_Y);
	tree_BEAM->Branch("BDC2_ThetaX",&BDC2_ThetaX);
	tree_BEAM->Branch("BDC2_ThetaY",&BDC2_ThetaY);
	tree_BEAM->Branch("Target_X",&Target_X);
	tree_BEAM->Branch("Target_Y",&Target_Y);
	tree_BEAM->Branch("Target_ThetaX",&Target_ThetaX);
	tree_BEAM->Branch("Target_ThetaY",&Target_ThetaY);



	////////////////////////////////Analysis  loop/////////////

	const Int_t DISPLAY_EVERY_EVENT = 1000 ;
	std::clock_t start = std::clock();
	std::clock_t clock0 = std::clock();
	//MaxEventNumber=138;
	while(EventStore->GetNextEvent() 
			&& EventNumber < MaxEventNumber
	     )
	{

		EventNumber++;
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


		// Reconstruct 
		CalibPla->ClearData();
		CalibPla->ReconstructData();

		CalibBDC1Hit->ClearData();
		CalibBDC1Hit->ReconstructData();

		CalibBDC1Track->ClearData();
		CalibBDC1Track->ReconstructData();

		CalibBDC2Hit->ClearData();
		CalibBDC2Hit->ReconstructData();

		CalibBDC2Track->ClearData();
		CalibBDC2Track->ReconstructData();

		// ======================= Obtain event =============================//
		TClonesArray *BDC1Hit = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");
		TClonesArray *BDC2Hit = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");
		// Track check
		TClonesArray *BDC1Track= (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
		TClonesArray *BDC2Track= (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");



		// Plastic-- Beam PID
		F3_Charge = NAN;
		F3_Time = NAN;
		F7_Charge = NAN;
		F7_Time = NAN;
		F13_Charge = NAN;
		F13_Time = NAN;

		////////////////////////////////////////////////////////////

		F3_LTRaw = NAN;
		F3_RTRaw = NAN;
		F3_LQRaw = NAN;
		F3_RQRaw = NAN;


		F7_LTRaw = NAN;
		F7_RTRaw = NAN;
		F7_LQRaw = NAN;
		F7_RQRaw = NAN;


		SBT1_LTRaw = NAN;
		SBT1_RTRaw = NAN;
		SBT1_LQRaw = NAN;
		SBT1_RQRaw = NAN;

		SBT2_LTRaw = NAN;
		SBT2_RTRaw = NAN;
		SBT2_LQRaw = NAN;
		SBT2_RQRaw = NAN;


		SBV_Charge=NAN;
		SBV_Time=NAN;
		Double_t TOFF713=NAN;
		Double_t TOF713off=330;// modified later, 20180710

		TArtPlastic* f7pla;
		TArtPlastic* f13pla1;
		TArtPlastic* f13pla2;
		TArtPlastic* vetopla;

		TArtPlastic *PlasticF3 = CalibPla->FindPlastic((char*)"F3pl");
		TArtPlastic *PlasticF7 = CalibPla->FindPlastic((char*)"F7pl");
		TArtPlastic *PlasticSBT1 = CalibPla->FindPlastic((char*)"F13pl-1");
		TArtPlastic *PlasticSBT2 = CalibPla->FindPlastic((char*)"F13pl-2");
		TArtPlastic *PlasticSBV = CalibPla->FindPlastic((char*)"SBV");


		TClonesArray* pla_array = CalibPla->GetPlasticArray();
		int npla=pla_array->GetEntries();
		for(int ipla=0; ipla < npla; ++ipla){
			TArtPlastic* pla = (TArtPlastic*)pla_array->At(ipla);
			Int_t ID=pla->GetID();
			if (ID==3) f7pla = pla;
			if (ID==4) f13pla1 = pla;
			if (ID==5) f13pla2 = pla;
			if (ID==6) vetopla = pla;
		}
		/*
		   if(vetopla)
		   {
		   SBV_Charge = vetopla->GetQRRaw();
		   SBV_Time = vetopla->GetTRRaw();

		   cout<<"SBV_Charge1="<<SBV_Charge<<"  SBV_Time1="<<SBV_Time<<endl;
		   }
		   */

		if(PlasticF3){
			F3_Charge = PlasticF3->GetQAveRaw();
			F3_Time = PlasticF3->GetTimeSlew() ;

			F3_LTRaw = PlasticF3->GetTLRaw();
			F3_RTRaw = PlasticF3->GetTRRaw();
			F3_LQRaw = PlasticF3->GetQLRaw();
			F3_RQRaw = PlasticF3->GetQRRaw();


		}


		if(PlasticF7){
			F7_Charge = PlasticF7->GetQAveRaw();
			F7_Time = PlasticF7->GetTimeSlew(); // Test of offset to have a ToF F7-F13

			F7_LTRaw = PlasticF7->GetTLRaw();
			F7_RTRaw = PlasticF7->GetTRRaw();
			F7_LQRaw = PlasticF7->GetQLRaw();
			F7_RQRaw = PlasticF7->GetQRRaw();

		}

		if(PlasticSBT1){

			SBT1_LTRaw = PlasticSBT1->GetTLRaw();
			SBT1_RTRaw = PlasticSBT1->GetTRRaw();
			SBT1_LQRaw = PlasticSBT1->GetQLRaw();
			SBT1_RQRaw = PlasticSBT1->GetQRRaw();


		}
		if(PlasticSBT2){

			SBT2_LTRaw = PlasticSBT2->GetTLRaw();
			SBT2_RTRaw = PlasticSBT2->GetTRRaw();
			SBT2_LQRaw = PlasticSBT2->GetQLRaw();
			SBT2_RQRaw = PlasticSBT2->GetQRRaw();

		}


		if(PlasticSBV)
		{
			SBV_Charge = PlasticSBV->GetQRRaw();
			SBV_Time = PlasticSBV->GetTRRaw();

			//cout<<"SBV_Charge2="<<SBV_Charge<<"  SBV_Time2="<<SBV_Time<<endl;

		}

		F13_Time = (PlasticSBT1->GetTime()+PlasticSBT2->GetTime())/2.;
		F13_Charge = sqrt((PlasticSBT1->GetQAveRaw())*(PlasticSBT2->GetQAveRaw()));
		TOFF7F13=F13_Time-PlasticF7->GetTime()+TOF713off;




		//BDC1
		// Initialize Array
		BDC1_nhits=NAN;
		BDC1_layer_hits.clear();
		BDC1_layer_hits.resize(8,0);
		BDC1_TDC.clear();
		BDC1_layerid.clear();
		BDC1_wireid.clear();

		if(BDC1Hit){

			BDC1_nhits=BDC1Hit->GetEntries();
			//for(int i=0;i<BDC1_nhits;i++){
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
									//if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC1_Track_dl[planeid]<<" xpos="<<BDC1_Track_XY[planeid]<<" zpos="<<BDC1_Track_Z[planeid]<<" dx="<<BDC1_Track_dXY[planeid]<<endl;

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
									if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC1_Track_dl[planeid]<<" xpos="<<BDC1_Track_XY[planeid]<<" zpos="<<BDC1_Track_Z[planeid]<<" dx="<<BDC1_Track_dXY[planeid]<<endl;

								}


							}
						}
					}
				}
			}
		}


		//BDC2
		// Initialize Array
		BDC2_nhits=NAN;
		BDC2_layer_hits.clear();
		BDC2_layer_hits.resize(8,0);
		BDC2_TDC.clear();
		BDC2_layerid.clear();
		BDC2_wireid.clear();

		if(BDC2Hit){

			BDC2_nhits=BDC2Hit->GetEntries();
			//for(int i=0;i<BDC2_nhits;i++){
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
									if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC2_Track_dl[planeid]<<" xpos="<<BDC2_Track_XY[planeid]<<" zpos="<<BDC2_Track_Z[planeid]<<" dx="<<BDC2_Track_dXY[planeid]<<endl;

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
									if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC2_Track_dl[planeid]<<" xpos="<<BDC2_Track_XY[planeid]<<" zpos="<<BDC2_Track_Z[planeid]<<" dx="<<BDC2_Track_dXY[planeid]<<endl;

								}


							}
						}
					}
				}
			}
		}


		//TARGET
		Target_X = NAN;
		Target_Y = NAN;
		Target_ThetaX = NAN;
		Target_ThetaY = NAN;


		Target_X = BDC1_X + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_X - BDC1_X);
		Target_Y = BDC1_Y + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_Y - BDC1_Y);
		Target_ThetaX = TMath::ATan( (BDC2_X - BDC1_X) / Dist_BDC1BDC2 );
		Target_ThetaY = TMath::ATan( (BDC2_Y - BDC1_Y) / Dist_BDC1BDC2 );

		//for(int bdci=0;bdci<8;bdci++)	cout<<"    hitlayer="<<bdci<<" drift length="<<BDC1_Track_dl[bdci]<<" xpos="<<BDC1_Track_XY[bdci]<<" zpos="<<BDC1_Track_Z[bdci]<<endl;
		tree_BEAM->Fill();

		// END BEAM ANALYSIS


		}
		//std::clog << std::endl;

		tree_BEAM->BuildIndex("RunNumber","EventNumber"); fout_BEAM->cd();  fout_BEAM->Write(); fout_BEAM->Close("R"); 

		EventStore->ClearData();

		delete CalibBDC1Hit;
		delete CalibBDC1Track;
		delete CalibBDC2Hit;
		delete CalibBDC2Track;
		delete TArtStoreManager::Instance();

		return 0;
		}

