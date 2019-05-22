/**
 * known:Beam track (0,0,1), BDC1 perfect detector, BDC2 Sigma(0.45 / 0.15) 
 * to: Sigma on DSSD Plane
 * Steps
 * 1. Generate Trajectory
 * 2. Calcualte Position on BDC1,BDC2
 * 3. Add BDC2 Position sigma effect
 * 4. Add material angular straggling 
 * 4. using detected BDC1,FDC0 to calculate dBDC2
 * 5. Save event
 */
/**
 * v1: add angularStraggling in code
 * v2: BDC1 add position resolution
 * v3: remove Angular Straggling
 * v4: add Beam Generator
 * v5: add Beam read position on each plane
 * v6: add angular straggling again
 * v7: add FDC0 plane
 * v8: add dBDC2 interpolation
 */
int version = 8;
#include <math.h>
#include <fstream>
#include <TFile.h>
#include <TMath.h>
#include <TH3D.h>
#include <TTree.h>
#include <TVector3.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <TRandom2.h>
#include <TRandom3.h>
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

TRandom3	r;
class BeamGenerator{
	public:
		Double_t	dirX;
		Double_t	dirY;
		Double_t	dirZ;
		Double_t	pointX;
		Double_t	pointY;
		Double_t	pointZ;
		BeamGenerator(){
			setPointX();
			setPointY();
			setPointZ();
			setDirect();
			//printPoint();
			//printDirect();
		}
		BeamGenerator(TString axis){
			setPointX(0);
			setPointY(0);
			setPointZ(-7000);
			TVector3 eB(0,0,1);
			//eB.SetTheta(0.01);
			//eB.SetPhi(1.3);
			//eB.SetMag(1);
			setDirect(eB);
			//setDirect(new TVector3(0,0,1));
			//printPoint();
			//printDirect();
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
	
		void setPointX(){
			pointX=r.Gaus(0,12);
		}
		void setPointY(){
			pointY=r.Gaus(0,12);
		}
		void setPointZ(){
			pointZ=r.Gaus(-6666,10);
		}
		void setDirect(){
			//dirZ=7.5*r.Exp(1./3.17113e+04);
			dirZ=1-1.5e+3*r.Exp(1./3.17113e+04);
			dirX=r.Gaus(0,0.004);
			dirY=r.Gaus(0,0.004);
		}



};
class Plane{
	public:
		double A;
		double B;
		double C;
		double D;
		// corner pixel for calculating base vector
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

class BeamDetector{
	private : 
		const static double xDCSigma=0.15;	
		const static double yDCSigma=0.15;	

//		const static double xDCSigma=0.458;	
//		const static double yDCSigma=0.455;	



	public :
		Double_t X;
		Double_t Y;
		// true position beam hit on
		Double_t vX;
		Double_t vY;
	
		Double_t Z;
		Plane *detectorPlane;

		BeamDetector(){
		}
		BeamDetector(BeamGenerator *bg){
			setDetectorPlane();
			calculateCrossPosition(bg);
			addPositionResolution();
			
		}
		void addPositionResolution(){
			Double_t deltaX=r.Gaus(0,xDCSigma);
			Double_t deltaY=r.Gaus(0,yDCSigma);
			Double_t newX=X+deltaX;
			Double_t newY=Y+deltaY;
			setX(newX);
			setY(newY);
			
		}
		void setDetectorPlane(){
			detectorPlane=new Plane(0,0,1,Z);
		}
		void calculateCrossPosition(BeamGenerator *bg){

			double planeVector[3];
			double planePoint[3];
			setPlaneVP(planeVector,planePoint);

			double lineVector[3];
			double linePoint[3];
			setLineVP(bg,lineVector,linePoint);

			double vVirtualPoint[3];
			calPlaneLineIntersectPoint(vVirtualPoint,planeVector,planePoint,lineVector,linePoint);
			setX(vVirtualPoint[0]);
			setY(vVirtualPoint[1]);
			setZ(vVirtualPoint[2]);

			vX=vVirtualPoint[0];
			vY=vVirtualPoint[1];
		}
		void calPlaneLineIntersectPoint(double *returnResult,double *planeVector, double *planePoint, double *lineVector, double *linePoint){  
			double vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t,vpt;  
			vp1 = planeVector[0];  
			vp2 = planeVector[1];  
			vp3 = planeVector[2];  
			n1 = planePoint[0];  
			n2 = planePoint[1];  
			n3 = planePoint[2];  
			v1 = lineVector[0];  
			v2 = lineVector[1];  
			v3 = lineVector[2];  
			m1 = linePoint[0];  
			m2 = linePoint[1];  
			m3 = linePoint[2];  
			vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;  
			//首先判断直线是否与平面平行  
			if (vpt == 0)  
			{  
				cout<<"Plane Parallel, not good!"<<endl;
			}  
			else  
			{  
				t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;  
				returnResult[0] = m1 + v1 * t;  
				returnResult[1] = m2 + v2 * t;  
				returnResult[2] = m3 + v3 * t;  
			}  
		}  


