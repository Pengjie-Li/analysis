//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////



void drawIMPACT(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);
	int runnum=310;
	//int runnum=596;
	//int runnum=597;
	//int runnum=598;
	//int runnum=595;

	TString inputname=Form("rootfiles/run0%d_analysed.root_1",runnum);
	TFile *f = new TFile(inputname,"READ");
	TTree *tree=(TTree*)f->Get("tree");

	//Declaration of leaves types
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Int_t           Trig_DSB;
	Double_t        Target_X;
	Double_t        Target_Y;
	Double_t        dssdEnergyCal[4][32];

	// Set branch addresses.
	tree->SetBranchAddress("RunNumber",&RunNumber);
	tree->SetBranchAddress("EventNumber",&EventNumber);
	tree->SetBranchAddress("Trig_DSB",&Trig_DSB);

	tree->SetBranchAddress("Target_X",&Target_X);
	tree->SetBranchAddress("Target_Y",&Target_Y);
	tree->SetBranchAddress("dssdEnergyCal",&dssdEnergyCal);

	
	// Left: -5.5--37.5, Right: 5.5-37.5
	TH2F *hMap=new TH2F(Form("hMap_run%d",runnum),Form("hMap_run%d",runnum),75,-37.5,37.5,32,-0.5,31.5);

	Long64_t nentries = tree->GetEntries();

	//nentries=100000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree->GetEntry(ientry);
		if(Trig_DSB){
			for(int fid=0;fid<32;fid++){
				for(int bid=0;bid<32;bid++)
				{
					double thr=5000;
					if(dssdEnergyCal[0][fid]>thr&&dssdEnergyCal[1][bid]>thr) hMap->Fill(bid-37,31-fid);
					if(dssdEnergyCal[2][fid]>thr&&dssdEnergyCal[3][bid]>thr) hMap->Fill(37-bid,31-fid);
				}
			}
		}


		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cMap=new TCanvas("cMap","cMap",1600,800);

	cMap->cd();
	hMap->Draw("colz");
	//hMap->Write();
	//cMap->Write();
	cMap->Print(Form("cMap%d.root",runnum));
}

