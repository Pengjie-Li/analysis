
class PlasticRead{
	private:
	public:
		PlasticRead(TArtPlastic *plastic, int *TRaw,int *QRaw,double *TCal,double *QCal,double &T,double &Q){

			TRaw[0] = plastic->GetTLRaw();
			TRaw[1] = plastic->GetTRRaw();
			QRaw[0] = plastic->GetQLRaw();
			QRaw[1] = plastic->GetQRRaw();

			TCal[0] = plastic->GetTimeLSlew();
			TCal[1] = plastic->GetTimeRSlew();
			//cout<<"Cal*F3_LTRaw="<<0.0156251*F3_LTRaw<<"  F3_LTSlew="<<F3_LTSlew<<endl;
			QCal[0] = -9999;
			QCal[1] = -9999;

			if(TCal[0]!=-9999 && TCal[1]!=-9999){
				T = 0.5*(TCal[0]+TCal[1]);
			}else{
				if(TCal[0]!= -9999) T = TCal[0];
				if(TCal[1]!= -9999) T = TCal[1];
			}
			if(QRaw[0]!= -9999 && QRaw[1]!= -9999){
				Q = sqrt(QRaw[0]*QRaw[1]);
			}else{
				if(QRaw[0]!=-9999) Q = QRaw[0];
				if(QRaw[1]!=-9999) Q = QRaw[1];
			}

		}
		~PlasticRead(){}
};
class PLARead{
	private :
		//Design Data Structure
		//Raw Data Structure
		int F3TRaw[2];
		int F3QRaw[2];
		double F3TCal[2];
		double F3QCal[2];

		int F7TRaw[2];
		int F7QRaw[2];
		double F7TCal[2];
		double F7QCal[2];
	
		int SBT1TRaw[2];
		int SBT1QRaw[2];
		double SBT1TCal[2];
		double SBT1QCal[2];

		int SBT2TRaw[2];
		int SBT2QRaw[2];
		double SBT2TCal[2];
		double SBT2QCal[2];

		int SBVTRaw[2];
		int SBVQRaw[2];
		double SBVTCal[2];
		double SBVQCal[2];
	
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

		TArtPlastic *PlasticF3  ; 
		TArtPlastic *PlasticF7  ; 
		TArtPlastic *PlasticSBT1;
		TArtPlastic *PlasticSBT2;
		TArtPlastic *PlasticSBV ;



	public:
		PLARead(){};
		~PLARead(){};

                void getDataContainer(TArtCalibPlastic *calibPlastic){
			PlasticF3 = calibPlastic->FindPlastic((char*)"F3pl");
			PlasticF7 = calibPlastic->FindPlastic((char*)"F7pl");
			PlasticSBT1 = calibPlastic->FindPlastic((char*)"F13pl-1");
			PlasticSBT2 = calibPlastic->FindPlastic((char*)"F13pl-2");
			PlasticSBV = calibPlastic->FindPlastic((char*)"SBV");

		}

		void read(TArtCalibPlastic *calibPlastic){
			init();
			getDataContainer(calibPlastic);
			readF3();
			readF7();
			readF13();
			readSBV();
		}
		void readF13(){
			readSBT1();
			readSBT2();
			if(SBT1T!=-9999 && SBT2T!= -9999){
				F13T = 0.5*(SBT1T+SBT2T);
			}else{
				if(SBT1T!= -9999) F13T = SBT1T;
				if(SBT2T!= -9999) F13T = SBT2T;
			}
			if(SBT1Q!=-9999 && SBT2Q!= -9999){
				F13Q = 0.5*(SBT1Q+SBT2Q);
			}else{
				if(SBT1Q!= -9999) F13Q = SBT1Q;
				if(SBT2Q!= -9999) F13Q = SBT2Q;
			}

		}
		void readF3(){
			PlasticRead *plaF3 = new PlasticRead(PlasticF3,F3TRaw,F3QRaw,F3TCal,F3QCal,F3T,F3Q);
			delete plaF3;
		}
		void readF7(){
			PlasticRead *plaF7 = new PlasticRead(PlasticF7,F7TRaw,F7QRaw,F7TCal,F7QCal,F7T,F7Q);
			delete plaF7;
		}
		void readSBT1(){
			PlasticRead *plaSBT1 = new PlasticRead(PlasticSBT1,SBT1TRaw,SBT1QRaw,SBT1TCal,SBT1QCal,SBT1T,SBT1Q);
			delete plaSBT1;
		}
		void readSBT2(){
			PlasticRead *plaSBT2 = new PlasticRead(PlasticSBT2,SBT2TRaw,SBT2QRaw,SBT2TCal,SBT2QCal,SBT2T,SBT2Q);
			delete plaSBT2;
		}
		void readSBV(){
			PlasticRead *plaSBV = new PlasticRead(PlasticSBV,SBVTRaw,SBVQRaw,SBVTCal,SBVQCal,SBVT,SBVQ);
			delete plaSBV;
		}






