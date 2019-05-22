
#include "Pixel.h"

double Pixel::sqr(double x){ return x*x; }
void Pixel::Fill(double x,double y)
{
	xarray.push_back(x);
	yarray.push_back(y);
	xerror.push_back(0);
	yerror.push_back(0);

	//if(x>700) cout<<"X="<<x<<" Y="<<y<<endl;
}
void Pixel::Init()
{

	sumx = 0.0;                      /* sum of x     */
	sumx2 = 0.0;                     /* sum of x**2  */
	sumxy = 0.0;                     /* sum of x * y */
	sumy = 0.0;                      /* sum of y     */
	sumy2 = 0.0;                     /* sum of y**2  */

	n=0;
	k=0;
	b=0;
	ek=0;
	eb=0;
	r=0;
	denom=0;
	S=0;

	status=false;


}
void Pixel::Precal()
{
	n=xarray.size();
	for(int i=0;i<n;i++)
	{
		double x=xarray[i];
		double y=yarray[i];
		sumx  += x;       
		sumx2 += sqr(x);  
		sumxy += x * y;
		sumy  += y;      
		sumy2 += sqr(y); 
	}


}

//double sqr(double x){ return x*x; }
bool Pixel::Fit()
{
        cout<<"Now this is the first time fitting"<<endl;
	cout<<" We got "<<xarray.size()<<" points for Pixel"<<endl;
	Init();
	Precal();

	denom = (n * sumx2 - sqr(sumx));
	if( denom==0)  return false; // singular matrix
	//cout<<denom<<endl;

	/* compute correlation coeff */
	r = (sumxy - sumx * sumy /n ) / sqrt((sumx2 - sqr(sumx)/n) * (sumy2 - sqr(sumy)/n));
	//cout<<r<<endl;

	if(TMath::Abs(r-1)<1E-2) 
	{
		k = (n * sumxy  -  sumx * sumy) / denom;
		b = (sumy * sumx2  -  sumx * sumxy) / denom;
		S=getS();

		ek=S*sqrt(n)/sqrt(n*sumx2-sqr(sumx));
		eb=ek*sqrt(sumx2/n);
		if(ek!=0&&eb!=0) status=true;
		cout<<"k="<<k<<" b="<<b<<"ek="<<ek<<" eb="<<eb<<" S="<<S<<" r="<<r<<endl;

		return true;

	}

	return false;


}

void Pixel::Draw()
{
  TGraphErrors *gr=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
  gr->Draw("AP");

}
bool Pixel::Refit()
{
        if(!status) return false; // first fit should be successful

	n=xarray.size();
	vector<double> tempx,tempy;
	vector<double> tempxe,tempye;

	for(int i=0;i<n;i++)
	{
		double x=xarray[i];
		double y=yarray[i];
		double dy=y-k*x-b;
		double dy2=sqr(dy);
		//cout<<dy<<endl;
		if(dy2<10)
		{
                  tempx.push_back(x);
                  tempy.push_back(y);
                  tempxe.push_back(0);
                  tempye.push_back(dy);
		}
	}
	xarray.clear();
	yarray.clear();
	xerror.clear();
	yerror.clear();

	xarray=tempx;
	yarray=tempy;
	xerror=tempxe;
	yerror=tempye;
	status=Fit();
	cout<<"Now this is the second time fitting"<<endl;
	cout<<" We got "<<xarray.size()<<" points for Pixel"<<endl;


}
double Pixel::getS()
{

	double sumdy2=0;
	for(int i=0;i<n;i++)
	{
		double x=xarray[i];
		double y=yarray[i];
		double dy2=sqr(y-k*x-b);      
		sumdy2+=dy2;
	}

	double ss=0;
        if(n>2) ss=sqrt(sumdy2/(n-2));

	return ss;

}
