#include "PositionESPRI.h"
#include "CalibESPRI.h"
class EspriEvent{
	private:

		MergeESPRI *mergeData;
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
		void loadData(MergeESPRI *mergeESPRI){
			mergeData = mergeESPRI;
		}

		void init(){

			mergeData = NULL;
		
			calibESPRI->init();
			positionESPRI->init();
		}
		void setOutputBranch(TTree *tree){

			calibESPRI->setBranch(tree);
			positionESPRI->setBranch(tree);

		}
		void setESPRIEvent(){
			if(mergeData->isGoodEvent()){
				setESPRIEnergy();
				setESPRIPosition();
			}
		}
		bool isGoodEvent(){
			return mergeData->isGoodEvent()&&(getAngle()>0)&&(getNaiEnergy()>0);// Good Event->roughly good, real good event selected by TCut
		}
		void setESPRIPosition(){
			positionESPRI->loadTargetPosition(targetPosition);
			positionESPRI->loadBeamVector(vBeam);
			
			positionESPRI->loadData(mergeData);
			positionESPRI->analysis();
		}
		void setESPRIEnergy(){

			calibESPRI->loadData(mergeData);
			calibESPRI->calibrate();
			
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		bool isNaiHit(){
			return (mergeData->getNaiHit()==1);
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
		int getEspriSide(){
			return mergeData->getSide();
		}
		TVector3 * getTargetPosition(){
			return targetPosition;
		}
		TVector3 * getRdcPosition(){
			return positionESPRI->getRdcPosition();
		}
};
