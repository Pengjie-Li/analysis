

int fid=15;
int bid=15;
double LLid[32][32]={-1};
double LRTid[32][32]={-1};
double LRBid[32][32]={-1};

double RRTid[32][32]={-1};
double RRBid[32][32]={-1};
double RLTid[32][32]={-1};
double RLBid[32][32]={-1};




void Load(double id[32][32],TString CsIname);

void LL(int runnum);
void LRT(int runnum);
void LRB(int runnum);
void RLT(int runnum);
void RLB(int runnum);
void RRT(int runnum);
void RRB(int runnum);





void Load(double LLid[32][32]);
void Check(int fid,int bid,double Target_X,double Target_Y,double SiLF_E[32],double SiLB_E[32],int &spixel,int &ssum);
int AreaLL(int SiLF_id,int SiLB_id);
int AreaLRT(int SiLF_id,int SiLB_id);
int AreaLRB(int SiLF_id,int SiLB_id);
int AreaRLT(int SiLF_id,int SiLB_id);
int AreaRLB(int SiLF_id,int SiLB_id);
int AreaRRT(int SiLF_id,int SiLB_id);
int AreaRRB(int SiLF_id,int SiLB_id);





void Comparison()
{
	Load(RRBid,"CsIRRB");
	RRB(598);

//	Load(RRTid,"CsIRRT");
//	RRT(597);



//	Load(RLBid,"CsIRLB");
//	RLB(598);



//	Load(RLTid,"CsIRLT");
//	RLT(598);

//	Load(LRBid,"CsILRB");
//	LRB(599);




//	Load(LRTid,"CsILRT");
//	LRT(599);

//	Load(LLid,"CsILL");
//	LL(599);




}
void Load(double id[32][32],TString CsIname)
{

	//TString parname=CsIname+"pixel_run0596.txt";
	TString parname=CsIname+"_pixel.txt";
	ifstream in;
	in.open(parname);
	//      if(!in.open(par_name))
	//      {
	//              cout<<"Error: parameter file didn't open"<<endl;
	//              cout<<par_name<<endl;
	//      }
	int fid;
	int bid;
	double k;
	double b;
	//	double  constant;
//	double  mean;
//	double  sigma;
	while (1)
	{
		//in >>fid>>bid>>constant>>mean>>sigma;
		in >>fid>>bid>>k>>b;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;

		id[fid][bid]=k;
		//cout<<"fid="<<fid<<"  bid="<<bid<<" k="<<k<<" b="<<b<<endl;
	}
	in.close();




}

