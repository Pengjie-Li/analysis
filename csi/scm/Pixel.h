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

		bool status;

		void Fill(double x,double y);

		void Init();
		void Precal();
		bool Fit();
		bool Refit();

		void Draw();

		double  getS();

		double sqr(double x);
};
#endif
