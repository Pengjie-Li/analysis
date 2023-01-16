class DSSDEnergyCalPara{
	private:
		double dssdPedestal[4][32];
		double dssdPedSigma[4][32];

		void load(){
			ifstream in;
			TString inputName;

			inputName = env->GetValue("dssdPedestal","txt/dssdPedestal.txt");
			cout<<inputName<<endl;
			in.open(inputName);

			int side;
			int strip;
			double ped;
			double sigma;
			while (1)
			{
				in >>side>>strip>>ped>>sigma;
				if (!in.good()) break;
				dssdPedestal[side][strip] = ped;
				dssdPedSigma[side][strip] = sigma;
			}
		}


	public:

		DSSDEnergyCalPara(){
			load();
			print();
		}
		void print(){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 32; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<dssdPedestal[i][j]<<"\t"<<dssdPedSigma[i][j]<<endl;
				}
			}
		}
		double getDssdPedestal(int side, int id){
			return dssdPedestal[side][id];
		}
		double getDssdPedSigma(int side, int id){
			return dssdPedSigma[side][id];
		}
};


class DSSDEnergyCal{
	private:
		TELEReadRaw *rawData;
		DSSDEnergyCalPara *dssdPara;

		double dssdQPed[4][32];	
		
		void setQPedAndHit(){
			// raw->SCM->cal
			//side = 0 LF, 1 LB, 2 RF, 3 RB
			
			for(int side = 0;side<4;side++)
				for(int id=0;id<32;id++){
					if(getDssdQRaw(side,id)<=4096){
						dssdQPed[side][id] = getDssdQRaw(side,id) - getDssdPedestal(side,id);
					}
				}
		}

	public:
		DSSDEnergyCal(){
			dssdPara = new DSSDEnergyCalPara();
		}

		~DSSDEnergyCal(){
			delete dssdPara;
		}
		void init(){
			rawData = NULL;
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdQPed[i][j] = -9999;
				}
			}
		}

		void setBranch(TTree *tree){
			tree->Branch("dssdQPed",dssdQPed,"dssdQPed[4][32]/D");
		}
		void calibrate(TELEReadRaw *raw){
			rawData = raw;
			setQPedAndHit();
		}
		double getDssdPedestal(int side, int id){
			return dssdPara->getDssdPedestal(side,id);
		}
		double getDssdPedSigma(int side, int id){
			return dssdPara->getDssdPedSigma(side,id);
		}
		double getDssdQRaw(int side,int id){
			return rawData->getDssdQRaw(side,id);
		}
		void print(){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 32; ++j) {
					cout<<i<<" "<<j<<" "<<dssdQPed[i][j]<<endl;	
				}
			}
		}


};

class DSSDTimeCal{

		TELEReadRaw *teleRaw;
		int dssdTHit;
		int dssdTHitSide[64];
		int dssdTHitStripId[64];
		double dssdTHitTCal[64];
	public:
		void init(){
			teleRaw = NULL;
			dssdTHit = 0;
			for (int i = 0; i < 64; ++i) {
				dssdTHitSide[i] = -1;
				dssdTHitStripId[i] = -1;
				dssdTHitTCal[i] = -9999;
			}
		}
		void calibrate(TELEReadRaw *rawData){
			teleRaw = rawData;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 32; ++j) {
					if(getTdcRaw(i,j)!=-1){
						dssdTHitSide[dssdTHit] = i;
						dssdTHitStripId[dssdTHit] = j;
						dssdTHitTCal[dssdTHit] = getCh2ns()*(getTdcRaw(i,j)-getTdcRef(i));
						dssdTHit++;
					}
				}
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdTHit",&dssdTHit,"dssdTHit/I");
			tree->Branch("dssdTHitSide",dssdTHitSide,"dssdTHitSide[dssdTHit]/I");
			tree->Branch("dssdTHitStripId",dssdTHitStripId,"dssdTHitStripId[dssdTHit]/I");
			tree->Branch("dssdTHitTCal",dssdTHitTCal,"dssdTHitTCal[dssdTHit]/D");
		}
		int getTHit(){
			return dssdTHit;
		}
		void setHit(int nHit){
			dssdTHit = nHit;
		}

		int getTHitSide(int iHit){
			return dssdTHitSide[iHit];
		}
		int getTHitStripId(int iHit){
			return dssdTHitStripId[iHit];
		}
		double getTHitTCal(int iHit){
			return dssdTHitTCal[iHit];
		}

		int getTdcRaw(int side,int stripId){
			return teleRaw->getDssdTRaw(side,stripId);
		}
		int getTdcRef(int side){
			return teleRaw->getDssdTRef(side);
		}
		double getCh2ns(){
			return 1.0;
		}
		void print(){
			cout<<"Dssd Time Hit"<<endl;
			for (int i = 0; i < dssdTHit; ++i) {
				cout<<" Hit"<<i<<" "<<dssdTHitSide[i]<<" "<<dssdTHitStripId[i]<<" "<<dssdTHitTCal[i]<<endl;	
			}
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
			dssdEnergy->calibrate(rawData);
			dssdTime->calibrate(rawData);
		}
		void print(){
			dssdEnergy->print();
			dssdTime->print();
		}
		~DssdCal(){}

};
