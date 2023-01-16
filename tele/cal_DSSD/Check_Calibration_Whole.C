//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////


void Check_Calibration_Whole(){ 

	//int runnum=436;
	//int runnum=340;
	int runnum=598;
	//int runnum=597;
	//int runnum=596;
	//int runnum=599;
	//int runnum=596;
	//int runnum=300;
	Check_Pixel_Line(runnum);
}

void Check_Pixel_Line(int runnum){

	gROOT->Reset();
	gStyle->SetStatStyle(0);
	//gStyle->SetOptStat(1111111);

	int dDSSD=1;
	//TString inputname=Form("./rootfiles/run0%d/run0%d_SILICONS.root",runnum,runnum);
	TString inputname=Form("./rootfiles/run0%d/run0%d_SILICONS.root",runnum,runnum); // ped parameter
	TFile *f = new TFile(inputname,"READ");
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


	double k[4][32]={0};
	double b[4][32]={0};

	double ek[4][32]={0};
	double eb[4][32]={0};


	Load(k,b,ek,eb);


//	double lkb=6.626367576;
//	double lbb=-1903.367442;
//	double lkf=7.171468546;
//	double lbf=-1524.868862;
//

	double kl=6.0063;
	double bl=-918.189;




//	double rkb=7.074502166;
//	double rbb=-1670.625365;
//	double rkf=7.698357364;
//	double rbf=-1665.092353;

	double kr=6.35382;
	double br=-624.359;


	double SiLF_ADC[32]={0};
	double SiLB_ADC[32]={0};

	double SiRF_ADC[32]={0};
	double SiRB_ADC[32]={0};



	double SiLF_SCM[32]={0};
	double SiLB_SCM[32]={0};

	double SiRF_SCM[32]={0};
	double SiRB_SCM[32]={0};



	double SiLF_E[32]={0};
	double SiLB_E[32]={0};

	double SiRF_E[32]={0};
	double SiRB_E[32]={0};



	//TString outputname=Form("run%d_checking_calibration.root",runnum);
	//TString outputname=Form("run%d_checking_calibration_v3.root",runnum); //SCM paramter whole DSSD 
	TString outputname=Form("run%d_checking_calibration_v8.root",runnum); //Fit paramter whole DSSD 
	TFile *g=new TFile(outputname,"recreate");

	//	TH2F *hLF_SCM[32];
	//	TH2F *hLB[32];

	//=new TH2F("hLF","Check Cal Strip vs Ref Strip",4100,0,4100,4100,0,4100);

	TTree *tree=new TTree("tree","tree");
	tree->Branch("SiLF_ADC",&SiLF_ADC,"SiLF_ADC[32]/D");
	tree->Branch("SiLB_ADC",&SiLB_ADC,"SiLB_ADC[32]/D");

	tree->Branch("SiLF_SCM",&SiLF_SCM,"SiLF_SCM[32]/D");
	tree->Branch("SiLB_SCM",&SiLB_SCM,"SiLB_SCM[32]/D");

	tree->Branch("SiLF_E",&SiLF_E,"SiLF_E[32]/D");
	tree->Branch("SiLB_E",&SiLB_E,"SiLB_E[32]/D");

	tree->Branch("SiRF_ADC",&SiRF_ADC,"SiRF_ADC[32]/D");
	tree->Branch("SiRB_ADC",&SiRB_ADC,"SiRB_ADC[32]/D");

	tree->Branch("SiRF_SCM",&SiRF_SCM,"SiRF_SCM[32]/D");
	tree->Branch("SiRB_SCM",&SiRB_SCM,"SiRB_SCM[32]/D");

	tree->Branch("SiRF_E",&SiRF_E,"SiRF_E[32]/D");
	tree->Branch("SiRB_E",&SiRB_E,"SiRB_E[32]/D");





	Long64_t nentries = tree_BEAM->GetEntries();
	//nentries=100000;
	//nentries=10;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree_BEAM->GetEntry(ientry);

		for(int id=0;id<32;id++)
		{


			SiLF_ADC[id]=-999;
			SiLB_ADC[id]=-999;


			SiLF_SCM[id]=-999;
			SiLB_SCM[id]=-999;


			SiLF_E[id]=-999;
			SiLB_E[id]=-999;


			SiRF_ADC[id]=-999;
			SiRB_ADC[id]=-999;


			SiRF_SCM[id]=-999;
			SiRB_SCM[id]=-999;


			SiRF_E[id]=-999;
			SiRB_E[id]=-999;


		}
		for(int id=0;id<32;id++)
		{


			// raw->SCM->cal

			double lfraw=(*SiLF_rawADC)[id];
			double lbraw=(*SiLB_rawADC)[id];
			//double fscm=0;
			double lfscm=k[0][id]*lfraw+b[0][id];
			//double bscm=0;
			double lbscm=k[1][id]*lbraw+b[1][id];
			double lfcal=kl*lfscm+bl;
			double lbcal=kl*lbscm+bl;
			//cout<<lfscm<<"  "<<lbscm<<endl;




			SiLF_ADC[id]=lfraw;
			SiLB_ADC[id]=lbraw;


			SiLF_SCM[id]=lfscm;
			SiLB_SCM[id]=lbscm;


			SiLF_E[id]=lfcal;
			SiLB_E[id]=lbcal;
			//cout<<SiLF_SCM[id]<<endl;



			double rfraw=(*SiRF_rawADC)[id];
			double rbraw=(*SiRB_rawADC)[id];
			//double fscm=0;
			double rfscm=k[2][id]*rfraw+b[2][id];
			//double bscm=0;
			double rbscm=k[3][id]*rbraw+b[3][id];
			double rfcal=kr*rfscm+br;
			double rbcal=kr*rbscm+br;
			//cout<<rfscm<<"  "<<rbscm<<endl;

			SiRF_ADC[id]=rfraw;
			SiRB_ADC[id]=rbraw;


			SiRF_SCM[id]=rfscm;
			SiRB_SCM[id]=rbscm;

			SiRF_E[id]=rfcal;
			SiRB_E[id]=rbcal;

			//if(id==31) cout<<rfraw<<" "<<rfscm<<" "<<rfcal<<endl;


		}

		//cout<<SiLF_ADC[15]<<"   "<<SiLF_SCM[15]<<"  "<<SiLF_E[15]<<endl;
		tree->Fill();


		//		int Refid=15;
		//		hRef->Fill(k[0][Refid]*(*SiLF_rawADC)[Refid]+b[0][Refid],(*SiLB_rawADC)[15]);


		if(ientry%10000==0) cout<<ientry<<endl;

	}

	tree->Write();
	g->Write();
	g->Close();


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

