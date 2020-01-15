//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////



void draw_and_write(TCanvas *c,TH2F *h[4]);
void drawDssdEnergyVsId(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);
	//int runnum=310;
	//int runnum=340;
	//int runnum=380;
	int runnum=400;
	//int runnum=596;
	//int runnum=597;
	//int runnum=598;
	//int runnum=595;

	TString inputname=Form("rootfiles/run0%d_analysed.root",runnum);
	TFile *f = new TFile(inputname,"READ");
	TTree *AnalysisTree=(TTree*)f->Get("tree");

	//TChain *tree = new TChain("tree");
	//tree->Add("rootfiles/run0596_analysed.root");
	//tree->Add("rootfiles/run0597_analysed.root");
	//tree->Add("rootfiles/run0598_analysed.root");
	//tree->Add("rootfiles/run0599_analysed.root");

	//Declaration of leaves types
	Int_t           RunNumber;
	Long64_t        EventNumber;
	TVector3 	*vTarget;
	Double_t        Target_X;
	Double_t        Target_Y;
	Int_t        dssdQRaw[4][32];

	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("vTarget",&vTarget);


	AnalysisTree->SetBranchAddress("dssdQRaw",&dssdQRaw);




	TH2F *hDSSD[4];
	for(int i=0;i<4;i++)
	{
		TString name;
		switch(i)
		{
			case 0: {name="SiLF"; break;}
			case 1: {name="SiLB"; break;}
			case 2: {name="SiRF"; break;}
			case 3: {name="SiRB"; break;}
			default: exit(0);
		}

		TString hname="h"+name;
		hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,1024,0,4096);
		hDSSD[i]->SetContour(5);
	}
	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=100000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

			for (int i = 0; i < 4; ++i) {

				for(int id=0;id<32;id++)
				{
					hDSSD[i]->Fill(id,dssdQRaw[i][id]);
				}
			}
			if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSD=new TCanvas("cDSSD","cDSSD",1400,900);
	draw_and_write(cDSSD,hDSSD);
	cDSSD->Print(Form("cDSSD%d.root",runnum));
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
		//h[i]->Write();
	}

	//c->Write();
	//tree->Write();

}

