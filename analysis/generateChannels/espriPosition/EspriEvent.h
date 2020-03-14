#include "PhiFunction.h"
class EspriEvent{
	private:

		ReadFile *rf;
		TVector3 *espriPosition;
		TVector3 *targetPosition;
		TVector3 *vESPRI;
		TVector3 *vBeam;
		PhiFunction *phiFunction;
		TVector3 *targetCenter;

		double espriAngle[4][5];
		double espriPhi[4][5];


		void shiftLR(double angle){
			(*espriPosition) = (*espriPosition) - (*targetCenter);
			(*espriPosition).RotateY(angle*TMath::DegToRad());
			(*espriPosition) = (*espriPosition) + (*targetCenter);
		}
        
		void shiftUD(double angle){
			(*espriPosition) = (*espriPosition) - (*targetCenter);
			(*espriPosition).RotateX(angle*TMath::DegToRad());
			(*espriPosition) = (*espriPosition) + (*targetCenter);
		}
                double setAngle(){
                        (*vESPRI)        = (*espriPosition)-(*targetPosition);
                        (*vESPRI)        = (*vESPRI).Unit();
                        return (*vESPRI).Angle((*vBeam))*TMath::RadToDeg();
                }
                void setAngle(double &angle,double &phi){
                        (*vESPRI)        = (*espriPosition)-(*targetPosition);
                        (*vESPRI)        = (*vESPRI).Unit();
                        angle 		 = (*vESPRI).Angle((*vBeam))*TMath::RadToDeg();
			phi  	         = phiFunction->getPhi((*vBeam),(*vESPRI));
                }

	public:
		EspriEvent(){
			vESPRI = new TVector3;
			phiFunction = new PhiFunction();
			targetCenter = new TVector3;
			targetCenter->SetXYZ(0,0,0);
		}

		~EspriEvent(){
		}
		void init(){
			rf = NULL;
			vESPRI->SetXYZ(NAN,NAN,NAN);

			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j) {
					espriAngle[i][j] =NAN;	
					espriPhi[i][j] =NAN;	
				}
			}
		}
		void load(ReadFile *te){
			rf = te;
		}
		void setRdcPosition(int sideLR,double dcX,double dcY){
			(*espriRdcPosition) = espri3DPosition->getESPRIPosition(sideLR,dcX,dcY);
			shiftCenter();
		}
		void shiftCenter(){
			double tempZ = (*espriRdcPosition).Z();
			(*espriRdcPosition).SetZ(tempZ + 4222.34);
		}
		void setESPRIAngle(double offsetX, double offsetY,double &angle,double &phi){

			TVector3 *espriRdcPosition = setRdcPosition(rf->getEspriSide(),rf->getRdcX()+offsetX,rf->getRdcY()+offsetY);
			(*vESPRI)	= (*espriRdcPosition)-(*targetPosition);
			(*vESPRI)	= (*vESPRI).Unit();
			angle      = (*vESPRI).Angle((*vBeam))*TMath::RadToDeg();
			phi 	= phiFunction->getPhi((*vBeam),(*vESPRI));
		}

		void setEvent(){
			espriPosition = rf->getEspriPosition();
			targetPosition = rf->getTargetPosition();
			vBeam = rf->getBeamDirection();

			//targetPosition->Print();
			//vBeam->Print();
			//espriPosition->Print();
			//Shift Right Loop
			for (int i = 0; i < 5; ++i) {
				shiftLR(0.1);
				setAngle(espriAngle[0][i],espriPhi[0][i]);
			}
			//espriPosition->Print();
			shiftLR(-0.5);

			//Shift Left Loop
			for (int i = 0; i < 5; ++i) {
				shiftLR(-0.1);
				setAngle(espriAngle[1][i],espriPhi[1][i]);
			}
			//espriPosition->Print();
			shiftLR(0.5);

			//Shift Up Loop
			for (int i = 0; i < 5; ++i) {
				shiftUD(-0.1);
				setAngle(espriAngle[2][i],espriPhi[2][i]);
			}
			//espriPosition->Print();
			shiftUD(0.5);

			//Shift Down Loop
			for (int i = 0; i < 5; ++i) {
				shiftUD(0.1);
				setAngle(espriAngle[3][i],espriPhi[3][i]);
			}
			//espriPosition->Print();
			shiftUD(-0.5);

	
		}
		void print(){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j) {
					cout<<espriAngle[i][j]<<"  "<<espriPhi[i][j]<<endl;	
				}
			}
		}
		void setOutputBranch(TTree *tree){

			tree->Branch("espriAngleR",espriAngle,"espriAngleR[4][5]/D");
			tree->Branch("espriPhiR",espriPhi,"espriPhiR[4][5]/D");
		}
};
