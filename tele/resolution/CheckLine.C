//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void CheckLine(){ 

	//int runnum=436;
	//int runnum=340;
	int runnum=300;
	Draw_2DRaw(runnum);
}

void Draw_2DRaw(int runnum){
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

	TH2F *hDSSD[6];
	TH2F *hRef=new TH2F("hRef","Check Cal Strip vs Ref Strip",4100,0,4100,4100,0,4100);
	for(int i=0;i<6;i++)
	{
		TString name;
		switch(i)
		{
			case 0: {name="SiLFCal"; break;}
			case 1: {name="SiLBCal"; break;}
			case 2: {name="SiLFScm"; break;}
			case 3: {name="SiLBScm"; break;}
			case 4: {name="SiLFRaw"; break;}
			case 5: {name="SiLBRaw"; break;}
			default: exit(0);
		}

		TString hname="h"+name;
		if(i>1) hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,4100,-0.5,4099.5);
		else hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,3500,0,35000);

		hDSSD[i]->SetContour(5);
	}

	Long64_t nentries = tree_BEAM->GetEntries();

	double k[4][32]={0};
	double b[4][32]={0};

	double ek[4][32]={0};
	double eb[4][32]={0};

	Load(k,b,ek,eb);

	double kb=7.11443;
	double bb=-1719.02;
	double kf=7.64654;
	double bf=-1600.15;
	//nentries=100000;
	//nentries=10;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree_BEAM->GetEntry(ientry);
		int Refid=15;
		hDSSD[0]->Fill(k[0][Refid]*(*SiLF_rawADC)[Refid]+b[0][Refid],(*SiLB_rawADC)[15]);
		hDSSD[1]->Fill(kf*(k[0][Refid]*(*SiLF_rawADC)[Refid]+b[0][Refid])+bf,kb*(*SiLB_rawADC)[15]+bb);


		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSD=new TCanvas("cDSSD","cDSSD",800,800);
	TCanvas *cRef=new TCanvas("cRef","cRef",800,800);

	cRef->cd();
	gPad->SetGridx();
	gPad->SetGridy();
	hRef->Draw("colz");

	if(dDSSD==1) draw_and_write(cDSSD,hDSSD);


}
void Load(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32])
{
	ifstream in;
	//TString par_name=Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/runs/run%d_scm_par.txt",runnum);
	TString par_name="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/runs/DSSD_SCM_Left.txt";
	if(!in.open(par_name))
	{
		cout<<"Error: parameter file didn't open"<<endl;
		cout<<par_name<<endl;
	}
	int side;
	int strip;
	double  k0;
	double  b0;
	double ek0;
	double eb0;
	while (1)
	{
		in >>side>>strip>>k0>>b0>>ek0>>eb0;
		cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;


		k[side][strip]=k0;
		ek[side][strip]=ek0;

		b[side][strip]=b0;
		eb[side][strip]=eb0;

	}
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

