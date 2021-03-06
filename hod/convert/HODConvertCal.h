class PlasticEnergyCal{
	private:
	public:
		int ID;
		bool isUpBar;
		int rawADC;
};
class HODUpDownTOffset{
	private:
		double TOffset[40];
	public:
		HODUpDownTOffset(){
			loadUpDownTOffset();
		}
		~HODUpDownTOffset(){}
		void loadUpDownTOffset(){
			TString inputName = env->GetValue("upDownTOffset","./txt/test.txt");
			ifstream in;
			in.open(inputName);
			int id;
			double offset;
			while (1)
			{
				if (!in.good()) break;
				in >>id>> offset;
				TOffset[id] = offset;
			}
		}
		double getOffset(int side,int id){
			if(side == 0) return 0;
			else return TOffset[id];
		}

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
		HODUpDownTOffset *hodUpDownTOffset;


		double hodTSync[2][40];
		double hodTCal[2][40];
		double hodQCal[2][40];
		double hodQPed[2][40];
		double hodBarQCal[40];
		double hodBarTCal[40];



		void setBranch(TTree *tree){
			tree->Branch("hodTSync",hodTSync,"hodTSync[2][40]/D");
			tree->Branch("hodTCal",hodTCal,"hodTCal[2][40]/D");
			tree->Branch("hodQCal",hodQCal,"hodQCal[2][40]/D");
			tree->Branch("hodQPed",hodQPed,"hodQPed[2][40]/D");
			tree->Branch("hodBarQCal",hodBarQCal,"hodBarQCal[40]/D");
			tree->Branch("hodBarTCal",hodBarTCal,"hodBarTCal[40]/D");
		}

		void loadHodParameters(){
			hodPedestal = new HODPedestal();
			hodUpDownTOffset = new HODUpDownTOffset();
		}
		void initialize(){

			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					hodTSync[i][j] = NAN;
					hodTCal[i][j] = NAN;
					hodQCal[i][j] = NAN;
					hodQPed[i][j] = NAN;
					hodBarQCal[j] = NAN;
					hodBarTCal[j] = NAN;
				}
			}
		}

		HODPlasticCal(){
			initialize();
			loadHodParameters();
			
		}
		void loadRawData(HODPlasticRaw *inputData){
			rawData = inputData;
		}
		void calibQ(){
			substractPedestal();
			convertQ();
		}
		void substractPedestal(){

			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					if(getEnergyRaw(i,j)!=-1) hodQPed[i][j] = getEnergyRaw(i,j) - getPedestal(i,j);
				}
			}

		}
		void convertQ(){
			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					if(getEnergyRaw(i,j)!=-1) hodQCal[i][j] = getEnergySlope(i,j)*hodQPed[i][j];
				}
			}

		}

		void calibT(){
			convertT();
		}
		void convertT(){
			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					if(getTimeRaw(i,j)!=-1) hodTSync[i][j] = getUpDownTOffset(i,j) + getTimeRaw(i,j);
					if(getTimeRaw(i,j)!=-1) hodTCal[i][j] = getTimeSlope(i,j)*hodTSync[i][j];
				}
			}

		}

		void calculateBar(){
			calculateBarEnergy();
			calculateBarTime();
		}
		void calculateBarEnergy(){

			for(int i=0;i<NUMBER_OF_HOD;i++){
				if(hodQCal[0][i]>0 && hodQCal[1][i]>0 ) hodBarQCal[i] = sqrt(hodQCal[0][i]*hodQCal[1][i]);
			}
		}
		void calculateBarTime(){

			for(int i=0;i<NUMBER_OF_HOD;i++){
				if(!isnan(hodTCal[0][i]) && !isnan(hodTCal[1][i])) hodBarTCal[i] = 0.5*(hodTCal[0][i]+hodTCal[1][i]);
			}

		}

		int getTimeRaw(int side, int ID){
			return rawData->getTimeRaw(side,ID);
		}
		double getTimeSlope(int side, int ID){
			return 0.0684615384615384626; // Why???
		}
		double getUpDownTOffset(int side, int ID){
			return hodUpDownTOffset->getOffset(side,ID);
		}
		int getEnergyRaw(int side, int ID){
			return rawData->getEnergyRaw(side,ID);
		}
		double getPedestal(int side, int ID){
			return hodPedestal->getPedestal(side,ID);
		}
		double getEnergySlope(int side, int ID){
			return 1;
		}

};

