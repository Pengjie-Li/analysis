#include "header.h"
#include "DriftLength.h"
#include "distance.h"
#include "LoadTDCDistribution.h"

int main(int argc, char *argv[])
{
	int runnum=-1;
	Long64_t MaxEventNumber = LLONG_MAX;
	if(argc==2) runnum=atoi(argv[1]);
	else if(argc==3) { runnum=atoi(argv[1]); MaxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./bdc runnumber"<<endl;
		cout<<" USAGE: ./bdc runnumber maxevtnumber"<<endl;
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
	TFile *dcin = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/root/dcdist.root","READ");
	if(dcin->IsOpen()){
		gROOT->cd();
		TH1* hist = NULL;
		// BDC1
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hbdc1tdc%d",ihist));
			CalibBDC1Track->SetTDCDistribution(hist,ihist);
			//SetDriftLength(hist,ihist);
			delete hist;
			hist = NULL;
		}

		// BDC2
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hbdc2tdc%d",ihist));
			CalibBDC2Track->SetTDCDistribution(hist,ihist);
			//SetDriftLength(hist,ihist);
			delete hist;
			hist = NULL;
		}
	}


	////////////////////Setup input and output files////////////////////       
	
	TString inputpath="/media/Rawdata/RIKEN_Cluster_2018/";
	TString inputfilename=Form("run0%d.ridf.gz",runnum);
	TString inputname=inputpath+inputfilename;

	TString outputpath="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/rootfiles/converted/";
	TString outputfilename=Form("run0%d_Beamevt.root",runnum);
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

	// BDC
	Double_t BDC1_X,BDC1_Y,BDC2_X,BDC2_Y;
	Double_t BDC1_ThetaX,BDC1_ThetaY,BDC2_ThetaX,BDC2_ThetaY;
	Double_t Target_X,Target_Y,Target_ThetaX,Target_ThetaY; // Value at the entrance

	//Beam
	tree_BEAM->Branch("RunNumber",&RunNumber);
	tree_BEAM->Branch("EventNumber",&EventNumber);
	///////////////////////////////////////////////////////////////////
	tree_BEAM->Branch("BDC1_X",&BDC1_X);
	tree_BEAM->Branch("BDC1_Y",&BDC1_Y);
	tree_BEAM->Branch("BDC1_ThetaX",&BDC1_ThetaX);
	tree_BEAM->Branch("BDC1_ThetaY",&BDC1_ThetaY);
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
		// ======================= Checking event by event =============================//
		TClonesArray *bdc1hits = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");
		TClonesArray *bdc2hits = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");
		// Track checking
		TClonesArray *bdc1tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
		TClonesArray *bdc2tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");


		if(bdc1hits){
			int bdc1_nhit[8];// how many hits fired in each layer for this event
			bool isbdc1Hit[8][16+2];// layer:wire fire or not

                        //initialization
			for(int i=0;i<8;i++){
				bdc1_nhit[i] = 0; 
				for(int j=0;j<16+2;j++) isbdc1Hit[i][j] = false;
			}
			cout<<"runnum="<<runnum<<" EventNumber="<<EventNumber<<" BDC1 Data"<<endl;

			for(int i=0;i<bdc1hits->GetEntries();i++){
				TArtDCHit *hit = (TArtDCHit *)bdc1hits->At(i);
				int layer = hit->GetLayer();
				int wireid = hit->GetWireID();
				int val = hit->GetTDC();
				//double dl=CalcDriftLength(val,layer); 
				//Double_t pos = hit->GetPosition();
                                cout<<"    layer="<<layer<<" wireid="<<wireid<<" tdc="<<val<<endl;

				bdc1_nhit[layer] ++;
				isbdc1Hit[layer][wireid] = true;

			}
		}
		cout<<endl;

		if (bdc1tracks)
		{

                        // Note: Chi2 here is not real Chi2, without divide over sigma, so it's meanningless to over NDF.
			Int_t BDC1NumberOfTracks = bdc1tracks->GetEntries();
			Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,TempChi2,TempNDF; 
			Int_t nhits;
			Double_t dl[100];
			Double_t xpos[100];
			Double_t zpos[100];

			if (BDC1NumberOfTracks > 0)
			{
			cout<<"BDC1 Number of Tracks="<<BDC1NumberOfTracks<<endl;	

				for(Int_t i=0; i<BDC1NumberOfTracks; i++)
				{
					TArtDCTrack *TrackBDC1 = (TArtDCTrack *)bdc1tracks->At(i);

					if(TrackBDC1)
					{

						TempXPosition = TrackBDC1->GetPosition(0);
						Temp_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
						TempYPosition = TrackBDC1->GetPosition(1);
						Temp_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
						TempChi2 = TrackBDC1->GetChi2();
						TempNDF = TrackBDC1->GetNDF();
						cout<<endl;
						cout<<"Track="<<i<<" X="<<TempXPosition<<" Y="<<TempYPosition<<" ThetaX="<<Temp_ThetaX<<" ThetaY="<<Temp_ThetaY<<" Chi2="<<TempChi2<<" NDF="<<TempNDF<<endl;
						nhits=TrackBDC1->GetNumHitLayer();
						for(int st=0;st<nhits;st++)
						{
							dl[st]=TrackBDC1->GetDriftLength(st);
							xpos[st]=TrackBDC1->GetHitXPosition(st);
							zpos[st]=TrackBDC1->GetHitZPosition(st);
							cout<<"    hitlayer="<<st<<" drift length="<<dl[st]<<" xpos="<<xpos[st]<<" zpos="<<zpos[st]<<endl;

						}

					}
				}
			}
		}
		cout<<endl;
		if(bdc2hits){
			int bdc2_nhit[8];// how many hits fired in each layer for this event
			bool isbdc2Hit[8][16+2];// layer:wire fire or not

                        //initialization
			for(int i=0;i<8;i++){
				bdc2_nhit[i] = 0; 
				for(int j=0;j<16+2;j++) isbdc2Hit[i][j] = false;
			}
			cout<<"runnum="<<runnum<<" EventNumber="<<EventNumber<<" BDC2 Data"<<endl;

			for(int i=0;i<bdc2hits->GetEntries();i++){
				TArtDCHit *hit = (TArtDCHit *)bdc2hits->At(i);
				int layer = hit->GetLayer();
				int wireid = hit->GetWireID();
				int val = hit->GetTDC();
                               double dl=CalcDriftLength(val,layer); 
				//Double_t pos = hit->GetPosition();
                                cout<<"    layer="<<layer<<" wireid="<<wireid<<" tdc="<<val<<" driftlength="<<dl<<endl;

				bdc2_nhit[layer] ++;
				isbdc2Hit[layer][wireid] = true;

			}
		}

		cout<<endl;
		if (bdc2tracks)
		{

                        // Note: Chi2 here is not real Chi2, without divide over sigma, so it's meanningless to over NDF.
			Int_t BDC2NumberOfTracks = bdc2tracks->GetEntries();
			Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,TempChi2,TempNDF; 
			Int_t nhits;
			Double_t dl[100];
			Double_t xpos[100];
			Double_t zpos[100];

			if (BDC2NumberOfTracks > 0)
			{
			cout<<"BDC2 Number of Tracks="<<BDC2NumberOfTracks<<endl;	

				for(Int_t i=0; i<BDC2NumberOfTracks; i++)
				{
					TArtDCTrack *TrackBDC2 = (TArtDCTrack *)bdc2tracks->At(i);

					if(TrackBDC2)
					{

						TempXPosition = TrackBDC2->GetPosition(0);
						Temp_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
						TempYPosition = TrackBDC2->GetPosition(1);
						Temp_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
						TempChi2 = TrackBDC2->GetChi2();
						TempNDF = TrackBDC2->GetNDF();
						cout<<endl;
						cout<<"Track="<<i<<" X="<<TempXPosition<<" Y="<<TempYPosition<<" ThetaX="<<Temp_ThetaX<<" ThetaY="<<Temp_ThetaY<<" Chi2="<<TempChi2<<" NDF="<<TempNDF<<endl;
						nhits=TrackBDC2->GetNumHitLayer();
						for(int st=0;st<nhits;st++)
						{
							dl[st]=TrackBDC2->GetDriftLength(st);
							xpos[st]=TrackBDC2->GetHitXPosition(st);
							zpos[st]=TrackBDC2->GetHitZPosition(st);
							cout<<"    hitlayer="<<st<<" drift length="<<dl[st]<<" xpos="<<xpos[st]<<" zpos="<<zpos[st]<<endl;

						}

					}
				}
			}
		}



		// Plastic-- Beam PID
		Double_t TOF713=NAN;
		Double_t f7qave=NAN;
		Double_t f13qave=NAN;
		Double_t F13t = NAN;
		Double_t TOF713off=330;// modified later, 20180710

		TArtPlastic* f7pla;
		TArtPlastic* f13pla1;
		TArtPlastic* f13pla2;
		TArtPlastic* vetopla;

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
		F13t = (f13pla1->GetTime()+f13pla2->GetTime())/2.;
		TOF713=F13t-f7pla->GetTime()+TOF713off;
		f7qave = f7pla->GetQAveRaw();
		f13qave = sqrt((f13pla1->GetQAveRaw())*(f13pla2->GetQAveRaw()));



		//BDC1
		BDC1_X = NAN;
		BDC1_Y = NAN;
		BDC1_ThetaX = NAN;
		BDC1_ThetaY = NAN;
		TClonesArray *BDC1Tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
		if (BDC1Tracks)
		{
			Int_t BDC1NumberOfTracks = BDC1Tracks->GetEntries();
			Double_t TempXPosition, TempYPosition, TempChi2, MinChi2x = 1e6, MinChi2y = 1e6;

			if (BDC1NumberOfTracks > 0)
			{
				TArtDCTrack *TrackBDC1;

				for(Int_t i=0; i<BDC1NumberOfTracks; i++)
				{
					TrackBDC1 = (TArtDCTrack *)BDC1Tracks->At(i);

					if(TrackBDC1)
					{
						TempXPosition = TrackBDC1->GetPosition(0);
						TempYPosition = TrackBDC1->GetPosition(1);
						TempChi2 = TrackBDC1->GetChi2();

						if(TempChi2 > 0 ){

							if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
								BDC1_X = TempXPosition;
								BDC1_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
								MinChi2x = TempChi2;
							}

							if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
								BDC1_Y = TempYPosition;
								BDC1_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
								MinChi2y = TempChi2;
							}
						}
					}
				}
			}
		}

		//BDC2
		BDC2_X = NAN;
		BDC2_Y = NAN;
		BDC2_ThetaX = NAN;
		BDC2_ThetaY = NAN;

		CalibBDC2Hit->ReconstructData();
		CalibBDC2Track->ReconstructData();

		TClonesArray *BDC2Tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");
		if (BDC2Tracks)
		{
                        
			Int_t BDC2NumberOfTracks = BDC2Tracks->GetEntries();
			Double_t TempXPosition, TempYPosition, TempChi2, MinChi2x=1e6, MinChi2y=1e6;

			if (BDC2NumberOfTracks > 0)
			{
				TArtDCTrack *TrackBDC2;

				for(Int_t i=0; i<BDC2NumberOfTracks; i++)
				{
					TrackBDC2 = (TArtDCTrack *)BDC2Tracks->At(i);

					if(TrackBDC2)
					{
						TempXPosition = TrackBDC2->GetPosition(0);
						TempYPosition = TrackBDC2->GetPosition(1);
						TempChi2 = TrackBDC2->GetChi2();

						if(TempChi2 > 0 ){
							if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
								BDC2_X = TempXPosition;
								BDC2_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
								MinChi2x = TempChi2;
							}
							if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
								BDC2_Y = TempYPosition;
								BDC2_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
								MinChi2y = TempChi2;
							}
						}
					}
				}
			}
		}

		cout<<"BDC1_X="<<BDC1_X<<" BDC1_Y="<< BDC1_Y<<" BDC2_X="<<BDC2_X<<" BDC2_Y="<<BDC2_Y<<endl;

		//TARGET
		Target_X = NAN;
		Target_Y = NAN;
		Target_ThetaX = NAN;
		Target_ThetaY = NAN;

		Target_X = BDC1_X + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_X - BDC1_X);
		Target_Y = BDC1_Y + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_Y - BDC1_Y);
		Target_ThetaX = TMath::ATan( (BDC2_X - BDC1_X) / Dist_BDC1BDC2 );
		Target_ThetaY = TMath::ATan( (BDC2_Y - BDC1_Y) / Dist_BDC1BDC2 );

		tree_BEAM ->Fill();

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