		void setX(Double_t inX){
			X=inX;

		}
		void setY(Double_t inY){
			Y=inY;

		}

		void setZ(Double_t inZ){
			Z=inZ;

		}




		void setLineVP(BeamGenerator *bg,double *lineVector,double *linePoint){

			lineVector[0]=bg->dirX;
			lineVector[1]=bg->dirY;
			lineVector[2]=bg->dirZ;
			linePoint[0]=bg->pointX;
			linePoint[1]=bg->pointY;
			linePoint[2]=bg->pointZ;
		}


		void setPlaneVP(double *planeVector, double *planePoint){

			planePoint[0]=0;
			planePoint[1]=0;
			planePoint[2]=detectorPlane->getZ(0,0);

			planeVector[0]=detectorPlane->A;
			planeVector[1]=detectorPlane->B;
			planeVector[2]=detectorPlane->C;

		}

};
class BDC1Detector:public BeamDetector{
	private:
	public:
		BDC1Detector(BeamGenerator *bg){

			Z=6666.11;//BDC1 Z+6666=0;
			setDetectorPlane();
			calculateCrossPosition(bg);
			addPositionResolution();

		}

};
class BDC2Detector:public BeamDetector{
	private:
	public:
		BDC2Detector(BeamGenerator *bg){
			Z=5666.67;// later check
			setDetectorPlane();
			calculateCrossPosition(bg);
			addPositionResolution();

		}

};
class FDC0Detector:public BeamDetector{
	private:
	public:
		FDC0Detector(BeamGenerator *bg){
			Z=3384.7;// later check
			setDetectorPlane();
			calculateCrossPosition(bg);
			addPositionResolution();
		}

};


class VirtualTargetDetector:public BeamDetector{
	private:
	public:
		VirtualTargetDetector(BeamGenerator *bg){
			Z=6666.11-2443.77;
			setDetectorPlane();
			calculateCrossPosition(bg);
		}

};
class VirtualDSSDDetector:public BeamDetector{
	private:
	public:
		VirtualDSSDDetector(BeamGenerator *bg){
			Z=3820;// later check
			setDetectorPlane();
			calculateCrossPosition(bg);
		}

};




class EventBuilder{
	public:
		BeamGenerator *bg   ;
		BDC1Detector  *BDC1 ;
		BDC2Detector  *BDC2 ;
		FDC0Detector  *FDC0 ;
		VirtualTargetDetector  *vTarget;
		VirtualDSSDDetector  *vDSSD;

		Double_t BDC1_X;
		Double_t BDC1_Y;
		Double_t BDC1_Z;

		Double_t BDC2_X;
		Double_t BDC2_Y;
		Double_t BDC2_Z;

		Double_t FDC0_X;
		Double_t FDC0_Y;
		Double_t FDC0_Z;



