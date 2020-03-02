#include "PositionESPRI.h"
#include "CalibESPRI.h"
class EspriEvent{
	private:

		double espriEnergy;
		double espriAngle;
		TVector3 *espriPosition;
		double espriAngle_rand;

		MergeESPRI *mergeData;
		TVector3 *targetPosition;
		TVector3 *vBeam;

		CalibESPRI *calibESPRI;
		PositionESPRI *positionESPRI;
		
	public:
		void print(){
			calibESPRI->print();
			positionESPRI->print();
			cout<<"espriEnergy = "<<espriEnergy<<" MeV  espriAngle = "<<espriAngle<<"  espriLocusAngle = "<<getLocusAngle()<<endl;
			
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
			espriAngle = NAN;
			espriEnergy = NAN;
			espriPosition->SetXYZ(NAN,NAN,NAN);
			espriAngle_rand = NAN;
		
			calibESPRI->init();
			positionESPRI->init();
		}
		void setOutputBranch(TTree *tree){

			espriPosition = new TVector3;

			calibESPRI->setBranch(tree);
			positionESPRI->setBranch(tree);

			tree->Branch("espriEnergy",&espriEnergy,"espriEnergy/D");
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");

			tree->Branch("espriAngle_rand",&espriAngle_rand,"espriAngle_rand/D");
			tree->Branch("espriPosition","TVector3",&espriPosition);

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

			espriAngle = positionESPRI->getAngle();
			espriAngle_rand = espriAngle+gRandom->Uniform(-0.3,0.3);
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
};
