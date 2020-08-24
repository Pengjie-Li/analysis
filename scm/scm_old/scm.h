
#ifndef SCM_h 
#define SCM_h 

#include "header.h"

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
		TTree *tree;
	// Load data into pixel

		//Pixel pixel;
		TNewPixel pixel[32][32];

		TNewPixel  *P[32][32];

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
		// Check
		TH1F *Residue[2][32];



		double k[4][32];
		double b[4][32];
		double ek[4][32];
		double eb[4][32];



		void Open();
		void Open(TString inputname);
		void Init();
		void Load();
		void Build();

		void Fit();
		void OverAllSCM();
		//void OverAllSCM(int );
		void CalSCM(int side,int strip);
		void Write();
		void Draw(int i,int j);
		void ReDraw(int i,int j);
		void ReReDraw(int i,int j);
		void Output(int i,int j);
		void Check(int side,int strip);
		void LoadFitPar();


		double sqr(double x);
};
#endif