		void setBranch(TTree *tree){

			tree->Branch("F3TRaw",F3TRaw,"F3TRaw[2]/I");
			tree->Branch("F3QRaw",F3QRaw,"F3QRaw[2]/I");
			tree->Branch("F3TCal",F3TCal,"F3TCal[2]/D");
			tree->Branch("F3QCal",F3QCal,"F3QCal[2]/D");
			tree->Branch("F3T",&F3T,"F3T/D");
			tree->Branch("F3Q",&F3Q,"F3Q/D");

			tree->Branch("F7TRaw",F7TRaw,"F7TRaw[2]/I");
			tree->Branch("F7QRaw",F7QRaw,"F7QRaw[2]/I");
			tree->Branch("F7TCal",F7TCal,"F7TCal[2]/D");
			tree->Branch("F7QCal",F7QCal,"F7QCal[2]/D");
			tree->Branch("F7T",&F7T,"F7T/D");
			tree->Branch("F7Q",&F7Q,"F7Q/D");

			tree->Branch("SBT1TRaw",SBT1TRaw,"SBT1TRaw[2]/I");
			tree->Branch("SBT1QRaw",SBT1QRaw,"SBT1QRaw[2]/I");
			tree->Branch("SBT1TCal",SBT1TCal,"SBT1TCal[2]/D");
			tree->Branch("SBT1QCal",SBT1QCal,"SBT1QCal[2]/D");
			tree->Branch("SBT1T",&SBT1T,"SBT1T/D");
			tree->Branch("SBT1Q",&SBT1Q,"SBT1Q/D");

			tree->Branch("SBT2TRaw",SBT2TRaw,"SBT2TRaw[2]/I");
			tree->Branch("SBT2QRaw",SBT2QRaw,"SBT2QRaw[2]/I");
			tree->Branch("SBT2TCal",SBT2TCal,"SBT2TCal[2]/D");
			tree->Branch("SBT2QCal",SBT2QCal,"SBT2QCal[2]/D");
			tree->Branch("SBT2T",&SBT2T,"SBT2T/D");
			tree->Branch("SBT2Q",&SBT2Q,"SBT2Q/D");

			tree->Branch("F13T",&F13T,"F13T/D");
			tree->Branch("F13Q",&F13Q,"F13Q/D");

			tree->Branch("SBVTRaw",SBVTRaw,"SBVTRaw[2]/I");
			tree->Branch("SBVQRaw",SBVQRaw,"SBVQRaw[2]/I");
			tree->Branch("SBVTCal",SBVTCal,"SBVTCal[2]/D");
			tree->Branch("SBVQCal",SBVQCal,"SBVQCal[2]/D");
			tree->Branch("SBVT",&SBVT,"SBVT/D");
			tree->Branch("SBVQ",&SBVQ,"SBVQ/D");

		}

		void init(){

			F3T = -9999;
			F3Q = -9999;

			F7T = -9999;
			F7Q = -9999;

			F13T = -9999;
			F13Q = -9999;

			SBVT = -9999;
			SBVQ = -9999;
			SBT1T = -9999;
			SBT1Q = -9999;

			SBT2T = -9999;
			SBT2Q = -9999;


			for (int i = 0; i < 2; ++ i) {
				F3TRaw[i] = -9999; 		
				F7TRaw[i] = -9999; 		
				SBT1TRaw[i] = -9999; 		
				SBT2TRaw[i] = -9999; 		
				SBVTRaw[i] = -9999; 		

				F3QRaw[i] = -9999; 		
				F7QRaw[i] = -9999; 		
				SBT1QRaw[i] = -9999; 		
				SBT2QRaw[i] = -9999; 		
				SBVQRaw[i] = -9999; 		

				F3TCal[i] = -9999; 		
				F7TCal[i] = -9999; 		
				SBT1TCal[i] = -9999; 		
				SBT2TCal[i] = -9999; 		
				SBVTCal[i] = -9999; 		

				F3QCal[i] = -9999; 		
				F7QCal[i] = -9999; 		
				SBT1QCal[i] = -9999; 		
				SBT2QCal[i] = -9999; 		
				SBVQCal[i] = -9999; 		

			}
		}

};
