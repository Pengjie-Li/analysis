
class ESPRIPlasCalPara{
        private:

                double plasBirksParA[2];
                double plasBirksParB[2];

        public:
                ESPRIPlasCalPara(){
                        init();
                        loadBirksPara();
                        print();
                }
		void init(){
			for (int i = 0; i < 2; ++i) {
				plasBirksParA[i] = NAN;
				plasBirksParB[i] = NAN;
			}
		}
		void loadBirksPara(){
			ifstream in;
			TString inputName = "plasBirksCalib.txt";
			in.open(inputName);
			int side;
			double parA;
			double parB;
			while(1){
				in >>side>>parA>>parB;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				plasBirksParA[side] = parA;
				plasBirksParB[side] = parB;
			}

		}
		double getBirksParA(int i){
			return plasBirksParA[i];
		}
		double getBirksParB(int i){
			return plasBirksParB[i];
		}
		void print(){
			cout<<"Plas Birks Para:"<<endl;
			for (int i = 0; i < 2; ++i) {
				cout<<i<<":"<<plasBirksParA[i]<<":"<<plasBirksParB[i]<<endl;
			}
		}

};
class ESPRINaiCalPara{
	private:
		double naiBirksParA[2][7];
		double naiBirksParB[2][7];
		double naiBirksParC[2][7];

		double naiLinearParA[2][7];
		double naiLinearParB[2][7];


	public:
		ESPRINaiCalPara(){
			init();
			loadBirks();
			loadLinear();
			print();
		}
		void loadLinear(){

			ifstream in;
			TString inputName = "txt/naiCalibOutput.txt_Be10_Linear";
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double parA;
			double parB;
			while(1){
				//in >>side>>barID>>parA>>parB;
				in >>side>>barID>>parA>>parB;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiLinearParA[side][barID] = parA;
				naiLinearParB[side][barID] = parB;
			}

			in.close();
		}

		void loadBirks(){

			ifstream in;
			TString inputName = "txt/naiCalibOutput.txt";
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double parA;
			double parB;
			double parC;
			while(1){
				//in >>side>>barID>>parA>>parB;
				in >>side>>barID>>parA>>parB>>parC;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiBirksParA[side][barID] = parA;
				naiBirksParB[side][barID] = parB;
				naiBirksParC[side][barID] = parC;
			}

			in.close();
		}
		void print(){
			cout<<" Nai Birks Bar Para:"<<endl;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					cout<<i<<":"<<j<<":"<<naiBirksParA[i][j]<<":"<<naiBirksParB[i][j]<<endl;
				}
			}	

		}
		~ESPRINaiCalPara(){}
		void init(){
			for(int i =0;i<2;i++){
				for(int j = 0;j<7;j++){
					naiBirksParA[i][j] = 1;
					naiBirksParB[i][j] = 0;
					naiBirksParC[i][j] = 0;
					naiLinearParA[i][j] = 1;
					naiLinearParB[i][j] = 0;
				
			}
			}
		}
		double getBirksParA(int i, int j){
			return naiBirksParA[i][j];
		}
		double getBirksParB(int i, int j){
			return naiBirksParB[i][j];
		}
		double getBirksParC(int i, int j){
			return naiBirksParC[i][j];
		}

		double getLinearParA(int i, int j){
			return naiLinearParA[i][j];
		}
		double getLinearParB(int i, int j){
			return naiLinearParB[i][j];
		}
	
};

class EspriEnergyPara{
	private:
		double plasGain[2][7];
		double plasDead[2][7];
		double naiGain[2][7];
		double naiDead[2][7];

		void init(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j< 7; ++j) {
					plasGain[i][j]= 0;
					plasDead[i][j]= 0;
					naiGain[i][j]= 0;
					naiDead[i][j]= 0;
				}

			}

		}
		void loadCalibPara(){
			init();
			ifstream in;
			TString inputName = "txt/espriEnergyCalibPara.txt";
			//TString inputName = "txt/espriEnergyCalibParaBe14.txt";
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barId;
			double gPlas;
			double dPlas;
			double gNai;
			double dNai;
			while(1){
				if(!in.good()) break;
				in>>side>>barId>>gPlas>>dPlas>>gNai>>dNai;
				naiGain[side][barId] = gNai;
				naiDead[side][barId] = dNai;
				plasGain[side][barId] = gPlas;
				plasDead[side][barId] = dPlas;
			}
		}
		void print(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j< 7; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<plasGain[i][j]<<"\t"<<plasDead[i][j]<<"\t"<<naiGain[i][j]<<"\t"<<naiDead[i][j]<<endl;
				}

			}
		}
	public:
		EspriEnergyPara(){
			loadCalibPara();
			print();
		}
		~EspriEnergyPara(){}
		double getNaiGain(int side,int barId){
			return naiGain[side][barId];
		}
		double getNaiDead(int side,int barId){
			return naiDead[side][barId];
		}
		double getPlasGain(int side){
			return plasGain[side][0];
		}
		double getPlasDead(int side){
			return plasDead[side][0];
		}
};
class EspriEnergy{
	private:
		EspriEnergyPara *calibPara;
		ESPRIPlasCalPara *plasPara;
		ESPRINaiCalPara *naiPara;

