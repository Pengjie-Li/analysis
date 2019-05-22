void pixelR()
{


	//int runnum=599;
	//int runnum=597;
	int runnum=598;

	for(int i=15;i<16;i++)
		//for(int i=0;i<32;i++)
		for(int j=15;j<16;j++)
			//for(int j=0;j<32;j++)
		{
			select_pixel(runnum,i,j);

		}


}



void select_pixel(int runnum=598, int fid=16, int bid=12){ 
	//Reset ROOT and connect tree file
	//


	gROOT->Reset();
	gStyle->SetOptStat(1111111);

	TString inputname=Form("./analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"READ");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");


	//Declaration of leaves types
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;
	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_ADC;
	Double_t        CsI_LRT_ADC;
	Double_t        CsI_LRB_ADC;
	Double_t        CsI_RLT_ADC;
	Double_t        CsI_RLB_ADC;
	Double_t        CsI_RRT_ADC;
	Double_t        CsI_RRB_ADC;


	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("SiLF_SCM",SiLF_SCM);
	AnalysisTree->SetBranchAddress("SiLB_SCM",SiLB_SCM);
	AnalysisTree->SetBranchAddress("SiRF_SCM",SiRF_SCM);
	AnalysisTree->SetBranchAddress("SiRB_SCM",SiRB_SCM);
	
	AnalysisTree->SetBranchAddress("CsI_LL_ADC",&CsI_LL_ADC);
	AnalysisTree->SetBranchAddress("CsI_LRT_ADC",&CsI_LRT_ADC);
	AnalysisTree->SetBranchAddress("CsI_LRB_ADC",&CsI_LRB_ADC);
	AnalysisTree->SetBranchAddress("CsI_RLT_ADC",&CsI_RLT_ADC);
	AnalysisTree->SetBranchAddress("CsI_RLB_ADC",&CsI_RLB_ADC);
	AnalysisTree->SetBranchAddress("CsI_RRT_ADC",&CsI_RRT_ADC);
	AnalysisTree->SetBranchAddress("CsI_RRB_ADC",&CsI_RRB_ADC);



	TString outputname=Form("./pixelrootfiles/pixel%d_%d_run0%d.root",fid,bid,runnum);
	TFile *g=new TFile(outputname,"recreate");
	TTree *tree=new TTree("tree","tree");


	double pixelF;
	double pixelB;

	double pixelRLT;
	double pixelRLB;
	double pixelRRT;
	double pixelRRB;

	tree->Branch("pixelF",  &pixelF);
	tree->Branch("pixelB",  &pixelB);
	tree->Branch("pixelRLT",  &pixelRLT);
	tree->Branch("pixelRLB",  &pixelRLB);
	tree->Branch("pixelRRT",  &pixelRRT);
	tree->Branch("pixelRRB",  &pixelRRB);


	tree->Branch("Target_X",&Target_X);
	tree->Branch("Target_Y",&Target_Y);





	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;

	for (Long64_t ientry=0; ientry<nentries;ientry++) {



		// Init 
		pixelF=-999;
		pixelB=-999;

		pixelRLT=-999;
		pixelRLB=-999;
		pixelRRT=-999;
		pixelRRB=-999;
		for(int i=0;i<32;i++)
		{
			SiLF_SCM[i]=-999;
			SiLB_SCM[i]=-999;
			SiRF_SCM[i]=-999;
			SiRB_SCM[i]=-999;



		}



		nbytes += AnalysisTree->GetEntry(ientry);


		if(SiRF_SCM[fid]>500&&SiRB_SCM[bid]>500)
		{
			pixelF=SiRF_SCM[fid];
			pixelB=SiRB_SCM[bid];

			pixelRLT=CsI_RLT_ADC;
			pixelRLB=CsI_RLB_ADC;
			pixelRRT=CsI_RRT_ADC;
			pixelRRB=CsI_RRB_ADC;


			tree->Fill();
		}

		if(ientry%10000==0) cout<<ientry<<endl;


	}

	tree->Write();
	g->Close();


}
