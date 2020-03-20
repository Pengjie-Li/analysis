#include "PhiFunction.h"
class Fdc0Event{
	private:

		ReadFile *rf;
		TVector3 *fdc0Position;
		TVector3 *targetPosition;
		TVector3 *vFDC0;
		TVector3 *vBeam;
		PhiFunction *phiFunction;
		TVector3 *targetCenter;


		double fdc0PhiS[2][7];
		double fdc0AngleS[2][7];

		void shiftLR(double angle){
			(*fdc0Position) = (*fdc0Position) - (*targetCenter);
			(*fdc0Position).RotateY(angle*TMath::DegToRad());
			(*fdc0Position) = (*fdc0Position) + (*targetCenter);
		}

		void shiftUD(double angle){
			(*fdc0Position) = (*fdc0Position) - (*targetCenter);
			(*fdc0Position).RotateX(angle*TMath::DegToRad());
			(*fdc0Position) = (*fdc0Position) + (*targetCenter);
		}
		double setAngle(){
			(*vFDC0)        = (*fdc0Position)-(*targetPosition);
			(*vFDC0)        = (*vFDC0).Unit();
			return (*vFDC0).Angle((*vBeam))*TMath::RadToDeg();
		}
		void setAngle(double rotateAng,double &angle,double &phi){

			(*fdc0Position).RotateZ(rotateAng*TMath::DegToRad());
			//fdc0Position->Print();
			(*vFDC0)        = (*fdc0Position)-(*targetPosition);
			(*vFDC0)        = (*vFDC0).Unit();
			angle 		 = (*vFDC0).Angle((*vBeam))*TMath::RadToDeg();
			phi  	         = phiFunction->getPhi((*vBeam),(*vFDC0));

			(*fdc0Position).RotateZ(-rotateAng*TMath::DegToRad());
		}

	public:
		Fdc0Event(){
			vFDC0 = new TVector3;
			phiFunction = new PhiFunction();
			targetCenter = new TVector3;
			targetCenter->SetXYZ(0,0,0);
		}

		~Fdc0Event(){
		}
		void init(){
			rf = NULL;
			vFDC0->SetXYZ(NAN,NAN,NAN);

			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					fdc0AngleS[i][j] =NAN;	
					fdc0PhiS[i][j] =NAN;	
				}

			}
		}
		void load(ReadFile *te){
			rf = te;
		}

		void setEvent(){

			fdc0Position = rf->getFdc0Position();
			vBeam = rf->getBeamDirection();
			targetPosition = rf->getTargetPosition();

			for (int i = 0; i < 4; ++i) {
				setAngle(0.6*(i+1),fdc0AngleS[0][i],fdc0PhiS[0][i]);
				setAngle(-0.6*(i+1),fdc0AngleS[1][i],fdc0PhiS[1][i]);
			}

			setAngle(1.1,fdc0AngleS[0][4],fdc0PhiS[0][4]);
			setAngle(1.3,fdc0AngleS[0][5],fdc0PhiS[0][5]);
			setAngle(1.4,fdc0AngleS[0][6],fdc0PhiS[0][6]);

			setAngle(-1.1,fdc0AngleS[1][4],fdc0PhiS[1][4]);
			setAngle(-1.3,fdc0AngleS[1][5],fdc0PhiS[1][5]);
			setAngle(-1.4,fdc0AngleS[1][6],fdc0PhiS[1][6]);

		}
		void print(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					cout<<fdc0AngleS[i][j]<<"  "<<fdc0PhiS[i][j]<<endl;	
				}
			}
		}
		void setOutputBranch(TTree *tree){

			tree->Branch("fdc0AngleS",fdc0AngleS,"fdc0AngleS[2][7]/D");
			tree->Branch("fdc0PhiS",fdc0PhiS,"fdc0PhiS[2][7]/D");

		}
};
