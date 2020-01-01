#include "PositionESPRI.h"
#include "CalibESPRI.h"
class EspriEvent{
	private:

		double espriEnergy;
		double espriAngle;
		TVector3 *espriPosition;

		MergeESPRI *mergeData;
		TVector3 *targetPosition;
		TVector3 *vBeam;

		CalibESPRI *calibESPRI;
		PositionESPRI *positionESPRI;
		
	public:
		void print(){
			cout<<"espriEnergy = "<<espriEnergy<<" MeV  espriAngle = "<<espriAngle<<endl;
		}
		EspriEvent(){
			positionESPRI = new PositionESPRI();
			calibESPRI = new CalibESPRI();
		}

		~EspriEvent(){
			delete positionESPRI;
		}
		void loadData(MergeESPRI *mergeESPRI){
			mergeData = NULL;
			mergeData = mergeESPRI;
		}

		void init(){

			espriAngle = NAN;
			espriEnergy = NAN;
			espriPosition->SetXYZ(NAN,NAN,NAN);
		}
		void setOutputBranch(TTree *tree){

			espriPosition = new TVector3;

			positionESPRI->setBranch(tree);

			tree->Branch("espriEnergy",&espriEnergy,"espriEnergy/D");
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");

			tree->Branch("espriPosition","TVector3",&espriPosition);

		}
		void setESPRIEvent(){
			init();
			if(goodEvent()){
				setESPRIEnergy();
				setESPRIPosition();
			}
		}
		bool goodEvent(){
			return mergeData->isGoodEvent();// Good Event->roughly good, real good event selected by TCut
		}
		void setESPRIPosition(){
			positionESPRI->loadTargetPosition(targetPosition);
			positionESPRI->loadBeamVector(vBeam);
			
			positionESPRI->loadData(mergeData);
			positionESPRI->analysis();

			espriAngle = positionESPRI->getAngle();
			espriPosition = positionESPRI->getPosition();
		}
		void setESPRIEnergy(){

			calibESPRI->loadData(mergeData);
			calibESPRI->calibrate();
			
			espriEnergy = calibESPRI->getEnergy();
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}

};
