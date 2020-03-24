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


		double fdc0PhiS[4][4];
		double fdc0AngleS[4][4];

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


		void shiftFdc0(double dx,double dy,double &angle,double &phi){

			double xTemp = (*fdc0Position).X();
			double yTemp = (*fdc0Position).Y();
			(*fdc0Position).SetX(xTemp+dx);
			(*fdc0Position).SetY(yTemp+dy);
			//fdc0Position->Print();
			(*vFDC0)        = (*fdc0Position)-(*targetPosition);
			(*vFDC0)        = (*vFDC0).Unit();
			angle 		 = (*vFDC0).Angle((*vBeam))*TMath::RadToDeg();
			phi  	         = phiFunction->getPhi((*vBeam),(*vFDC0));

			(*fdc0Position).SetX(xTemp);
			(*fdc0Position).SetY(yTemp);
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

			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
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

			shiftFdc0( 0.64, 0.75,fdc0AngleS[2][0],fdc0PhiS[2][0]);
			shiftFdc0(-0.64,-0.75,fdc0AngleS[2][1],fdc0PhiS[2][1]);
			shiftFdc0(-0.64, 0.75,fdc0AngleS[2][2],fdc0PhiS[2][2]);
			shiftFdc0( 0.64,-0.75,fdc0AngleS[2][3],fdc0PhiS[2][3]);


			shiftFdc0( 0.64*2, 0.75*2,fdc0AngleS[3][0],fdc0PhiS[3][0]);
			shiftFdc0(-0.64*2,-0.75*2,fdc0AngleS[3][1],fdc0PhiS[3][1]);
			shiftFdc0(-0.64*2, 0.75*2,fdc0AngleS[3][2],fdc0PhiS[3][2]);
			shiftFdc0( 0.64*2,-0.75*2,fdc0AngleS[3][3],fdc0PhiS[3][3]);



		}
		void print(){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					cout<<fdc0AngleS[i][j]<<"  "<<fdc0PhiS[i][j]<<endl;	
				}
			}
		}
		void setOutputBranch(TTree *tree){

			tree->Branch("fdc0AngleS",fdc0AngleS,"fdc0AngleS[4][4]/D");
			tree->Branch("fdc0PhiS",fdc0PhiS,"fdc0PhiS[4][4]/D");

		}
};
