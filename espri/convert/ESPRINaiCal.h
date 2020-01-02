class ESPRINaiCalPara{
	private:
		double naiPedestal[4][7];
	public:
		ESPRINaiCalPara(){
			init();
			load();
			print();
		}
		void load(){
			loadPedestal();
		}
		void loadPedestal(){
			ifstream in;
			TString inputName = env->GetValue("naiPedestal","naiPedestal.txt");
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double ped;
			while(1){
				in >>side>>barID>>ped;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiPedestal[side][barID] = ped;
			}
			in.close();
		}
		void print(){
			cout<<" Nai QCal Pedestal Para:"<<endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 7; ++j) {
						
					cout<<i<<":"<<j<<":"<<naiPedestal[i][j]<<endl;
				}
			}	
		}
		~ESPRINaiCalPara(){}
		void init(){
			for(int i =0;i<4;i++){
				for(int j = 0;j<7;j++){
					naiPedestal[i][j] = 0;
				}
			}
		}
		double getPedestal(int i, int j){
			return naiPedestal[i][j];
		}
};
class ESPRINaiCal{
	private:
		int runNumber;
		ESPRINaiRaw *naiRaw;
		ESPRINaiCalPara *naiPara;

		int naiHit;
		int naiHitSide[5];// Maximum 5 bar Hit
		int naiHitBarId[5];
		double naiHitQPed[5];

		double naiQPed[4][7];
		double naiBarQPed[2][7]; // Magnet

		void setQPed(){
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					if(getQRaw(i,j)!=-9999){
						naiQPed[i][j] = getQRaw(i,j) - getPedestal(i,j);
					}
				}
			}

		}
		void setBarQPed(){
			double naiQPedTh = 50;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					if(naiQPed[2*i][j]>0&&naiQPed[2*i+1][j]>0){
						naiBarQPed[i][j]= sqrt(naiQPed[2*i][j]*naiQPed[2*i+1][j]);
						if(naiBarQPed[i][j]>naiQPedTh){
							naiHitSide[naiHit] = i;
							naiHitBarId[naiHit] = j;
							naiHitQPed[naiHit] = naiBarQPed[i][j];
							naiHit++;
						}
					}
				}
			}
		}
		double getQRaw(int i,int j){
			return naiRaw->getQRaw(i,j);
		}
		double getPedestal(int i,int j){
			return naiPara->getPedestal(i,j);
		}

	public:

		ESPRINaiCal(){
			naiPara = new ESPRINaiCalPara();
		}
		~ESPRINaiCal(){
			delete naiPara;
		}
		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void init(){
			naiRaw = NULL;

			naiHit = 0;
			for (int i = 0; i < 5; ++i) {
				naiHitSide[i] = -1;	
				naiHitBarId[i] = -1;	
				naiHitQPed[i] = -9999;	
			}
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					naiQPed[i][j] = -9999;
					if(i%2==0){
						naiBarQPed[i/2][j] = -9999;
					}
				}
			}
		}
		void convertCal(ESPRINaiRaw *raw){
			init();
			naiRaw = raw;
			setQPed();
			setBarQPed();
			//printRawQ();
			//printQ();
		}
		void print(){

			//naiRaw->printQ();
			//cout<<"Nai QPed:"<<endl;
			//for (int i = 0; i < 2; ++i) {
			//	for (int j = 0; j < 7; ++j) {
			//		cout<<i<<" "<<j<<" "<<naiQPed[2*i][j]<<" "<<naiQPed[2*i+1][j]<<" "<<naiBarQPed[i][j]<<endl;
			//	}
			//}
			for (int i = 0; i < naiHit; ++i) {
				cout<<" nai Hit"<<i<<" Side = "<<naiHitSide[i]<<" BarId = "<<naiHitBarId[i]<<" QPed = "<<naiHitQPed[i]<<endl;	
			}

		}
		void setBranch(TTree *tree){
				
			tree->Branch("naiHit", &naiHit, "naiHit/I");
			tree->Branch("naiHitSide", naiHitSide, "naiHitSide[naiHit]/I");
			tree->Branch("naiHitBarId", naiHitBarId, "naiHitBarId[naiHit]/I");
			tree->Branch("naiHitQPed", naiHitQPed, "naiHitQPed[naiHit]/D");

			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
			tree->Branch("naiBarQPed", naiBarQPed, "naiBarQPed[2][7]/D");
		}
};


