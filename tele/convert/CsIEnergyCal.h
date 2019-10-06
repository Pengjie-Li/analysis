class CsIEnergyCalPara{
	private:
		double csiPedestal[7];
		double csiSyncA[7];
		double csiSyncB[7];
		double csiCalibA[7];
		double csiCalibB[7];
	
		void init(){
			for (int i = 0; i < 7; ++i) {
				csiPedestal[i] = NAN;	
				csiSyncA[i] = NAN;
				csiSyncB[i] = NAN;
				csiCalibA[i] = NAN;
				csiCalibB[i] = NAN;
			}
		}
		void load(){
			loadPedestal();
			loadSync();
			loadCalib();
		}
		void loadPedestal(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("csiPedestal","csiPedestal.txt");
			cout<<"Openning CsI Pedestal Txt: "<<inputName<<endl;
			in.open(inputName);
			int id;
			double ped;
			while(1){
				if(!in.good()) break;
				in>>id>>ped;
				cout<<id<<"\t"<<ped<<endl;
				csiPedestal[id] = ped;
			}
		}
		void loadSync(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("csiSyncPara","csiSyncPara.txt");
			in.open(inputName);
			cout<<"Openning Sync  Txt: "<<inputName<<endl;
			int id;
			double syncA;
			double syncB;
			while(1){
				if(!in.good()) break;
				in>>id>>syncA>>syncB;
				cout<<id<<"\t"<<syncA<<"\t"<<syncB<<endl;
				csiSyncA[id] = syncA;
				csiSyncB[id] = syncB;
			}
		}
		void loadCalib(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("csiCalibPara","csiCalibPara.txt");
			in.open(inputName);
			cout<<"Openning Calib  Txt: "<<inputName<<endl;
			int id;
			double calibA;
			double calibB;
			while(1){
				if(!in.good()) break;
				in>>id>>calibA>>calibB;
				cout<<id<<"\t"<<calibA<<"\t"<<calibB<<endl;
				csiCalibA[id] = calibA;
				csiCalibB[id] = calibB;
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
		double getCsISyncA(int id){
			return csiSyncA[id];
		}
		double getCsISyncB(int id){
			return csiSyncB[id];
		}
		double getCsICalibA(int id){
			return csiCalibA[id];
		}
		double getCsICalibB(int id){
			return csiCalibB[id];
		}
	
	
	
		
};
class CsIEnergyCal{
	private:

		TELEReadRaw *rawData;
		CsIEnergyCalPara *csiQCalPara;
		double csiQCal[7];
		double csiQPed[7];
		double csiQSync[7];

		void init(){
			for(int k = 0;k<7;k++){
				csiQPed[k] = NAN;
				csiQSync[k] = NAN;
				csiQCal[k] = NAN;
			}

		}
		double getCsIQRaw(int id){
			return rawData->getCsIQRaw(id);
		}
		double getCsIPedestal(int id){
			return csiQCalPara->getCsIPedestal(id);
		}
		double getCsISyncA(int id){
			return csiQCalPara->getCsISyncA(id);
		}
		double getCsISyncB(int id){
			return csiQCalPara->getCsISyncB(id);
		}
		double getCsICalibA(int id){
			return csiQCalPara->getCsICalibA(id);
		}
		double getCsICalibB(int id){
			return csiQCalPara->getCsICalibB(id);
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
				csiQSync[k] = getCsISyncA(k)*csiQPed[k]/(1+getCsISyncB(k)*csiQPed[k]);
				csiQCal[k] = getCsICalibA(k)*csiQSync[k]/(1+getCsICalibB(k)*csiQSync[k]);
			}
		}
	
		void setBranch(TTree *tree){

			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
			tree->Branch("csiQSync",csiQSync,"csiQSync[7]/D");
			tree->Branch("csiQCal",csiQCal,"csiQCal[7]/D");
		}
};