		EventBuilder(){
			bg   =new BeamGenerator();
			BDC1 =new BDC1Detector(bg);
			BDC2 =new BDC2Detector(bg);
			FDC0 =new FDC0Detector(bg);
			vTarget =new VirtualTargetDetector(bg);
			vDSSD =new VirtualDSSDDetector(bg);
		}
		EventBuilder(TString axis){
			bg   =new BeamGenerator(axis);
			BDC1 =new BDC1Detector(bg);
			BDC2 =new BDC2Detector(bg);
			FDC0 =new FDC0Detector(bg);
			vTarget =new VirtualTargetDetector(bg);
			vDSSD =new VirtualDSSDDetector(bg);

		}


		Double_t getBDC1_X(){
			return BDC1->X;
		}
		Double_t getBDC1_Y(){
			return BDC1->Y;
		}
		Double_t getvBDC1_X(){
			return BDC1->vX;
		}
		Double_t getvBDC1_Y(){
			return BDC1->vY;
		}
	
		Double_t getBDC1_Z(){
			return BDC1->Z;
		}
		Double_t getBDC2_X(){
			return BDC2->X;
		}
		Double_t getBDC2_Y(){
			return BDC2->Y;
		}
		Double_t getvBDC2_X(){
			return BDC2->vX;
		}
		Double_t getvBDC2_Y(){
			return BDC2->vY;
		}
	
		Double_t getBDC2_Z(){
			return BDC2->Z;
		}

		Double_t getFDC0_X(){
			return FDC0->X;
		}
		Double_t getFDC0_Y(){
			return FDC0->Y;
		}
		Double_t getvFDC0_X(){
			return FDC0->vX;
		}
		Double_t getvFDC0_Y(){
			return FDC0->vY;
		}
	
		Double_t getFDC0_Z(){
			return FDC0->Z;
		}

		Double_t getvTarget_X(){
			return vTarget->vX;
		}
		Double_t getvTarget_Y(){
			return vTarget->vY;
		}
		Double_t getvTarget_Z(){
			return vTarget->Z;
		}

		Double_t getvDSSD_X(){
			return vDSSD->vX;
		}
		Double_t getvDSSD_Y(){
			return vDSSD->vY;
		}
		Double_t getvDSSD_Z(){
			return vDSSD->Z;
		}


		

};
class EventSimulator{
	public : 
		int nEvent;

		TFile *outputFile;
		TTree *tree;
		// SetBranch variables
		Double_t BDC1_X;
		Double_t BDC1_Y;
		Double_t BDC1_Z;

		Double_t BDC2_X;
		Double_t BDC2_Y;
		Double_t BDC2_Z;

		Double_t dBDC2_X;
		Double_t dBDC2_Y;
		Double_t dBDC2_Z;


		Double_t FDC0_X;
		Double_t FDC0_Y;
		Double_t FDC0_Z;


		Double_t Target_X;
		Double_t Target_Y;
		Double_t Target_Z;

		Double_t DSSD_X;
		Double_t DSSD_Y;
		Double_t DSSD_Z;

		Double_t vBDC1_X;
		Double_t vBDC1_Y;

		Double_t vBDC2_X;
		Double_t vBDC2_Y;


		Double_t vFDC0_X;
		Double_t vFDC0_Y;

		Double_t vTarget_X;
		Double_t vTarget_Y;

		Double_t vDSSD_X;
		Double_t vDSSD_Y;
	

		TVector3 vBDC1;
		TVector3 vBDC2;
		TVector3 vdBDC2;
		TVector3 vFDC0;
		TVector3 vDSSD;
		TVector3 vTarget;
		TVector3 vDirection;
		TVector3 *vBeam;


		EventSimulator(){
			nEvent=1000;
			createFile();
			setBranch();
			lanchSimulatorLoop();
			saveFile();
		}
		EventSimulator(int nevt){
			nEvent=nevt;
			createFile();
			setBranch();
			lanchSimulatorLoop();
			saveFile();
		}


