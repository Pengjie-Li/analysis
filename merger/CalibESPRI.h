
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
			TString inputName = calib->GetValue("plasBirksCalib","plasBirksCalib.txt");
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
		double naiPol3P0[2][7];
		double naiPol3P1[2][7];
		double naiPol3P2[2][7];

	public:
		ESPRINaiCalPara(){
			init();
			load();
			print();
		}
		void load(){
			loadPol3Gain();
		}

		void loadPol3Gain(){
			ifstream in;
			TString inputName = calib->GetValue("naiPol3Calib","naiPol3Calib.txt");
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double p0;
			double p1;
			double p2;
			while(1){
				in >>side>>barID>>p0>>p1>>p2;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiPol3P0[side][barID] = p0;
				naiPol3P1[side][barID] = p1;
				naiPol3P2[side][barID] = p2;
			}

			in.close();
		}
		void print(){
			cout<<" Nai BarQCal Pol3 Para:"<<endl;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					cout<<i<<":"<<j<<":"<<naiPol3P0[i][j]<<":"<<naiPol3P1[i][j]<<":"<<naiPol3P2[i][j]<<endl;
				}
			}	

		}
		~ESPRINaiCalPara(){}
		void init(){
			for(int i =0;i<2;i++){
				for(int j = 0;j<7;j++){
						naiPol3P0[i][j] = 1;
						naiPol3P1[i][j] = 0;
						naiPol3P2[i][j] = 0;
				}
			}
		}
		double getPol3P0(int i, int j){
			return naiPol3P0[i][j];
		}
		double getPol3P1(int i, int j){
			return naiPol3P1[i][j];
		}
		double getPol3P2(int i, int j){
			return naiPol3P2[i][j];
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
			TString inputName = calib->GetValue("espriCalib","txt/espriEnergyCalibPara.txt");;
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

                double getPol3P0(int i,int j){
                        return naiPara->getPol3P0(i,j);
                }
                double getPol3P1(int i,int j){
                        return naiPara->getPol3P1(i,j);
                }
                double getPol3P2(int i,int j){
                        return naiPara->getPol3P2(i,j);
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
			return getNaiGain(side,barId)*naiBarQPed+getNaiDead(side,barId);
		}
		
		double getNaiQ_Pol3(int i, int j,double ped){
			return getPol3P0(i,j)*ped + getPol3P1(i,j)*ped*ped+getPol3P2(i,j)*ped*ped*ped;
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

		MergeESPRI *mergeData;
		EspriEnergy *calibEspri;	
		EspriPlasTime *plasTime;

		double espriPlasE_Birks;
		double espriNaiE_Pol3;

		double espriPlasT;
		double espriPlasE;
		double espriNaiE;

		double espriDeeEnergy;

		double getPlasQ(){
			return calibEspri->getPlasQ(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getPlasQ_Birks(){
			return calibEspri->getPlasQ_Birks(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getPlasT(){
			return plasTime->getPlasT(mergeData->getSide(),mergeData->getPlasT(0),mergeData->getPlasT(1),mergeData->getRdcY());
		}
		double getNaiQ(){
			return calibEspri->getNaiQ(mergeData->getSide(),mergeData->getNaiId(),mergeData->getNaiQPed());
		}
		double getNaiQ_Pol3(){
			return calibEspri->getNaiQ_Pol3(mergeData->getSide(),mergeData->getNaiId(),mergeData->getNaiQPed());
		}



	public:

		CalibESPRI(){
			calibEspri = new EspriEnergy();
			plasTime = new EspriPlasTime();
		}
		~CalibESPRI(){}
		void init(){

			espriPlasE_Birks = NAN;
			espriNaiE_Pol3 = NAN;

			espriPlasT	= NAN;
			espriPlasE	= NAN;
			espriNaiE	= NAN;

			espriDeeEnergy	= NAN;
		}

		void loadData(MergeESPRI *mergeESPRI){
			mergeData = NULL;
			mergeData = mergeESPRI;
		}
		void calibrate(){
			init();

			espriPlasE_Birks = getPlasQ_Birks();
			espriPlasE = getPlasQ();

			if(mergeData->getNaiHit()==1){

				espriNaiE_Pol3 = getNaiQ_Pol3();
				espriNaiE  = getNaiQ();

				espriDeeEnergy = espriPlasE + espriNaiE;
			}else{
				espriDeeEnergy = espriPlasE;
			}
			espriPlasT = getPlasT();

		}
		double getEnergy(){
			return espriDeeEnergy;
		}
		void setBranch(TTree *tree){

			tree->Branch("espriPlasE_Birks",&espriPlasE_Birks,"espriPlasE_Birks/D");
			tree->Branch("espriNaiE_Pol3",&espriNaiE_Pol3,"espriNaiE_Pol3/D");

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriPlasT",&espriPlasT,"espriPlasT/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");
			tree->Branch("espriDeeEnergy",&espriDeeEnergy,"espriDeeEnergy/D");

		}
		void print(){
			cout<<"Plas Energy versions:  "<< espriPlasE<<" "<<espriPlasE_Birks<<endl;
			cout<<"Nai  Energy versions:  "<< espriNaiE<<" "<<espriNaiE_Pol3<<endl;

			cout<<"espriPlasT = "<<espriPlasT<<" ns"<<endl;
			cout<<"espriPlasE = "<<espriPlasE<<" MeV espriNaiE = "<<espriNaiE<<" MeV  espriDeeEnergy = "<<espriDeeEnergy<<" MeV "<<endl;

		}
};
