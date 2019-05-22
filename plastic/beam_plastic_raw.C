#include "header.h"
int main(int argc, char* argv[]) {

	Int_t runnum;
	Int_t MaxEventNumber = 5;
	//Int_t MaxEventNumber = 50000000;

	if(argc==1) 
	{
		cout << "USAGE: ./plastic runnumber MaxmiumEvent " << endl;
	} 
	else if(argc==2)
	{
		runnum= atoi(argv[1]);
	}
	else if(argc==3)
	{

		runnum= atoi(argv[1]);
		MaxEventNumber = atoi(argv[2]);
	}

	//////////////////// Load anaroot decode class ////////////////////      
	gSystem->Load("libanacore.so");
	gSystem->Load("libanasamurai.so");
	gSystem->Load("libXMLParser.so");

	////////////////////ANAROOT Parameters////////////////////      

	TArtStoreManager *sman = TArtStoreManager::Instance();
	TArtBigRIPSParameters* BigRIPSPara = TArtBigRIPSParameters::Instance();
	TArtSAMURAIParameters *SamuraiPara = TArtSAMURAIParameters::Instance();

	//BigRIPSPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/BigRIPSPlastic.xml"); //F3 F7 and SBT plastic
	BigRIPSPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIPlastic.xml"); //F3 F7 and SBT plastic
	////////////////////Create ANAROOT Reconstruction classes////////////////////   
	// Load BigRIPS Plastic detector
	TArtCalibPlastic *CalibPla = new TArtCalibPlastic();

	////////////////////Setup input and output files////////////////////       
	TString inputpath="/media/Rawdata/RIKEN_Cluster_2018/";
	TString inputfilename=Form("run0%d.ridf.gz",runnum);
	TString inputname=inputpath+inputfilename;

	TString outputpath="./rootfiles/";
	TString outputfilename=Form("run%d_raw_plastic.root",runnum);
	TString outputname=outputpath+outputfilename;


	// Open RIDF input
	TArtEventStore *EventStore = new TArtEventStore;

	if(!EventStore->Open(inputname)) 
	{
		std::cout << "\e[34m " << "cannot open " << inputname << "\e[37m" << std::endl;
		exit(0);
	}
	// Create Rootfiles Output
	TFile *fout = NULL;
	TTree *tree = NULL;
	fout = new TFile(outputname,"recreate");
	tree = new TTree("tree","Ridf to raw");

	tree->AutoSave("SaveSelf");
	tree->SetAutoSave(1e5);

	// Variables
	Long64_t EventNumber = 0;
	Int_t RunNumber = -1;

	// Plastics
	////////////////////////////////////////////////////////
	Double_t F3_LTRaw,F7_LTRaw,SBT1_LTRaw,SBT2_LTRaw; //
	Double_t F3_RTRaw,F7_RTRaw,SBT1_RTRaw,SBT2_RTRaw; //
	Double_t F3_LQRaw,F7_LQRaw,SBT1_LQRaw,SBT2_LQRaw; //
	Double_t F3_RQRaw,F7_RQRaw,SBT1_RQRaw,SBT2_RQRaw; //
	Double_t SBV_RQRaw,SBV_RTRaw;

	tree->Branch("EventNumber",&EventNumber);

	tree->Branch("F3_LTRaw",&F3_LTRaw);
	tree->Branch("F3_RTRaw",&F3_RTRaw);
	tree->Branch("F3_LQRaw",&F3_LQRaw);
	tree->Branch("F3_RQRaw",&F3_RQRaw);

	tree->Branch("F7_LTRaw",&F7_LTRaw);
	tree->Branch("F7_RTRaw",&F7_RTRaw);
	tree->Branch("F7_LQRaw",&F7_LQRaw);
	tree->Branch("F7_RQRaw",&F7_RQRaw);

	tree->Branch("SBT1_LTRaw",&SBT1_LTRaw);
	tree->Branch("SBT1_RTRaw",&SBT1_RTRaw);
	tree->Branch("SBT1_LQRaw",&SBT1_LQRaw);
	tree->Branch("SBT1_RQRaw",&SBT1_RQRaw);


	tree->Branch("SBT2_LTRaw",&SBT2_LTRaw);
	tree->Branch("SBT2_RTRaw",&SBT2_RTRaw);
	tree->Branch("SBT2_LQRaw",&SBT2_LQRaw);
	tree->Branch("SBT2_RQRaw",&SBT2_RQRaw);


	tree->Branch("SBV_RQRaw",&SBV_RQRaw);
	tree->Branch("SBV_RTRaw",&SBV_RTRaw);



	//////////////////// Analysis Loop ////////////////////       
	const Int_t DISPLAY_EVERY_EVENT = 1000 ;
	std::clock_t start = std::clock();
	std::clock_t clock0 = std::clock();


	while(EventStore->GetNextEvent() 
			&& EventNumber < MaxEventNumber
	     ) {

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


		SBV_RQRaw=NAN;
		SBV_RTRaw=NAN;

		TArtPlastic *PlasticF3 = CalibPla->FindPlastic((char*)"F3pl");
		TArtPlastic *PlasticF7 = CalibPla->FindPlastic((char*)"F7pl");
		TArtPlastic *PlasticSBT1 = CalibPla->FindPlastic((char*)"F13pl-1");
		TArtPlastic *PlasticSBT2 = CalibPla->FindPlastic((char*)"F13pl-2");
		TArtPlastic *PlasticSBV = CalibPla->FindPlastic((char*)"SBV");


		if(PlasticF3){

			F3_LTRaw = PlasticF3->GetTLRaw();
			F3_RTRaw = PlasticF3->GetTRRaw();
			F3_LQRaw = PlasticF3->GetQLRaw();
			F3_RQRaw = PlasticF3->GetQRRaw();


		}


		if(PlasticF7){

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
			SBV_RQRaw = PlasticSBV->GetQRRaw();
			SBV_RTRaw = PlasticSBV->GetTRRaw();

			//cout<<"SBV_Charge2="<<SBV_Charge<<"  SBV_Time2="<<SBV_Time<<endl;

		}


		tree->Fill();
	}

	tree->Write();
	fout->Close();

	EventStore->ClearData();

	delete CalibPla;
	delete TArtStoreManager::Instance();
	return 0;

}
