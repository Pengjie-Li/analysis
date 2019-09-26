#include "PositionTELE.h"
class TeleEvent{
	private:
		TEnv *env;

		double dssdSideQ[4];
		double dssdNHit[4];
		int dssdId[4];
	
		int csiNHit;
		int hitIdArray[5];
		int csiId;
		int dssdFid;
		int dssdBid;

		MergeTELE *calibData;
		double teleDssdE;
		double teleCsiE;
		double teleEnergy;
		double teleAngle;
		TVector3 *telePosition;
		TVector3 *targetPosition;
		TVector3 *vBeam;
		PositionTELE *positionTELE;

	public:
		void print(){
			if(csiId!=-1){	
				cout<<"TELE Event:"<<endl;
				cout<<"csiNHit = "<<csiNHit<<" csiId = "<<csiId<<endl;
				cout<<"dE = "<<teleDssdE<<" E ="<<teleCsiE<<" TotalE = "<<teleEnergy<<endl;
				cout<<"side = "<<((csiId<4)?1:0)<<" dssdFid = "<<dssdFid<<" dssdBid = "<<dssdBid<<endl;
				cout<<"Angle = "<<teleAngle<<endl;
				telePosition->Print();
			}
		}
		void setTELEEvent(){
			init();
			analysingDSSD();
			selectGoodEvent();
			if(csiId != -1){
				setTELEEnergy();
				setTELEAngle();
			}
		}
		void selectGoodEvent(){
			findCsiMultHit();		
			determineCsiId();
		}
		void setTELEEnergy(){
			teleDssdE = getDssdEnergy(csiId);	
			teleCsiE = getCsiQCal(csiId);
			teleEnergy = teleDssdE + teleCsiE;
			//cout<<"dE = "<<teleDssdE<<" E ="<<teleCsiE<<" Total = "<<teleEnergy<<endl;
		}
		void setTELEAngle(){
			//loadPos
			setTELEPosition();
			teleAngle = ((*telePosition)-(*targetPosition)).Angle((*vBeam))*TMath::RadToDeg();
	
		}

		void findCsiMultHit(){
			for (int i = 0; i < 7; ++i) {
				//if(getCsiQCal(i)>10&&getSiQCal(i)> 1)
				if(getCsiQCal(i)>50){
					hitIdArray[csiNHit] = i;
					csiNHit++;
					//cout<<i<<":"<<csiNHit<<endl;
				}	

			}
			//if(csiNHit>2) cout<<csiNHit<<endl;
		}
		double getDssdEnergyCal(int side,int id){
			return calibData->getDssdEnergyCal(side,id);
		}
		double getDssdEnergy(int csi){
			int side = (csi<4)?1:0;
			//cout<<dssdSideQ[2*side]<<":"<<dssdSideQ[2*side+1]<<endl;
			return 0.5*(dssdSideQ[2*side]+dssdSideQ[2*side+1])/1000.;
		}
		double getCsiQCal(int id){
			return calibData->getCsiQCal(id);	
		}
		void determineCsiId(){
			if(csiNHit == 1&&checkDssdHit(hitIdArray[0])){
				csiId = hitIdArray[0];
			}
			if(csiNHit > 1){
				for (int i = 0; i < csiNHit; ++i) {
				int csiNum = hitIdArray[i];
				if(checkCsiRange(csiNum)&&checkDssdHit(csiNum)) csiId = csiNum;	
				}
				if(csiId == -1) csiId = hitIdArray[0];
			}
			//cout<<"csiNHit = "<<csiNHit<<" csiId = "<<csiId<<endl;
		}
		bool checkCsiRange(int i){
			if(getCsiQCal(i)>50&&getCsiQCal(i)<1000) return true;
			return false;
		}
		bool checkDssdHit(int id){
			int side = (id<4)?1:0;
			if(dssdNHit[2*side]>0&&dssdNHit[2*side+1]>0) return true;
			return false;
		}
		void analysingDSSD(){
			for (int i = 0; i < 4; ++i) {
				setDssdSide(i);
			}
		}
		void setDssdSide(int side){

			double dssdQThr = env->GetValue("siliconHitThreshold",500.);
			for (int i = 0; i < 32; ++i) {
				if(getDssdEnergyCal(side,i)>dssdQThr){
					dssdNHit[side]++; 
					if(getDssdEnergyCal(side,i)>dssdSideQ[side]){
						dssdId[side] = i;	
						dssdSideQ[side] = getDssdEnergyCal(side,i);
					}
				}
			}
		}
		void setTELEPosition(){
			int side = (csiId<4)?1:0;
			dssdFid = dssdId[2*side];	
			dssdBid = dssdId[2*side+1];	
			//cout<<side<<":"<<dssdFid<<":"<<dssdBid<<endl;
			if(dssdFid!=-1&&dssdBid!=-1){
				(*telePosition) = positionTELE->getTELEPosition(side,dssdFid,dssdBid);
				//telePosition->Print();
			}

		}

		
		TeleEvent(){
			env = new TEnv("configMerger.prm");
			positionTELE = new PositionTELE();
		}
		~TeleEvent(){
			delete env;
			delete positionTELE;
		}
		void loadData(MergeTELE *mergeTELE){
			calibData = mergeTELE;
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void init(){
			for (int i = 0; i < 4; ++i) {
				dssdSideQ[i] = -9999;
				dssdNHit[i] = 0;
			}
			dssdFid = -1;
			dssdBid = -1;

			csiNHit = 0;
			for (int i = 0; i < 5; ++i) {
				hitIdArray[i] = -1;
			}
			csiId = -1; // 0-6 for CsI LL, LRT, LRB, RLT,RLB,RRT,RRB
			teleDssdE = NAN;
			teleCsiE = NAN;
			teleEnergy = NAN;
			teleAngle = NAN;
			telePosition->SetXYZ(NAN,NAN,NAN);
		}
		void setOutputBranch(TTree *tree){
			telePosition = new TVector3;

			tree->Branch("dssdNHit",dssdNHit,"dssdNHit[4]/I");
			tree->Branch("dssdSideQ",dssdSideQ,"dssdSideQ[4]/D");
			tree->Branch("dssdId",dssdId,"dssdId[4]/I");

			tree->Branch("csiNHit",&csiNHit,"csiNHit/I");
			tree->Branch("csiHitIdArray",&hitIdArray,"hitIdArray[csiNHit]/I");
			tree->Branch("csiId",&csiId,"csiId/I");
			tree->Branch("dssdFid",&dssdFid,"dssdFid/I");
			tree->Branch("dssdBid",&dssdBid,"dssdBid/I");

			tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("teleAngle",&teleAngle,"teleAngle/D");
			tree->Branch("telePosition","TVector3",&telePosition);
		}	
};
