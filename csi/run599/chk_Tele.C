//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////



void chk_Tele(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int dDSSD=1;
	int dCsI=1;
	int dMap=1;
	int dMapCsI=1;
	TString inputname="./rootfiles/run0598_Beamv8.root";
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *tree_BEAM=(TTree*)f->Get("tree_BEAM");



	//Declaration of leaves types
	vector<double>  *SiLF_rawADC;
	vector<double>  *SiLB_rawADC;
	vector<double>  *SiRF_rawADC;
	vector<double>  *SiRB_rawADC;
	vector<double>  *SiLF_rawTDC;
	vector<double>  *SiLB_rawTDC;
	vector<double>  *SiRF_rawTDC;
	vector<double>  *SiRB_rawTDC;
	Double_t        CsILL_rawADC;
	Double_t        CsILRT_rawADC;
	Double_t        CsILRB_rawADC;
	Double_t        CsIRLT_rawADC;
	Double_t        CsIRLB_rawADC;
	Double_t        CsIRRT_rawADC;
	Double_t        CsIRRB_rawADC;
	Double_t        CsILL_rawTDC;
	Double_t        CsILRT_rawTDC;
	Double_t        CsILRB_rawTDC;
	Double_t        CsIRLT_rawTDC;
	Double_t        CsIRLB_rawTDC;
	Double_t        CsIRRT_rawTDC;
	Double_t        CsIRRB_rawTDC;

	tree_BEAM->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
	tree_BEAM->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
	tree_BEAM->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
	tree_BEAM->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);
	tree_BEAM->SetBranchAddress("SiLF_rawTDC",&SiLF_rawTDC);
	tree_BEAM->SetBranchAddress("SiLB_rawTDC",&SiLB_rawTDC);
	tree_BEAM->SetBranchAddress("SiRF_rawTDC",&SiRF_rawTDC);
	tree_BEAM->SetBranchAddress("SiRB_rawTDC",&SiRB_rawTDC);
	tree_BEAM->SetBranchAddress("CsILL_rawADC",&CsILL_rawADC);
	tree_BEAM->SetBranchAddress("CsILRT_rawADC",&CsILRT_rawADC);
	tree_BEAM->SetBranchAddress("CsILRB_rawADC",&CsILRB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLT_rawADC",&CsIRLT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLB_rawADC",&CsIRLB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRT_rawADC",&CsIRRT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRB_rawADC",&CsIRRB_rawADC);
	tree_BEAM->SetBranchAddress("CsILL_rawTDC",&CsILL_rawTDC);
	tree_BEAM->SetBranchAddress("CsILRT_rawTDC",&CsILRT_rawTDC);
	tree_BEAM->SetBranchAddress("CsILRB_rawTDC",&CsILRB_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRLT_rawTDC",&CsIRLT_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRLB_rawTDC",&CsIRLB_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRRT_rawTDC",&CsIRRT_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRRB_rawTDC",&CsIRRB_rawTDC);

	TH2F *hDSSD[4];
	TH2F *hCsI=new TH2F("hCsI","CsI",7,-0.5,6.5,4100,0,4100);
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
		hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,4100,0,4100);
		hDSSD[i]->SetContour(5);
	}
	// Left: -5.5--37.5, Right: 5.5-37.5
	TH2F *hMap=new TH2F("hMap","Map",75,-37.5,37.5,32,-0.5,31.5);
	TH2F *hMapCsI=new TH2F("hMapCsI","MapCsI",5,-2.5,2.5,2,-1,1);

	Long64_t nentries = tree_BEAM->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree_BEAM->GetEntry(ientry);

		if(dDSSD==1){
			for(int id=0;id<32;id++)
			{
				hDSSD[0]->Fill(id,(*SiLF_rawADC)[id]);
				hDSSD[1]->Fill(id,(*SiLB_rawADC)[id]);
				hDSSD[2]->Fill(id,(*SiRF_rawADC)[id]);
				hDSSD[3]->Fill(id,(*SiRB_rawADC)[id]);
			}
		}
		if(dCsI==1){

			hCsI->Fill(0,CsILL_rawADC);
			hCsI->Fill(1,CsILRT_rawADC);
			hCsI->Fill(2,CsILRB_rawADC);
			hCsI->Fill(3,CsIRLT_rawADC);
			hCsI->Fill(4,CsIRLB_rawADC);
			hCsI->Fill(5,CsIRRT_rawADC);
			hCsI->Fill(6,CsIRRB_rawADC);
		}
		if(dMap==1){

			for(int fid=0;fid<32;fid++)
				for(int bid=0;bid<32;bid++)
				{

					if((*SiLF_rawADC)[fid]>1000&&(*SiLB_rawADC)[bid]>1000) hMap->Fill(bid-37,31-fid);
					if((*SiRF_rawADC)[fid]>1000&&(*SiRB_rawADC)[bid]>1000) hMap->Fill(37-bid,31-fid);

				}
		}
		if(dMapCsI==1){

			if(CsILL_rawADC>1000) { hMapCsI->Fill(-2,-0.5);  hMapCsI->Fill(-2,0.5); }
			if(CsILRT_rawADC>1000) { hMapCsI->Fill(-1,0.5); }
			if(CsILRB_rawADC>1000) { hMapCsI->Fill(-1,-0.5); }
			if(CsIRLT_rawADC>1000) { hMapCsI->Fill(1,0.5); }
			if(CsIRLB_rawADC>1000) { hMapCsI->Fill(1,-0.5); }
			if(CsIRRT_rawADC>1000) { hMapCsI->Fill(2,0.5); }
			if(CsIRRB_rawADC>1000) { hMapCsI->Fill(2,-0.5); }



		}



		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSD=new TCanvas("cDSSD","cDSSD",800,800);
	TCanvas *cCsI=new TCanvas("cCsI","cCsI",800,800);
	TCanvas *cMap=new TCanvas("cMap","cMap",1600,800);
	TCanvas *cMapCsI=new TCanvas("cMapCsI","cMapCsI",1600,800);

	if(dDSSD==1) draw_and_write(cDSSD,hDSSD);

	if(dCsI==1){
		cCsI->cd();
		hCsI->Draw("colz");
		hCsI->Write();
		cCsI->Write();
	}

	if(dMap==1){
		cMap->cd();
		hMap->Draw("colz");
		hMap->Write();
		cMap->Write();
	}

	if(dMapCsI==1){
		cMapCsI->cd();
		hMapCsI->Draw("colz");
		hMapCsI->Write();
		cMapCsI->Write();
	}


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

