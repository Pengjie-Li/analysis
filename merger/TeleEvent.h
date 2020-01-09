#include "PositionTELE.h"
#include "CalibTELE.h"
class TeleEvent{
	private:

		MergeTELE *mergeData;

		TeleEnergy *calibEnergy;
		TeleTime *calibTime;
		PositionTELE *positionTELE;
		
		double teleCsiE[3];
		double teleDssdFE[3];
		double teleDssdBE[3];
		double teleCsiT[3];
		double teleDssdT[3];
		double teleEnergy[3];
		TVector3 *telePosition[3];

		TVector3* getPosition(int i){
			return positionTELE->getPosition(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitBid(i));
		}
		double getCsiE(int i){
			return calibEnergy->getCsiE(mergeData->getHitCid(i),mergeData->getHitCsiQPed(i));
		} 
		double getCsiT(int i){
			return calibEnergy->getCsiE(mergeData->getHitCid(i),mergeData->getHitCsiTCal(i));
		} 
		double getDssdFrontE(int i){
			return calibEnergy->getDssdE(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitDssdFQPed(i));
		}

		double getDssdBackE(int i){
			return calibEnergy->getDssdE(mergeData->getHitSide(i),mergeData->getHitBid(i),mergeData->getHitDssdBQPed(i));
		}

		double getDssdT(int i){
			return calibTime->getDssdT(mergeData->getHitSide(i),mergeData->getHitBid(i));
		}



	public:
		void print(){
			cout<<"TELE Event:"<<endl;

			cout<<"Tele Energy: dssdE = "<<teleDssdE<<" csiE ="<<teleCsiE<<" totE = "<<teleEnergy<<endl;	
			cout<<"Tele Time: dssdT = "<<teleDssdT<<" csiT ="<<teleCsiT<<endl;	
	
		}
		
		TeleEvent(){
			calibEnergy = new TeleEnergy();
			calibTime = new TeleTime();
			positionTELE = new PositionTELE();
		}
		~TeleEvent(){
			delete positionTELE;
			delete calibEnergy;
			delete calibTime;
		}
		void loadData(MergeTELE *mergeTELE){
			mergeData = mergeTELE;
		}
		void init(){
			mergeData = NULL;
			for (int i = 0; i < 3; ++i) {

				teleCsiE[i]=NAN;
				teleDssdFE[i]=NAN;
				teleDssdBE[i]=NAN;
				teleCsiT[i]=NAN;
				teleDssdT[i]=NAN;
				teleEnergy[i]=NAN;
				telePosition->SetXYZ(NAN,NAN,NAN);
				
			}
		}
		void setOutputBranch(TTree *tree){

			telePosition[0] = new TVector3();
			telePosition[1] = new TVector3();
			telePosition[2] = new TVector3();

			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE[teleHit]/D");
			tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE[teleHit]/D");
			tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE[teleHit]/D");
			tree->Branch("teleCsiT",&teleCsiT,"teleCsiT[teleHit]/D");
			tree->Branch("teleDssdT",&teleDssdT,"teleDssdT[teleHit]/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy[teleHit]/D");
			tree->Branch("telePosition",&telePosition,"telePosition[teleHit]/D");
	
		}
		void setTELEEvent(){
			for (int i = 0; i < getTeleHit(); ++i) {

				teleCsiE[i]	 = getCsiE(i);
				teleDssdFE[i]	 = getDssdFrontE(i);
				teleDssdBE[i]	 = getDssdBackE(i);
				teleCsiT[i]	 = getCsiT(i);
				teleDssdT[i]	 = getDssdT(i);
				teleEnergy[i]	 = 0.5*(teleDssdFE[i]+teleDssdBE[i])+teleCsiE[i];
				telePosition[i]	 = getPosition(i);
			}
		}
};