		void lanchSimulatorLoop(){
			for(int i=0;i<nEvent;i++){
				r.SetSeed(i);
				//EventBuilder *eb=new EventBuilder("zaxis");
				EventBuilder *eb=new EventBuilder();
				BDC1_X=eb->getBDC1_X();
				BDC1_Y=eb->getBDC1_Y();
				BDC1_Z=eb->getBDC1_Z();

				vBDC1_X=eb->getvBDC1_X();
				vBDC1_Y=eb->getvBDC1_Y();



				BDC2_X=eb->getBDC2_X();
				BDC2_Y=eb->getBDC2_Y();
				BDC2_Z=eb->getBDC2_Z();

				vBDC2_X=eb->getvBDC2_X();
				vBDC2_Y=eb->getvBDC2_Y();

				FDC0_X=eb->getFDC0_X();
				FDC0_Y=eb->getFDC0_Y();
				FDC0_Z=eb->getFDC0_Z();

				vFDC0_X=eb->getvFDC0_X();
				vFDC0_Y=eb->getvFDC0_Y();

				vTarget_X=eb->getvTarget_X();
				vTarget_Y=eb->getvTarget_Y();

				vDSSD_X=eb->getvDSSD_X();
				vDSSD_Y=eb->getvDSSD_Y();

				setBeamVector();
				setBDC2FromBDC1AndFDC0();
				setTargetXYZ();
				setDSSDXYZ();
				tree->Fill();


			}

		}

		double getRatio(double z1,double z2,double interval){
			return (z2-z1)/interval;
		}
		void setBDC2FromBDC1AndFDC0(){
			vBDC1.SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
			vBDC2.SetXYZ(BDC2_X,BDC2_Y,BDC2_Z);
			vFDC0.SetXYZ(FDC0_X,FDC0_Y,FDC0_Z);
			vDirection=(vFDC0-vBDC1).Unit();
			// determine k
			double k=getRatio(BDC1_Z,BDC2_Z,vDirection.Z());
			vdBDC2=vBDC1+k*vDirection;
			dBDC2_X=vdBDC2.X();
			dBDC2_Y=vdBDC2.Y();
			dBDC2_Z=vdBDC2.Z();

		}
		void setBeamVector(){
			
			vBDC1.SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
			vBDC2.SetXYZ(BDC2_X,BDC2_Y,BDC2_Z);
			(*vBeam)=vBDC2-vBDC1;
			(*vBeam)=(*vBeam).Unit();
			
		//	cout<<"BDC1:x="<<vBDC1.X()<<" y="<<vBDC1.Y()<<" z="<<vBDC1.Z()<<endl;
		//	cout<<"BDC2:x="<<vBDC2.X()<<" y="<<vBDC2.Y()<<" z="<<vBDC2.Z()<<endl;
		//	cout<<"x="<<vBeam->X()<<" Y="<<vBeam->Y()<<"z="<<vBeam->Z()<<endl;
	
		}
		// add TVector DSSD, Target, add angle stragling in Beam Vector
		void setDSSDXYZ(){
			DSSD_Z = -3820;
			//vDSSD = getVectorInLine(vBDC2,vTarget,DSSD_Z,0); // 10 mrad
			vDSSD = getVectorInLine(vBDC2,vTarget,DSSD_Z); // 10 mrad
			DSSD_X = vDSSD.X();
			DSSD_Y = vDSSD.Y();

		}
		void setTargetXYZ(){
			Target_Z=2443.77-6666.11;
			vTarget = getVectorInLine(vBDC1,vBDC2,Target_Z,0.509);
			//vTarget = getVectorInLine(vBDC1,vBDC2,Target_Z);
			Target_X = vTarget.X();
			Target_Y = vTarget.Y();

		}

