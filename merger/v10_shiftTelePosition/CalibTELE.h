class DssdEnergyPara{
	private:
		double kScmSlope[4][32];
		double bScmOffset[4][32];
		double ekScmSlope[4][32];
		double ebScmOffset[4][32];

		double kCalSlope[2];
		double bCalOffset[2];

		double kScmGain[4][32]; // new Para
		double kCalibGain[4]; // new Para
		//double kRefA[4]; // Ref LF,LB,RF,RB
		//double kRefB[4]; // 


		void loadNewScmPara(){
			ifstream in;
			TString inputName;

			inputName = env->GetValue("dssdScmNewPara","le.txt");
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int strip;
			int refId;
			double offset;
			double gain;
			while (1)
			{
				in >>side>>strip>>refId>>offset>>gain;
				cout<<side<<"\t"<<strip<<"\t"<<offset<<"\t"<<gain<<endl;
				if (!in.good()) break;
				kScmGain[side][strip]=gain;
			}
			in.close();
		}
		void loadCalibPeak5(){
			ifstream in;
			TString inputName;

			inputName = env->GetValue("dssdPeak5CalibPara","le.txt");
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			double gain;
			while (1)
			{
				in >>side>>gain;
				cout<<side<<"\t"<<gain<<endl;
				if (!in.good()) break;
				kCalibGain[side] = gain;
			}
			in.close();
		}
		void loadSiliconCalibrationParas(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32]){
			ifstream in;
			TString inputName;

			inputName = env->GetValue("dssdScmPara","DSSD_Fit_Whole.txt");
			cout<<inputName<<endl;
			in.open(inputName);

			int side;
			int strip;
			double  k0;
			double  b0;
			double ek0;
			double eb0;
			while (1)
			{
				in >>side>>strip>>k0>>b0>>ek0>>eb0;
				cout<<side<<"\t"<<strip<<"\t"<<k0<<"\t"<<b0<<endl;
				if (!in.good()) break;

				k[side][strip]=k0;
				ek[side][strip]=ek0;

				b[side][strip]=b0;
				eb[side][strip]=eb0;

			}
		}


	public:

	public:
		~DssdEnergyPara(){}

		DssdEnergyPara(){
			env = new TEnv("./config/configMerger.prm");
			loadSiliconCalibrationParas(kScmSlope,bScmOffset,ekScmSlope,ebScmOffset);

			kCalSlope[0] =  0.00645438;
			bCalOffset[0] = -0.621313;

			kCalSlope[1] = 0.00683802;
			bCalOffset[1] = -0.612683;

			loadNewScmPara();
			loadCalibPeak5();
	
		}
		double getScmSlope_old(int side, int id){
			return kScmSlope[side][id];
		}
		double getScmOffset_old(int side, int id){
			return bScmOffset[side][id];
		}
		double getCalSlope_old(int side){ // side dssd Left right
			return kCalSlope[side];
		}
		double getCalOffset_old(int side){ // side dssd Left right

			return bCalOffset[side];
		}
		double getScmGain(int side,int id){
			return kScmGain[side][id];
		}
		double getCalibGain(int side){
			return kCalibGain[side];
		}


};
class DssdEnergy{
	private:
		DssdEnergyPara *dssdPara;
		double getScm_old(int side,int id,double qPed){
			return dssdPara->getScmSlope_old(side,id)*qPed + dssdPara->getScmOffset_old(side,id);
		}
		double getQCal_old(int side,double scm){
			return dssdPara->getCalSlope_old(side)*scm + dssdPara->getCalOffset_old(side);
		}

		double getScm(int side,int id,double qPed){
			return qPed/dssdPara->getScmGain(side,id);
		}
		double getQCal(int side,double scm){
			//cout<<side<<" scm="<<scm<<" "<<dssdPara->getRefParaA(side)<<" "<<dssdPara->getRefParaB(side)<<endl;	
			//return dssdPara->getRefParaA(side)*scm/(1+dssdPara->getRefParaB(side)*scm);
			return dssdPara->getCalibGain(side)*scm;
		}



	public:
		DssdEnergy(){
			dssdPara = new DssdEnergyPara();
		}
		~DssdEnergy(){}
		double getFront_old(int side,int fid,double fQPed){
			double scm = getScm_old(2*side,fid,fQPed);
			return getQCal_old(side,scm);
		}
		double getBack_old(int side,int bid,double bQPed){
			double scm = getScm_old(2*side+1,bid,bQPed);
			return getQCal_old(side,scm);
		}

