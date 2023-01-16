class PLAConvert{
	private:
		// Each plastic calibrated T and Q	
		double F3T;
		double F3Q;

		double F7T;
		double F7Q;

		double SBT1T;
		double SBT1Q;

		double SBT2T;
		double SBT2Q;

		double SBVT;
		double SBVQ;

		double F13T;
		double F13Q;
		void init(){
			F3T = NAN;
			F3Q = NAN;

			F7T = NAN;
			F7Q = NAN;

			F13T = NAN;
			F13Q = NAN;

			SBVT = NAN;
			SBVQ = NAN;
			SBT1T = NAN;
			SBT1Q = NAN;

			SBT2T = NAN;
			SBT2Q = NAN;

		}

		PLARead *rawData;


		void finalizeF13(){
			if(SBT1T!=NAN && SBT2T!= NAN){
				F13T = 0.5*(SBT1T+SBT2T);
			}else{
				if(SBT1T!= NAN) F13T = SBT1T;
				if(SBT2T!= NAN) F13T = SBT2T;
			}
			if(SBT1Q!=NAN && SBT2Q!= NAN){
				F13Q = 0.5*(SBT1Q+SBT2Q);
			}else{
				if(SBT1Q!= NAN) F13Q = SBT1Q;
				if(SBT2Q!= NAN) F13Q = SBT2Q;
			}

		}

		void convertTime(double t0,double t1,double &t){
			if(t0!=-9999 && t1!=-9999){
				t = 0.5*(t0+t1);
			}else{
				if(t0 != -9999) t = t0;
				if(t1 != -9999) t = t1;
			}
		}
		void convertEnergy(double q0,double q1,double &q){
			if(q0!= -9999 && q1!= -9999){
				q = sqrt(q0*q1);
			}else{
				if(q0 !=-9999) q = q0;
				if(q1 !=-9999) q = q1;
			}

		}
		void convertF3(){
			convertTime(getF3TCal(0),getF3TCal(1),F3T);
			convertEnergy(getF3QCal(0),getF3QCal(1),F3Q);
		}
		double getF3TCal(int id){
			return rawData->getF3TCal(id);
		}
		double getF3QCal(int id){
			return rawData->getF3QCal(id);
		}
		void convertF7(){
			convertTime(getF7TCal(0),getF7TCal(1),F7T);
			convertEnergy(getF7QCal(0),getF7QCal(1),F7Q);
		}
		double getF7TCal(int id){
			return rawData->getF7TCal(id);
		}
		double getF7QCal(int id){
			return rawData->getF7QCal(id);
		}
		void convertSBT1(){
			convertTime(getSBT1TCal(0),getSBT1TCal(1),SBT1T);
			convertEnergy(getSBT1QCal(0),getSBT1QCal(1),SBT1Q);
		}
		double getSBT1TCal(int id){
			return rawData->getSBT1TCal(id);
		}
		double getSBT1QCal(int id){
			return rawData->getSBT1QCal(id);
		}
		void convertSBT2(){
			convertTime(getSBT2TCal(0),getSBT2TCal(1),SBT2T);
			convertEnergy(getSBT2QCal(0),getSBT2QCal(1),SBT2Q);
		}
		double getSBT2TCal(int id){
			return rawData->getSBT2TCal(id);
		}
		double getSBT2QCal(int id){
			return rawData->getSBT2QCal(id);
		}
		void convertSBV(){
			convertTime(getSBVTCal(0),getSBVTCal(1),SBVT);
			convertEnergy(getSBVQCal(0),getSBVQCal(1),SBVQ);
		}
		double getSBVTCal(int id){
			return rawData->getSBVTCal(id);
		}
		double getSBVQCal(int id){
			return rawData->getSBVQCal(id);
		}

	
	public:
		PLAConvert(){}
		~PLAConvert(){}
		void setBranch(TTree *tree){
			tree->Branch("F3T",&F3T,"F3T/D");
			tree->Branch("F3Q",&F3Q,"F3Q/D");
			tree->Branch("F7T",&F7T,"F7T/D");
			tree->Branch("F7Q",&F7Q,"F7Q/D");
			tree->Branch("SBT1T",&SBT1T,"SBT1T/D");
			tree->Branch("SBT1Q",&SBT1Q,"SBT1Q/D");
			tree->Branch("SBT2T",&SBT2T,"SBT2T/D");
			tree->Branch("SBT2Q",&SBT2Q,"SBT2Q/D");
			tree->Branch("F13T",&F13T,"F13T/D");
			tree->Branch("F13Q",&F13Q,"F13Q/D");
			tree->Branch("SBVT",&SBVT,"SBVT/D");
			tree->Branch("SBVQ",&SBVQ,"SBVQ/D");
		}
		void convert(PLARead *pla){
			init();
			rawData = pla;	
			convertF3();
			convertF7();
			convertSBT1();
			convertSBT2();
			finalizeF13();
			convertSBV();
		}
		void print(){
			//printF3();
		}
		void printF3(){
			cout<<"F3T = "<<F3T<<" F3Q = "<<F3Q<<endl;
		}
		void printF7(){
			cout<<"F7T = "<<F7T<<" F7Q = "<<F7Q<<endl;
		}
		void printSBT1(){
			cout<<"SBT1T = "<<SBT1T<<" SBT1Q = "<<SBT1Q<<endl;
		}
		void printSBT2(){
			cout<<"SBT2T = "<<SBT2T<<" SBT2Q = "<<SBT2Q<<endl;
		}
		void printSBV(){
			cout<<"SBVT = "<<SBVT<<" SBVQ = "<<SBVQ<<endl;
		}

};
