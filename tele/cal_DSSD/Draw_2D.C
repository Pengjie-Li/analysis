//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void Draw_2D(){ 

	//int runnum=436;
	//int runnum=340;
	//int runnum=596;
	//int runnum=597;
	//int runnum=598;
	int runnum=599;
	//int runnum=300;
	Draw_2DRaw(runnum);
}

void Draw_2DRaw(int runnum){
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	TString filename=Form("run%d_checking_calibration_v8.root",runnum);
	//TString filename=Form("run%d_checking_calibration_v3.root",runnum);
	//TString filename=Form("run%d_checking_calibration.root",runnum);
	TFile *f = new TFile(filename,"UPDATE");
	TTree *tree=f->Get("tree");

	//Declaration of leaves types
	Double_t        SiLF_ADC[32];
	Double_t        SiLB_ADC[32];
	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_ADC[32];
	Double_t        SiRB_ADC[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	// Set branch addresses.
	tree->SetBranchAddress("SiLF_ADC",SiLF_ADC);
	tree->SetBranchAddress("SiLB_ADC",SiLB_ADC);
	tree->SetBranchAddress("SiLF_SCM",SiLF_SCM);
	tree->SetBranchAddress("SiLB_SCM",SiLB_SCM);
	tree->SetBranchAddress("SiLF_E",SiLF_E);
	tree->SetBranchAddress("SiLB_E",SiLB_E);
	tree->SetBranchAddress("SiRF_ADC",SiRF_ADC);
	tree->SetBranchAddress("SiRB_ADC",SiRB_ADC);
	tree->SetBranchAddress("SiRF_SCM",SiRF_SCM);
	tree->SetBranchAddress("SiRB_SCM",SiRB_SCM);
	tree->SetBranchAddress("SiRF_E",SiRF_E);
	tree->SetBranchAddress("SiRB_E",SiRB_E);


	int dDSSD=1;
	TH2F *hDSSDL[6];
	TH2F *hDSSDR[6];
	TH2F *hRef=new TH2F("hRef","Check Cal Strip vs Ref Strip",4100,0,4100,4100,0,4100);
	for(int i=0;i<6;i++)
	{
		TString namel;
		switch(i)
		{
			case 0: {namel="SiLFCal"; break;}
			case 1: {namel="SiLBCal"; break;}
			case 2: {namel="SiLFScm"; break;}
			case 3: {namel="SiLBScm"; break;}
			case 4: {namel="SiLFRaw"; break;}
			case 5: {namel="SiLBRaw"; break;}
			default: exit(0);
		}

		TString hnamel="h"+namel;
		if(i>1) hDSSDL[i]=new TH2F(hnamel,namel,32,-0.5,31.5,4100,-0.5,4099.5);
		else hDSSDL[i]=new TH2F(hnamel,namel,32,-0.5,31.5,3500,0,35000);

		hDSSDL[i]->SetContour(5);

		TString namer;
		switch(i)
		{
			case 0: {namer="SiRFCal"; break;}
			case 1: {namer="SiRBCal"; break;}
			case 2: {namer="SiRFScm"; break;}
			case 3: {namer="SiRBScm"; break;}
			case 4: {namer="SiRFRaw"; break;}
			case 5: {namer="SiRBRaw"; break;}
			default: exit(0);
		}

		TString hnamer="h"+namer;
		if(i>1) hDSSDR[i]=new TH2F(hnamer,namer,32,-0.5,31.5,4100,-0.5,4099.5);
		else hDSSDR[i]=new TH2F(hnamer,namer,32,-0.5,31.5,3500,0,35000);

		hDSSDR[i]->SetContour(5);
	
	}

	Long64_t nentries = tree->GetEntries();


	//nentries=100000;
	//nentries=10;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree->GetEntry(ientry);

			for(int id=0;id<32;id++)
			{
				hDSSDL[0]->Fill(id,SiLF_E[id]);
				hDSSDL[1]->Fill(id,SiLB_E[id]);
				hDSSDL[2]->Fill(id,SiLF_SCM[id]);
				hDSSDL[3]->Fill(id,SiLB_SCM[id]);
				hDSSDL[4]->Fill(id,SiLF_ADC[id]);
				hDSSDL[5]->Fill(id,SiLB_ADC[id]);

				hDSSDR[0]->Fill(id,SiRF_E[id]);
				hDSSDR[1]->Fill(id,SiRB_E[id]);
				hDSSDR[2]->Fill(id,SiRF_SCM[id]);
				hDSSDR[3]->Fill(id,SiRB_SCM[id]);
				hDSSDR[4]->Fill(id,SiRF_ADC[id]);
				hDSSDR[5]->Fill(id,SiRB_ADC[id]);
	
			
			}
		
		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSDL=new TCanvas("cDSSDL","cDSSDL",800,800);

	draw_and_write(cDSSDL,hDSSDL);

	TCanvas *cDSSDR=new TCanvas("cDSSDR","cDSSDR",800,800);

	draw_and_write(cDSSDR,hDSSDR);



}
void draw_and_write(TCanvas *c,TH2F *h[6])
{

	c->Divide(2,3);
	for(int i=0;i<6;i++)
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

