class HodSynPara{
	private:
		
		double tSynPara[40]; // Para Offset for i and i + 1

		double qSynPara[40]; // Para Offset for i and i + 1
	public:
		HodSynPara(TEnv *hodEnv){
			
			TString tInputName = hodEnv->GetValue("hodTSynPara","le.txt");
			TString qInputName = hodEnv->GetValue("hodQSynPara","le.txt");
			loadTPara(tInputName);
			loadQPara(qInputName);
			print();
		}
		~HodSynPara(){}
		void loadTPara(TString inputName){
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

		void loadQPara(TString inputName){
			ifstream inputFile;
			cout<<inputName<<endl;
			inputFile.open(inputName);
			int ch;
			int ch2;
			double gain;
			while (1)
			{
				inputFile >>ch>>ch2>>gain;
				if (!inputFile.good()) break;
				qSynPara[ch] = gain;
			}
			inputFile.close();
		}
		void print(){
			for (int i = 0; i < 40; ++i) {
				cout<<" ch = "<<i<<"\t tSynPara = "<<tSynPara[i]<<"\t qSynPara = "<<qSynPara[i]<<endl;	
			}
		}
		double getTSynPara(int i){
			return tSynPara[i];
		}
		double getQSynPara(int i){
			return qSynPara[i];
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
		double hodQHitQSyn[40];

		int hodTHit;
		int hodTHitId[40];
		double hodTHitTSyn[40];

		int hodHit;
		int hodHitId[40];
		double hodHitQ[40];
		double hodHitT[40];

		double getHodQSyn(int id, double hodQ){

			double gain = hodSynPara->getQSynPara(id);
			//Q all aligned to Bar23
			//double gain = 1;
			//if(id<24){ // HODF
			//	for (int i = 22; i >= id; i--) { // Gain 22 To 23
			//		gain = gain*hodSynPara->getQSynPara(i);	
			//		//cout<<i<<" "<<gain<<endl;
			//	}
			//}else{ //HODP
			//	for (int i = 23; i < id; i++) { //Gain 23 to 24
			//		gain = gain/hodSynPara->getQSynPara(i);	
			//		//cout<<i<<" "<<gain<<endl;
			//	}
			//}
			//cout<<"id = "<<id<<" gain = "<<gain<<endl;
			return gain*hodQ;
		}
		double getHodTSyn(int id, double hodT){
			double offset = hodSynPara->getTSynPara(id);
			//double offset = 0;
			//if(id<24){ // HODF
			//	for (int i = 23; i >= id; i--) {
			//		offset -= hodSynPara->getTSynPara(i);	
			//	}
			//}else{ //HODP
			//	for (int i = 24; i <= id; i++) {
			//		offset += hodSynPara->getTSynPara(i - 1);	
			//	}

			//}		
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
					hodQHitQSyn[hodQHit] = getHodQSyn(i,hodQ);
					//cout<<hodQHitQSyn[hodQHit]<<" "<<hodQ<<endl;
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
						hodHitQ[hodHit] = hodQHitQSyn[i];
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
				cout<<"QHit "<<i<<" Id = "<<hodQHitId[i]<<" QSyn = "<<hodQHitQSyn[i]<<endl;	
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
			tree->Branch("hodQHitQSyn",&hodQHitQSyn,"hodQHitQSyn[hodQHit]/D");
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
				hodQHitQSyn[i] = -1;	

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
