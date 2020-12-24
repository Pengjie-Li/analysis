class EspriTimeEvent{
	private:
	public:
		EspriTimeEvent(){}
		~EspriTimeEvent(){}
};
class ESPRI3DPosition{
	private:

		TVector3 leftPlaneNorm;
		TVector3 rightPlaneNorm;
		TVector3 leftPedal;
		TVector3 leftBaseX;
		TVector3 leftBaseY;
		TVector3 rightPedal;
		TVector3 rightBaseX;
		TVector3 rightBaseY;
		double centerX;
		double centerY;

	public:
		ESPRI3DPosition(){
			// From PGS 
			//leftPedal.SetXYZ(-878.501926,-4.057746,-3715.121798);
			//leftBaseX.SetXYZ(0.500011,0.000000,0.866019);
			//leftBaseY.SetXYZ(-0.003464,0.999992,0.002000);
			//rightPedal.SetXYZ(882.276111,0.000000,-3719.777658);
			//rightBaseX.SetXYZ(0.494954,0.000000,-0.868919);
			//rightBaseY.SetXYZ(0.000000,1.000000,-0.000000);
			// Expected position
			leftPlaneNorm.SetXYZ(-0.867158, 0.000000,0.498034);
			leftPedal.SetXYZ(-877.015389,0.000000,-3718.644642);
			leftBaseX.SetXYZ(0.498034,0.000000,0.867158);
			leftBaseY.SetXYZ(0.000000,1.000000,0.000000);

			rightPlaneNorm.SetXYZ(0.868919,0,0.494954);
			//rightPedal.SetXYZ(900.813644,0.000000,-3702.255000);
			rightPedal.SetXYZ(877.985787,0.000000,-3722.221514);
			rightBaseX.SetXYZ(0.494954,0.000000,-0.868919);
			rightBaseY.SetXYZ(0.000000,1.000000,0.000000);
	
			centerX = 227.5;
			centerY = 227.5 - 3.0; // 3 mm offset comes from ppBe phi center offset
		}
		TVector3 getESPRIPosition(int lr,double X,double Y){
			TVector3 pedal;
			TVector3 baseX;
			TVector3 baseY;
			if(lr ==0 ){
				X = X -centerX;
				Y = Y -centerY;

				pedal = leftPedal;
				baseX = leftBaseX;
				baseY = leftBaseY;
			}
			else{
				//X = X -centerX ;
				X = X -centerX -2.27;
				Y = Y -centerY; // Shift ESPRI from Phi

				pedal = rightPedal;
				baseX = rightBaseX;
				baseY = rightBaseY;
			}
			return (pedal + X*baseX + Y*baseY);
		}
		TVector3 getESPRIPlaneNorm(int lr){
			if(lr == 0) return leftPlaneNorm;
			else return rightPlaneNorm;
		}
		~ESPRI3DPosition(){}
};
class Plane{
	public:
		double A;
		double B;
		double C;
		double D;
		// corner pixel for calculating base vector
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
		TVector3 getPlaneVector(){
			TVector3 vResult;
                        vResult.SetXYZ(A,B,C);
                        return vResult;
		}
		TVector3 getPlanePoint(){
                        TVector3 vResult;
                        vResult.SetXYZ(0,0,getZ(0,0));
                        return vResult;

		}
}; 
class ESPRIPlasPosition{
	private:
		Plane *leftPlane;
		Plane *rightPlane;
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

                void vector2Array(TVector3 vector,double *array){
                        array[0] = vector.X();
                        array[1] = vector.Y();
                        array[2] = vector.Z();
                }
                TVector3 calPlaneLineIntersectPoint(TVector3 planeVector,TVector3 planePoint,TVector3 lineVector,TVector3 linePoint){
                        double planeVectorArray[3];
                        vector2Array(planeVector,planeVectorArray);

                        double planePointArray[3];
                        vector2Array(planePoint,planePointArray);

                        double lineVectorArray[3];
                        vector2Array(lineVector,lineVectorArray);

                        double linePointArray[3];
                        vector2Array(linePoint,linePointArray);

                        double returnResult[3];
                        calPlaneLineIntersectPoint(returnResult,planeVectorArray,planePointArray,lineVectorArray,linePointArray);
                        TVector3 vResult;
                        vResult.SetXYZ(returnResult[0],returnResult[1],returnResult[2]);
                        return vResult;

                }

