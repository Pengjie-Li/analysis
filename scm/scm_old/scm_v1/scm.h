
#ifndef SCM_h 
#define SCM_h 

#include "header.h"
#include "Pixel.h"

class SCM
{

	private:
		int refback;
		int reffront;
	public:

		SCM();
		SCM(int ref);
		SCM(int ref1,int ref2);
		SCM(int ref1,int ref2, int run);

		TFile *f;
		int runnum;
		TTree *tree;
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
		Pixel pixel[32][32];

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



		double k[4][32];
		double b[4][32];
		double ek[4][32];
		double eb[4][32];



		void Open();
		void Open(TString inputname);
		void Init();
		void Load();
		void Build();
		void LoadPar(TString inputname);

		void LoadFitPar();
		void Fit();
		void OverAllSCM();
		//void OverAllSCM(int );
		void CalSCM(int side,int strip);
		void Write();
		void Draw(int i,int j);
		void ReDraw(int i,int j);
		void ReReDraw(int i,int j);
		void Output(int i,int j);

		int remove_multihit(vector<double>  *fadc,vector<double>  *badc);
		int remove_multihit(vector<double>  fadc,vector<double>  badc,int &fid,int &bid);
		bool select(double x,double y);

		double sqr(double x);
};
#endif
