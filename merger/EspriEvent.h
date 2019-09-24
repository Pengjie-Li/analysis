class EspriEvent{
	private:

		int naiNHit;
		int hitIdArray[5];
		int naiId;

		MergeESPRI *calibData;
		double espriEnergy;
		double espriAngle;
		TVector3 *espriPosition;
	public:
		EspriEvent(){}
		~EspriEvent(){}
		void loadData(MergeESPRI *mergeESPRI){
			calibData = mergeESPRI;
		}
		void init(){

			naiNHit = 0;
			for (int i = 0; i < 5; ++i) {
				hitIdArray[i] = -1;
			}

			espriEnergy = NAN;
			espriAngle = NAN;
			espriPosition->SetXYZ(NAN,NAN,NAN);
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("naiNHit",&naiNHit,"naiNHit/I");
			tree->Branch("naiHitIdArray",&hitIdArray,"hitIdArray[naiNHit]/I");
			tree->Branch("naiId",&naiId,"naiId/I");

			tree->Branch("espriEnergy",&espriEnergy,"espriEnergy/D");
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");
			tree->Branch("espriPosition","TVector3",&espriPosition);
		}
		void analysing(){
			findNaiMultHit();
			
			setESPRIEvent();
		}
		void setESPRIEvent(){
			selectGoodEvent();
		}
		void selectGoodEvent(){
			
		}
		void findNaiMultHit(){
			for (int i = 0; i < 14; ++i) {
				//cout<<getNaiBarQCal(i)<<endl;
				if(getNaiBarQCal(i)>2){
					hitIdArray[naiNHit] = i;
					naiNHit++; 
				}
			}
			if(naiNHit>3) cout<<naiNHit<<endl;
		}
		double getNaiBarQCal(int i){
			int side = i/7;
			int id = i%7;
			return calibData->getNaiBarQCal(side,id);
		}
};

