#include "header.h"
class BeamGenerator{
	protected: 
		const static double pointXMean = 0;
		const static double pointYMean = 0;
		const static double pointZMean = -7000;

		const static double pointXSigma = 12;
		const static double pointYSigma = 12;
		const static double pointZSigma = 10;

		
		const static double dirXMean = 0;
		const static double dirYMean = 0;

		const static double dirXSigma = 0.002;
		const static double dirYSigma = 0.002;

		/** dirZ = 1 - Amp*Exp(1/Tao) **/	
		const static double dirZAmplitude = 15;
		const static double dirZTao = 317000;


	public:
		double	dirX;
		double	dirY;
		double	dirZ;
		double	pointX;
		double	pointY;
		double	pointZ;
		TVector3 beamVector;
		BeamGenerator(){
			setPointX();
			setPointY();
			setPointZ();
			setDirect();
			setBeamVector();
			//printPoint();
			//printDirect();
		}
		void setBeamVector(){
			beamVector.SetXYZ(dirX,dirY,dirZ);
			beamVector = beamVector.Unit();
			dirX = beamVector.X();
			dirY = beamVector.Y();
			dirZ = beamVector.Z();
		}
		TVector3 getBeamVector(){
			setBeamVector();
			return beamVector;
		}

		void printDirect(){
			cout<<"dirX="<<dirX<<" dirY="<<dirY<<" dirZ="<<dirZ<<endl;
		}
		void printPoint(){
			cout<<"x="<<pointX<<" y="<<pointY<<" z="<<pointZ<<endl;
		}

		void setPointX(Double_t arg){
			pointX=arg;
		}
		void setPointY(Double_t arg){
			pointY=arg;
		}
		void setPointZ(Double_t arg){
			pointZ=arg;
		}
		void setDirect(TVector3 *ev){
			dirX=ev->X();
			dirY=ev->Y();
			dirZ=ev->Z();
		}
		void setDirect(TVector3 ev){
			dirX=ev.X();
			dirY=ev.Y();
			dirZ=ev.Z();
		}
	
		void setPointXYZ(double newX,double newY,double newZ){
			pointX = newX;
			pointY = newY;
			pointZ = newZ;
		}
		void setPointXYZ(TVector3 newPoint){
			pointX = newPoint.X();
			pointY = newPoint.Y();
			pointZ = newPoint.Z();
		}

		void setPointX(){
			pointX=r.Gaus(pointXMean,pointXSigma);
		}
		void setPointY(){
			pointY=r.Gaus(pointYMean,pointYSigma);
		}
		void setPointZ(){
			pointZ=r.Gaus(pointZMean,pointZSigma);
		}
		void setDirect(){
			//dirZ=7.5*r.Exp(1./3.17113e+04);
			dirZ=1-dirZAmplitude*r.Exp(1./dirZTao);
			dirX=r.Gaus(dirXMean,dirXSigma);
			dirY=r.Gaus(dirYMean,dirYSigma);
		}

		double getPointX(){
			return pointX;
		}
		double getPointY(){
			return pointY;
		}
		double getPointZ(){
			return pointZ;
		}

		double getDirX(){
			return dirX;
		}
		double getDirY(){
			return dirY;
		}
		double getDirZ(){
			return dirZ;
		}

};
class ZaxisBeamGenerator:public BeamGenerator{
	private:
	public:
		ZaxisBeamGenerator(){
			setPointX(pointXMean);
			setPointY(pointYMean);
			setPointZ(pointZMean);
			TVector3 eB(0,0,1);
			//eB.SetTheta(0.01);
			//eB.SetPhi(1.3);
			//eB.SetMag(1);
			setDirect(eB);
			//setDirect(new TVector3(0,0,1));
			//printPoint();
			//printDirect();
		}

};

