class ESPRIPlasCalPara{
	private: 
		double plasPedestal[4];
		double plasPedSigma[4];

	public:
		ESPRIPlasCalPara(){
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
			TString inputName = calib->GetValue("plasPedestal","plasPedestal.txt");
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
class ESPRIPlasCal{
	private:
		int runNumber;
		ESPRIPlasRaw *plasRaw;
		ESPRIPlasCalPara *plasPara;
	
		double plasTRef[4];	
		double plasTCal[4];	

		double plasQPed[4];
		double plasBarQPed[2];

		int plasHit;
		int plasHitSide[2];
		double plasHitQPed[2];

		double getTCalSlope(int i){
			return 0.025;
		}

		int getTRaw(int i){
			return plasRaw->getTRaw(i);
		}
		double getPlasTimeRef(){
			return plasRaw->getPlasTimeRef();
		}


		void setPlasQ(int side){
			double plasHitTh = 50;
			if(plasQPed[2*side]>0&&plasQPed[2*side+1]>0){
				plasBarQPed[side] = sqrt(plasQPed[2*side]*plasQPed[2*side+1]);
				if(plasBarQPed[side]>plasHitTh){
					plasHitQPed[plasHit] = plasBarQPed[side];
					plasHitSide[plasHit] = side;
					plasHit++;
				}
			}
		}
		void setPlasQL(){
			setPlasQ(0);
		}
		void setPlasQR(){
			setPlasQ(1);
		}
		double getQRaw(int i){
			return plasRaw->getQRaw(i);
		}
		double getPedestal(int i){
			return plasPara->getPedestal(i);
		}

	public:

		ESPRIPlasCal(){
			plasPara = new ESPRIPlasCalPara();
		}
		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void init(){

			plasHit = 0;
			plasHitSide[0] = -1;
			plasHitSide[1] = -1;

			plasBarQPed[0] = -9999;
			plasBarQPed[1] = -9999;

			for(int i=0;i<4;i++){
				plasQPed[i] = -9999;
				plasTRef[i] = -9999;
				plasTCal[i] = -9999;
			}
		}
		void convertCal(ESPRIPlasRaw *raw){
			init();
			plasRaw = raw;
			calibrateQ();
			calibrateT();
		}
		void calibrateT(){
			for(int i=0;i<4;i++){
				if(getTRaw(i) == 0 ||getTRaw(i) == -1||getTRaw(i) == -9999) continue;
				plasTRef[i] = getTRaw(i) - getPlasTimeRef();
				plasTCal[i] = getTCalSlope(i)*plasTRef[i];
			}
		}
		void calibrateQ(){
			//plasRaw->printQ();
			for(int i=0;i<4;i++){
				if(getQRaw(i)!=-9999) {
					plasQPed[i] = (getQRaw(i) - getPedestal(i));
				}
			}
			setPlasQL();
			setPlasQR();
			//printQ();
		}
		void printQ(){
			cout<<"PlasBarQPed[2]: ";
			for(int i=0;i<2;i++){
				cout<<plasBarQPed[i]<<":";
			}
			cout<<endl;
		}
		void printT(){
			cout<<"Plastic TCal[4]: ";
			for(int i=0;i<4;i++){
				cout<<plasTCal[i]<<":";
			}
			cout<<endl;
		}
		void print(){
			for (int i = 0; i < plasHit; ++i) {
				//plasRaw->print();
				int side = plasHitSide[i];
				cout<<"Plas Hit"<<i<<" Side = "<<side<<" QPed = "<<plasBarQPed[side]<<" TCal = "<<plasTCal[2*side]<<" : "<<plasTCal[2*side+1]<<endl;
			}
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
			tree->Branch("plasHitQPed",&plasHitQPed,"plasHitQPed[plasHit]/D");

			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
			tree->Branch("plasBarQPed",plasBarQPed,"plasBarQPed[2]/D");
			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");
			tree->Branch("plasTRef",plasTRef,"plasTRef[4]/D");

		}
};

