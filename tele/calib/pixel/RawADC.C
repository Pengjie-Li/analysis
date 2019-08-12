

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



void Load(double LLid[32][32]);
void Check(int fid,int bid,double Target_X,double Target_Y,double SiLF_E[32],double SiLB_E[32],int &spixel,int &ssum);
int AreaLL(int SiLF_id,int SiLB_id);
int AreaLRT(int SiLF_id,int SiLB_id);
int AreaLRB(int SiLF_id,int SiLB_id);
int AreaRLT(int SiLF_id,int SiLB_id);
int AreaRLB(int SiLF_id,int SiLB_id);
int AreaRRT(int SiLF_id,int SiLB_id);
int AreaRRB(int SiLF_id,int SiLB_id);

void RawADC(int runnum, TString side);
void Draw(int runnum, TString side);




void RawADC()
{

	//int runnum=596;
	//int runnum=599;
	int runnum=598;
	//TString side="Left";
	TString side="Right";
	RawADC(runnum,side);

}
void RawADC(int runnum, TString side)
{
	if(side=="Left") 
	{

		Load(LLid,"CsILL");
		Load(LRTid,"CsILRT");
		Load(LRBid,"CsILRB");
	}

	else if(side=="Right")
	{

		Load(RLTid,"CsIRLT");
		Load(RLBid,"CsIRLB");

		Load(RRTid,"CsIRRT");
		Load(RRBid,"CsIRRB");

	}
	else cout<<"Error! Side option: Left or Right"<<endl;

	Draw(runnum, side);



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

void Draw(int runnum,TString side)
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

	Double_t         CsI_LL_ADC;
	Double_t        CsI_LRT_ADC;
	Double_t        CsI_LRB_ADC;
	Double_t        CsI_RLT_ADC;
	Double_t        CsI_RLB_ADC;
	Double_t        CsI_RRT_ADC;
	Double_t        CsI_RRB_ADC;



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

	AnalysisTree->SetBranchAddress("CsI_LL_ADC",&CsI_LL_ADC);
	AnalysisTree->SetBranchAddress("CsI_LRT_ADC",&CsI_LRT_ADC);
	AnalysisTree->SetBranchAddress("CsI_LRB_ADC",&CsI_LRB_ADC);
	AnalysisTree->SetBranchAddress("CsI_RLT_ADC",&CsI_RLT_ADC);
	AnalysisTree->SetBranchAddress("CsI_RLB_ADC",&CsI_RLB_ADC);
	AnalysisTree->SetBranchAddress("CsI_RRT_ADC",&CsI_RRT_ADC);
	AnalysisTree->SetBranchAddress("CsI_RRB_ADC",&CsI_RRB_ADC);


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


	int keyLL=0;
	int keyLRT=0;
	int keyLRB=0;

	int keyRLT=0;
	int keyRLB=0;
	int keyRRT=0;
	int keyRRB=0;

	if(side=="Left"){
		keyLL=1;
		keyLRT=1;
		keyLRB=1;
	}
	else if(side=="Right"){
		keyRLT=1;
		keyRLB=1;
		keyRRT=1;
		keyRRB=1;
	}
	else {cout<<"Input: Left or Right for side"<<endl;}


	TH1F *hRawADCLL=new TH1F(Form("hRawADCLL_%d",runnum),Form("hRawADCLL_%d",runnum),1200,0,2400);
	TH1F *hRawADCLRT=new TH1F(Form("hRawADCLRT_%d",runnum),Form("hRawADCLRT_%d",runnum),1200,0,2400);
	TH1F *hRawADCLRB=new TH1F(Form("hRawADCLRB_%d",runnum),Form("hRawADCLRB_%d",runnum),1200,0,2400);

	TH1F *hRawADCRLT=new TH1F(Form("hRawADCRLT_%d",runnum),Form("hRawADCRLT_%d",runnum),1200,0,2400);
	TH1F *hRawADCRLB=new TH1F(Form("hRawADCRLB_%d",runnum),Form("hRawADCRLB_%d",runnum),1200,0,2400);
	TH1F *hRawADCRRT=new TH1F(Form("hRawADCRRT_%d",runnum),Form("hRawADCRRT_%d",runnum),1200,0,2400);
	TH1F *hRawADCRRB=new TH1F(Form("hRawADCRRB_%d",runnum),Form("hRawADCRRB_%d",runnum),1200,0,2400);






	Long64_t nentries = AnalysisTree->GetEntries();

//	nentries=10000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += AnalysisTree->GetEntry(ientry);

		int sLL=-1;
		int sLRT=-1;
		int sLRB=-1;

		int sRLT=-1;
		int sRLB=-1;
		int sRRT=-1;
		int sRRB=-1;





		bool b1=false;
		if(side=="Left") b1=(SiLF_Emax>SiLFmin&&SiLF_Emax<SiLFmax&&SiLB_Emax>SiLFmin&&SiLB_Emax<SiLFmax);
		if(side=="Right") b1=(SiRF_Emax>SiRFmin&&SiRF_Emax<SiRFmax&&SiRB_Emax>SiRFmin&&SiRB_Emax<SiRFmax);
                //cout<<b1<<endl;
		if(b1)
		{
			if(sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))<14)
			{
				if((keyLL==1)&&AreaLL(SiLF_id,SiLB_id)) sLL=1;
				if((keyLRT==1)&&AreaLRT(SiLF_id,SiLB_id)) sLRT=1;
				if((keyLRB==1)&&AreaLRB(SiLF_id,SiLB_id)) sLRB=1;

				if((keyRLT==1)&&AreaRLT(SiRF_id,SiRB_id)) sRLT=1;
				if((keyRLB==1)&&AreaRLB(SiRF_id,SiRB_id)) sRLB=1;
				if((keyRRT==1)&&AreaRRT(SiRF_id,SiRB_id)) sRRT=1;
				if((keyRRB==1)&&AreaRRB(SiRF_id,SiRB_id)) sRRB=1;

			}


		}

		//cout<<spixel<<endl;
		if(sLL==1)  hRawADCLL->Fill(CsI_LL_ADC);
		if(sLRT==1) hRawADCLRT->Fill(CsI_LRT_ADC);
		if(sLRB==1) hRawADCLRB->Fill(CsI_LRB_ADC);

		if(sRLT==1) hRawADCRLT->Fill(CsI_RLT_ADC);
		if(sRLB==1) hRawADCRLB->Fill(CsI_RLB_ADC);
		if(sRRT==1) hRawADCRRT->Fill(CsI_RRT_ADC);
		if(sRRB==1) hRawADCRRB->Fill(CsI_RRB_ADC);

		if(ientry%1000==0) cout<<ientry<<endl;

	}


	TCanvas *cRawADC=new TCanvas("cRawADC","cRawADC");
	cRawADC->cd();


	hRawADCLL->SetLineColor(1);
	hRawADCLRT->SetLineColor(2);
	hRawADCLRB->SetLineColor(3);
	hRawADCRRB->SetLineColor(1);
	hRawADCRRT->SetLineColor(2);
	hRawADCRLT->SetLineColor(3);
	hRawADCRLB->SetLineColor(4);

	if(side=="Left") {
		hRawADCLL->Draw();
		hRawADCLRT->Draw("same");
		hRawADCLRB->Draw("same");
	}
	else if(side=="Right"){
		hRawADCRRB->Draw();
		hRawADCRRT->Draw("same");
		hRawADCRLT->Draw("same");
		hRawADCRLB->Draw("same");

	}




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


