class CsIEnergyCalPara{
	private:
		double csiPedestal[7];
		double csiPedSigma[7];

		void init(){
			for (int i = 0; i < 7; ++i) {
				csiPedestal[i] = NAN;	
			}
		}
		void load(){
			loadPedestal();
		}
		void loadPedestal(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("csiPedestal","csiPedestal.txt");
			cout<<"Openning CsI Pedestal Txt: "<<inputName<<endl;
			in.open(inputName);
			int id;
			double ped;
			double sigma;
			while(1){
				if(!in.good()) break;
				in>>id>>ped>>sigma;
				cout<<id<<"\t"<<ped<<endl;
				csiPedestal[id] = ped;
				csiPedSigma[id] = sigma;
			}
		}

	public:

		CsIEnergyCalPara(){
			init();
			load();
		}
		double getCsIPedestal(int id){
			return csiPedestal[id];
		}
		double getCsIPedSigma(int id){
			return csiPedSigma[id];
		}
	
	
		
};
class CsIEnergyCal{
	private:

		TELEReadRaw *rawData;
		CsIEnergyCalPara *csiQCalPara;
		int csiQHit;
		int csiQHitId[7];
		double csiQHitQPed[7];
		double csiQPed[7];

		int getCsIQRaw(int id){
			return rawData->getCsIQRaw(id);
		}
		double getCsIPedestal(int id){
			return csiQCalPara->getCsIPedestal(id);
		}
		double getCsIPedSigma(int id){
			return csiQCalPara->getCsIPedSigma(id);
		}
	
	
	
	public:
		CsIEnergyCal(){

			csiQCalPara = new CsIEnergyCalPara();
		}

		~CsIEnergyCal(){
			delete csiQCalPara;
		}
		void calibrate(TELEReadRaw *raw){
			rawData = raw;
			for(int k = 0;k<7;k++){
				csiQPed[k] = getCsIQRaw(k) - getCsIPedestal(k);
				
				if(csiQPed[k]>5*getCsIPedSigma(k)){
					csiQHitId[csiQHit] = k;
					csiQHitQPed[csiQHit] = csiQPed[k];
					csiQHit++;
				}
			}
		}
	
		void init(){
			rawData = NULL;
			csiQHit = 0;
			for(int k = 0;k<7;k++){
				csiQHitId[k] = -1;
				csiQHitQPed[k] = NAN;
				csiQPed[k] = NAN;
			}
		}

		void setBranch(TTree *tree){

			tree->Branch("csiQHit",&csiQHit,"csiQHit/I");
			tree->Branch("csiQHitId",csiQHitId,"csiQHitId[csiQHit]/I");
			tree->Branch("csiQHitQPed",csiQHitQPed,"csiQHitQPed[csiQHit]/D");
			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
		}
		void print(){
			cout<<" Csi QPed Hit :"<<endl;
			for (int i = 0; i < csiQHit; ++i) {
				cout<<i<<" "<<csiQHitId[i]<<" "<<csiQHitQPed[i]<<endl;	
			}
			//for (int i = 0; i < 7; ++i) {
			//	cout<<csiQPed[i]<<endl;	
			//}
		}
		int getQHit(){
			return csiQHit;
		}
		int getQHitId(int iHit){
			return csiQHitId[iHit];
		}
		double getQHitQPed(int iHit){
			return csiQHitQPed[iHit];
		}


};
class CsITimeCal{

		TELEReadRaw *rawData;
		int csiTHit;
		int csiTHitId[7];
		double csiTHitTCal[7];
		
		int getCsITRaw(int id){
			return rawData->getCsITRaw(id);
		} 
	public:
		void init(){
			rawData = NULL;
			csiTHit = 0;
			for(int k = 0;k<7;k++){
				csiTHitId[k] = -1;
				csiTHitTCal[k] = -9999;
			}
		}

		void calibrate(TELEReadRaw *raw){
			rawData = raw;
			for (int i = 0; i < 7; ++i) {
				if(getCsITRaw(i)!=-1){
					csiTHitId[csiTHit] = i;
					csiTHitTCal[csiTHit] = getCsITRaw(i);
					csiTHit++;	
				}
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("csiTHit",&csiTHit,"csiTHit/I");
			tree->Branch("csiTHitId",csiTHitId,"csiTHitId[csiTHit]/I");
			tree->Branch("csiTHitTCal",csiTHitTCal,"csiTHitTCal[csiTHit]/D");
		}
		void print(){
			cout<<" CsI TCal Hit"<<endl;
			for (int i = 0; i < csiTHit; ++i) {
				cout<<i<<" "<<csiTHitId[i]<<" "<<csiTHitTCal[i]<<endl;	
			}
		}
		int getTHit(){
			return csiTHit;
		}
		int getTHitId(int iHit){
			return csiTHitId[iHit];
		}
		double getTHitTCal(int iHit){
			return csiTHitTCal[iHit];
		}


};

class CsIHit{
	private:
		CsIEnergyCal *csiEnergy;
		CsITimeCal *csiTime;

