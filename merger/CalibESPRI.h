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
			TString inputName = "txt/espriEnergyCalibParaBe14.txt";
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
		}
		~EspriEnergy(){}
		double getPlasEnergy(int side,double plasBarQPed){
			return getPlasGain(side)*plasBarQPed+getPlasDead(side);
		}
		double getNaiEnergy(int side, int barId,double naiBarQPed){
			return getNaiGain(side,barId)*naiBarQPed+getNaiDead(side,barId);
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

		double espriPlasT;
		double espriPlasE;
		double espriNaiE;

		double espriDeeEnergy;
		double espriTofEnergy;

		double espriEnergy;

		double getPlasQ(){
			return calibEspri->getPlasEnergy(mergeData->getSide(),mergeData->getPlasQPed());
		}
		double getPlasT(){
			return plasTime->getPlasT(mergeData->getSide(),mergeData->getPlasT(0),mergeData->getPlasT(1),mergeData->getRdcY());
		}
		double getNaiQ(){
			return calibEspri->getNaiEnergy(mergeData->getSide(),mergeData->getNaiId(),mergeData->getNaiQPed());
		}
		void init(){
			espriPlasT	= NAN;
			espriPlasE	= NAN;
			espriNaiE	= NAN;

			espriDeeEnergy	= NAN;
			espriTofEnergy	= NAN;
			espriEnergy	= NAN;
		}

	public:

		CalibESPRI(){
			calibEspri = new EspriEnergy();
			plasTime = new EspriPlasTime();
		}
		~CalibESPRI(){}
		void loadData(MergeESPRI *mergeESPRI){
			mergeData = NULL;
			mergeData = mergeESPRI;
		}
		void calibrate(){
			init();
			espriPlasE = getPlasQ();
			if(mergeData->getNaiHit()==1){
				espriNaiE  = getNaiQ();
				espriDeeEnergy = espriPlasE + espriNaiE;
			}else{
				espriDeeEnergy = espriPlasE;
			}
			espriPlasT = getPlasT();

			espriEnergy = espriDeeEnergy;
		}
		double getEnergy(){
			return espriEnergy;
		}
		void setBranch(TTree *tree){

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriPlasT",&espriPlasT,"espriPlasT/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");

			tree->Branch("espriDeeEnergy",&espriDeeEnergy,"espriDeeEnergy/D");
			tree->Branch("espriTofEnergy",&espriTofEnergy,"espriTofEnergy/D");


		}
		void print(){
			cout<<"espriPlasT = "<<espriPlasT<<" ns"<<endl;
			cout<<"espriPlasE = "<<espriPlasE<<" MeV espriNaiE = "<<espriNaiE<<" MeV  espriEnergy = "<<espriEnergy<<" MeV "<<endl;

		}


};
