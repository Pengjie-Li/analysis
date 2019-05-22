//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void Draw_2D(){ 

	//int runnum=436;
	int runnum=300;
	//int runnum=340;
	//int runnum=596;
	//int runnum=436;
	//int runnum=597;
	Draw_2DCal(runnum);
}

void Draw_2DCal(int runnum){
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int dDSSD=1;
	TString inputname=Form("./analysedrootfiles/run0%d_analysed_v1.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");


	Double_t        SiLF_E[32];
	Double_t        SiLF_T[32];
	Double_t        SiLB_E[32];
	Double_t        SiLB_T[32];
	Double_t        SiRF_E[32];
	Double_t        SiRF_T[32];
	Double_t        SiRB_E[32];
	Double_t        SiRB_T[32];

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLF_T",SiLF_T);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiLB_T",SiLB_T);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRF_T",SiRF_T);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);
	AnalysisTree->SetBranchAddress("SiRB_T",SiRB_T);

	TH2F *hDSSD[4];
	for(int i=0;i<4;i++)
	{
		TString name;
		switch(i)
		{
			case 0: {name="SiLFCal"; break;}
			case 1: {name="SiLBCal"; break;}
			case 2: {name="SiRFCal"; break;}
			case 3: {name="SiRBCal"; break;}
			
			default: exit(0);
		}

		TString hname="h"+name;
		hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,3500,0,35000);

		hDSSD[i]->SetContour(5);
	}

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=100000;
	//nentries=10;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes +=  AnalysisTree->GetEntry(ientry);

		for(int id=0;id<32;id++)
		{
			double lfcal=SiLF_E[id];
			double lbcal=SiLB_E[id];

			hDSSD[0]->Fill(id,lfcal);
			hDSSD[1]->Fill(id,lbcal);

			double rfcal=SiRF_E[id];
			double rbcal=SiRB_E[id];
			hDSSD[2]->Fill(id,rfcal);
			hDSSD[3]->Fill(id,rbcal);
	
		}

		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSD=new TCanvas("cDSSD","cDSSD",800,800);


	if(dDSSD==1) draw_and_write(cDSSD,hDSSD);


}

void draw_and_write(TCanvas *c,TH2F *h[4])
{

	c->Divide(2,2);
	for(int i=0;i<4;i++)
	{
		c->cd(i+1);
		h[i]->Draw("colz");
		if(gPad) gPad->SetLogz();
		h[i]->SetMaximum(1e3);
		h[i]->SetMinimum(1);

		gPad->Update();
		TPaletteAxis *palette = (TPaletteAxis*)h[i]->GetListOfFunctions()->FindObject("palette");
		// the following lines move the palette. Choose the values you need for the position.

		gPad->Modified();
		gPad->Update();
		h[i]->Write();
	}

	c->Write();
	//tree->Write();

}

