#include "PositionTELE.h"
#include "CalibTELE.h"
class TeleEvent{
	private:

		double teleEnergy;
		double teleAngle;

		MergeTELE *mergeData;

		TVector3 *telePosition;
		TVector3 *targetPosition;
		TVector3 *vBeam;
		
		CalibTELE *calibTELE;
		PositionTELE *positionTELE;

	public:
		void print(){
			cout<<"TELE Event:"<<endl;
			calibTELE->print();
			positionTELE->print();
			cout<<"teleEnergy = "<<teleEnergy<<" teleAngle = "<<teleAngle<<endl;
		}
		
		TeleEvent(){
			positionTELE = new PositionTELE();
			calibTELE = new CalibTELE();
		}
		~TeleEvent(){
			delete positionTELE;
			delete calibTELE;
		}
		void loadData(MergeTELE *mergeTELE){
			mergeData = mergeTELE;
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void init(){
			mergeData = NULL;
			teleEnergy = NAN;
			teleAngle = NAN;
			telePosition->SetXYZ(NAN,NAN,NAN);
			calibTELE->init();
			positionTELE->init();
		}
		void setOutputBranch(TTree *tree){
			telePosition = new TVector3;

			calibTELE->setBranch(tree);
			positionTELE->setBranch(tree);

			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("teleAngle",&teleAngle,"teleAngle/D");
			tree->Branch("telePosition","TVector3",&telePosition);
		}
		void setTELEEvent(){
			if(isGoodEvent()){
				setTELEEnergy();
				setTELEPosition();
			}
		}
		bool isGoodEvent(){
			return mergeData->isGoodEvent();
		}

		void setTELEPosition(){
			telePosition = positionTELE->getPosition(mergeData->getHitSide(),mergeData->getHitFid(),mergeData->getHitBid());
		}
		void setTELEEnergy(){
			calibTELE->loadData(mergeData);
			calibTELE->calibrate();
			teleEnergy = calibTELE->getEnergy();
		}
};
