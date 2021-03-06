// Detector: DetectorPlane, + Response Position
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


class Detector{
	private:
	public: 

		TEnv *env;
		//Response *detectorResponse;
		//Detected 3D Position
		Double_t X;
		Double_t Y;
		Double_t Z;
		// true position with Trajectory line beam hit on
		Double_t virtualX;
		Double_t virtualY;
	
		Plane *detectorPlane;

		void printPosition(){
			cout<<"X ="<<getX()<<" Y ="<<getY()<<" Z ="<<getZ()<<endl;
			cout<<"virtualX ="<<getVirtualX()<<" virtualY ="<<getVirtualY()<<endl;
		}
	
		Detector(){
			env = new TEnv("configDetector.prm");
		}
		~Detector(){
			delete env;
			delete detectorPlane;
			
			env = NULL;
			detectorPlane = NULL;
		}
		void addPositionResolution(){}
		void setDetectorPlane(){
			//Plane: Ax+By+Cz+D=0
			//Z in definition should be positive
			detectorPlane=new Plane(0,0,1,Z);
		}
		void calculateCrossPosition(BeamGenerator *beam){

			double planeVector[3];
			double planePoint[3];
			setPlaneVP(planeVector,planePoint);

			double lineVector[3];
			double linePoint[3];
			setLineVP(beam,lineVector,linePoint);

			double vVirtualPoint[3];
			calPlaneLineIntersectPoint(vVirtualPoint,planeVector,planePoint,lineVector,linePoint);
			setX(vVirtualPoint[0]);
			setY(vVirtualPoint[1]);
			setZ(vVirtualPoint[2]);

			virtualX=vVirtualPoint[0];
			virtualY=vVirtualPoint[1];
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
		Double_t getX(){
			return X;
		}
		Double_t getY(){
			return Y;
		}
		Double_t getZ(){
			return Z;
		}
		Double_t getVirtualX(){
			return virtualX;
		}
		Double_t getVirtualY(){
			return virtualY;
		}


		void setLineVP(BeamGenerator *beam,double *lineVector,double *linePoint){

			lineVector[0]=beam->dirX;
			lineVector[1]=beam->dirY;
			lineVector[2]=beam->dirZ;
			linePoint[0]=beam->pointX;
			linePoint[1]=beam->pointY;
			linePoint[2]=beam->pointZ;
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
class BDCDetector:public Detector{
// User won't call this class
	private: 
	//	const static double xDCSigma=0.15;	
	//	const static double yDCSigma=0.15;	
	public:
		double xDCSigma;
		double yDCSigma;
		double angDCSigma;
		bool isAddPositionResolution;
		bool isAddAngularStraggling;
		BDCDetector(){}
		void launchDetector(BeamGenerator *beam){
			setDetectorPlane();
			calculateCrossPosition(beam);
			if(isAddPositionResolution) addPositionResolution();
			if(isAddAngularStraggling) addAngularStraggling(beam);
		}
		void addPositionResolution(){

			r.SetSeed(0);
			Double_t deltaX=r.Gaus(0,xDCSigma);

			r.SetSeed(0);
			Double_t deltaY=r.Gaus(0,yDCSigma);
			Double_t newX=X+deltaX;
			Double_t newY=Y+deltaY;
			setX(newX);
			setY(newY);
		}

		void addAngularStraggling(BeamGenerator *beam){
			// This straggling wont change position in BDC, but will change the direction of Beam
			//cout<<" Now add Angular Straggling = "<<angDCSigma<<endl;
			//evaluate10cmAfter();
			double newDistance = 100; // mm  mean after 10 cm after BDC1 Plane
			double spaceDCSigma = angDCSigma*newDistance/1000; // 1000 means angle here is mrad

			r.SetSeed(0);
			Double_t deltaX=r.Gaus(0,spaceDCSigma);
			r.SetSeed(0);
			Double_t deltaY=r.Gaus(0,spaceDCSigma);
			TVector3 virtualDC;
			virtualDC.SetXYZ(virtualX,virtualY,Z);
			TVector3 beamVector = beam->getBeamVector();
			TVector3 newDC = virtualDC + newDistance*beamVector;
			double newX = newDC.X()+deltaX;
			double newY = newDC.Y()+deltaY;
			newDC.SetX(newX);
			newDC.SetY(newY);
			TVector3 newBeamVector = (newDC - virtualDC).Unit();


			//showBeamVector(beam);
			beam->setDirect(newBeamVector);
			beam->setPointXYZ(virtualDC);
			//showBeamVector(beam);
		}
		void showBeamVector(BeamGenerator *beam){
			beam->printDirect();
		}
};
class BDC1Detector:public BDCDetector{
	private:
		const static double BDC1Z = 6666.11;
	public:
		BDC1Detector(BeamGenerator *beam){
			Z=BDC1Z;
			xDCSigma = env->GetValue("xBDC1Sigma",0.);
			yDCSigma = env->GetValue("yBDC1Sigma",0.);
			isAddPositionResolution = env ->GetValue("isBDC1Add",false);
			angDCSigma = env->GetValue("angBDC1Sigma",0.);
			isAddAngularStraggling = env ->GetValue("isBDC1AddAng",false);
			launchDetector(beam);
		}



};
class BDC2Detector:public BDCDetector{
	private:
		const static double BDC2Z = 5666.67;
	public:
		BDC2Detector(BeamGenerator *beam){
			Z=BDC2Z;
			xDCSigma = env->GetValue("xBDC2Sigma",0.);
			yDCSigma = env->GetValue("yBDC2Sigma",0.);
			isAddPositionResolution = env ->GetValue("isBDC2Add",false);
			angDCSigma = env->GetValue("angBDC2Sigma",0.);
			isAddAngularStraggling = env ->GetValue("isBDC2AddAng",false);
			launchDetector(beam);
		}
};

class DSSDDetector:public Detector{
	private:
		const static double DSSDZ = 3850;
		//const static double DSSDZ = env->GetValue("DSSDZ",3850.);
	public:
		int firedFrontStripId;
		int firedBackStripId;
		bool isDSSDActive;

		DSSDDetector(BeamGenerator *beam){
			Z = DSSDZ;
			isDSSDActive = env->GetValue("isDSSDActive",false);
			if(isDSSDActive){
				setDetectorPlane();
				calculateCrossPosition(beam);
				calculateHitStrip();
			}
		}
		void calculateHitStrip(){
			firedFrontStripId = (15 - floor((virtualY)/2));
			if(firedFrontStripId>31||firedFrontStripId<0) firedFrontStripId = -1;

			firedBackStripId = (15 - floor((virtualX)/2));
			if(firedBackStripId>31||firedBackStripId<0) firedBackStripId = -1;
		}
		int getFrontStripId(){
			return firedFrontStripId;
		}
		int getBackStripId(){
			return firedBackStripId;
		}
		void printDSSD(){
			printPosition();
			cout<<"Front id ="<<firedFrontStripId<<" Back id ="<<firedBackStripId<<endl;
		}


};
class MaterialDetector:public Detector{
	private:
		//const static double DSSDZ = env->GetValue("DSSDZ",3850.);
	public:

		//double MaterialZ = 3920;
		double angMaterialSigma;

		MaterialDetector(BeamGenerator *beam,double MaterialZ,double angStraSigma){
			Z = MaterialZ;
			setDetectorPlane();
			calculateCrossPosition(beam);

			angMaterialSigma = angStraSigma;
			addAngularStraggling(beam);
		}
		MaterialDetector(double MaterialZ){
			Z = MaterialZ;
			setDetectorPlane();

		}
		MaterialDetector(BeamGenerator *beam,double MaterialZ){
			Z = MaterialZ;
			setDetectorPlane();
			calculateCrossPosition(beam);

		}

		void addAngularStraggling(BeamGenerator *beam, double angStraSigma){

			calculateCrossPosition(beam);

			angMaterialSigma = angStraSigma;
			addAngularStraggling(beam);
		}


		void addAngularStraggling(BeamGenerator *beam){
			// This straggling wont change position in Material, but will change the direction of Beam
			double newDistance = 100; // mm  mean after 10 cm after BDC1 Plane
			double spaceMaterialSigma = angMaterialSigma*newDistance/1000; // 1000 means angle here is mrad

			r.SetSeed(0);
			Double_t deltaX=r.Gaus(0,spaceMaterialSigma);
			r.SetSeed(0);
			Double_t deltaY=r.Gaus(0,spaceMaterialSigma);
			TVector3 virtualMaterial;
			virtualMaterial.SetXYZ(virtualX,virtualY,Z);
			TVector3 beamVector = beam->getBeamVector();
			TVector3 newMaterial = virtualMaterial + newDistance*beamVector;
			double newX = newMaterial.X()+deltaX;
			double newY = newMaterial.Y()+deltaY;
			newMaterial.SetX(newX);
			newMaterial.SetY(newY);
			TVector3 newBeamVector = (newMaterial - virtualMaterial).Unit();


			//cout<<" show Angle Difference between Before and After:"<<endl;
			//cout<<newBeamVector.Angle(beamVector)/sqrt(2)<<endl;
			beam->setDirect(newBeamVector);
			beam->setPointXYZ(virtualMaterial);
			
		}
		void showBeamVector(BeamGenerator *beam){
			beam->printDirect();
		}

};

