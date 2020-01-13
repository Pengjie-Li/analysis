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
		
		int 	goodTeleHit[3];
		double teleCsiE[3];
		double teleCsiE_sync[3];
		double teleDssdFE[3];
		double teleDssdBE[3];
		double teleCsiT[3];
		double teleDssdT[3];
		double teleEnergy[3];
		double teleX[3];
		double teleY[3];
		double teleZ[3];
		TVector3 *telePosition[3];

		TVector3 getPosition(int i){
			return positionTELE->getPosition(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitBid(i));
		}
		int getHit(){
			return mergeData->getHit();
		}
		double getCsiE(int i){
			return calibEnergy->getCsiE(mergeData->getHitCid(i),mergeData->getHitCsiQPed(i));
		} 
		double getCsiE_sync(int i){
			return calibEnergy->getSyncCsiE(mergeData->getHitCid(i),mergeData->getHitCsiQPed(i));
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

			for (int i = 0; i < getHit(); ++i) {
				
				if(goodTeleHit[i] == 1) cout<<" dssdE = "<<teleDssdFE[i]<<" "<<teleDssdBE[i]<<" csiE ="<<teleCsiE[i]<<" totE = "<<teleEnergy[i]<<" dssdPosition : "<<teleX[i]<<" "<<teleY[i]<<" "<<teleZ[i]<<endl;
			}
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
				teleCsiE[i]=NAN;
				teleCsiE_sync[i]=NAN;
				teleDssdFE[i]=NAN;
				teleDssdBE[i]=NAN;
				teleCsiT[i]=NAN;
				teleDssdT[i]=NAN;
				teleEnergy[i]=NAN;
				teleX[i] = NAN;
				teleY[i] = NAN;
				teleZ[i] = NAN;
				telePosition[i]->SetXYZ(NAN,NAN,NAN);
				
			}
		}
		void setOutputBranch(TTree *tree){

			telePosition[0] = new TVector3();
			telePosition[1] = new TVector3();
			telePosition[2] = new TVector3();

			tree->Branch("goodTeleHit",&goodTeleHit,"goodTeleHit[teleHit]/I");
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE[teleHit]/D");
			tree->Branch("teleCsiE_sync",&teleCsiE_sync,"teleCsiE_sync[teleHit]/D");
			tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE[teleHit]/D");
			tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE[teleHit]/D");
			tree->Branch("teleCsiT",&teleCsiT,"teleCsiT[teleHit]/D");
			tree->Branch("teleDssdT",&teleDssdT,"teleDssdT[teleHit]/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy[teleHit]/D");
			tree->Branch("teleX",&teleX,"teleX[teleHit]/D");
			tree->Branch("teleY",&teleY,"teleY[teleHit]/D");
			tree->Branch("teleZ",&teleZ,"teleZ[teleHit]/D");
			//tree->Branch("telePosition","TVector3","telePosition[teleHit]/D");
	
		}
		void setEvent(){
			for (int i = 0; i < getHit(); ++i) {

				teleCsiE[i]	 = getCsiE(i);
				teleCsiE_sync[i]	 = getCsiE_sync(i);
				teleDssdFE[i]	 = getDssdFrontE(i);
				teleDssdBE[i]	 = getDssdBackE(i);
				teleCsiT[i]	 = getCsiT(i);
				teleDssdT[i]	 = getDssdT(i);
				teleEnergy[i]	 = 0.5*(teleDssdFE[i]+teleDssdBE[i])+teleCsiE[i];
				(*telePosition[i])	 = getPosition(i);
				teleX[i] = telePosition[i]->X();
				teleY[i] = telePosition[i]->Y();
				teleZ[i] = telePosition[i]->Z();
			}
		}
		double getDEECsiE(double dssdE){
			return deePara->getDEECsiE(dssdE);
		}
		double getDEEResidue(int i){
			return abs(getDEECsiE(0.5*(teleDssdFE[i]+teleDssdBE[i]))- teleCsiE[i]);
		}
		bool isGoodEvent(){
			if(getHit()==0) return false;
			if(getHit()==1) return true;
			if(getHit()>1){
				for (int i = 0; i < getHit()-1; ++i) {
					if(getDEEResidue(i)>getDEEResidue(i+1)) goodTeleHit[i] = -1;
					else goodTeleHit[i+1] = -1;
				}
				return true;
			}
			else return false;
		}
		TVector3 getDssdPlaneNorm(){
			for (int i = 0; i < getHit(); ++i) {
				if(goodTeleHit[i]==1) return positionTELE->getDssdPlaneNorm(mergeData->getHitSide(i));
			}
		}
		TVector3 *getTelePosition(){
			for (int i = 0; i < getHit(); ++i) {
				if(goodTeleHit[i]==1) return telePosition[i];
			}
		}
		double getCsiEnergy(){
			for (int i = 0; i < getHit(); ++i) {
				if(goodTeleHit[i]==1) return teleCsiE[i];
			}

		}
};
