#include "header.h"
#include "distance.h"
#include "LoadTDCDistribution.h"

int main(int argc, char *argv[])
{
	int runnum=-1;
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
	TString outputfilename=Form("run0%d_Beamv1.root",runnum);
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
	Double_t F3_Time,F5_Time,F7_Time,F13_Time;
	////////////////////////////////////////////////////////
	Double_t F3_LTRaw,F7_LTRaw,SBT1_LTRaw,SBT2_LTRaw; //
	Double_t F3_RTRaw,F7_RTRaw,SBT1_RTRaw,SBT2_RTRaw; //
	Double_t F3_LQRaw,F7_LQRaw,SBT1_LQRaw,SBT2_LQRaw; //
	Double_t F3_RQRaw,F7_RQRaw,SBT1_RQRaw,SBT2_RQRaw; //
	Double_t TOFF3F7,TOFF7F13; //


	// BDC
	Int_t BDC1_nhits;
        Int_t BDC1_layer_hits[8];
	vector<double> BDC1_TDC;// for each hits, no matter layer, wireid
	vector<double> BDC1_layerid;// for each hits, no matter layer, wireid
	vector<double> BDC1_wireid;// for each hits, no matter layer, wireid

	Double_t BDC1_X,BDC1_Y,BDC2_X,BDC2_Y;
	Double_t BDC1_ThetaX,BDC1_ThetaY,BDC2_ThetaX,BDC2_ThetaY;
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

	tree_BEAM->Branch("TOFF3F7",&TOFF3F7);
	tree_BEAM->Branch("TOFF7F13",&TOFF7F13);

	///////////////////////////////////////////////////////////////////
	// Raw
	
	tree_BEAM->Branch("BDC1_nhits",&BDC1_nhits);
	tree_BEAM->Branch("BDC1_layer_hits",&BDC1_layer_hits);
	tree_BEAM->Branch("BDC1_TDC",&BDC1_TDC);
	tree_BEAM->Branch("BDC1_layerid",&BDC1_layerid);
	tree_BEAM->Branch("BDC1_wireid",&BDC1_wireid);
	// Analysed
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
		F7_Charge=NAN;
		F7_Charge=f7qave;
		TOFF7F13=NAN;
		TOFF7F13=TOF713;




		// Initialize Array
		BDC1_nhits=NAN;
                for(int bdci=0;bdci<8;bdci++) BDC1_layer_hits[bdci]=0;
		BDC1_TDC.clear();
		BDC1_layerid.clear();
		BDC1_wireid.clear();

		//BDC1
		if(CalibBDC1Hit){

                        //BDC1_nhits=CalibBDC1Hit->GetEntries();
			//for(int i=0;i<BDC1_nhits;i++){
			for(int i=0;i<CalibBDC1Hit->GetEntries();i++){
				TArtDCHit *hit = (TArtDCHit *)CalibBDC1Hit->At(i);
				int layer = hit->GetLayer();
				int wireid = hit->GetWireID();
				int val = hit->GetTDC();
                                BDC1_layer_hits[layer]++;
                                BDC1_TDC.push_back(val);
                                BDC1_layerid.push_back(layer);
                                BDC1_wireid.push_back(wireid);


			}
		}
		cout<<endl;


		BDC1_X = NAN;
		BDC1_Y = NAN;
		BDC1_ThetaX = NAN;
		BDC1_ThetaY = NAN;
		TClonesArray *BDC1Tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
		if (BDC1Tracks)
		{
			Int_t BDC1NumberOfTracks = BDC1Tracks->GetEntries();
			Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 
			Int_t nhits;
			Double_t dl[100];
			Double_t xpos[100];
			Double_t zpos[100];


			if (BDC1NumberOfTracks > 0)
			{
				TArtDCTrack *TrackBDC1;

				for(Int_t i=0; i<BDC1NumberOfTracks; i++)
				{
					TrackBDC1 = (TArtDCTrack *)BDC1Tracks->At(i);

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

