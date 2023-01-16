//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void pixelL()
{
	//for(int i=15;i<16;i++)
	for(int i=0;i<32;i++)
		for(int j=20;j<32;j++)
		//for(int j=0;j<32;j++)
		{
			select_pixel(i,j);

		}


}

void select_pixel(int fid=16, int bid=12){ 

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int runnum=595;
	//int runnum=596;
	//int runnum=599;

	TString inputname=Form("../analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types
	
	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Int_t        SiLF_id;
	Int_t        SiLB_id;
	Int_t        SiRF_id;
	Int_t        SiRB_id;



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
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);
	
	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);
	
	
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






	TString outputname=Form("./pixelrootfiles/Lpixel%d_%d_run0%d.root",fid,bid,runnum);
	TFile *g=new TFile(outputname,"recreate");
	TTree *tree=new TTree("tree","tree");


	double pixelF;
	double pixelB;
	double pixelLL;
	double pixelLRT;
	double pixelLRB;

	tree->Branch("pixelF",  &pixelF);
	tree->Branch("pixelB",  &pixelB);
	tree->Branch("pixelLL",  &pixelLL);
	tree->Branch("pixelLRT",  &pixelLRT);
	tree->Branch("pixelLRB",  &pixelLRB);



	tree->Branch("Beam",  &Beam);
	tree->Branch("Target_X",&Target_X);
	tree->Branch("Target_Y",&Target_Y);
	tree->Branch("Target_ThetaX",&Target_ThetaX);
	tree->Branch("Target_ThetaY",&Target_ThetaY);



	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=1000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		//if(SiLF_E[fid]>3000&&SiLB_E[bid]>3000&&(SiLF_E[fid]<40000&&SiLB_E[bid]<40000))
		if(SiLF_id==fid&&SiLB_id==bid)
		{
			pixelF=SiLF_E[fid];
			pixelB=SiLB_E[bid];
			pixelLL =CsI_LL_ADC;
			pixelLRT=CsI_LRT_ADC;
			pixelLRB=CsI_LRB_ADC;

			tree->Fill();
		}






		if(ientry%10000==0) cout<<ientry<<endl;

	}

	f->Close();
	tree->Write();
	g->Close();

}

