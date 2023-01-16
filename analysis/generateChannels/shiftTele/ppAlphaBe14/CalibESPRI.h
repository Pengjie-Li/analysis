
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
		double getNaiQ(int side, int barId,double naiBarQPed){
			return getNaiGain(side,barId)*naiBarQPed+getNaiDead(side,barId);
		}

};

class CalibESPRI{
	private:

		ReadFile *rf;
		EspriEnergy *calibEspri;	

		double espriNaiE;

		double getNaiQ(){
			return calibEspri->getNaiQ(rf->getSide(),rf->getNaiId(),rf->getNaiQPed());
		}

	public:

		CalibESPRI(){
			calibEspri = new EspriEnergy();
		}
		~CalibESPRI(){}
		void init(){

			rf = NULL;
			espriNaiE	= NAN;

		}

		void loadData(ReadFile *mergeESPRI){
			rf = mergeESPRI;
		}
		void calibrate(){

			if(rf->getNaiHit()==1){

				espriNaiE  = getNaiQ();
			}


		}
		double getNaiEnergy(){
			return espriNaiE;
		}
		void setBranch(TTree *tree){
			tree->Branch("espriNaiE_old",&espriNaiE,"espriNaiE_old/D");
		}
		void print(){

		}
};
