class DSSDTimeCal{

		double dssdTCal[4][32];	
	public:
		void init(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdTCal[i][j] = NAN;
				}
			}

		}


		void calibrate(TELEReadRaw *rawData){
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdTCal",dssdTCal,"dssdTCal[4][32]/D");
		}

};


class DssdCal{
	private:

		TELEReadRaw *teleReadRaw;
		DSSDEnergyCal	*dssdEnergy;
		DSSDTimeCal	*dssdTime;

	public:
		DssdCal(){
			dssdEnergy = new DSSDEnergyCal();
			dssdTime   = new DSSDTimeCal();

		}
		void setBranch(TTree *tree){
			dssdEnergy->setBranch(tree);
			dssdTime->setBranch(tree);
			
		}
		void init(){
			dssdEnergy->init();
			dssdTime->init();
		}
		void calibration(TELEReadRaw *rawData){
			teleReadRaw = rawData;
			dssdCal->calib(rawData);
			dssdTime->calibrate(rawData);

		}
		~DssdCal(){}
};
