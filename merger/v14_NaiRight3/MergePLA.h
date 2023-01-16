/**
 * MergePLA Provides:
 * 1 TRaw QRaw
 * 2 TCal
 * 3 TCorrection 
 * 4 Detector Q and T
 */
class MergePLA:public Convert{
	private:
	public:
		//Declaration of leaves types
		Int_t           F3TRaw[2];
		Int_t           F3QRaw[2];
		Double_t        F3TCal[2];
		Double_t        F3QCal[2];
		Double_t        F3T;
		Double_t        F3Q;
		Int_t           F7TRaw[2];
		Int_t           F7QRaw[2];
		Double_t        F7TCal[2];
		Double_t        F7QCal[2];
		Double_t        F7T;
		Double_t        F7Q;
		Int_t           SBT1TRaw[2];
		Int_t           SBT1QRaw[2];
		Double_t        SBT1TCal[2];
		Double_t        SBT1QCal[2];
		Double_t        SBT1T;
		Double_t        SBT1Q;
		Int_t           SBT2TRaw[2];
		Int_t           SBT2QRaw[2];
		Double_t        SBT2TCal[2];
		Double_t        SBT2QCal[2];
		Double_t        SBT2T;
		Double_t        SBT2Q;
		Double_t        F13T;
		Double_t        F13Q;
		Int_t           SBVTRaw[2];
		Int_t           SBVQRaw[2];
		Double_t        SBVTCal[2];
		Double_t        SBVQCal[2];
		Double_t        SBVT;
		Double_t        SBVQ;


		void setBranch(){


			// Set branch addresses.
			inputTree->SetBranchAddress("F3TRaw",F3TRaw);
			inputTree->SetBranchAddress("F3QRaw",F3QRaw);
			inputTree->SetBranchAddress("F3TCal",F3TCal);
			inputTree->SetBranchAddress("F3QCal",F3QCal);
			inputTree->SetBranchAddress("F3T",&F3T);
			inputTree->SetBranchAddress("F3Q",&F3Q);
			inputTree->SetBranchAddress("F7TRaw",F7TRaw);
			inputTree->SetBranchAddress("F7QRaw",F7QRaw);
			inputTree->SetBranchAddress("F7TCal",F7TCal);
			inputTree->SetBranchAddress("F7QCal",F7QCal);
			inputTree->SetBranchAddress("F7T",&F7T);
			inputTree->SetBranchAddress("F7Q",&F7Q);
			inputTree->SetBranchAddress("SBT1TRaw",SBT1TRaw);
			inputTree->SetBranchAddress("SBT1QRaw",SBT1QRaw);
			inputTree->SetBranchAddress("SBT1TCal",SBT1TCal);
			inputTree->SetBranchAddress("SBT1QCal",SBT1QCal);
			inputTree->SetBranchAddress("SBT1T",&SBT1T);
			inputTree->SetBranchAddress("SBT1Q",&SBT1Q);
			inputTree->SetBranchAddress("SBT2TRaw",SBT2TRaw);
			inputTree->SetBranchAddress("SBT2QRaw",SBT2QRaw);
			inputTree->SetBranchAddress("SBT2TCal",SBT2TCal);
			inputTree->SetBranchAddress("SBT2QCal",SBT2QCal);
			inputTree->SetBranchAddress("SBT2T",&SBT2T);
			inputTree->SetBranchAddress("SBT2Q",&SBT2Q);
			inputTree->SetBranchAddress("F13T",&F13T);
			inputTree->SetBranchAddress("F13Q",&F13Q);
			inputTree->SetBranchAddress("SBVTRaw",SBVTRaw);
			inputTree->SetBranchAddress("SBVQRaw",SBVQRaw);
			inputTree->SetBranchAddress("SBVTCal",SBVTCal);
			inputTree->SetBranchAddress("SBVQCal",SBVQCal);
			inputTree->SetBranchAddress("SBVT",&SBVT);
			inputTree->SetBranchAddress("SBVQ",&SBVQ);


		}