		TVector3 getVectorInLine(TVector3 v1,TVector3 v2,Double_t Z0,Double_t angularStraggling/* mrad */){
			TVector3 vDir = (v2-v1).Unit();

			//cout<<"Before add Angular Straggling"<<endl; 
			//cout<<"Unit Direction: Mag="<<vDir.Mag()<<" Phi="<<vDir.Phi()<<" Theta="<<vDir.Theta()<<endl;
			Double_t eventAngularStraggling = r.Gaus(0,angularStraggling/1000); 
			Double_t newTheta=vDir.Theta()+eventAngularStraggling;

			//cout<<" angularStraggling = "<<angularStraggling<<" evt angularStraggling = "<< eventAngularStraggling<<endl;
			vDir = setAngularStraggling(vDir,newTheta);
			//cout<<"Add Angular Straggling"<<endl; 
			//cout<<"Unit Direction: Mag="<<vDir.Mag()<<" Phi="<<vDir.Phi()<<" Theta="<<vDir.Theta()<<endl;
			double kRatio = (Z0-v2.Z())/vDir.Z();
			TVector3 result = v2+kRatio*vDir;
			return result;
		}
		TVector3 setAngularStraggling(TVector3 vDir,Double_t newTheta){
			if(newTheta >= 0){
				vDir.SetTheta(newTheta);
				return vDir;
			}else{
				//Double_t newPhi = vDir.Phi()+TMath::Pi();
				//if(newPhi>-(TMath::Pi())&&newPhi<=TMath::Pi()) vDir.SetPhi(newPhi);
				//else vDir.SetPhi(newPhi-2*TMath::Pi());
				vDir.RotateZ(TMath::Pi());
				vDir.SetTheta(-newTheta);	
				return vDir;
			}

		}

		TVector3 getVectorInLine(TVector3 v1,TVector3 v2,Double_t Z0){
			TVector3 vDir = (v2-v1).Unit();
			double kRatio = (Z0-v2.Z())/vDir.Z();
			TVector3 result = v2+kRatio*vDir;
			return result;
		}






		void createFile(){
			outputFile=new TFile(Form("./rootfiles/EvaluateSigmaToDSSD_v%d.root",version),"recreate");
			tree=new TTree("tree","tree");
		}
		void setBranch(){

			vBeam=new TVector3();
			tree->Branch("Beam","TVector3",&vBeam);

			tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");
			tree->Branch("BDC1_Z",&BDC1_Z,"BDC1_Z/D");

			tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");
			tree->Branch("BDC2_Z",&BDC2_Z,"BDC2_Z/D");

			tree->Branch("dBDC2_X",&dBDC2_X,"dBDC2_X/D");
			tree->Branch("dBDC2_Y",&dBDC2_Y,"dBDC2_Y/D");
			tree->Branch("dBDC2_Z",&dBDC2_Z,"dBDC2_Z/D");

			tree->Branch("FDC0_X",&FDC0_X,"FDC0_X/D");
			tree->Branch("FDC0_Y",&FDC0_Y,"FDC0_Y/D");
			tree->Branch("FDC0_Z",&FDC0_Z,"FDC0_Z/D");

			tree->Branch("DSSD_X",&DSSD_X,"DSSD_X/D");
			tree->Branch("DSSD_Y",&DSSD_Y,"DSSD_Y/D");
			tree->Branch("DSSD_Z",&DSSD_Z,"DSSD_Z/D");

			tree->Branch("Target_X",&Target_X,"Target_X/D");
			tree->Branch("Target_Y",&Target_Y,"Target_Y/D");
			tree->Branch("Target_Z",&Target_Z,"Target_Z/D");

			tree->Branch("vBDC1_X",&vBDC1_X,"vBDC1_X/D");
			tree->Branch("vBDC1_Y",&vBDC1_Y,"vBDC1_Y/D");

			tree->Branch("vBDC2_X",&vBDC2_X,"vBDC2_X/D");
			tree->Branch("vBDC2_Y",&vBDC2_Y,"vBDC2_Y/D");

			tree->Branch("vFDC0_X",&vFDC0_X,"vFDC0_X/D");
			tree->Branch("vFDC0_Y",&vFDC0_Y,"vFDC0_Y/D");

			tree->Branch("vTarget_X",&vTarget_X,"vTarget_X/D");
			tree->Branch("vTarget_Y",&vTarget_Y,"vTarget_Y/D");

			tree->Branch("vDSSD_X",&vDSSD_X,"vDSSD_X/D");
			tree->Branch("vDSSD_Y",&vDSSD_Y,"vDSSD_Y/D");
	
			}

		void saveFile(){
			tree->Write();
			outputFile->Close();
		}


};
int Evaluate_Sigma(){
	int nEvent=800000;
	//int nEvent=1000;
	EventSimulator *es=new EventSimulator(nEvent);
	return 0;
}
int main(){
	return 0;
}
