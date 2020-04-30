#include "PositionESPRI.h"
#include "CalibESPRI.h"
class EspriEvent{
	private:

		ReadFile *rf;
		TVector3 *targetPosition;
		TVector3 *vBeam;

		CalibESPRI *calibESPRI;
		PositionESPRI *positionESPRI;
		
	public:
		void print(){
			calibESPRI->print();
			positionESPRI->print();
		}
		EspriEvent(){
			positionESPRI = new PositionESPRI();
			calibESPRI = new CalibESPRI();
		}

		~EspriEvent(){
			delete positionESPRI;
		}
		void loadData(ReadFile *mergeESPRI){
			rf = mergeESPRI;
		}

		void init(){

			rf = NULL;
		
			calibESPRI->init();
			positionESPRI->init();
		}
		void setOutputBranch(TTree *tree){

			calibESPRI->setBranch(tree);
			//positionESPRI->setBranch(tree);

		}
		void setESPRIEvent(){
				setESPRIEnergy();
				//setESPRIPosition();
		}
		bool isGoodEvent(){
			return rf->isGoodEvent()&&(getAngle()>0)&&(getNaiEnergy()>0);// Good Event->roughly good, real good event selected by TCut
		}
		void setESPRIPosition(){
			positionESPRI->loadTargetPosition(targetPosition);
			positionESPRI->loadBeamVector(vBeam);
			
			positionESPRI->loadData(rf);
			positionESPRI->analysis();
		}
		void setESPRIEnergy(){

			calibESPRI->loadData(rf);
			calibESPRI->calibrate();
			
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		bool isNaiHit(){
			return (rf->getNaiHit()==1);
		}
		double getNaiEnergy(){
			return calibESPRI->getNaiEnergy();
		}
		double getLocusAngle(){
			return positionESPRI->getLocusAngle();
		}
		double getAngle(){
			return positionESPRI->getAngle();
		}
};
