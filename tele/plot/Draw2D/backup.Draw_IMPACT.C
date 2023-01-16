//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////



void Draw_IMPACT(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int dDSSD=1;
	int dCsI=1;
	int dMap=1;
	int dMapCsI=1;

	int runnum=599;
	//int runnum=596;
	//int runnum=597;
	//int runnum=598;
	//int runnum=595;

	TString inputname=Form("rootfiles/run0%d_analysed.root_1",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
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
		hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,1000,0,35000);
		hDSSD[i]->SetContour(5);
	}
	// Left: -5.5--37.5, Right: 5.5-37.5
	TH2F *hMap=new TH2F(Form("hMap_run%d",runnum),Form("hMap_run%d",runnum),75,-37.5,37.5,32,-0.5,31.5);
	TH2F *hMapCsI=new TH2F("hMapCsI","MapCsI",5,-2.5,2.5,2,-1,1);

	TH2F *hDim=new TH2F("hDim","Dimension",75,-75,75,32,-1,63);

	Long64_t nentries = AnalysisTree->GetEntries();

	nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);
		//if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.10)*(Target_Y+1.10))<12.1&&sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.10)*(Target_Y+1.10))>11.9)
//		if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.10)*(Target_Y+1.10))<15)
		{

			if(dDSSD==1){
				for(int id=0;id<32;id++)
				{
					hDSSD[0]->Fill(id,SiLF_E[id]);
					hDSSD[1]->Fill(id,SiLB_E[id]);
					hDSSD[2]->Fill(id,SiRF_E[id]);
					hDSSD[3]->Fill(id,SiRB_E[id]);
				}
			}
			if(dCsI==1){

				hCsI->Fill(0,CsI_LL_ADC);
				hCsI->Fill(1,CsI_LRT_ADC);
				hCsI->Fill(2,CsI_LRB_ADC);
				hCsI->Fill(3,CsI_RLT_ADC);
				hCsI->Fill(4,CsI_RLB_ADC);
				hCsI->Fill(5,CsI_RRT_ADC);
				hCsI->Fill(6,CsI_RRB_ADC);
			}
			if(dMap==1){

				for(int fid=0;fid<32;fid++)
					for(int bid=0;bid<32;bid++)
					{
                                                double thr=5000;

						if(SiLF_E[fid]>thr&&SiLB_E[bid]>thr) hMap->Fill(bid-37,31-fid);
						if(SiRF_E[fid]>thr&&SiRB_E[bid]>thr) hMap->Fill(37-bid,31-fid);

						if(SiLF_E[fid]>thr&&SiLB_E[bid]>thr) hDim->Fill(2*(bid-37),2*(31-fid));
						if(SiRF_E[fid]>thr&&SiRB_E[bid]>thr) hDim->Fill(2*(37-bid),2*(31-fid));



					}
			}
			if(dMapCsI==1){

				if(CsI_LL_ADC>1000) { hMapCsI->Fill(-2,-0.5);  hMapCsI->Fill(-2,0.5); }
				if(CsI_LRT_ADC>1000) { hMapCsI->Fill(-1,0.5); }
				if(CsI_LRB_ADC>1000) { hMapCsI->Fill(-1,-0.5); }
				if(CsI_RLT_ADC>1000) { hMapCsI->Fill(1,0.5); }
				if(CsI_RLB_ADC>1000) { hMapCsI->Fill(1,-0.5); }
				if(CsI_RRT_ADC>1000) { hMapCsI->Fill(2,0.5); }
				if(CsI_RRB_ADC>1000) { hMapCsI->Fill(2,-0.5); }



			}


		}

		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSD=new TCanvas("cDSSD","cDSSD",800,800);
	TCanvas *cCsI=new TCanvas("cCsI","cCsI",800,800);
	TCanvas *cMap=new TCanvas("cMap","cMap",1600,800);
	TCanvas *cMapCsI=new TCanvas("cMapCsI","cMapCsI",1600,800);

	TCanvas *cDim=new TCanvas("cDim","cDim",1600,800);

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

		cDim->cd();
		hDim->Draw("colz");
		hDim->Write();
		cDim->Write();

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

