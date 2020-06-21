#include "PlasTime.h"
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
		double naiBirksParA[2][7];
		double naiBirksParB[2][7];
		double naiBirksParC[2][7];

	public:
		ESPRINaiCalPara(){
			init();
			loadBirks();
			print();
		}

		void loadBirks(){

			ifstream in;
			TString inputName = calib->GetValue("naiCalib","naiCalibErrorPath.txt");
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
		
		double getNaiBirksParA(int i,int j){
			//cout<<naiPara->getBirksParA(i,j)<<endl;
                        return naiPara->getBirksParA(i,j);
                }
                double getNaiBirksParB(int i,int j){
                        return naiPara->getBirksParB(i,j);
                }
                double getNaiBirksParC(int i,int j){
                        return naiPara->getBirksParC(i,j);
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
	

};
class CalibESPRI{
	private:

		MergeESPRI *mergeData;
		EspriEnergy *calibEspri;	
		PlasTime *plasTime;

		double espriPlasE_Birks;

		double espriPlasE;
		double espriNaiE;
		double espriDeeEnergy;

		double beamToF;

		double getPlasQ(){
			return calibEspri->getPlasQ(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getPlasQ_Birks(){
			return calibEspri->getPlasQ_Birks(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getNaiQ(){
			return calibEspri->getNaiQ(mergeData->getSide(),mergeData->getNaiId(),mergeData->getNaiQPed());
		}


	public:

		CalibESPRI(){
			calibEspri = new EspriEnergy();
			plasTime = new PlasTime();
		}
		~CalibESPRI(){
			delete calibEspri;
			delete plasTime;
		}
		void init(){

			mergeData = NULL;
			espriPlasE_Birks = NAN;

			espriPlasE	= NAN;
			espriNaiE	= NAN;

			espriDeeEnergy	= NAN;
			beamToF = NAN;

			plasTime->init();
		}

		void loadData(MergeESPRI *mergeESPRI){
			mergeData = mergeESPRI;
		}
		void loadBeamToF(double tof){
			beamToF = tof;
		}
		void calibrate(){

			espriPlasE_Birks = getPlasQ_Birks();
			espriPlasE = getPlasQ();

			if(mergeData->getNaiHit()==1){

				espriNaiE  = getNaiQ();

				espriDeeEnergy = espriPlasE + espriNaiE;
			}else{
				espriDeeEnergy = espriPlasE;
			}
			calibPlasTime();
		}
		
		void calibPlasTime(){
				if(plasTime->read(mergeData->getSide(),mergeData->getPlasT(0),mergeData->getPlasT(1))){
						plasTime->positionCorr(mergeData->getRdcY()); 
						plasTime->slewCorr(mergeData->getPlasQPed());
						plasTime->tofBeamCorr(beamToF);
				}
		}
		double getEnergy(){
			return espriDeeEnergy;
		}
		double getNaiEnergy(){
			return espriNaiE;
		}
		void setBranch(TTree *tree){

			plasTime->setBranch(tree);
			tree->Branch("espriPlasE_Birks",&espriPlasE_Birks,"espriPlasE_Birks/D");

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");
			tree->Branch("espriDeeEnergy",&espriDeeEnergy,"espriDeeEnergy/D");

		}
		void print(){
			cout<<"Plas Energy versions:  "<< espriPlasE<<" "<<espriPlasE_Birks<<endl;
			cout<<"Nai  Energy versions:  "<< espriNaiE<<" "<<endl;
			cout<<"espriPlasE = "<<espriPlasE<<" MeV espriNaiE = "<<espriNaiE<<" MeV  espriDeeEnergy = "<<espriDeeEnergy<<" MeV "<<endl;
			plasTime->print();

		}
};
