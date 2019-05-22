
#ifndef LDP_h 
#define LDP_h 

#include "header.h"

class LDP
{

	private:
		int refback;
		int reffront;
	public:

		LDP();
		LDP(int ref);
		LDP(int ref1,int ref2);
		LDP(int ref1,int ref2, int run);

		TFile *f;
		int runnum;
		//TTree *tree;
		TChain *tree;
		//Declaration of leaves types
		vector<double>  *SiLF_rawADC;
		vector<double>  *SiLB_rawADC;
		vector<double>  *SiRF_rawADC;
		vector<double>  *SiRB_rawADC;

		//Declaration of leaves types
		vector<double>  lfadc;
		vector<double>  lbadc;
		vector<double>  rfadc;
		vector<double>  rbadc;

		// Read parameters from Pedestral check
		double ped[4][32];
		double pedsigma[4][32];
		double pedthrd[4][32];
		// Load data into pixel

		//Pixel pixel;
		TNewPixel pixel[32][32];

		// Output
		TFile *g;
		TGraphErrors *gr[32][32];
		TF1 *fit[32][32];
		TGraphErrors *regr[32][32];
		TF1 *refit[32][32];
		TH1F *redy[32][32];
		TGraphErrors *reregr[32][32];
		TF1 *rerefit[32][32];
		TH1F *reredy[32][32];

		TTree *treeW;


		double k[4][32];
		double b[4][32];
		double ek[4][32];
		double eb[4][32];



		void Open();
		void Open(TString inputname);
		void Init();
		void Load();
		void Build();
		void LoadPar();

		void Remove();
		void Write();
		void Draw(int i,int j);
		void ReDraw(int i,int j);
		void ReReDraw(int i,int j);
		void Output(int i,int j);

		int remove_multihit(vector<double>  fadc,vector<double>  badc);
		int remove_multihit(vector<double>  fadc,vector<double>  badc,int &fid,int &bid);
		bool select(double x,double y);

		double sqr(double x);
};
#endif
