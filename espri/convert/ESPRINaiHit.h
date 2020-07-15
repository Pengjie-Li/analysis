class ESPRINaiHitPara{
	private:
		double naiPedestal[4][7];
		double naiPedestalSigma[4][7];
	public:
		ESPRINaiHitPara(){
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
			double sig;
			while(1){
				in >>side>>barID>>ped>>sig;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiPedestal[side][barID] = ped;
				naiPedestalSigma[side][barID] = sig;
			}
			in.close();
		}
		void print(){
			cout<<" Nai QHit Pedestal Para:"<<endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 7; ++j) {
						
					cout<<i<<":"<<j<<":"<<naiPedestal[i][j]<<endl;
				}
			}	
		}
		~ESPRINaiHitPara(){}
		void init(){
			for(int i =0;i<4;i++){
				for(int j = 0;j<7;j++){
					naiPedestal[i][j] = 0;
					naiPedestalSigma[i][j] = 0;
				}
			}
		}
		double getPedestal(int i, int j){
			return naiPedestal[i][j];
		}
		double getPedestalSigma(int i, int j){
			return naiPedestalSigma[i][j];
		}

};
class ESPRINaiHit{
	private:
		ESPRINaiRaw *naiRaw;
		ESPRINaiHitPara *naiPara;

		int naiHit;
		int naiHitSide[14];
		int naiHitBarId[14];

		double naiQPed[4][7];

		void setQPed(){
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					if(getQRaw(i,j)!=-9999){
						double qPed = getQRaw(i,j) - getPedestal(i,j);
						if(qPed>5*getPedestalSigma(i,j)){
							naiQPed[i][j] = qPed;
						}
					}
				}
			}

		}
		double getNaiBarQPed(int i,int j){
			return sqrt(naiQPed[2*i][j]*naiQPed[2*i+1][j]);
		}
		void setHit(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					if(naiQPed[2*i][j]>0&&naiQPed[2*i+1][j]>0){
						naiHitSide[naiHit] = i;
						naiHitBarId[naiHit] = j;
						naiHit++;
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
		double getPedestalSigma(int i,int j){
			return naiPara->getPedestalSigma(i,j);
		}



	public:

		ESPRINaiHit(){
			naiPara = new ESPRINaiHitPara();
		}
		~ESPRINaiHit(){
			delete naiPara;
		}
		void init(){
			naiRaw = NULL;

			naiHit = 0;
			for (int i = 0; i < 14; ++i) {
				naiHitSide[i] = -1;	
				naiHitBarId[i] = -1;	
			}
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					naiQPed[i][j] = -9999;
				}
			}
		}
		void sortHit(ESPRINaiRaw *raw){
			init();
			naiRaw = raw;
			setQPed();
			setHit();
			//printRawQ();
			//printQ();
		}
		int getHit(){
			return naiHit;
		}
		int getSide(int nHit){
			return naiHitSide[nHit];
		}
		double getNaiQPed(int side,int &barId){
			double qPed = 0;			
			for (int i = 0; i < naiHit; ++i) {
				if(naiHitSide[i] == side){
					if(getNaiBarQPed(side,naiHitBarId[i])>qPed){
						qPed = getNaiBarQPed(side,naiHitBarId[i]);
						barId = naiHitBarId[i];
					}
				}
			}
			return qPed;
		}
		void print(){

			for (int i = 0; i < naiHit; ++i) {
				cout<<" Nai Hit"<<i<<" Side = "<<naiHitSide[i]<<" BarId = "<<naiHitBarId[i]<<" QPed = "<<getNaiBarQPed(naiHitSide[i],naiHitBarId[i])<<endl;	
			}

		}
		void setBranch(TTree *tree){
			tree->Branch("naiHit", &naiHit, "naiHit/I");
			tree->Branch("naiHitSide", naiHitSide, "naiHitSide[naiHit]/I");
			tree->Branch("naiHitBarId", naiHitBarId, "naiHitBarId[naiHit]/I");
			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
		}
};


