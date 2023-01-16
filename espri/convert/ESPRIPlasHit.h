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

		double plasHitTh;
		double plasPMTTh;

		double plasQPed[4];

		int plasHit;// 0,1,2: no, one, both side
		int plasQHit;// 4: all hit, 3: 1 ch missing 
		int plasTHit;// 1 ch hit as bottom line 
		int plasHitSide[2]; // -1, 0, 1: no, left, right
		int plasTHitSide[4]; // -1, 0, 1: no, left, right
		int plasQHitSide[4]; // -1, 0, 1: no, left, right

		void checkNormalHit(){
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
		void checkPMTHit(){
			//cout<<getQRaw(0)<<":"<<getQRaw(1)<<getQRaw(2)<<":"<<getQRaw(3)<<endl;
			for (int side = 0; side < 2; ++side) {
				if(getQRaw(2*side)==-9999&&getQRaw(2*side+1)>plasPMTTh){
					plasHitSide[plasHit] = side;
					plasHit++;
				}else if(getQRaw(2*side+1)==-9999&&getQRaw(2*side)>plasPMTTh){
					plasHitSide[plasHit] = side;
					plasHit++;
				}else if(getQRaw(2*side+1)!=-9999&&getQRaw(2*side)!=-9999&&getBarQPed(side)>plasHitTh){
					plasHitSide[plasHit] = side;
					plasHit++;
				}else{
				}
			}
			//cout<<plasHit<<endl;
		}
		void checkOneBarHit(){
			if(plasQHitSide[0]==plasQHitSide[1]&&getBarQPed(plasQHitSide[0])>plasHitTh){
				plasHitSide[plasHit] = plasQHitSide[0];
				plasHit++;
			}
		}
		void setHit(){

			if(plasQHit==4){
				checkNormalHit();
			}else if(plasQHit == 3){
				checkPMTHit();
			}else if(plasQHit==2&&plasTHit>=1){
				checkOneBarHit();
			}else{
				cout<<"You shouldn't go to here!!!"<<endl;
			}
		}
		double getTRaw(int i){
			return plasRaw->getTRaw(i);
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
			plasHitTh = 50;
			plasPMTTh = 250;
		}
		void init(){

			plasHit = 0;
			plasQHit = 0;
			plasTHit = 0;
			for (int i = 0; i < 4; ++i) {
				plasHitSide[i/2] = -1;
				plasQHitSide[i] = -1;
				plasTHitSide[i] = -1;
			}
			for(int i=0;i<4;i++){
				plasQPed[i] = -9999;
			}
		}
		void sortHit(ESPRIPlasRaw *raw){
			plasRaw = raw;
			setQHit();
			setTHit();
			setHit();
		}
		void setTHit(){
			for(int i=0;i<4;i++){
				if(getTRaw(i)!=-9999) {
					plasTHitSide[plasTHit] = i/2;
					plasTHit++;
				}
			}
		}
		void setQHit(){
			//plasRaw->printQ();
			for(int i=0;i<4;i++){
				if(getQRaw(i)!=-9999) {
					plasQPed[i] = (getQRaw(i) - getPedestal(i));
					plasQHitSide[plasQHit] = i/2;
					plasQHit++;
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

			tree->Branch("plasTHit",&plasTHit,"plasTHit/I");
			tree->Branch("plasQHit",&plasQHit,"plasQHit/I");
			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
		}
};

