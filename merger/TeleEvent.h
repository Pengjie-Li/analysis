class TeleEvent{
	private:

		double dssdSideQ[4];
		double dssdNHit[4];
	
		int csiNHit;
		int hitIdArray[5];
		int csiId;
		int dssdFid;
		int dssdBid;

	//double csiQ
		MergeTELE *calibData;
		double teleDssdE;
		double teleCsiE;
		double teleEnergy;
		double teleAngle;
		TVector3 *telePosition;
		TVector3 *targetPosition;
		TVector3 *vBeam;

	public:
		void analysingDSSD(){
			for (int i = 0; i < 4; ++i) {
				setDssdSide(i);
			}
		}
		void setDssdSide(int side){

			double dssdQThr = env->GetValue("siliconHitThreshold",500.);
			for (int i = 0; i < 32; ++i) {
				if(getDssdEnergyCal(side,i)>dssdQThr) dssdNHit[side]++; 
				if(getDssdEnergyCal(side,i)>dssdSideQ[side]) dssdSideQ[side] = getDssdEnergyCal(side,i);
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
		void setTELEEnergy(){}
		void setTELEAngle(){}

		void findCsiMultHit(){
			for (int i = 0; i < 7; ++i) {
				//if(getCsiQCal(i)>10&&getSiQCal(i)> 1)
				if(getCsiQCal(i)>50){
					hitIdArray[csiNHit] = i;
					csiNHit++;
					cout<<i<<":"<<csiNHit<<endl;
				}	

			}
			if(csiNHit>2) cout<<csiNHit<<endl;
		}
		double getDssdEnergyCal(int side,int id){
			return calibData->getDssdEnergyCal(side,id);
		}
		double getCsiQCal(int id){
			return calibData->getCsiQCal(id);	
		}
		double getSiQCal(int id){
			int side = (id<4)?1:0;
			//return dssdQ[side];
		}
		void determineCsiId(){
		}
		void determineSiEnergy(){
		}
		TeleEvent(){}
		~TeleEvent(){}
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
				dssdSideQ[i] = NAN;
				dssdNHit[i] = 0;
			}

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

			tree->Branch("csiNHit",&csiNHit,"csiNHit/I");
			tree->Branch("csiHitIdArray",&hitIdArray,"hitIdArray[csiNHit]/I");
			tree->Branch("csiId",&csiId,"csiId/I");
			tree->Branch("dssdFid",&dssdFid,"dssdFid/I");
			tree->Branch("dssdBid",&dssdBid,"dssdBid/I");

			tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("telePosition","TVector3",&telePosition);
		}	
};
