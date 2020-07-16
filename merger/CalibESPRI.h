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

		double beamToF;
		double tdcOffset;

		double getPlasQ(){
			return calibEspri->getPlasQ(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getPlasQ_Birks(){
			return calibEspri->getPlasQ_Birks(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getNaiQ(){
			//cout<<mergeData->getNaiId()<<" "<<mergeData->getNaiQPed()<<endl;
			if(mergeData->getRunNumber()>430&&mergeData->getSide()==1&&mergeData->getNaiId()==3) return naiBar13Treat();
			else return calibEspri->getNaiQ(mergeData->getSide(),mergeData->getNaiId(),mergeData->getNaiQPed());
		}
		double naiBar13Treat(){
			int run = mergeData->getRunNumber();
			int evt = mergeData->getEventNumber();
			double sf = 1;
			//if((run<=433&&run>=431)||(run<=447&&run>=440)) sf = 0;				
			//else if(run==434) sf = 1.75754;
			//else if(run ==435) sf = 1.12507;
			//else if((run == 436&&evt>1000000)||run == 437) sf = 1.44163;
			//else if(run ==438) sf = 2.39333;
			//else if(run ==439) sf = 3.47167;
			if(run>=431&&run<=447) sf = 0;				
			//else if(run>=448) sf = 1.52916;
			else if(run>=448) sf = 0;
			else {}
			//cout<<run<<" "<<sf<<endl;
			return calibEspri->getNaiQ(mergeData->getSide(),mergeData->getNaiId(),sf*mergeData->getNaiQPed());
		}


	public:

		CalibESPRI(){
			tdcOffset = 329*0.025;
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
			if(mergeData->getNaiQPed()>0) espriNaiE  = getNaiQ();
			calibPlasTime();
		}
		
		void calibPlasTime(){
			plasTime->setEnergyPara(mergeData->getSide(),mergeData->getPlasQPed());
			int offset = 0;
			if(mergeData->getRunNumber()<=306) offset = tdcOffset;
			if(plasTime->read(mergeData->getSide(),mergeData->getPlasT(0),mergeData->getPlasT(1))){
				plasTime->positionCorr(mergeData->getRdcY()); 
				plasTime->slewCorr(mergeData->getPlasQPed());
				plasTime->tofBeamCorr(beamToF);
			}
			plasTime->addOffset(offset);
		}
		double getNaiEnergy(){
			return espriNaiE;
		}
		void setBranch(TTree *tree){

			plasTime->setBranch(tree);
			tree->Branch("espriPlasE_Birks",&espriPlasE_Birks,"espriPlasE_Birks/D");

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");

		}
		void print(){
			cout<<"Plas Energy versions:  "<< espriPlasE<<" "<<espriPlasE_Birks<<endl;
			cout<<"Nai  Energy versions:  "<< espriNaiE<<" "<<endl;
			cout<<"espriPlasE = "<<espriPlasE<<" MeV espriNaiE = "<<espriNaiE<<" MeV  "<<endl;
			plasTime->print();

		}
};
