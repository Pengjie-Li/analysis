
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

// For fitB
	A=0;
	B=0;
	C=0;
	W=0;
	sumbetaU=0;
	sumbetaV=0;
	sumbeta=0;
	sumW  =0;
	sumWbeta2=0;



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

	least_points=10;
	Rstandard=1E-3;

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

bool Pixel::Fit(double standard)
{
	Init();
	Precal();

	denom = (n * sumx2 - sqr(sumx));
	if( denom==0)  return false; // singular matrix
	//cout<<denom<<endl;

	/* compute correlation coeff */
	r = (sumxy - sumx * sumy /n ) / sqrt((sumx2 - sqr(sumx)/n) * (sumy2 - sqr(sumy)/n));
	//cout<<r<<endl;

	if(TMath::Abs(r-1)<standard) 
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
bool Pixel::FitB(double EPS)
{
	Init();
	Precal();

	U.clear();
	V.clear();
	beta.clear();
	U.resize(n,0);
	V.resize(n,0);
	beta.resize(n,0);

	for(int i=0;i<n;i++)
	{
		U[i]=xarray[i]-sumx/n;
		V[i]=yarray[i]-sumy/n;
		A+=U[i]*V[i];
		B+=(sqr(U[i])-sqr(V[i]));

		//cout<<n<<endl;
		//cout<<U[i]<<"  "<<V[i]<<"  "<<A<<"  "<<B<<endl;
	}
	C=-A;

	k=(-B+sqrt(sqr(B)-4*A*C))/(2*A);
	W=1/(1+k*k);
	cout<<k<<endl;
	//while(1)
	for(int i=0;i<100;i++)
	{
		for(int i=0;i<n;i++)
		{

			beta[i]=W*(k*U[i]+V[i]);
			sumbetaV+=beta[i]*V[i];
			sumbetaU+=beta[i]*U[i];
			//cout<<beta[i]<<"  "<<sumbetaV<<"  "<<sumbetaU<<endl;
		}

		double temp_k=sumbetaV/sumbetaU;
		cout<<temp_k<<"  "<<k<<endl;
		if(TMath::Abs(temp_k-k)<EPS) {status=true; break;}
		else k=temp_k;

		W=1/(1+k*k);
	}

	if(status)
	{
		W=1/(1+k*k);
		for(int i=0;i<n;i++)
		{

			beta[i]=W*(k*U[i]+V[i]);
			sumW+=W;
			sumbeta+=beta[i];
		}

		for(int i=0;i<n;i++)
		{
			sumWbeta2=W*sqr(beta[i]-sumbeta/n);
		}

		S=getS();

		b=(sumy-k*sumx)/n;
		cout<<"S="<<S<<"  sumWbeta2="<<sumWbeta2<<endl;
		cout<<"k="<<k<<" b="<<b<<endl;
		ek=S*sqrt(1/sumWbeta2);
		eb=S*sqrt(1/sumW+sqr((sumx+sumbeta)/n)/sumWbeta2);
		cout<<"ek="<<ek<<" eb="<<eb<<endl;
		return true;
	}

return false;

}
bool Pixel::ReFitB()
{
	if(!status) return false; // first fit should be successful
	if(xarray.size()<least_points) {status=false;return false;}
	//cout<<Remove(30)<<endl;;
	if(Remove(30)) { double EPS=0.00001;if(FitB(EPS)) cout<<"SECOND fitting successful"<<endl;}

	if(xarray.size()<least_points) {status=false;return false;}
	//cout<<status<<endl;;
	if(status&&Remove(5)) { double EPS=0.000001;if(FitB(EPS)) cout<<"THIRD fitting successful"<<endl;}
	
}
bool Pixel::Remove(double Residue2)
{
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
		if(dy2<Residue2)
		{
			tempx.push_back(x);
			tempy.push_back(y);
			tempxe.push_back(0);
			tempye.push_back(dy);
		}
	}
	if(tempx.size()>least_points)
	{
		xarray.clear();
		yarray.clear();
		xerror.clear();
		yerror.clear();

		xarray=tempx;
		yarray=tempy;
		xerror=tempxe;
		yerror=tempye;
		cout<<" REMOVE::We got "<<xarray.size()<<" points for Pixel"<<endl;
		return true;

	}
	else {return false;}
	//return false;

}

void Pixel::Draw()
{
	TGraphErrors *gr=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
	gr->Draw("AP");

}
bool Pixel::Refit()
{
	if(!status) return false; // first fit should be successful

	if(xarray.size()<least_points) {status=false;return false;}

	double Residue2=30;
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
		if(dy2<Residue2)
		{
			tempx.push_back(x);
			tempy.push_back(y);
			tempxe.push_back(0);
			tempye.push_back(dy);
		}
	}
	if(tempx.size()>least_points)
	{
		xarray.clear();
		yarray.clear();
		xerror.clear();
		yerror.clear();

		xarray=tempx;
		yarray=tempy;
		xerror=tempxe;
		yerror=tempye;
		cout<<"Now this is the second time fitting"<<endl;
		cout<<" We got "<<xarray.size()<<" points for Pixel"<<endl;
		bool sta=Fit(1E-2);
		return true;

	}
	else {return false;}
	return false;

}
bool Pixel::ReRefit()
{
	if(!status) return false; // first fit should be successful

	if(xarray.size()<least_points) {status=false;return false;}
	if(xarray.size()<10*least_points&&r<Rstandard) {

		cout<<"Now Third time fitting doesn't need for this pixel"<<endl;
		cout<<" We got "<<xarray.size()<<" points for Pixel"<<endl;
		return true;
	}

	double Residue2=5;
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
		if(dy2<Residue2)
		{
			tempx.push_back(x);
			tempy.push_back(y);
			tempxe.push_back(0);
			tempye.push_back(dy);
		}
	}
	if(tempx.size()>least_points)
	{
		xarray.clear();
		yarray.clear();
		xerror.clear();
		yerror.clear();

		xarray=tempx;
		yarray=tempy;
		xerror=tempxe;
		yerror=tempye;
		cout<<"Now this is the Third time fitting"<<endl;
		cout<<" We got "<<xarray.size()<<" points for Pixel"<<endl;
		bool sta=Fit(Rstandard);
		return true;

	}
	else {return false;}
	return false;

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