		double getFront(int side,int fid,double fQPed){
			double scm = getScm(2*side,fid,fQPed);
			//cout<<2*side<<" scm="<<scm<<endl;
			return getQCal(2*side,scm);
		}
		double getBack(int side,int bid,double bQPed){
			double scm = getScm(2*side+1,bid,bQPed);
			return getQCal(2*side+1,scm);
		}
	
};
class CsiEnergyPara{
	private:
		double csiSyncA[7];
		double csiSyncB[7];
		double csiSyncCalibA[7];
		double csiSyncCalibB[7];

		double csiCalibA[7];
		double csiCalibB[7];
	
	
		void load(){
			loadSync();
			loadSyncCalib();

			loadCalibPeak5();
		}
		void loadCalibPeak5(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("csiPeak5CalibPara","txt/peak5CsiQPedEnergy.txt");
			in.open(inputName);
			cout<<"Openning peak5 Calib  Txt: "<<inputName<<endl;
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
		void loadSyncCalib(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("csiSyncCalibPara","csiSyncCalibPara.txt");
			in.open(inputName);
			cout<<"Openning Calib  Txt: "<<inputName<<endl;
			int id;
			double calibA;
			double calibB;
			while(1){
				if(!in.good()) break;
				in>>id>>calibA>>calibB;
				cout<<id<<"\t"<<calibA<<"\t"<<calibB<<endl;
				csiSyncCalibA[id] = calibA;
				csiSyncCalibB[id] = calibB;
			}
		}

	public:
		~CsiEnergyPara(){}


		CsiEnergyPara(){
			load();
		}
		double getCsISyncA(int id){
			return csiSyncA[id];
		}
		double getCsISyncB(int id){
			return csiSyncB[id];
		}
		double getCsISyncCalibA(int id){
			return csiSyncCalibA[id];
		}
		double getCsISyncCalibB(int id){
			return csiSyncCalibB[id];
		}

		double getCsICalibA(int id){
			return csiCalibA[id];
		}
		double getCsICalibB(int id){
			return csiCalibB[id];
		}

	
};
class CsiEnergy{

	private:
		CsiEnergyPara *csiPara;
		double syncQPed(int id, double qPed){
			return csiPara->getCsISyncA(id)*qPed/(1+csiPara->getCsISyncB(id)*qPed);
		}
		double getSyncQCal(int id,double sync){
			return csiPara->getCsISyncCalibA(id)*sync/(1+csiPara->getCsISyncCalibB(id)*sync);
		}


	public:
		CsiEnergy(){
			csiPara = new CsiEnergyPara();
		}
		~CsiEnergy(){
			delete csiPara;
		}
		double getSyncEnergy(int id,double qPed){
			double sync = syncQPed(id,qPed);
			return getSyncQCal(id,sync);
		}
		double getEnergy(int id,double qPed){
			return csiPara->getCsICalibA(id)*qPed/(1+csiPara->getCsICalibB(id)*qPed);
		}

};
class EnergyTELE{
	private:
		DssdEnergy *dssdEnergy;
		CsiEnergy *csiEnergy;
	public:
		EnergyTELE(){
			dssdEnergy = new DssdEnergy();
			csiEnergy = new CsiEnergy();
		}
		~EnergyTELE(){
			delete dssdEnergy;
			delete csiEnergy;
		}
		double getCsiE(int id,double qPed){
			return csiEnergy->getEnergy(id,qPed);
		}
		double getSyncCsiE(int id,double qPed){ // first sync CsiQPed then calib only 1 crystal
			return csiEnergy->getSyncEnergy(id,qPed);
		}

		double getDssdFrontE(int side,int fid,double fQPed){
			return dssdEnergy->getFront(side,fid,fQPed);
		}

		double getDssdBackE(int side, int bid,double bQPed){
			return dssdEnergy->getBack(side,bid,bQPed);
		}

		double getDssdFrontE_old(int side,int fid,double fQPed){
			return dssdEnergy->getFront_old(side,fid,fQPed);
		}

		double getDssdBackE_old(int side, int bid,double bQPed){
			return dssdEnergy->getBack_old(side,bid,bQPed);
		}


};
class TimeTELE{
	private:
	public:
		TimeTELE(){}
		~TimeTELE(){}
		double getCsiT(int id,double tCal){
			return 0;
		}
		double getDssdT(int side,int fid,double tCal){
			return 0;
		}
};
