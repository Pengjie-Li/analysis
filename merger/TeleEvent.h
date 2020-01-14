#include "PositionTELE.h"
#include "CalibTELE.h"
class DEECurve{
	private:
		TGraph *dEE;
	public:
		DEECurve(){
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
                        dEE = (TGraph *)gDirectory->Get("dEEReverse");
                        fCalib->Close();	

		}
		~DEECurve(){}
		double getDEECsiE(double dssd){
			return dEE->Eval(dssd);
		}
};
class TeleEvent{
	private:

		
		MergeTELE *mergeData;
		DEECurve *deePara;

		EnergyTELE *calibEnergy;
		TimeTELE *calibTime;
		PositionTELE *positionTELE;
		
		int iHit;
		int 	goodTeleHit[3];
		double teleCsiE;
		double teleCsiE_sync;
		double teleDssdFE;
		double teleDssdBE;
		double teleDssdE;
		double teleCsiT;
		double teleDssdT;
		double teleEnergy;

		double teleX;
		double teleY;
		double teleZ;
		TVector3 *telePosition;

		TVector3 getPosition(int i){
			return positionTELE->getPosition(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitBid(i));
		}
		int getHit(){
			return mergeData->getHit();
		}
		double getCsiE(int i){

			double csiE = calibEnergy->getCsiE(mergeData->getHitCid(i),mergeData->getHitCsiQPed(i));

			if(mergeData->getRunNumber()<305&&mergeData->getHitCid(i)==4) csiE = 1.8*csiE;  
			return csiE;
		} 
		double getCsiE_sync(int i){
			double csiE =  calibEnergy->getSyncCsiE(mergeData->getHitCid(i),mergeData->getHitCsiQPed(i));
			if(mergeData->getRunNumber()<305&&mergeData->getHitCid(i)==4) csiE = 1.8*csiE;  
			return csiE;
		} 

		double getCsiT(int i){
			return calibTime->getCsiT(mergeData->getHitCid(i),mergeData->getHitCsiTCal(i));
		} 
		double getDssdFrontE(int i){
			return calibEnergy->getDssdFrontE(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitDssdFQPed(i));
		}

		double getDssdBackE(int i){
			return calibEnergy->getDssdBackE(mergeData->getHitSide(i),mergeData->getHitBid(i),mergeData->getHitDssdBQPed(i));
		}
		double getDssdT(int i){
			return calibTime->getDssdT(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitDssdTCal(i));
		}


	public:
		void print(){
			cout<<"TELE Event:"<<endl;

				
			cout<<" dssdE = "<<teleDssdFE<<" "<<teleDssdBE<<" csiE ="<<teleCsiE<<" totE = "<<teleEnergy<<" dssdPosition : "<<teleX<<" "<<teleY<<" "<<teleZ<<endl;
			
			//cout<<"Tele Time: dssdT = "<<teleDssdT<<" csiT ="<<teleCsiT<<endl;	
	
		}
		
		TeleEvent(){
			calibEnergy = new EnergyTELE();
			calibTime = new TimeTELE();
			positionTELE = new PositionTELE();
			deePara = new DEECurve();
		}
		~TeleEvent(){
			delete positionTELE;
			delete calibEnergy;
			delete calibTime;
			delete deePara;
		}
		void loadData(MergeTELE *mergeTELE){
			mergeData = mergeTELE;
		}
		void init(){
			mergeData = NULL;
			for (int i = 0; i < 3; ++i) {

				goodTeleHit[i]=1;
							
			}
			iHit = -1;
			teleCsiE=NAN;
			teleCsiE_sync=NAN;
			teleDssdFE=NAN;
			teleDssdBE=NAN;
			teleDssdE=NAN;
			teleCsiT=NAN;
			teleDssdT=NAN;
			teleEnergy=NAN;
			teleX = NAN;
			teleY = NAN;
			teleZ = NAN;
			telePosition->SetXYZ(NAN,NAN,NAN);

		}
		void setOutputBranch(TTree *tree){

			telePosition = new TVector3();

			tree->Branch("goodTeleHit",&goodTeleHit,"goodTeleHit[teleHit]/I");
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
			tree->Branch("teleCsiE_sync",&teleCsiE_sync,"teleCsiE_sync/D");
			tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE/D");
			tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE/D");
			tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
			tree->Branch("teleCsiT",&teleCsiT,"teleCsiT/D");
			tree->Branch("teleDssdT",&teleDssdT,"teleDssdT/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("telePosition","TVector3",&telePosition);
	
		}
		void setEvent(){
			iHit = getGoodHit();
			if(isGoodEvent()){
				teleCsiE	 = getCsiE(iHit);
				teleCsiE_sync	 = getCsiE_sync(iHit);
				teleDssdFE	 = getDssdFrontE(iHit);
				teleDssdBE	 = getDssdBackE(iHit);
				teleCsiT	 = getCsiT(iHit);
				teleDssdT	 = getDssdT(iHit);
				teleDssdE	 = 0.5*(teleDssdFE+teleDssdBE);
				teleEnergy	 = teleDssdE+teleCsiE;
				(*telePosition)	 = getPosition(iHit);
				teleX = telePosition->X();
				teleY = telePosition->Y();
				teleZ = telePosition->Z();
			}
		}
		double getDEECsiE(double dssdE){
			return deePara->getDEECsiE(dssdE);
		}
		double getDEEResidue(int i){
			return abs(getDEECsiE(0.5*(getDssdFrontE(i)+getDssdBackE(i)))- getCsiE(i));
		}
		int getGoodHit(){
			if(getHit()==1) return 0;
			if(getHit()>1){
				for (int i = 0; i < getHit()-1; ++i) {
					if(getDEEResidue(i)>getDEEResidue(i+1)) goodTeleHit[i] = -1;
					else goodTeleHit[i+1] = -1;
				}
				for (int i = 0; i < getHit(); ++i) {
					if(abs(getDssdFrontE(i)-getDssdBackE(i))<2){
						if(goodTeleHit[i]==1) return i;
					}
				}
			}
			return -1;
		}
		bool isGoodEvent(){
			if(iHit!=-1) return true;
			else return false;
		}
		TVector3 getDssdPlaneNorm(){
			return positionTELE->getDssdPlaneNorm(mergeData->getHitSide(iHit));
		}
		TVector3 *getTelePosition(){
			return telePosition;
		}
		double getCsiEnergy(){
			return teleCsiE;
		}
};