		int csiHit;	
		int csiHitId[7];// csi maximum pixel effective hit	
		double csiHitQPed[7];
		double csiHitTCal[7];

		int getQHit(){
			return csiEnergy->getQHit();
		}
		int getTHit(){
			return csiTime->getTHit();
		}
		int getQHitId(int iHit){
			return csiEnergy->getQHitId(iHit);
		}
		int getTHitId(int iHit){
			return csiTime->getTHitId(iHit);
		}
		double getTHitTCal(int iHit){
			return csiTime->getTHitTCal(iHit);
		}
		double getQHitQPed(int iHit){
			return csiEnergy->getQHitQPed(iHit);
		}



	public:
		CsIHit(){}
		~CsIHit(){}
		void init(){
			csiEnergy = NULL;
			csiTime = NULL;
			csiHit = 0;
			for (int i = 0; i < 7; ++i) {
				csiHitId[i] = -1;	
				csiHitQPed[i] = -9999;
				csiHitTCal[i] = -9999;
			}
		}
		void hitEvent(CsIEnergyCal *csiE,CsITimeCal *csiT){

			csiEnergy = csiE;
			csiTime   = csiT;
			hitEvent();
		}
		void hitEvent(){
			for (int j = 0; j < getQHit(); ++j) {
				csiHitQPed[csiHit] = getQHitQPed(j);
				csiHitId[csiHit] = getQHitId(j);

				for (int i = 0; i < getTHit(); ++i) {
					if(getTHitId(i)==getQHitId(j)){
						csiHitTCal[csiHit] = getTHitTCal(i);
					}
				}
				csiHit++;
			}

		}
		void setBranch(TTree *tree){
			tree->Branch("csiHit",&csiHit,"csiHit/I");
			tree->Branch("csiHitId",&csiHitId,"csiHitId[csiHit]/I");
			tree->Branch("csiHitQPed",&csiHitQPed,"csiHitQPed[csiHit]/D");
			tree->Branch("csiHitTCal",&csiHitTCal,"csiHitTCal[csiHit]/D");
		}
		void print(){
			cout<<"Csi Hit Event:"<<endl;
			for (int i = 0; i < csiHit; ++i) {
				cout<<" "<<i<<" "<<csiHitId[i]<<" "<<csiHitQPed[i]<<" "<<csiHitTCal[i]<<endl;	
			}
		}
		int getHit(){
			return csiHit;
		}
		int getHitId(int iHit){
			return csiHitId[iHit];
		}
		double getHitQPed(int iHit){
			return csiHitQPed[iHit];
		}
		double getHitTCal(int iHit){
			return csiHitTCal[iHit];
		}
};
class CsiCal{
	private:
		TELEReadRaw 	*teleReadRaw;
		CsIEnergyCal	*csiEnergy;
		CsITimeCal 	*csiTime;
		CsIHit 		*csiHit;


	public:
		CsiCal(){
			csiEnergy  = new CsIEnergyCal();
			csiTime    = new CsITimeCal();
			csiHit = new CsIHit();
		}
		~CsiCal(){}
		void setBranch(TTree *tree){
			csiEnergy->setBranch(tree);
			csiTime->setBranch(tree);
			csiHit->setBranch(tree);

		}
		void init(){
			csiEnergy->init();
			csiTime->init();
			csiHit->init();
		}
		void calibration(TELEReadRaw *rawData){
			teleReadRaw = rawData;
			csiEnergy->calibrate(rawData);
			csiTime->calibrate(rawData);
			csiHit->hitEvent(csiEnergy,csiTime);
		}
		void print(){
			csiEnergy->print();
			csiTime->print();
			csiHit->print();
		}
		int getHit(){
			return csiHit->getHit();
		}
		int getHitId(int iHit){
			return csiHit->getHitId(iHit);
		}
		double getHitQPed(int iHit){
			return csiHit->getHitQPed(iHit);
		}
		double getHitTCal(int iHit){
			return csiHit->getHitTCal(iHit);
		}

};
