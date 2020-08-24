#ifndef Pixel_h 
#define Pixel_h 

#include "header.h"

class Pixel
{
	private:
	public:
		vector<double> xarray;
		vector<double> yarray;
		vector<double> xerror;
		vector<double> yerror;



		// for one fitting line
		int n; // how many points
		double k;
		double b;
		double ek;
		double eb;
		double r;
		double denom;
		double S;

		double   sumx;                      /* sum of x     */
		double   sumx2;                     /* sum of x**2  */
		double   sumxy;                     /* sum of x * y */
		double   sumy;                      /* sum of y     */
		double   sumy2;                     /* sum of y**2  */


		// FitB
		vector<double> U;
		vector<double> V;
		vector<double> beta;
		double A;
		double B;
		double C;
		double W;
		double sumbetaU;
		double sumbetaV;
		double sumbeta;
		double sumW;
		double sumWbeta2;

		bool status;
		int least_points;
		double Rstandard;

		void Fill(double x,double y);

		bool Remove();

		bool Refill();

		void Init();
		void Precal();
		bool Fit();
		bool Fit(double standard);
		bool Refit();
		bool ReRefit();
		//bool FitB();
		bool FitB(double EPS);
		bool ReFitB();
		bool Remove(double Residue2);
		bool Remove(double Residue1,double Residue2,double Residue3);

		bool Bivariate_Least_Square_Fit(double EPS);
		bool Least_Square_Fit();
		void Draw();

		double  getS();

		double sqr(double x);
		int  Np(); // return Pixel Number of Points 
};
#endif
