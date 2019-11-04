class ESPRI3DPosition{
	private:
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
			leftPedal.SetXYZ(-878.501926,-4.057746,-3715.121798);
			leftBaseX.SetXYZ(0.500011,0.000000,0.866019);
			leftBaseY.SetXYZ(-0.003464,0.999992,0.002000);
			rightPedal.SetXYZ(882.276111,0.000000,-3719.777658);
			rightBaseX.SetXYZ(0.494954,0.000000,-0.868919);
			rightBaseY.SetXYZ(0.000000,1.000000,-0.000000);
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
		~ESPRI3DPosition(){}
};
class PositionESPRI{
	private:

		double espriAngle;
		TVector3 *espriPosition;

		// intermediate var
		TVector3 *targetPosition;
		TVector3 *vBeam;
		int sideLR;
		double dcX;
		double dcY;

		ESPRI3DPosition *espri3DPosition;

		void setESPRIPosition(int sideLR,double dcX,double dcY){
			(*espriPosition) = espri3DPosition->getESPRIPosition(sideLR,dcX,dcY);
				//espriPosition->Print();
			}

		void setESPRIAngle(){
			espriAngle = ((*espriPosition)-(*targetPosition)).Angle((*vBeam))*TMath::RadToDeg();
		}
	public:
		PositionESPRI(){
			espri3DPosition = new ESPRI3DPosition();
		}
		~PositionESPRI(){}
		void init(){
			espriAngle = NAN;
			espriPosition->SetXYZ(NAN,NAN,NAN);
		}
		void analysis(){
			init();
			//setESPRIPosition();
			//setESPRIAngle();
		}
		void setBranch(TTree *tree){
			espriPosition = new TVector3;
			tree->Branch("espriPosition","TVector3",&espriPosition);
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");
		}
		void print(){
			cout<<"Angle = "<<espriAngle<<endl;
			espriPosition->Print();
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}

};
