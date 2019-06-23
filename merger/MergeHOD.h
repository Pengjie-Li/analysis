class MergeHOD:public Convert{
	private:
		Int_t           hodID[40];
		Int_t           hodTRaw[2][40];
		Int_t           hodQRaw[2][40];
		Double_t        hodTCal[2][40];
		Double_t        hodQCal[2][40];
		Double_t        hodBarQCal[40];


	public:


		void setBranch(){
			// Set branch addresses.
			inputTree->SetBranchAddress("hodID",hodID);
			inputTree->SetBranchAddress("hodTRaw",hodTRaw);
			inputTree->SetBranchAddress("hodQRaw",hodQRaw);
			inputTree->SetBranchAddress("hodTCal",hodTCal);
			inputTree->SetBranchAddress("hodQCal",hodQCal);
			inputTree->SetBranchAddress("hodBarQCal",hodBarQCal);

		}
		void setOutputBranch(TTree *tree){

			// Set branch addresses.
			tree->Branch("hodTRaw",hodTRaw,"hodTRaw[2][40]/I");
			tree->Branch("hodQRaw",hodQRaw,"hodQRaw[2][40]/I");

			tree->Branch("hodTCal",hodTCal,"hodTCal[2][40]/D");
			tree->Branch("hodQCal",hodQCal,"hodQCal[2][40]/D");
			tree->Branch("hodBarQCal",hodBarQCal,"hodBarQCal[40]/D");

		}

		MergeHOD(){}
		MergeHOD(int run){
			env = new TEnv("configMerger.prm");
			detector = "HOD";
			treeName = "CalTreeHOD";
			runNumber = run;
		}

		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (HOD):\t" << inputTree->GetEntries() << endl;
		}
		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}

};

