/**
 * 1 input: left/right fid, bid, x, y, z
 * 2.generate all the pixels x y z
 * 3. save into txt file
 */
#include <math.h>
#include <fstream>
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


class Plane{
	public:
		double A;
		double B;
		double C;
		double D;
		int cfid;
		int cbid;
		TVector3 e1;
		TVector3 e2;
		TVector3 e3;

		Plane(){};
		Plane(double a,double b,double c,double d){
			A=a;
			B=b;
			C=c;
			D=d;
		}
		double getX(double y,double z){
			return (-B*y-C*z-D)/A;
		}
		double getY(double x,double z){
			return (-A*x-C*z-D)/B;
		}
		double getZ(double x,double y){
			return (-A*x-B*y-D)/C;
		}
		void calBaseVector(){
			e3.SetXYZ(A,B,C);
			e3=e3.Unit();

			e1.SetXYZ(1,0,-e3.X()/e3.Z());
			e1=e1.Unit();
			e2 = e1.Cross(e3);
			if(e2.Y()<0) e2=-e2;
		}
		

};
class LeftPlane: public Plane{
	public:
		LeftPlane(){
			A=-0.147;
			B=0.004;
			C=0.989;
			D=3818.509;
			cfid=31;
			cbid=0;
			calBaseVector();
		}

};
class RightPlane: public Plane{
	public:
		RightPlane(){
			A=0.154;
			B=-0.002;
			C=0.988;
			D=3814.659;
			cfid=31;
			cbid=31;
			calBaseVector();
		}

};

class GeneratePosition{
public: 
	Plane *p;
	TString outputName;
	TVector3 corner;
	TVector3 fInterval;
	TVector3 bInterval;

	// intput
	int side;
	int fid;
	int bid;
	double x0;
	double y0;
	double z0;

	GeneratePosition(int s,int f,int b,double x,double y){

		side=s;
		fid=f;
		bid=b;
		x0=x;
		y0=y;
		findCornerPoint();
		outputPosition();
	}
	void findCornerPoint(){

		if(side==0) p=new LeftPlane();
		else p=new RightPlane();

		z0=p->getZ(x0,y0);
		//cout<<z0<<" "<<p->getZ(x0,y0)<<endl;
		fInterval=2*p->e2;
		bInterval=2*p->e1;

		int cornerfid=p->cfid;
		int cornerbid=p->cbid;
		corner.SetXYZ(x0,y0,z0);
		if(side==0) corner=corner+(fid-cornerfid)*fInterval-(bid-cornerbid)*bInterval;
		else corner=corner+(fid-cornerfid)*fInterval+(bid-cornerbid)*bInterval;
		cout<<corner.X()<<" "<<corner.Y()<<" "<<corner.Z()<<endl;
	}

	void outputPosition(){
		if(side==0) outputName="LeftDSSDPixelPosition.txt";
		else outputName="RightDSSDPixelPosition.txt";
		ofstream out(outputName,ios_base::app | ios_base::out);
		out.flags (ios::left);

		TVector3 targetCenter(0,0,-4222.45);
		for(int i=0;i<32;i++)
			for(int j=0;j<32;j++){
				TVector3 temp=corner+i*fInterval+j*bInterval;

				temp = temp - targetCenter;
				temp.RotateY(-1*TMath::DegToRad());
				temp = temp + targetCenter;

				double tempx=temp.X();
				double tempy=temp.Y();
				double tempz=temp.Z();


				int tempfid;
				int tempbid;

				if(side==0) {
					tempfid=31-i;
					tempbid=j;

				}else{
					tempfid=31-i;
					tempbid=31-j;
				}
				out<<setw(20)<<tempfid<<setw(20)<<tempbid<<setw(20)<<tempx<<setw(20)<<tempy<<setw(20)<<tempz<<endl;
				cout<<setw(20)<<tempfid<<setw(20)<<tempbid<<setw(20)<<tempx<<setw(20)<<tempy<<setw(20)<<tempz<<endl;
			}
		out.close();
	}


};
int Generate_Poisition(){
// Here input pixel (isLR,fid,bid, x,y)
	new GeneratePosition(0,16,26,-32.466,-1.40);	
//	new GeneratePosition(1,16,27,32.17,-1.75);	


//	LeftPlane *lp=new LeftPlane();
//	RightPlane *rp=new RightPlane();

// C++ 多态
//	Plane *lp=new LeftPlane();
//	cout<<lp->getZ(-24,-1)<<endl;;
//	Plane *rp=new RightPlane();
//	cout<<rp->getZ(24,-1)<<endl;;

	return 1;

}
