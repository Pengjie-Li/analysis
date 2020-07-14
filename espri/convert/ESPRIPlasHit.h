class ESPRIPlasHitPara{
	private: 
		double plasPedestal[4];
		double plasPedSigma[4];

	public:
		ESPRIPlasHitPara(){
			init();
			load();
			print();
		}
		void init(){
			for (int i = 0; i < 4; ++i) {
				plasPedestal[i] = 0;	
				plasPedSigma[i] = 0;	
			}
		}
		double getPedestal(int i){
			return plasPedestal[i];
		}
		void load(){
			ifstream in;
			TString inputName = env->GetValue("plasPedestal","plasPedestal.txt");
			in.open(inputName);
			int side;
			double ped;
			double sigma;
			while(1){
				in >>side>>ped>>sigma;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				plasPedestal[side] = ped;
				plasPedSigma[side] = sigma;
			}

		}
		void print(){
			cout<<"Plas Pedestal Para:"<<endl;		
			for (int i = 0; i < 4; ++i) {
				cout<<i<<"Pedestal = "<<plasPedestal[i]<<" Sigma = "<<plasPedSigma[i]<<endl;
			}
		}
		
};
class ESPRIPlasHit{
	private:
		ESPRIPlasRaw *plasRaw;
		ESPRIPlasHitPara *plasPara;
	
		double plasQPed[4];

		int plasHit;// 0,1,2: no, one, both side
		int plasHitSide[2]; // -1, 0, 1: no, left, right

		void setHit(){
			double plasHitTh = 50;
			for (int side = 0; side < 2; ++side) {
				if(plasQPed[2*side]>0&&plasQPed[2*side+1]>0){
					double plasBarQPed = getBarQPed(side);
					if(plasBarQPed>plasHitTh){
						plasHitSide[plasHit] = side;
						plasHit++;
					}
				}

			}
		}
		double getQRaw(int i){
			return plasRaw->getQRaw(i);
		}
		double getPedestal(int i){
			return plasPara->getPedestal(i);
		}

	public:

		ESPRIPlasHit(){
			plasPara = new ESPRIPlasHitPara();
		}
		void init(){

			plasHit = 0;
			plasHitSide[0] = -1;
			plasHitSide[1] = -1;

			for(int i=0;i<4;i++){
				plasQPed[i] = -9999;
			}
		}
		void sortHit(ESPRIPlasRaw *raw){
			plasRaw = raw;
			subtractPed();
			setHit();
		}
		void subtractPed(){
			//plasRaw->printQ();
			for(int i=0;i<4;i++){
				if(getQRaw(i)!=-9999) {
					plasQPed[i] = (getQRaw(i) - getPedestal(i));
				}
			}
			//printQ();
		}
		void print(){
			for (int i = 0; i < plasHit; ++i) {
				int side = plasHitSide[i];
				cout<<" Plas Hit"<<i<<" Side = "<<side<<" QPed = "<<getBarQPed(side)<<endl;
			}
		}
		double getBarQPed(int side){
			return sqrt(plasQPed[2*side]*plasQPed[2*side+1]);
		}
		int getNHit(){
			return plasHit;
		}
		int getSide(int hitId){
			return plasHitSide[hitId];
		}
		void setBranch(TTree *tree){
			tree->Branch("plasHit",&plasHit,"plasHit/I");
			tree->Branch("plasHitSide",plasHitSide,"plasHitSide[plasHit]/I");

			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
		}
};

