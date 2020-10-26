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

		int dssdQHit;
		int dssdQHitSide[10];
		int dssdQHitStripId[10];
		double dssdQHitQPed[10];

		double dssdQPed[4][32];	
		
		void setQPedAndHit(){
			// raw->SCM->cal
			//side = 0 LF, 1 LB, 2 RF, 3 RB
			
			for(int side = 0;side<4;side++)
				for(int id=0;id<32;id++){
					if(getDssdQRaw(side,id)<=4096){
						dssdQPed[side][id] = getDssdQRaw(side,id) - getDssdPedestal(side,id);
						if(dssdQPed[side][id]>10*getDssdPedSigma(side,id)&&dssdQHit<10){
							cout<<side<<" "<<id<<" "<<10*getDssdPedSigma(side,id)<<" "<<dssdQPed[side][id]<<endl;
							dssdQHitSide[dssdQHit] = side;
							dssdQHitStripId[dssdQHit] = id;
							dssdQHitQPed[dssdQHit] = dssdQPed[side][id];
							dssdQHit++;
							//cout<<dssdQHit<<" "<<side<<" "<<id<<endl;
						}
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
			for (int i = 0; i < 10; ++i) {
				dssdQHitSide[i] = -1; // 1 2 3 4
				dssdQHitStripId[i] = -1; // 1 2 3 4
				dssdQHitQPed[i] = -9999; // 1 2 3 4
			}
			dssdQHit = 0;
		}

		void setBranch(TTree *tree){
			tree->Branch("dssdQHit",&dssdQHit,"dssdQHit/I");
			tree->Branch("dssdQHitSide",dssdQHitSide,"dssdQHitSide[dssdQHit]/I");
			tree->Branch("dssdQHitStripId",dssdQHitStripId,"dssdQHitStripId[dssdQHit]/I");
			tree->Branch("dssdQHitQPed",dssdQHitQPed,"dssdQHitQPed[dssdQHit]/D");
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
		void setHit(int nHit){
			dssdQHit = nHit;
		}
		int getQHit(){
			return dssdQHit;
		}
		int getQHitSide(int iHit){
			return dssdQHitSide[iHit];
		}
		int getQHitStripId(int iHit){
			return dssdQHitStripId[iHit];
		}
		double getQHitQPed(int iHit){
			return dssdQHitQPed[iHit];
		}
		void print(){
			cout<<"Dssd QPed Hit:"<<endl;
			for (int i = 0; i < dssdQHit; ++i) {
				cout<<" Hit"<<i<<" "<<dssdQHitSide[i]<<" "<<dssdQHitStripId[i]<<" "<<dssdQHitQPed[i]<<endl;	
			}
			//for (int i = 0; i < 4; ++i) {
			//	for (int j = 0; j < 32; ++j) {
			//		cout<<i<<" "<<j<<" "<<dssdQPed[i][j]<<endl;	
			//	}
			//}
		}


};

class DSSDTimeCal{

		TELEReadRaw *teleRaw;
		int dssdTHit;
		int dssdTHitSide[10];
		int dssdTHitStripId[10];
		double dssdTHitTCal[10];
	public:
		void init(){
			teleRaw = NULL;
			dssdTHit = 0;
			for (int i = 0; i < 10; ++i) {
				dssdTHitSide[i] = -1;
				dssdTHitStripId[i] = -1;
				dssdTHitTCal[i] = -9999;
			}
		}
		void calibrate(TELEReadRaw *rawData){
			teleRaw = rawData;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 32; ++j) {
					if(getTdcRaw(i,j)!=-1&&dssdTHit<10){
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
class DSSDHit{
	private:
		DSSDEnergyCal *dssdEnergy;
		DSSDTimeCal *dssdTime;

		int dssdHit;	
		int dssdHitSide[10];// Dssd maximum pixel effective hit	
		int dssdHitFid[10];// Dssd maximum pixel effective hit	
		int dssdHitBid[10];// Dssd maximum pixel effective hit	
		double dssdHitFQPed[10];// Dssd maximum pixel effective hit	
		double dssdHitBQPed[10];// Dssd maximum pixel effective hit	
		double dssdHitTCal[10];// Dssd maximum pixel effective hit	

		int getQHit(){
			return dssdEnergy->getQHit();
		}
		int getTHit(){
			return dssdTime->getTHit();
		}
		int getQHitSide(int iHit){
			return dssdEnergy->getQHitSide(iHit);
		}
		int getTHitSide(int iHit){
			return dssdTime->getTHitSide(iHit);
		}
		int getQHitStripId(int iHit){
			return dssdEnergy->getQHitStripId(iHit);
		}
		int getTHitStripId(int iHit){
			return dssdTime->getTHitStripId(iHit);
		}
		double getTHitTCal(int iHit){
			return dssdTime->getTHitTCal(iHit);
		}
		double getQHitQPed(int iHit){
			return dssdEnergy->getQHitQPed(iHit);
		}

	public:
		DSSDHit(){}
		~DSSDHit(){}
		void init(){
			dssdEnergy = NULL;
			dssdTime = NULL;
			dssdHit = 0;
			for (int i = 0; i < 10; ++i) {
				dssdHitSide[i]	= -1;	
				dssdHitFid[i]	= -1;// Dssd maximum pixel effective hit	
				dssdHitBid[i]	= -1;// Dssd maximum pixel effective hit	
				dssdHitFQPed[i]	= -9999;// Dssd maximum pixel effective hit	
				dssdHitBQPed[i]	= -9999;// Dssd maximum pixel effective hit	
				dssdHitTCal[i]	= -9999;// Dssd maximum pixel effective hit	
			}                 
		}
		void hitEvent(DSSDEnergyCal *dssdE,DSSDTimeCal *dssdT){

			dssdEnergy = dssdE;
			dssdTime   = dssdT;
			hitEvent();
			if(dssdHit == 0){
				dssdEnergy->setHit(0);
				dssdTime->setHit(0);
			}
		}
		void hitEvent(){
			for (int i = 0; i < getTHit(); ++i) {
				for (int j = 0; j < getQHit(); ++j) {
					if((2*getTHitSide(i) == getQHitSide(j))&&(getTHitStripId(i)==getQHitStripId(j))){ // find T and FQ have same side and strip Id
						for (int k = 0; k < getQHit(); ++k) { // loop all Q to find back Q
							if(getQHitSide(k) == 2*getTHitSide(i)+1&&dssdHit<10){
								if(abs(getQHitQPed(j)/getQHitQPed(k))>3||abs(getQHitQPed(j)/getQHitQPed(k))<0.3) continue; // remove event unrelevent
								if(abs(getQHitQPed(j)-getQHitQPed(k))>500) continue; // remove event unrelevent
								dssdHitTCal[dssdHit]= getTHitTCal(i);
								dssdHitFQPed[dssdHit]= getQHitQPed(j);
								dssdHitBQPed[dssdHit]= getQHitQPed(k);

								dssdHitFid[dssdHit]= getTHitStripId(i);
								dssdHitBid[dssdHit]= getQHitStripId(k);
								dssdHitSide[dssdHit]= getTHitSide(i);
								dssdHit++;
							}
						}
					}
				}
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdHit",&dssdHit,"dssdHit/I");
			tree->Branch("dssdHitSide",&dssdHitSide,"dssdHitSide[dssdHit]/I");
			tree->Branch("dssdHitFid",&dssdHitFid,"dssdHitFid[dssdHit]/I");
			tree->Branch("dssdHitBid",&dssdHitBid,"dssdHitBid[dssdHit]/I");
			tree->Branch("dssdHitFQPed",&dssdHitFQPed,"dssdHitFQPed[dssdHit]/D");
			tree->Branch("dssdHitBQPed",&dssdHitBQPed,"dssdHitBQPed[dssdHit]/D");
			tree->Branch("dssdHitTCal",&dssdHitTCal,"dssdHitTCal[dssdHit]/D");
		}
		void print(){
			cout<<"Dssd Hit Event:"<<endl;
			for (int i = 0; i < dssdHit; ++i) {
				cout<<" Hit"<<i<<" "<<dssdHitSide[i]<<" "<<dssdHitFid[i]<<" "<<dssdHitBid[i]<<endl;	
			}
		}
		int getHit(){
			return dssdHit;
		}
		int getHitSide(int iHit){
			return dssdHitSide[iHit];
		}
		int getHitFid(int iHit){
			return dssdHitFid[iHit];
		}
		int getHitBid(int iHit){
			return dssdHitBid[iHit];
		}
		double getHitFQPed(int iHit){
			return dssdHitFQPed[iHit];
		}
		double getHitBQPed(int iHit){
			return dssdHitBQPed[iHit];
		}
		double getHitTCal(int iHit){
			return dssdHitTCal[iHit];
		}


};
class DssdCal{
	private:

		TELEReadRaw *teleReadRaw;
		DSSDEnergyCal	*dssdEnergy;
		DSSDTimeCal	*dssdTime;
		DSSDHit *dssdHit;

	public:
		DssdCal(){
			dssdEnergy = new DSSDEnergyCal();
			dssdTime   = new DSSDTimeCal();
			dssdHit = new DSSDHit();
		}
		void setBranch(TTree *tree){
			dssdEnergy->setBranch(tree);
			dssdTime->setBranch(tree);
			dssdHit->setBranch(tree);
		}
		void init(){
			dssdEnergy->init();
			dssdTime->init();
			dssdHit->init();
		}
		void calibration(TELEReadRaw *rawData){
			teleReadRaw = rawData;
			dssdEnergy->calibrate(rawData);
			dssdTime->calibrate(rawData);
			dssdHit->hitEvent(dssdEnergy,dssdTime);
		}
		void print(){
			dssdEnergy->print();
			dssdTime->print();
			dssdHit->print();
		}
		~DssdCal(){}
		int getHit(){
			return dssdHit->getHit();
		}
		int getHitSide(int iHit){
			return dssdHit->getHitSide(iHit);
		}
		int getHitFid(int iHit){
			return dssdHit->getHitFid(iHit);
		}
		int getHitBid(int iHit){
			return dssdHit->getHitBid(iHit);
		}
		double getHitFQPed(int iHit){
			return dssdHit->getHitFQPed(iHit);
		}
		double getHitBQPed(int iHit){
			return dssdHit->getHitBQPed(iHit);
		}
		double getHitTCal(int iHit){
			return dssdHit->getHitTCal(iHit);
		}

};
