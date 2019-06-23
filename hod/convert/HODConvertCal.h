class PlasticEnergyCal{
	private:
	public:
		int ID;
		bool isUpBar;
		int rawADC;
};
class HODPlasticPedestal{
	private:
	public:

        ifstream in;
        TString inputName;
	double pedestal[NUMBER_OF_HOD];
	double sigmaPed[NUMBER_OF_HOD];
	double adcThreshold[NUMBER_OF_HOD];

	HODPlasticPedestal(TString input){
		inputName = input;
		loadPedestal();
	}

	void loadPedestal(){
		in.open(inputName);
		int id;
		double mean;
		double sigma;
		double threshold;
		while (1)
		{
			if (!in.good()) break;
			in >>id>>mean>>sigma>>threshold;
			pedestal[id] = mean;
			sigmaPed[id] = sigma;
			adcThreshold[id] = threshold;
		}
	}
	double getPedestal(int id){
		return pedestal[id];
	}
};
class HODPedestal{
	private:
	public:
		HODPlasticPedestal *pedestalUp;
		HODPlasticPedestal *pedestalDown;

		HODPedestal(){
			pedestalUp = new HODPlasticPedestal("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/hod/pedestal/HOD_UP_Pedestal.txt");
			pedestalDown = new HODPlasticPedestal("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/hod/pedestal/HOD_DOWN_Pedestal.txt");

		}
		double getPedestal(int side, int ID){
			return side?getPedestalDown(ID):getPedestalUp(ID);
		}
		double getPedestalUp(int ID){
			return pedestalUp->getPedestal(ID);
		}
		double getPedestalDown(int ID){
			return pedestalDown->getPedestal(ID);
		}



};

class HODPlasticCal{
	private:
	public:
		HODPlasticRaw *rawData;
		HODPedestal *hodPedestal;


		double hodTCal[2][40];
		double hodQCal[2][40];
		double hodBarQCal[40];



		void setBranch(TTree *tree){
			tree->Branch("hodTCal",hodTCal,"hodTCal[2][40]/D");
			tree->Branch("hodQCal",hodQCal,"hodQCal[2][40]/D");
			tree->Branch("hodBarQCal",hodBarQCal,"hodBarQCal[40]/D");
		}

		void loadPedestalParameters(){
			hodPedestal = new HODPedestal();
		}
		void initialize(){

			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					hodTCal[i][j] = NAN;
					hodQCal[i][j] = NAN;
					hodBarQCal[j] = NAN;
				}
			}
		}

		HODPlasticCal(){
			initialize();
			loadPedestalParameters();
		}
		void loadRawData(HODPlasticRaw *inputData){
			rawData = inputData;
		}
		void substractPedestal(){

			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					if(getEnergyRaw(i,j)!=-1) hodQCal[i][j] = getEnergyRaw(i,j) - getPedestal(i,j);
				}
			}

		}
		void calculateBarEnergy(){

			for(int i=0;i<NUMBER_OF_HOD;i++){
				if(hodQCal[0][i]>0 && hodQCal[1][i]>0 ) hodBarQCal[i] = sqrt(hodQCal[0][i]*hodQCal[1][i]);
			}
		}
		int getEnergyRaw(int side, int ID){
			return rawData->getEnergyRaw(side,ID);
		}
		double getPedestal(int side, int ID){
			return hodPedestal->getPedestal(side,ID);
		}
};

