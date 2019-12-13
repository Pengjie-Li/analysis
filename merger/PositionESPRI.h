class CheckEspriEvent{
	private:
		MergeESPRI *calibData;

		int isEspriLR;
		int isEspriPlas;
		int isEspriRdc;

		double dcX;
		double dcY;
		double plasE;
		int naiNHit;
		int naiBarId;
		double naiE; // no considering multiHit on Nai

		double getRdcX(int side){
			return calibData->getRdcX(side);
		}
		double getRdcY(int side){
			return calibData->getRdcY(side);
		}
		double getPlasQ(int side){
			return calibData->getPlasQ(side);
		}
		double getPlasT(int side){
			return calibData->getPlasT(side);
		}
		bool isRdc(int side){
		        //cout<<getRdcX(side)<<":"<<getRdcY(side)<<endl;
			if(getRdcX(side)>0&&getRdcY(side)>0) return true;
			else return false;
		}
		bool isPlas(int side){
			if(getPlasQ(side)>0.1) return true; // set PlasQ>100KeV
			if(getPlasT(side)>-700&&getPlasT(side)<-500) return true;
			return false;
		}
		int checkLR(bool isESPRIL,bool isESPRIR){
			if(isESPRIL &&!isESPRIR) return 0; 
			else if(!isESPRIL&&isESPRIR) return 1;
			else if(isESPRIL&&isESPRIR){
				cout<<"Left and Right both give effective Hit, check this event"<<endl;
				return 2;
			}
			else return -1;
		}
		void isESPRILR(){
			bool	isESPRIL=false;
			bool	isESPRIR=false;
			bool isRdcL = isRdc(0);
			bool isRdcR = isRdc(1);
			bool isPlasL = isPlas(0);
			bool isPlasR = isPlas(1);

			if(isRdcL&&isPlasL){
				isESPRIL = true;
			}
			if(isRdcR&&isPlasR){
				isESPRIR = true;
			}
			isEspriLR = checkLR(isESPRIL,isESPRIR);
			if(isEspriLR !=-1){
				isEspriRdc = isRdc(isEspriLR);
				isEspriPlas = isPlas(isEspriLR);
			}
			
			//cout<<"isRdcL:"<<isRdcL<<" isPlasL:"<<isPlasL<<" isESPRIL:"<<isESPRIL<<endl;
			//cout<<"isRdcR:"<<isRdcR<<" isPlasR:"<<isPlasR<<" isESPRIR:"<<isESPRIR<<endl;
			//cout<<"isEspriLR:"<<isEspriLR<<endl;
		}
		double getNaiBarQCal(int side,int id){
			return calibData->getNaiBarQCal(side,id);
		}
		void findNaiBarId(){

			for (int i = 0; i < 7; ++i) {
				if(getNaiBarQCal(isEspriLR,i)>1.0){
					naiNHit++;
					naiBarId = i;
				}
			}
		}

		void init(){

			calibData = NULL;
			isEspriLR = -1;
			isEspriRdc = -1;
			isEspriPlas = -1;
			naiNHit = 0;
			naiBarId = -1;
		}


	public:
		CheckEspriEvent(){}
		~CheckEspriEvent(){}
		void setBranch(TTree *tree){

			tree->Branch("isEspriLR",&isEspriLR,"isEspriLR/I");
			tree->Branch("isEspriRdc",&isEspriRdc,"isEspriRdc/I");
			tree->Branch("isEspriPlas",&isEspriPlas,"isEspriPlas/I");
			tree->Branch("naiBarId",&naiBarId,"naiBarId/I");
			tree->Branch("naiNHit",&naiNHit,"naiNHit/I");
		}
		void checkData(MergeESPRI *mergeData){
			init();
			calibData = mergeData;
			isESPRILR();	
			findNaiBarId();
		}
		bool isGoodEvent(){
			if(isEspriLR ==0||isEspriLR ==1) return true;
			else return false;
		}
		int getNaiId(){
			return naiBarId;
		}
		int getSideLR(){
			return isEspriLR;
		}
		void print(){
			cout<<"isEspriRdc = "<<isEspriRdc<<" isEspriPlas = "<<isEspriPlas<<" isEspriLR = "<<isEspriLR<<endl;
			cout<<"naiNHit = "<<naiNHit<<" naiBarId = "<<naiBarId<<endl;
		}
		double getDcX(){
			return getRdcX(isEspriLR);
		}
		double getDcY(){
			return getRdcY(isEspriLR);
		}




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
			leftPlaneNorm.SetXYZ(-TMath::Sqrt(3)/2,0,0.5);
			leftPedal.SetXYZ(-900.813644,0.000000,-3702.255000);
			leftBaseX.SetXYZ(0.500000,0.000000,0.866025);
			leftBaseY.SetXYZ(0.000000,1.000000,0.000000);

			rightPlaneNorm.SetXYZ(TMath::Sqrt(3)/2,0,0.5);
			rightPedal.SetXYZ(900.813644,0.000000,-3702.255000);
			rightBaseX.SetXYZ(0.500000,0.000000,-0.866025);
			rightBaseY.SetXYZ(0.000000,1.000000,0.000000);
	
			centerX = 227.5;
			centerY = 227.5;
		}
		TVector3 getESPRIPosition(int lr,double X,double Y){
			X = X -centerX;
			Y = Y -centerY;
			TVector3 pedal;
			TVector3 baseX;
			TVector3 baseY;
			if(lr ==0 ){
				pedal = leftPedal;
				baseX = leftBaseX;
				baseY = leftBaseY;
			}
			else{
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
			//leftPlane  = new Plane(-sqrt(3)/2,0.0,0.5,896);
			//rightPlane = new Plane(sqrt(3)/2,0.0,0.5,896);
			leftPlane  = new Plane(-sqrt(3)/2,0.0,0.5,676);
			rightPlane = new Plane(sqrt(3)/2,0.0,0.5,676);

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

		MergeESPRI *calibData;
		CheckEspriEvent *checkData;

		double espriFL;
		double espriAngle;
		double espriLocusAngle;
		TVector3 *espriRdcPosition;
		TVector3 *espriPlasPosition;
		TVector3 *vESPRI;

		// intermediate var
		TVector3 *targetPosition;
		TVector3 *vBeam;

		ESPRI3DPosition *espri3DPosition;
		ESPRIPlasPosition *plasPosition;

		void setESPRIPosition(){
			setRdcPosition(checkData->getSideLR(),checkData->getDcX(),checkData->getDcY());
			setPlasPosition();
		}
		void setRdcPosition(int sideLR,double dcX,double dcY){
			(*espriRdcPosition) = espri3DPosition->getESPRIPosition(sideLR,dcX,dcY);
		}
		void setPlasPosition(){
			(*espriPlasPosition) = plasPosition->getPlasPosition(checkData->getSideLR(),espriRdcPosition,targetPosition);
		}

		void setESPRIAngle(){
			(*vESPRI)	= (*espriRdcPosition)-(*targetPosition);
			(*vESPRI)	= (*vESPRI).Unit();
			espriAngle      = (*vESPRI).Angle((*vBeam))*TMath::RadToDeg();
			TVector3 espriPlaneNorm = espri3DPosition->getESPRIPlaneNorm(checkData->getSideLR());
			espriLocusAngle = (*vESPRI).Angle(espriPlaneNorm)*TMath::RadToDeg();
		}
		void setESPRIFL(){
			espriFL = ((*espriPlasPosition)-(*targetPosition)).Mag();
		}
	public:
		PositionESPRI(){
			espri3DPosition = new ESPRI3DPosition();
			plasPosition = new ESPRIPlasPosition();
		}
		~PositionESPRI(){}
		void loadEvent(CheckEspriEvent *checkESPRI){
			checkData = checkESPRI;
		}
		void loadData(MergeESPRI *mergeData){
			calibData = mergeData;
		}
		void init(){
			espriFL = NAN;
			espriAngle = NAN;
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
			tree->Branch("espriRdcPosition","TVector3",&espriRdcPosition);
			tree->Branch("espriPlasPosition","TVector3",&espriPlasPosition);
			tree->Branch("espriFL",&espriFL,"espriFL/D");
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");
			tree->Branch("espriLocusAngle",&espriLocusAngle,"espriLocusAngle/D");
		}
		void print(){
			cout<<"Angle = "<<espriAngle<<"  Locus Angle = "<<espriLocusAngle<<endl;
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

};
