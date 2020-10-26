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
				
			}
		}
	
		void init(){
			rawData = NULL;
			for(int k = 0;k<7;k++){
				csiQPed[k] = -9999;
			}
		}

		void setBranch(TTree *tree){

			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
		}
		void print(){
			cout<<" Csi QPed Hit :"<<endl;
			for (int i = 0; i < 7; ++i) {
				cout<<csiQPed[i]<<endl;	
			}
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

class CsiCal{
	private:
		TELEReadRaw 	*teleReadRaw;
		CsIEnergyCal	*csiEnergy;
		CsITimeCal 	*csiTime;


	public:
		CsiCal(){
			csiEnergy  = new CsIEnergyCal();
			csiTime    = new CsITimeCal();
		}
		~CsiCal(){}
		void setBranch(TTree *tree){
			csiEnergy->setBranch(tree);
			csiTime->setBranch(tree);

		}
		void init(){
			csiEnergy->init();
			csiTime->init();
		}
		void calibration(TELEReadRaw *rawData){
			teleReadRaw = rawData;
			csiEnergy->calibrate(rawData);
			csiTime->calibrate(rawData);
		}
		void print(){
			csiEnergy->print();
			csiTime->print();
		}

};
