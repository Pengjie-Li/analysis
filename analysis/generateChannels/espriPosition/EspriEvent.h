#include "PhiFunction.h"
#include "PositionESPRI.h"
class EspriEvent{
	private:

		ReadFile *rf;
		TVector3 *espriPosition;
		TVector3 *targetPosition;
		TVector3 *vESPRI;
		TVector3 *vBeam;
		PhiFunction *phiFunction;
		TVector3 *targetCenter;
		ESPRI3DPosition *espri3DPosition;

		double espriAngle[4][5];
		double espriPhi[4][5];

		double espriPhiS[4][7];
		double espriAngleS[4][7];

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
			espri3DPosition = new ESPRI3DPosition();
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
				for (int j = 0; j < 7; ++j) {
					espriAngleS[i][j] =NAN;	
					espriPhiS[i][j] =NAN;	
				}
	
			}
		}
		void load(ReadFile *te){
			rf = te;
		}
		void setESPRIAngle(double offsetX, double offsetY,double &angle,double &phi){

			TVector3 *espriRdcPosition = new TVector3;
			(*espriRdcPosition) = espri3DPosition->getESPRIPosition(rf->getEspriSide(),rf->getRdcX()+offsetX,rf->getRdcY()+offsetY);
			double tempZ = (*espriRdcPosition).Z();
			(*espriRdcPosition).SetZ(tempZ + 4222.34);


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
			for (int i = 0; i < 7; ++i) {
				//setESPRIAngle(i+1 ,0,espriAngleS[0][i],espriPhiS[0][i]);
				//setESPRIAngle(-i-1,0,espriAngleS[1][i],espriPhiS[1][i]);

				setESPRIAngle(0,i+1+7 ,espriAngleS[0][i],espriPhiS[0][i]);
				setESPRIAngle(0,-i-1-7,espriAngleS[1][i],espriPhiS[1][i]);
				setESPRIAngle(0 ,i+1,espriAngleS[2][i],espriPhiS[2][i]);
				setESPRIAngle(0,-i-1,espriAngleS[3][i],espriPhiS[3][i]);
			}
	
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

			tree->Branch("espriAngleS",espriAngleS,"espriAngleS[4][7]/D");
			tree->Branch("espriPhiS",espriPhiS,"espriPhiS[4][7]/D");

		}
};
