//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void pixelL()
{
	for(int i=15;i<16;i++)
	//for(int i=0;i<32;i++)
		for(int j=15;j<16;j++)
		//for(int j=0;j<32;j++)
		{
			select_pixel(i,j);

		}


}

void select_pixel(int fid=16, int bid=12){ 

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);


	int runnum=599;


	TString inputname=Form("./rootfiles/run0%d_Beamv8.root",runnum);
	TFile *f = new TFile(inputname,"READ");
	TTree *tree_BEAM=(TTree*)f->Get("tree_BEAM");

	//Declaration of leaves types
	Double_t        Target_X;
	Double_t        Target_Y;
	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;


	vector<double>  *SiLF_rawADC;
	vector<double>  *SiLB_rawADC;
	vector<double>  *SiRF_rawADC;
	vector<double>  *SiRB_rawADC;
	Double_t        CsILL_rawADC;
	Double_t        CsILRT_rawADC;
	Double_t        CsILRB_rawADC;
	Double_t        CsIRLT_rawADC;
	Double_t        CsIRLB_rawADC;
	Double_t        CsIRRT_rawADC;
	Double_t        CsIRRB_rawADC;


	tree_BEAM->SetBranchAddress("Target_X",&Target_X);
	tree_BEAM->SetBranchAddress("Target_Y",&Target_Y);
	tree_BEAM->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	tree_BEAM->SetBranchAddress("Target_ThetaY",&Target_ThetaY);


	tree_BEAM->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
	tree_BEAM->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
	tree_BEAM->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
	tree_BEAM->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);

	tree_BEAM->SetBranchAddress("CsILL_rawADC",&CsILL_rawADC);
	tree_BEAM->SetBranchAddress("CsILRT_rawADC",&CsILRT_rawADC);
	tree_BEAM->SetBranchAddress("CsILRB_rawADC",&CsILRB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLT_rawADC",&CsIRLT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLB_rawADC",&CsIRLB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRT_rawADC",&CsIRRT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRB_rawADC",&CsIRRB_rawADC);


	TString outputname=Form("./pixelrootfiles/pixel%d_%d_run0%d_Beamv8.root",fid,bid,runnum);
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




	tree->Branch("Target_X",&Target_X);
	tree->Branch("Target_Y",&Target_Y);
	tree->Branch("Target_ThetaX",&Target_ThetaX);
	tree->Branch("Target_ThetaY",&Target_ThetaY);



	Long64_t nentries = tree_BEAM->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree_BEAM->GetEntry(ientry);
		if((*SiLF_rawADC)[fid]>500&&(*SiLB_rawADC)[bid]>500)
		{
			pixelF=(*SiLF_rawADC)[fid];
			pixelB=(*SiLB_rawADC)[bid];
			pixelLL=CsILL_rawADC;
			pixelLRT=CsILRT_rawADC;
			pixelLRB=CsILRB_rawADC;

			tree->Fill();
		}






		if(ientry%10000==0) cout<<ientry<<endl;

	}

	tree->Write();
	g->Close();

}