                double getNaiLinearParA(int i,int j){
                        return naiPara->getLinearParA(i,j);
                }
                double getNaiLinearParB(int i,int j){
                        return naiPara->getLinearParB(i,j);
                }
 
                double getNaiBirksParA(int i,int j){
                        return naiPara->getBirksParA(i,j);
                }
                double getNaiBirksParB(int i,int j){
                        return naiPara->getBirksParB(i,j);
                }
                double getNaiBirksParC(int i,int j){
                        return naiPara->getBirksParC(i,j);
                }


                double getBirksParA(int i){
                        return plasPara->getBirksParA(i);
                }
                double getBirksParB(int i){
                        return plasPara->getBirksParB(i);
                }
		double getPlasGain(int side){
			return calibPara->getPlasGain(side);
		}
		double getPlasDead(int side){
			return calibPara->getPlasDead(side);
		}
		double getNaiGain(int side,int barId){
			return calibPara->getNaiGain(side,barId);
		}
		double getNaiDead(int side,int barId){
			return calibPara->getNaiDead(side,barId);
		}
		

	public:
		EspriEnergy(){
			calibPara = new EspriEnergyPara();
			plasPara = new ESPRIPlasCalPara();
			naiPara = new ESPRINaiCalPara();
		}
		~EspriEnergy(){}
		double getPlasQ(int side,double plasBarQPed){
			return getPlasGain(side)*plasBarQPed+getPlasDead(side);
		}
		double getPlasQ_Birks(int side,double plasBarQPed){
			return plasBarQPed/(getBirksParA(side)+getBirksParB(side)*plasBarQPed);
		}
		double getNaiQ(int side, int barId,double naiBarQPed){
			return getNaiBirksParA(side,barId)*naiBarQPed/(1+getNaiBirksParB(side,barId)*naiBarQPed+getNaiBirksParC(side,barId)*naiBarQPed*naiBarQPed);
		}
		double getNaiQLinear(int side, int barId,double naiBarQPed){
			return getNaiLinearParA(side,barId)*naiBarQPed+getNaiLinearParB(side,barId);
		}
		

	

};
class EspriPlasTime{
	private:

		double posPara[2];	
		double timeOffset[2];
	public:
		EspriPlasTime(){
			timeOffset[0] = 691.382;
			timeOffset[1] = 691.082;
			posPara[0] = -0.01;
			posPara[1] = -0.0115;
		}
		~EspriPlasTime(){}

		double getPlasT(int side,double upTime,double downTime,double posY){
			if(downTime!=-9999) return  downTime + timeOffset[side]+posPara[side]*(posY-225);
			else return -9999;
		}
};

class CalibESPRI{
	private:

		ReadFile *rf;
		EspriEnergy *calibEspri;	

		double espriNaiE;
		double espriNaiE_Linear;


		double getNaiQ(){
			return calibEspri->getNaiQ(rf->getEspriSide(),rf->getNaiId(),rf->getNaiQPed());
		}
		double getNaiQLinear(){
			return calibEspri->getNaiQLinear(rf->getEspriSide(),rf->getNaiId(),rf->getNaiQPed());
		}


	public:

		CalibESPRI(){
			calibEspri = new EspriEnergy();
		}
		~CalibESPRI(){}
		void init(){

			rf = NULL;

			espriNaiE	= NAN;
			espriNaiE_Linear= NAN;

		}

		void loadData(ReadFile *mergeESPRI){
			rf = mergeESPRI;
		}
		void calibrate(){

				espriNaiE  = getNaiQ();
				espriNaiE_Linear  = getNaiQLinear();

		}
		
		double getNaiEnergyLinear(){
			return espriNaiE_Linear;
		}
	
		double getNaiEnergy(){
			return espriNaiE;
		}
		void setBranch(TTree *tree){
			tree->Branch("espriNaiE_Birks",&espriNaiE,"espriNaiE_Birks/D");
			tree->Branch("espriNaiE_Linear",&espriNaiE_Linear,"espriNaiE_Linear/D");
		}
		void print(){
			cout<<" espriNaiE = "<<espriNaiE<<" MeV" <<endl;

		}
};
