
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
		TNewPixel lfpixel[32];
		TNewPixel lbpixel[32];
		TNewPixel rfpixel[32];
		TNewPixel rbpixel[32];


                TGraphErrors *lfgr[32];
                TGraphErrors *lbgr[32];
                TGraphErrors *rfgr[32];
                TGraphErrors *rbgr[32];

		TGraphErrors *lfregr[32];
                TGraphErrors *lbregr[32];
                TGraphErrors *rfregr[32];
                TGraphErrors *rbregr[32];

		TGraphErrors *lfreregr[32];
                TGraphErrors *lbreregr[32];
                TGraphErrors *rfreregr[32];
                TGraphErrors *rbreregr[32];

		TH1F *hlf[32];
                TH1F *hlb[32];
                TH1F *hrf[32];
                TH1F *hrb[32];






		TNewPixel  *P[32][32];
		TNewPixel  *LF[32];
		TNewPixel  *LB[32];
		TNewPixel  *RF[32];
		TNewPixel  *RB[32];



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
		void LoadFitPar();


		void Remove();

		void RemoveLF();
		void DrawLF(TNewPixel p[32],int i);
		void ReDrawLF(TNewPixel p[32],int i);
		void ReReDrawLF(TNewPixel p[32],int i);

		void RemoveLB();
		void DrawLB(TNewPixel p[32],int i);
		void ReDrawLB(TNewPixel p[32],int i);
		void ReReDrawLB(TNewPixel p[32],int i);


		void RemoveRF();
		void DrawRF(TNewPixel p[32],int i);
		void ReDrawRF(TNewPixel p[32],int i);
		void ReReDrawRF(TNewPixel p[32],int i);

		void RemoveRB();
		void DrawRB(TNewPixel p[32],int i);
		void ReDrawRB(TNewPixel p[32],int i);
		void ReReDrawRB(TNewPixel p[32],int i);

		void Output();

		void FitLF();
		void FitLB();
		void FitRF();
		void FitRB();
	
		void GFitLF();
		void GFitLB();
		void GFitRF();
		void GFitRB();

		void Residue();
		void ResidueLF();
		void ResidueLB();
		void ResidueRF();
		void ResidueRB();
	
	
		double sqr(double x);
};
#endif
