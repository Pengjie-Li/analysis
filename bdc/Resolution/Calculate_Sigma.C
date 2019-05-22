#include <math.h>
#include <TFile.h>
#include <TH3D.h>
#include <TTree.h>
#include <TVector3.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH2D.h>
#include <TView.h>
#include <TH1.h>
#include <Math/Functor.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <Math/Vector3D.h>
#include <Fit/Fitter.h>

class CalculateSigma{
	private:
		static const double BDC1_Z=-6666.11;;
		static const double BDC2_Z=-5666.67;
		static const double FDC0_Z=-3384.7;
		static const double DSSD_Z=-3866;



	public:

		Double_t xFitBDC2Sigma;
		Double_t yFitBDC2Sigma;

		Double_t xDCSigma;
		Double_t yDCSigma;

		Double_t xDSSDSigma;
		Double_t yDSSDSigma;

		CalculateSigma(double x,double y){
			xFitBDC2Sigma=x;
			yFitBDC2Sigma=y;
			BDC_Sigma();
			DSSD_Sigma();
		}
		double getC0(double z1,double z2,double z3){
			return (z2-z1)/(z3-z1);
		}
		double getDCSigma(double sigma,double C0){
			return sigma/sqrt((1-C0)*(1-C0)+C0*C0+1);
		}
		double getDSSDSigma(double sigma,double C0){
			return sigma*sqrt((1-C0)*(1-C0)+C0*C0);
		}
		int BDC_Sigma(){
			
			Double_t C0=getC0(BDC1_Z,BDC2_Z,FDC0_Z);
			cout<<" Drift Chamber C0="<<C0<<endl;
			xDCSigma=getDCSigma(xFitBDC2Sigma,C0);
			yDCSigma=getDCSigma(yFitBDC2Sigma,C0);
			cout<<" sqrt()="<<sqrt((1-C0)*(1-C0)+C0*C0+1)<<endl;

			cout<<"Drift Chamber Position Resolution: xDCSigma="<<xDCSigma<<" yDCSigma="<<yDCSigma<<endl;


			return 1;
		}
		int DSSD_Sigma(){

			Double_t C0=getC0(BDC1_Z,DSSD_Z,BDC2_Z);
			xDSSDSigma=getDSSDSigma(xDCSigma,C0);
			yDSSDSigma=getDSSDSigma(yDCSigma,C0);

			cout<<"DSSD Position Resolution due to Drift Chamber Position: xDCSigma="<<xDSSDSigma<<" yDCSigma="<<yDSSDSigma<<endl;


			return 1;
		}
};
int Calculate_Sigma(){
	double xFitSigma;
	double yFitSigma;
	// run 595
	xFitSigma=0.576;
	yFitSigma=0.572;
//	xFitSigma=0.431;
//	yFitSigma=0.414;



	CalculateSigma *cs=new CalculateSigma(xFitSigma,yFitSigma);
}
int main(){
		
	Calculate_Sigma();
	return 0;
}
