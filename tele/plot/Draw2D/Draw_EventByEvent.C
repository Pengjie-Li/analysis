//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void Draw_EventByEvent(){ 

	//int runnum=436;
	//int runnum=340;
	int runnum=310;
	int iEventNumber = 24;
	Draw_2DRaw(runnum,iEventNumber);

}

void Draw_2DRaw(int runnum,int iEventNumber){
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int dDSSD=1;
	TString inputname=Form("./rootfiles/run0%d/run0%d_SILICONS.root",runnum,runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *tree_BEAM=(TTree*)f->Get("CalTreeSILICONS");



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

	TH2F *hDSSDRaw[4];
	TH2F *hDSSDCal[4];
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

		TString hNameRaw="h"+name+"Raw";
		TString hNameCal="h"+name+"Cal";
		hDSSDRaw[i]=new TH2F(hNameRaw,hNameRaw,32,-0.5,31.5,4100,-0.5,4099.5);
		hDSSDCal[i]=new TH2F(hNameCal,hNameCal,32,-0.5,31.5,1000,0.5,30000.5);

		hDSSDRaw[i]->SetContour(5);
		hDSSDCal[i]->SetContour(5);
	}

	Long64_t nentries = tree_BEAM->GetEntries();

	double k[4][32]={0};
	double b[4][32]={0};

	double ek[4][32]={0};
	double eb[4][32]={0};

	Load(k,b,ek,eb);


	double kl=7.17797775;
	double bl=-1524.240925;
	double kr=7.685283145;
	double br=-1646.273395;

	nentries=100000;
		tree_BEAM->GetEntry(iEventNumber);

		if(dDSSD==1){
			for(int id=0;id<32;id++)
			{
                                double lfraw=(*SiLF_rawADC)[id];
                                double lbraw=(*SiLB_rawADC)[id];
				double rfraw=(*SiRF_rawADC)[id];
                                double rbraw=(*SiRB_rawADC)[id];

                                double lfscm=k[0][id]*lfraw+b[0][id];
				double lbscm=k[1][id]*lbraw+b[1][id];
				double lfcal=kl*lfscm+bl;
				double lbcal=kl*lbscm+bl;

				double rfscm=k[2][id]*rfraw+b[2][id];
				double rbscm=k[3][id]*rbraw+b[3][id];
				double rfcal=kr*rfscm+br;
				double rbcal=kr*rbscm+br;
	

	
				
				//cout<<fscm<<"  "<<bscm<<endl;
				hDSSDRaw[0]->Fill(id,lfraw);
				hDSSDRaw[1]->Fill(id,lbraw);
				hDSSDRaw[2]->Fill(id,rfraw);
				hDSSDRaw[3]->Fill(id,rbraw);

				hDSSDCal[0]->Fill(id,lfcal);
				hDSSDCal[1]->Fill(id,lbcal);
				hDSSDCal[2]->Fill(id,rfcal);
				hDSSDCal[3]->Fill(id,rbcal);



			}
		}


	TCanvas *cDSSDRaw=new TCanvas("cDSSDRaw","cDSSDRaw",1400,800);

	if(dDSSD==1) draw_and_write(cDSSDRaw,hDSSDRaw);
	TCanvas *cDSSDCal=new TCanvas("cDSSDCal","cDSSDCal",1400,800);

	if(dDSSD==1) draw_and_write(cDSSDCal,hDSSDCal);




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
void Load(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32])
{
        ifstream in;
        TString par_name;

        par_name="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/Remove/DSSD_Fit_Whole.txt";
	in.open(par_name);
	//      if(!in.open(par_name))
	//      {
	//              cout<<"Error: parameter file didn't open"<<endl;
	//              cout<<par_name<<endl;
	//      }
	int side;
	int strip;
	double  k0;
	double  b0;
	double ek0;
	double eb0;
	while (1)
	{
		in >>side>>strip>>k0>>b0>>ek0>>eb0;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;


		k[side][strip]=k0;
		ek[side][strip]=ek0;

		b[side][strip]=b0;
		eb[side][strip]=eb0;

	}
}