	public:
		ESPRIPlasPosition(){
			// Distance: 1188.17, 1187.47
			//leftPlane  = new Plane(-sqrt(3)/2,0.0,0.5,923);
			//rightPlane = new Plane(sqrt(3)/2,0.0,0.5,923.7);
			leftPlane  = new Plane(-sqrt(3)/2,0.0,0.5,-1188.17);
			rightPlane = new Plane(sqrt(3)/2,0.0,0.5,-1187.47);
			//rightPlane = new Plane(0.869,0.0,0.495,902.5);
	
			
		}
		~ESPRIPlasPosition(){}
		TVector3 getPlasPosition(int sideLR,TVector3 *espriPos,TVector3 *target){
			Plane *pl = NULL;
			if(sideLR==0) pl = leftPlane;
			else pl = rightPlane;

                        TVector3 planeVector = pl->getPlaneVector();
                        TVector3 planePoint  = pl->getPlanePoint();
                        TVector3 lineVector  = (*espriPos)-(*target);
                        TVector3 linePoint   = (*espriPos);
			return calPlaneLineIntersectPoint(planeVector,planePoint,lineVector,linePoint);

		}
};
class PositionESPRI{
	private:

		MergeESPRI *mergeData;

		double espriFL;
		double espriAngle;
		double espriLocusAngle;
		double espriPhi;

		TVector3 *espriRdcPosition;
		TVector3 *espriPlasPosition;
		TVector3 *vESPRI;

		// intermediate var
		TVector3 *targetPosition;
		TVector3 *vBeam;

		ESPRI3DPosition *espri3DPosition;
		ESPRIPlasPosition *plasPosition;
		PhiFunction 	*phiFunction;

		void setESPRIPosition(){
			setRdcPosition(mergeData->getSide(),mergeData->getRdcX(),mergeData->getRdcY());
			setPlasPosition();
		}
		void setRdcPosition(int sideLR,double dcX,double dcY){
			(*espriRdcPosition) = espri3DPosition->getESPRIPosition(sideLR,dcX,dcY);
			shiftCenter();
		}

		void shiftCenter(){
			double tempZ = (*espriRdcPosition).Z();
			(*espriRdcPosition).SetZ(tempZ + 4222.34);
		}
		void setPlasPosition(){
			(*espriPlasPosition) = plasPosition->getPlasPosition(mergeData->getSide(),espriRdcPosition,targetPosition);
		}

		void setESPRIAngle(){
			(*vESPRI)	= (*espriRdcPosition)-(*targetPosition);
			(*vESPRI)	= (*vESPRI).Unit();
			espriAngle      = (*vESPRI).Angle((*vBeam))*TMath::RadToDeg();
			TVector3 espriPlaneNorm = espri3DPosition->getESPRIPlaneNorm(mergeData->getSide());
			espriLocusAngle = (*vESPRI).Angle(espriPlaneNorm)*TMath::RadToDeg();
			espriPhi 	= phiFunction->getPhi((*vBeam),(*vESPRI));
		}
		void setESPRIFL(){
			espriFL = ((*espriPlasPosition)-(*targetPosition)).Mag();
		}
	public:
		PositionESPRI(){
			espri3DPosition = new ESPRI3DPosition();
			plasPosition = new ESPRIPlasPosition();
			phiFunction = new PhiFunction();
		}
		~PositionESPRI(){}
		void loadData(MergeESPRI *mergeESPRI){
			mergeData = mergeESPRI;
		}
		void init(){
			espriFL = NAN;
			espriAngle = NAN;
			espriPhi = NAN;
			espriLocusAngle = NAN;
			vESPRI->SetXYZ(NAN,NAN,NAN);
			espriRdcPosition->SetXYZ(NAN,NAN,NAN);
			espriPlasPosition->SetXYZ(NAN,NAN,NAN);
		}
		void analysis(){
			init();
			setESPRIPosition();
			setESPRIAngle();
			setESPRIFL();//FL Flight Length
		}
		void setBranch(TTree *tree){
			vESPRI = new TVector3;
			espriRdcPosition = new TVector3;
			espriPlasPosition = new TVector3;
			tree->Branch("vESPRI","TVector3",&vESPRI);
			tree->Branch("espriPosition","TVector3",&espriRdcPosition);
			tree->Branch("espriRdcPosition","TVector3",&espriRdcPosition);
			tree->Branch("espriPlasPosition","TVector3",&espriPlasPosition);
			tree->Branch("espriFL",&espriFL,"espriFL/D");
			tree->Branch("espriLocusAngle",&espriLocusAngle,"espriLocusAngle/D");
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");
			tree->Branch("espriPhi",&espriPhi,"espriPhi/D");
		}
		void print(){
			cout<<"Angle = "<<espriAngle<<"  Locus Angle = "<<espriLocusAngle<<endl;
			cout<<"Phi ="<<espriPhi<<endl;
			cout<<"FL = "<<espriFL<<endl;
			vESPRI->Print();
			espriRdcPosition->Print();
			espriPlasPosition->Print();
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		double getAngle(){
			return espriAngle;
		}
		double getLocusAngle(){
			return espriLocusAngle;
		}

		TVector3 * getPosition(){
			return espriRdcPosition;
		}

		TVector3 * getRdcPosition(){
			return espriRdcPosition;
		}

};
