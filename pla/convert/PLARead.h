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
	
		TArtPlastic *PlasticF3  ; 
		TArtPlastic *PlasticF7  ; 
		TArtPlastic *PlasticSBT1;
		TArtPlastic *PlasticSBT2;
		TArtPlastic *PlasticSBV ;

		void plasticRead(TArtPlastic *plastic, int *TRaw,int *QRaw,double *TCal,double *QCal){

			TRaw[0] = plastic->GetTLRaw();
			TRaw[1] = plastic->GetTRRaw();
			QRaw[0] = plastic->GetQLRaw();
			QRaw[1] = plastic->GetQRRaw();

			TCal[0] = plastic->GetTimeLSlew();
			TCal[1] = plastic->GetTimeRSlew();
			//cout<<"Cal*F3_LTRaw="<<0.0156251*F3_LTRaw<<"  F3_LTSlew="<<F3_LTSlew<<endl;
			if(QRaw[0]!=-9999) QCal[0] = QRaw[0];
			if(QRaw[1]!=-9999) QCal[1] = QRaw[1];

		}
                void getDataContainer(TArtCalibPlastic *calibPlastic){
			PlasticF3 = calibPlastic->FindPlastic((char*)"F3pl");
			PlasticF7 = calibPlastic->FindPlastic((char*)"F7pl");
			PlasticSBT1 = calibPlastic->FindPlastic((char*)"F13pl-1");
			PlasticSBT2 = calibPlastic->FindPlastic((char*)"F13pl-2");
			PlasticSBV = calibPlastic->FindPlastic((char*)"SBV");

		}

	public:
		PLARead(){};
		~PLARead(){};

		void read(TArtCalibPlastic *calibPlastic){
			init();
			getDataContainer(calibPlastic);
			plasticRead(PlasticF3,F3TRaw,F3QRaw,F3TCal,F3QCal);
			plasticRead(PlasticF7,F7TRaw,F7QRaw,F7TCal,F7QCal);
			plasticRead(PlasticSBT1,SBT1TRaw,SBT1QRaw,SBT1TCal,SBT1QCal);
			plasticRead(PlasticSBT2,SBT2TRaw,SBT2QRaw,SBT2TCal,SBT2QCal);
			plasticRead(PlasticSBV,SBVTRaw,SBVQRaw,SBVTCal,SBVQCal);
	
		}
		void setBranch(TTree *tree){

			tree->Branch("F3TRaw",F3TRaw,"F3TRaw[2]/I");
			tree->Branch("F3QRaw",F3QRaw,"F3QRaw[2]/I");
			tree->Branch("F3TCal",F3TCal,"F3TCal[2]/D");
			tree->Branch("F3QCal",F3QCal,"F3QCal[2]/D");
			tree->Branch("F7TRaw",F7TRaw,"F7TRaw[2]/I");
			tree->Branch("F7QRaw",F7QRaw,"F7QRaw[2]/I");
			tree->Branch("F7TCal",F7TCal,"F7TCal[2]/D");
			tree->Branch("F7QCal",F7QCal,"F7QCal[2]/D");
			tree->Branch("SBT1TRaw",SBT1TRaw,"SBT1TRaw[2]/I");
			tree->Branch("SBT1QRaw",SBT1QRaw,"SBT1QRaw[2]/I");
			tree->Branch("SBT1TCal",SBT1TCal,"SBT1TCal[2]/D");
			tree->Branch("SBT1QCal",SBT1QCal,"SBT1QCal[2]/D");
			tree->Branch("SBT2TRaw",SBT2TRaw,"SBT2TRaw[2]/I");
			tree->Branch("SBT2QRaw",SBT2QRaw,"SBT2QRaw[2]/I");
			tree->Branch("SBT2TCal",SBT2TCal,"SBT2TCal[2]/D");
			tree->Branch("SBT2QCal",SBT2QCal,"SBT2QCal[2]/D");
			tree->Branch("SBVTRaw",SBVTRaw,"SBVTRaw[2]/I");
			tree->Branch("SBVQRaw",SBVQRaw,"SBVQRaw[2]/I");
			tree->Branch("SBVTCal",SBVTCal,"SBVTCal[2]/D");
			tree->Branch("SBVQCal",SBVQCal,"SBVQCal[2]/D");
		}

		void init(){


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
		void print(){
			printF3();
		}
		void printF3(){
			cout<<"F3TRaw[0] = "<<F3TRaw[0]<<" F3TRaw[1]= "<< F3TRaw[1]<<endl;
			cout<<"F3TCal[0] = "<<F3TCal[0]<<" F3TCal[1]= "<< F3TCal[1]<<endl;
			cout<<"F3QRaw[0] = "<<F3QRaw[0]<<" F3QRaw[1]= "<< F3QRaw[1]<<endl;
			cout<<"F3QCal[0] = "<<F3QCal[0]<<" F3QCal[1]= "<< F3QCal[1]<<endl;
		}
		void printF7(){
			cout<<"F7TRaw[0] = "<<F7TRaw[0]<<" F7TRaw[1]= "<< F7TRaw[1]<<endl;
			cout<<"F7TCal[0] = "<<F7TCal[0]<<" F7TCal[1]= "<< F7TCal[1]<<endl;
			cout<<"F7QRaw[0] = "<<F7QRaw[0]<<" F7QRaw[1]= "<< F7QRaw[1]<<endl;
			cout<<"F7QCal[0] = "<<F7QCal[0]<<" F7QCal[1]= "<< F7QCal[1]<<endl;
		}

		void printSBT1(){
			cout<<"SBT1TRaw[0] = "<<SBT1TRaw[0]<<" SBT1TRaw[1]= "<< SBT1TRaw[1]<<endl;
			cout<<"SBT1TCal[0] = "<<SBT1TCal[0]<<" SBT1TCal[1]= "<< SBT1TCal[1]<<endl;
			cout<<"SBT1QRaw[0] = "<<SBT1QRaw[0]<<" SBT1QRaw[1]= "<< SBT1QRaw[1]<<endl;
			cout<<"SBT1QCal[0] = "<<SBT1QCal[0]<<" SBT1QCal[1]= "<< SBT1QCal[1]<<endl;
		}
		void printSBT2(){
			cout<<"SBT2TRaw[0] = "<<SBT2TRaw[0]<<" SBT2TRaw[1]= "<< SBT2TRaw[1]<<endl;
			cout<<"SBT2TCal[0] = "<<SBT2TCal[0]<<" SBT2TCal[1]= "<< SBT2TCal[1]<<endl;
			cout<<"SBT2QRaw[0] = "<<SBT2QRaw[0]<<" SBT2QRaw[1]= "<< SBT2QRaw[1]<<endl;
			cout<<"SBT2QCal[0] = "<<SBT2QCal[0]<<" SBT2QCal[1]= "<< SBT2QCal[1]<<endl;
		}
		void printSBV(){
			cout<<"SBVTRaw[0] = "<<SBVTRaw[0]<<" SBVTRaw[1]= "<< SBVTRaw[1]<<endl;
			cout<<"SBVTCal[0] = "<<SBVTCal[0]<<" SBVTCal[1]= "<< SBVTCal[1]<<endl;
			cout<<"SBVQRaw[0] = "<<SBVQRaw[0]<<" SBVQRaw[1]= "<< SBVQRaw[1]<<endl;
			cout<<"SBVQCal[0] = "<<SBVQCal[0]<<" SBVQCal[1]= "<< SBVQCal[1]<<endl;
		}

		double getF3TCal(int id){
			return F3TCal[id];
		}
		double getF3QCal(int id){
			return F3QCal[id];
		}
		double getF7TCal(int id){
			return F7TCal[id];
		}
		double getF7QCal(int id){
			return F7QCal[id];
		}
		double getSBT1TCal(int id){
			return SBT1TCal[id];
		}
		double getSBT1QCal(int id){
			return SBT1QCal[id];
		}
		double getSBT2TCal(int id){
			return SBT2TCal[id];
		}
		double getSBT2QCal(int id){
			return SBT2QCal[id];
		}
		double getSBVTCal(int id){
			return SBVTCal[id];
		}
		double getSBVQCal(int id){
			return SBVQCal[id];
		}

};
