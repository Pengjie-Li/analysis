//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////



void drawCsiEnergyVsId(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);
	//int runnum=340;
	//int runnum=596;
	//int runnum=597;
	//int runnum=598;
	//int runnum=595;

	//TString inputname=Form("rootfiles/run0%d_analysed.root_1",runnum);
	TString inputname=Form("rootfiles/run0%d_analysed.root_2",runnum);
	TFile *f = new TFile(inputname,"READ");
	TTree *AnalysisTree=(TTree*)f->Get("tree");

	//Declaration of leaves types
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;
	Double_t        dssdEnergyCal[4][32];
	Double_t        csiEnergyCal[7];

	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);


	AnalysisTree->SetBranchAddress("dssdEnergyCal",&dssdEnergyCal);
	AnalysisTree->SetBranchAddress("csiEnergyCal",&csiEnergyCal);




	TH2F *hCsI=new TH2F("hCsI","CsI",7,-0.5,6.5,4100,0,4100);
	Long64_t nentries = AnalysisTree->GetEntries();

	nentries=100000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

			for (int i = 0; i < 7; ++i) {
				hCsI->Fill(i,csiEnergyCal[i]);

			}

			if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cCsI=new TCanvas("cCsI","cCsI",800,800);
	hCsI->Draw("colz");
	cCsI->Print(Form("cCsI%d.root",runnum));
}