		void setOutputBranch(TTree *tree){

			// Set branch addresses.
			tree->Branch("F3TRaw",F3TRaw,"F3TRaw[2]/I");
			tree->Branch("F3QRaw",F3QRaw,"F3QRaw[2]/I");
			tree->Branch("F3TCal",F3TCal,"F3TCal[2]/D");
			tree->Branch("F3QCal",F3QCal,"F3QCal[2]/D");
			tree->Branch("F3T",&F3T);
			tree->Branch("F3Q",&F3Q);
			tree->Branch("F7TRaw",F7TRaw,"F7TRaw[2]/I");
			tree->Branch("F7QRaw",F7QRaw,"F7QRaw[2]/I");
			tree->Branch("F7TCal",F7TCal,"F7TCal[2]/D");
			tree->Branch("F7QCal",F7QCal,"F7QCal[2]/D");
			tree->Branch("F7T",&F7T);
			tree->Branch("F7Q",&F7Q);
			tree->Branch("SBT1TRaw",SBT1TRaw,"SBT1TRaw[2]/I");
			tree->Branch("SBT1QRaw",SBT1QRaw,"SBT1QRaw[2]/I");
			tree->Branch("SBT1TCal",SBT1TCal,"SBT1TCal[2]/D");
			tree->Branch("SBT1QCal",SBT1QCal,"SBT1QCal[2]/D");
			tree->Branch("SBT1T",&SBT1T);
			tree->Branch("SBT1Q",&SBT1Q);
			tree->Branch("SBT2TRaw",SBT2TRaw,"SBT2TRaw[2]/I");
			tree->Branch("SBT2QRaw",SBT2QRaw,"SBT2QRaw[2]/I");
			tree->Branch("SBT2TCal",SBT2TCal,"SBT2TCal[2]/D");
			tree->Branch("SBT2QCal",SBT2QCal,"SBT2QCal[2]/D");
			tree->Branch("SBT2T",&SBT2T);
			tree->Branch("SBT2Q",&SBT2Q);
			tree->Branch("F13T",&F13T);
			tree->Branch("F13Q",&F13Q);
			tree->Branch("SBVTRaw",SBVTRaw,"SBVTRaw[2]/I");
			tree->Branch("SBVQRaw",SBVQRaw,"SBVQRaw[2]/I");
			tree->Branch("SBVTCal",SBVTCal,"SBVTCal[2]/D");
			tree->Branch("SBVQCal",SBVQCal,"SBVQCal[2]/D");
			tree->Branch("SBVT",&SBVT);
			tree->Branch("SBVQ",&SBVQ);


		}

		MergePLA(){}
		MergePLA(int run){
			detector = "PLA";
			treeName = "CalTreePLA";
			runNumber = run;
		}
		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (PLA):\t" << inputTree->GetEntries() << endl;
		}
		void print(){
			cout<<"PLA Raw Data:"<<endl;
			printF3();
			printF7();
			printF13();
			printSBV();
		}
		void printF3(){
			cout<<"F3T :"<<F3TRaw[0]<<":"<<F3TRaw[1]<<":"<<F3TCal[0]<<":"<<F3TCal[1]<<":"<<F3T<<endl;
			cout<<"F3Q :"<<F3QRaw[0]<<":"<<F3QRaw[1]<<":"<<F3QCal[0]<<":"<<F3QCal[1]<<":"<<F3Q<<endl;
		}
		void printF7(){
			cout<<"F7T :"<<F7TRaw[0]<<":"<<F7TRaw[1]<<":"<<F7TCal[0]<<":"<<F7TCal[1]<<":"<<F7T<<endl;
			cout<<"F7Q :"<<F7QRaw[0]<<":"<<F7QRaw[1]<<":"<<F7QCal[0]<<":"<<F7QCal[1]<<":"<<F7Q<<endl;
		}
		void printF13(){
			printSBT1();
			printSBT2();
			cout<<"F13TQ:"<<F13T<<":"<<F13Q<<endl;	
		}

		void printSBT1(){
			cout<<"SBT1T :"<<SBT1TRaw[0]<<":"<<SBT1TRaw[1]<<":"<<SBT1TCal[0]<<":"<<SBT1TCal[1]<<":"<<SBT1T<<endl;
			cout<<"SBT1Q :"<<SBT1QRaw[0]<<":"<<SBT1QRaw[1]<<":"<<SBT1QCal[0]<<":"<<SBT1QCal[1]<<":"<<SBT1Q<<endl;

		}
		void printSBT2(){
			cout<<"SBT2T :"<<SBT2TRaw[0]<<":"<<SBT2TRaw[1]<<":"<<SBT2TCal[0]<<":"<<SBT2TCal[1]<<":"<<SBT2T<<endl;
			cout<<"SBT2Q :"<<SBT2QRaw[0]<<":"<<SBT2QRaw[1]<<":"<<SBT2QCal[0]<<":"<<SBT2QCal[1]<<":"<<SBT2Q<<endl;

		}
		void printSBV(){
			cout<<"SBVT :"<<SBVTRaw[0]<<":"<<SBVTRaw[1]<<":"<<SBVTCal[0]<<":"<<SBVTCal[1]<<":"<<SBVT<<endl;
			cout<<"SBVQ :"<<SBVQRaw[0]<<":"<<SBVQRaw[1]<<":"<<SBVQCal[0]<<":"<<SBVQCal[1]<<":"<<SBVQ<<endl;

		}








		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}
		Double_t getF3Time(){
			return F3T;
		}
		Double_t getF7Time(){
			return F7T;

		//	double f7t_slew = (0.5*(F7TCal[0]+F7TCal[1])-(-1.06072e-03*F7Q+1.15839e+00/sqrt(sqrt(sqrt(F7Q+92.5)))));
		//	double f7tdiff =  F7TCal[0]-(F7TCal[1]+2.8);
		//	
		//	return f7t_slew+1.1*f7tdiff;
		}
		Double_t getF13Time(){
			return F13T;
		}

};
