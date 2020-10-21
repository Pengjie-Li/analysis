class HodSynPara{
	private:
		
		double tSynPara[40]; // Para Offset for i and i + 1
	public:
		HodSynPara(TEnv *hodEnv){
			
			TString inputName = hodEnv->GetValue("hodTSynPara","le.txt");
			loadPara(inputName);
			print();
		}
		~HodSynPara(){}
		void loadPara(TString inputName){
			ifstream inputFile;
			cout<<inputName<<endl;
			inputFile.open(inputName);
			int ch;
			int slp;
			double offset;
			while (1)
			{
				inputFile >>ch>>slp>>offset;
				if (!inputFile.good()) break;
				tSynPara[ch] = offset;
			}
			inputFile.close();
		}
		void print(){
			for (int i = 0; i < 40; ++i) {
				cout<<" ch = "<<i<<" tSynPara = "<<tSynPara[i]<<endl;	
			}
		}
		double getTSynPara(int i){
			return tSynPara[i];
		}

};
class HodEvent{
	private:
		MergeHOD *mergeHOD;
		TEnv *hodEnv;
		HodSynPara *hodSynPara;
		int hodfTRawMin;
		int hodfTRawMax;
		int hodpTRawMin;
		int hodpTRawMax;
		int hodQRawTh;

		int hodQHit;
		int hodQHitId[40];
		double hodQHitQPed[40];

		int hodTHit;
		int hodTHitId[40];
		double hodTHitTSyn[40];

		int hodHit;
		int hodHitId[40];
		double hodHitQ[40];
		double hodHitT[40];

		double getHodTSyn(int id, double hodT){
			double offset = 0;
			if(id<24){ // HODF
				for (int i = 23; i >= id; i--) {
					offset -= hodSynPara->getTSynPara(i);	
				}
			}else{ //HODP
				for (int i = 24; i <= id; i++) {
					offset += hodSynPara->getTSynPara(i - 1);	
				}

			}		
			return hodT+offset;
		}
		void setHodQHit(){
			for (int i = 0; i < 40; ++i) {
				double hodQ = mergeHOD->getHodBarQCal(i);
				if(
						((i==0 ||i == 39)&&hodQ>hodQRawTh)
						||(i<39&&i>0&&hodQ>10) 
				  ){
					hodQHitId[hodQHit] = i;
					hodQHitQPed[hodQHit] = hodQ;
					hodQHit++;
				}
			}
		}
		void setHodTHit(){
			for (int i = 0; i < 40; ++i) {
				double hodT = mergeHOD->getHodBarTRaw(i);
				if(
					(i<24&&hodT>hodfTRawMin&&hodT<hodfTRawMax)
					||(i>23&&hodT>hodpTRawMin&&hodT<hodpTRawMax)
				  ){
					//cout<<i<<" "<<hodT<<" "<<endl;
					hodTHitId[hodTHit] = i;
					hodTHitTSyn[hodTHit] = getHodTSyn(i,hodT);
					hodTHit++;
				}
			}
		}
		void setHodHit(){
			for (int i = 0; i < hodQHit; ++i) {
				for (int j = 0; j < hodTHit; ++j) {
					if(hodQHitId[i] == hodTHitId[j]){
						hodHitId[hodHit] = hodQHitId[i];
						hodHitQ[hodHit] = hodQHitQPed[i];
						hodHitT[hodHit] = hodTHitTSyn[j];
						hodHit++;
					}
				}
			}
		}
	
	
	public:
		HodEvent(){
			hodEnv = new TEnv("config/configHod.prm");
			hodfTRawMin = hodEnv->GetValue("hodfTRawMin", 10);
			hodfTRawMax = hodEnv->GetValue("hodfTRawMax", 10);
			hodpTRawMin = hodEnv->GetValue("hodpTRawMin", 10);
			hodpTRawMax = hodEnv->GetValue("hodpTRawMax", 10);
			hodQRawTh = hodEnv->GetValue("hodQRawTh", 10);
			cout<<" Hod Parameters: "<<endl;
			cout<<"HODF "<<hodfTRawMin<<" "<<hodfTRawMax<<endl;
			cout<<"HODP "<<hodpTRawMin<<" "<<hodpTRawMax<<endl;
			cout<<"HOD Qth "<<hodQRawTh<<endl;
	
			hodSynPara = new HodSynPara(hodEnv);
		}
		~HodEvent(){}
		void print(){
			for (int i = 0; i < hodQHit; ++i) {
				cout<<"QHit "<<i<<" Id = "<<hodQHitId[i]<<" QPed = "<<hodQHitQPed[i]<<endl;	
			}
			for (int i = 0; i < hodTHit; ++i) {
				cout<<"THit "<<i<<" Id = "<<hodTHitId[i]<<" TSyn = "<<hodTHitTSyn[i]<<endl;	
			}
			for (int i = 0; i < hodHit; ++i) {
				cout<<"Hod Hit "<<i<<" Id = "<<hodHitId[i]<<" Q = "<<hodHitQ[i]<<" T = "<<hodHitT[i]<<endl;	
			}
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("hodQHit",&hodQHit,"hodQHit/I");
			tree->Branch("hodQHitId",&hodQHitId,"hodQHitId[hodQHit]/I");
			tree->Branch("hodQHitQPed",&hodQHitQPed,"hodQHitQPed[hodQHit]/D");
			tree->Branch("hodTHit",&hodTHit,"hodTHit/I");
			tree->Branch("hodTHitId",&hodTHitId,"hodTHitId[hodTHit]/I");
			tree->Branch("hodTHitTSyn",&hodTHitTSyn,"hodTHitTSyn[hodTHit]/D");
			tree->Branch("hodHit",&hodHit,"hodHit/I");
			tree->Branch("hodHitId",&hodHitId,"hodHitId[hodHit]/I");
			tree->Branch("hodHitT",&hodHitT,"hodHitT[hodHit]/D");
			tree->Branch("hodHitQ",&hodHitQ,"hodHitQ[hodHit]/D");
	
		}
		void init(){
			hodQHit = 0;
			hodTHit = 0;
			hodHit = 0;
			for (int i = 0; i < 40; ++i) {
				hodQHitId[i] = -1;	
				hodQHitQPed[i] = -1;	

				hodTHitId[i] = -1;	
				hodTHitTSyn[i] = -1;	

				hodHitId[i] = -1;	
				hodHitQ[i] = -1;	
				hodHitT[i] = -1;	
			}
		}
		void setHodEvent(){
			setHodQHit();	
			setHodTHit();	
			setHodHit();	
		}
		void loadData(MergeHOD *rawData){
			mergeHOD = rawData;
		}
};
