#include "CalibESPRI.h"
class EspriEvent{
	private:

		ReadFile *rf;
		TVector3 *targetPosition;
		TVector3 *vBeam;

		CalibESPRI *calibESPRI;
		
	public:
		void print(){
			calibESPRI->print();
		}
		EspriEvent(){
			calibESPRI = new CalibESPRI();
		}

		~EspriEvent(){
		}
		void loadData(ReadFile *mergeESPRI){
			rf = mergeESPRI;

			targetPosition = rf->getTargetPosition();
			vBeam = rf->getBeamDirection();
		}

		void init(){

			rf = NULL;
		
			calibESPRI->init();
		}
		void setOutputBranch(TTree *tree){

			calibESPRI->setBranch(tree);

		}
		void setESPRIEvent(){
			calibESPRI->loadData(rf);
			calibESPRI->calibrate();

		}
		double getNaiEnergy(){
			return calibESPRI->getNaiEnergy();
		}
		double getLocusAngle(){
			return rf->getEspriLocusAngle();
		}
		double getAngle(){
			return rf->getEspriAngle();
		}
};