void LL(int runnum)
{
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);


	int SiLFmin;
	int SiLFmax;
	int SiLBmin;
	int SiLBmax;
	if(runnum==596)
	{
		SiLFmin=5500;
		SiLFmax=8500;
		SiLBmin=5500;
		SiLBmax=8500;
	}


	else if(runnum==599)
	{

		SiLFmin=8500;
		SiLFmax=11500;
		SiLBmin=8500;
		SiLBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for LL function"<<endl;



	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d",fid,bid),Form("hpixel%d_%d",fid,bid),1400,-200,1200);
	TH1F *hpixelsum=new TH1F("hpixelsumLL","hpixelsumLL",1400,-200,1200);
	TH1F *hsum=new TH1F("hsumLL","hsumLL",1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiLF_Emax>SiLFmin&&SiLF_Emax<SiLFmax&&SiLB_Emax>SiLFmin&&SiLB_Emax<SiLFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiLF_id==fid&&SiLB_id==bid) spixel=1;
				if(AreaLL(SiLF_id,SiLB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsILL_E);
		if(ssum==1) {hpixelsum->Fill(CsILL_E);hsum->Fill(CsI_LL_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumLL","cpixelsumLL");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");
	cpixelsum->Write();
//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}

void LRT(int runnum)
{

	fid=15;
	bid=16;

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int SiLFmin;
	int SiLFmax;
	int SiLBmin;
	int SiLBmax;
	if(runnum==596)
	{
		SiLFmin=5500;
		SiLFmax=8500;
		SiLBmin=5500;
		SiLBmax=8500;
	}


	else if(runnum==599)
	{

		SiLFmin=8500;
		SiLFmax=11500;
		SiLBmin=8500;
		SiLBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for LL function"<<endl;




	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d_run%d",fid,bid,runnum),Form("hpixel%d_%d_run%d",fid,bid,runnum),1400,-200,1200);
	TH1F *hpixelsum=new TH1F(Form("hpixelsumLRT_run%d",runnum),Form("hpixelsumLRT_run%d",runnum),1400,-200,1200);
	TH1F *hsum=new TH1F(Form("hsumLRT_run%d",runnum),Form("hsumLRT_run%d",runnum),1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiLF_Emax>SiLFmin&&SiLF_Emax<SiLFmax&&SiLB_Emax>SiLFmin&&SiLB_Emax<SiLFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiLF_id==fid&&SiLB_id==bid) spixel=1;
				if(AreaLRT(SiLF_id,SiLB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsILRT_E);
		if(ssum==1) {hpixelsum->Fill(CsILRT_E);hsum->Fill(CsI_LRT_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumLRT","cpixelsumLRT");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");
	cpixelsum->Write();

//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}
void LRB(int runnum)
{

	fid=16;
	bid=16;

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int SiLFmin;
	int SiLFmax;
	int SiLBmin;
	int SiLBmax;
	if(runnum==596)
	{
		SiLFmin=5500;
		SiLFmax=8500;
		SiLBmin=5500;
		SiLBmax=8500;
	}


	else if(runnum==599)
	{

		SiLFmin=8500;
		SiLFmax=11500;
		SiLBmin=8500;
		SiLBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for LL function"<<endl;



	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d_run%d",fid,bid,runnum),Form("hpixel%d_%d_run%d",fid,bid,runnum),1400,-200,1200);
	TH1F *hpixelsum=new TH1F(Form("hpixelsumLRB_run%d",runnum),Form("hpixelsumLRB_run%d",runnum),1400,-200,1200);
	TH1F *hsum=new TH1F(Form("hsumLRB_run%d",runnum),Form("hsumLRB_run%d",runnum),1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=1000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiLF_Emax>SiLFmin&&SiLF_Emax<SiLFmax&&SiLB_Emax>SiLFmin&&SiLB_Emax<SiLFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiLF_id==fid&&SiLB_id==bid) spixel=1;
				if(AreaLRB(SiLF_id,SiLB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsILRB_E);
		if(ssum==1) {hpixelsum->Fill(CsILRB_E);hsum->Fill(CsI_LRB_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumLRB","cpixelsumLRB");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");

	cpixelsum->Write();
//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}

void RLT(int runnum)
{

	fid=15;
	bid=17;

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int SiRFmin;
	int SiRFmax;
	int SiRBmin;
	int SiRBmax;
	if(runnum==597)
	{
		SiRFmin=5500;
		SiRFmax=8500;
		SiRBmin=5500;
		SiRBmax=8500;
	}


	else if(runnum==598)
	{

		SiRFmin=8500;
		SiRFmax=11500;
		SiRBmin=8500;
		SiRBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for RLT function"<<endl;




	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d_run%d",fid,bid,runnum),Form("hpixel%d_%d_run%d",fid,bid,runnum),1400,-200,1200);
	TH1F *hpixelsum=new TH1F(Form("hpixelsumRLT_run%d",runnum),Form("hpixelsumRLT_run%d",runnum),1400,-200,1200);
	TH1F *hsum=new TH1F(Form("hsumRLT_run%d",runnum),Form("hsumRLT_run%d",runnum),1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiRF_Emax>SiRFmin&&SiRF_Emax<SiRFmax&&SiRB_Emax>SiRFmin&&SiRB_Emax<SiRFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiRF_id==fid&&SiRB_id==bid) spixel=1;
				if(AreaRLT(SiRF_id,SiRB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsIRLT_E);
		if(ssum==1) {hpixelsum->Fill(CsIRLT_E);hsum->Fill(CsI_RLT_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumRLT","cpixelsumRLT");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");
	cpixelsum->Write();

//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}
void RLB(int runnum)
{

	fid=16;
	bid=17;

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int SiRFmin;
	int SiRFmax;
	int SiRBmin;
	int SiRBmax;
	if(runnum==597)
	{
		SiRFmin=5500;
		SiRFmax=8500;
		SiRBmin=5500;
		SiRBmax=8500;
	}


	else if(runnum==598)
	{

		SiRFmin=8500;
		SiRFmax=11500;
		SiRBmin=8500;
		SiRBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for RLB function"<<endl;




	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d_run%d",fid,bid,runnum),Form("hpixel%d_%d_run%d",fid,bid,runnum),1400,-200,1200);
	TH1F *hpixelsum=new TH1F(Form("hpixelsumRLB_run%d",runnum),Form("hpixelsumRLB_run%d",runnum),1400,-200,1200);
	TH1F *hsum=new TH1F(Form("hsumRLB_run%d",runnum),Form("hsumRLB_run%d",runnum),1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiRF_Emax>SiRFmin&&SiRF_Emax<SiRFmax&&SiRB_Emax>SiRFmin&&SiRB_Emax<SiRFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiRF_id==fid&&SiRB_id==bid) spixel=1;
				if(AreaRLB(SiRF_id,SiRB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsIRLB_E);
		if(ssum==1) {hpixelsum->Fill(CsIRLB_E);hsum->Fill(CsI_RLB_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumRLB","cpixelsumRLB");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");
	cpixelsum->Write();

//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}
void RRT(int runnum)
{

	fid=15;
	bid=16;

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int SiRFmin;
	int SiRFmax;
	int SiRBmin;
	int SiRBmax;
	if(runnum==597)
	{
		SiRFmin=5500;
		SiRFmax=8500;
		SiRBmin=5500;
		SiRBmax=8500;
	}


	else if(runnum==598)
	{

		SiRFmin=8500;
		SiRFmax=11500;
		SiRBmin=8500;
		SiRBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for RRT function"<<endl;




	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d_run%d",fid,bid,runnum),Form("hpixel%d_%d_run%d",fid,bid,runnum),1400,-200,1200);
	TH1F *hpixelsum=new TH1F(Form("hpixelsumRRT_run%d",runnum),Form("hpixelsumRRT_run%d",runnum),1400,-200,1200);
	TH1F *hsum=new TH1F(Form("hsumRRT_run%d",runnum),Form("hsumRRT_run%d",runnum),1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiRF_Emax>SiRFmin&&SiRF_Emax<SiRFmax&&SiRB_Emax>SiRFmin&&SiRB_Emax<SiRFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiRF_id==fid&&SiRB_id==bid) spixel=1;
				if(AreaRRT(SiRF_id,SiRB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsIRRT_E);
		if(ssum==1) {hpixelsum->Fill(CsIRRT_E);hsum->Fill(CsI_RRT_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumRRT","cpixelsumRRT");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");
	cpixelsum->Write();

//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}
void RRB(int runnum)
{

	fid=16;
	bid=16;

	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int SiRFmin;
	int SiRFmax;
	int SiRBmin;
	int SiRBmax;
	if(runnum==597)
	{
		SiRFmin=5500;
		SiRFmax=8500;
		SiRBmin=5500;
		SiRBmax=8500;
	}


	else if(runnum==598)
	{

		SiRFmin=8500;
		SiRFmax=11500;
		SiRBmin=8500;
		SiRBmax=11500;
	}
	else cout<<"Error!!!!, find good runnum for RRB function"<<endl;




	TString inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *AnalysisTree=(TTree*)f->Get("AnalysisTree");

	//Declaration of leaves types

	TVector3 *Beam = 0;
	Int_t           RunNumber;
	Long64_t        EventNumber;
	Double_t        Target_X;
	Double_t        Target_Y;

	Double_t        Target_ThetaX;
	Double_t        Target_ThetaY;

	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	Double_t SiLF_Emax;
	Double_t SiLB_Emax;
	Double_t SiRF_Emax;
	Double_t SiRB_Emax;

	Int_t SiLF_id;
	Int_t SiLB_id;
	Int_t SiRF_id;
	Int_t SiRB_id;





	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];



	Double_t        CsI_LL_E;
	Double_t        CsI_LRT_E;
	Double_t        CsI_LRB_E;
	Double_t        CsI_RLT_E;
	Double_t        CsI_RLB_E;
	Double_t        CsI_RRT_E;
	Double_t        CsI_RRB_E;

	Double_t        CsILL_E;
	Double_t        CsILRT_E;
	Double_t        CsILRB_E;
	Double_t        CsIRLT_E;
	Double_t        CsIRLB_E;
	Double_t        CsIRRT_E;
	Double_t        CsIRRB_E;



	// Set branch addresses.
	AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
	AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);
	AnalysisTree->SetBranchAddress("Target_X",&Target_X);
	AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
	AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
	AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

	AnalysisTree->SetBranchAddress("Beam",&Beam);

	AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
	AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
	AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
	AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

	AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
	AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
	AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
	AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
	AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
	AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
	AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

	AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
	AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
	AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
	AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
	AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
	AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
	AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

	AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
	AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);

	AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
	AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);




	AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
	AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
	AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
	AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);





	TH1F *hpixel=new TH1F(Form("hpixel%d_%d_run%d",fid,bid,runnum),Form("hpixel%d_%d_run%d",fid,bid,runnum),1400,-200,1200);
	TH1F *hpixelsum=new TH1F(Form("hpixelsumRRB_run%d",runnum),Form("hpixelsumRRB_run%d",runnum),1400,-200,1200);
	TH1F *hsum=new TH1F(Form("hsumRRB_run%d",runnum),Form("hsumRRB_run%d",runnum),1400,-200,1200);

	Long64_t nentries = AnalysisTree->GetEntries();

	//nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int spixel=-1;
		int ssum=-1;

		if(SiRF_Emax>SiRFmin&&SiRF_Emax<SiRFmax&&SiRB_Emax>SiRFmin&&SiRB_Emax<SiRFmax)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if(SiRF_id==fid&&SiRB_id==bid) spixel=1;
				if(AreaRRB(SiRF_id,SiRB_id)) ssum=1;

			}


		}

		//cout<<spixel<<endl;
		if(spixel==1&&ssum==1) hpixel->Fill(CsIRRB_E);
		if(ssum==1) {hpixelsum->Fill(CsIRRB_E);hsum->Fill(CsI_RRB_E);}

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cpixel=new TCanvas(Form("cpixel%d_%d",fid,bid),Form("cpixel%d_%d",fid,bid));
	cpixel->cd();
	hpixel->Draw();
	cpixel->Write();

	TCanvas *cpixelsum=new TCanvas("cpixelsumRRB","cpixelsumRRB");
	cpixelsum->cd();
	hpixelsum->Draw();
	hsum->SetLineColor(2);
	hsum->Draw("same");
	cpixelsum->Write();

//	TCanvas *csum=new TCanvas("csumLL","csumLL");
//	csum->cd();
	//hsum->Draw();




}
int AreaLL(int fid,int bid)
{
	if(LLid[fid][bid]>0) return 1;
	return 0;
}

int AreaLRT(int fid,int bid)
{
	if(LRTid[fid][bid]>0) return 1;
	return 0;
}

int AreaLRB(int fid,int bid)
{
	if(LRBid[fid][bid]>0) return 1;
	return 0;
}

int AreaRLT(int fid,int bid)
{
	if(RLTid[fid][bid]>0) return 1;
	return 0;
}

int AreaRLB(int fid,int bid)
{
	if(RLBid[fid][bid]>0) return 1;
	return 0;
}
int AreaRRT(int fid,int bid)
{
	if(RRTid[fid][bid]>0) return 1;
	return 0;
}

int AreaRRB(int fid,int bid)
{
	if(RRBid[fid][bid]>0) return 1;
	return 0;
}
void Check(int fid,int bid,double Target_X,double Target_Y,double SiLF_E[32],double SiLB_E[32],int &spixel,int &ssum)
{


	double pixelF=SiLF_E[fid];
	double pixelB=SiLB_E[bid];

	if(pixelF>5500&&pixelF<8500&&pixelB>5500&&pixelB<8500)
	{
		if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
		{
			spixel=1;

		}

	}





}


