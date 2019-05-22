class MergePLA:public Convert{
	private:
	public:
		//Declaration of leaves types
		Double_t        F3_LTRaw;
		Double_t        F3_RTRaw;
		Double_t        F3_LTSlew;
		Double_t        F3_RTSlew;
		Double_t        F3_LQRaw;
		Double_t        F3_RQRaw;
		Double_t        F7_LTRaw;
		Double_t        F7_RTRaw;
		Double_t        F7_LTSlew;
		Double_t        F7_RTSlew;
		Double_t        F7_LQRaw;
		Double_t        F7_RQRaw;
		Double_t        SBT1_LTRaw;
		Double_t        SBT1_RTRaw;
		Double_t        SBT1_LTSlew;
		Double_t        SBT1_RTSlew;
		Double_t        SBT1_LQRaw;
		Double_t        SBT1_RQRaw;
		Double_t        SBT2_LTRaw;
		Double_t        SBT2_RTRaw;
		Double_t        SBT2_LTSlew;
		Double_t        SBT2_RTSlew;
		Double_t        SBT2_LQRaw;
		Double_t        SBT2_RQRaw;
		Double_t        SBV_RQRaw;
		Double_t        SBV_RTRaw;
		Double_t        SBV_RTSlew;
		Double_t        F3_Charge;
		Double_t        F3_Time;
		Double_t        F7_Charge;
		Double_t        F7_Time;
		Double_t        F13_Charge;
		Double_t        F13_Time;
		Double_t        SBV_Charge;
		Double_t        SBV_Time;
		Double_t        SBT1_Charge;
		Double_t        SBT1_Time;
		Double_t        SBT2_Charge;
		Double_t        SBT2_Time;

		void setBranch(){


			// Set branch addresses.
			inputTree->SetBranchAddress("F3_LTRaw",&F3_LTRaw);
			inputTree->SetBranchAddress("F3_RTRaw",&F3_RTRaw);
			inputTree->SetBranchAddress("F3_LTSlew",&F3_LTSlew);
			inputTree->SetBranchAddress("F3_RTSlew",&F3_RTSlew);
			inputTree->SetBranchAddress("F3_LQRaw",&F3_LQRaw);
			inputTree->SetBranchAddress("F3_RQRaw",&F3_RQRaw);
			inputTree->SetBranchAddress("F7_LTRaw",&F7_LTRaw);
			inputTree->SetBranchAddress("F7_RTRaw",&F7_RTRaw);
			inputTree->SetBranchAddress("F7_LTSlew",&F7_LTSlew);
			inputTree->SetBranchAddress("F7_RTSlew",&F7_RTSlew);
			inputTree->SetBranchAddress("F7_LQRaw",&F7_LQRaw);
			inputTree->SetBranchAddress("F7_RQRaw",&F7_RQRaw);
			inputTree->SetBranchAddress("SBT1_LTRaw",&SBT1_LTRaw);
			inputTree->SetBranchAddress("SBT1_RTRaw",&SBT1_RTRaw);
			inputTree->SetBranchAddress("SBT1_LTSlew",&SBT1_LTSlew);
			inputTree->SetBranchAddress("SBT1_RTSlew",&SBT1_RTSlew);
			inputTree->SetBranchAddress("SBT1_LQRaw",&SBT1_LQRaw);
			inputTree->SetBranchAddress("SBT1_RQRaw",&SBT1_RQRaw);
			inputTree->SetBranchAddress("SBT2_LTRaw",&SBT2_LTRaw);
			inputTree->SetBranchAddress("SBT2_RTRaw",&SBT2_RTRaw);
			inputTree->SetBranchAddress("SBT2_LTSlew",&SBT2_LTSlew);
			inputTree->SetBranchAddress("SBT2_RTSlew",&SBT2_RTSlew);
			inputTree->SetBranchAddress("SBT2_LQRaw",&SBT2_LQRaw);
			inputTree->SetBranchAddress("SBT2_RQRaw",&SBT2_RQRaw);
			inputTree->SetBranchAddress("SBV_RQRaw",&SBV_RQRaw);
			inputTree->SetBranchAddress("SBV_RTRaw",&SBV_RTRaw);
			inputTree->SetBranchAddress("SBV_RTSlew",&SBV_RTSlew);
			inputTree->SetBranchAddress("F3_Charge",&F3_Charge);
			inputTree->SetBranchAddress("F3_Time",&F3_Time);
			inputTree->SetBranchAddress("F7_Charge",&F7_Charge);
			inputTree->SetBranchAddress("F7_Time",&F7_Time);
			inputTree->SetBranchAddress("F13_Charge",&F13_Charge);
			inputTree->SetBranchAddress("F13_Time",&F13_Time);
			inputTree->SetBranchAddress("SBV_Charge",&SBV_Charge);
			inputTree->SetBranchAddress("SBV_Time",&SBV_Time);
			inputTree->SetBranchAddress("SBT1_Charge",&SBT1_Charge);
			inputTree->SetBranchAddress("SBT1_Time",&SBT1_Time);
			inputTree->SetBranchAddress("SBT2_Charge",&SBT2_Charge);
			inputTree->SetBranchAddress("SBT2_Time",&SBT2_Time);

		}

		void setOutputBranch(TTree *tree){
			// Set branch addresses.
			tree->Branch("F3_LTRaw",&F3_LTRaw);
			tree->Branch("F3_RTRaw",&F3_RTRaw);
			tree->Branch("F3_LTSlew",&F3_LTSlew);
			tree->Branch("F3_RTSlew",&F3_RTSlew);
			tree->Branch("F3_LQRaw",&F3_LQRaw);
			tree->Branch("F3_RQRaw",&F3_RQRaw);
			tree->Branch("F7_LTRaw",&F7_LTRaw);
			tree->Branch("F7_RTRaw",&F7_RTRaw);
			tree->Branch("F7_LTSlew",&F7_LTSlew);
			tree->Branch("F7_RTSlew",&F7_RTSlew);
			tree->Branch("F7_LQRaw",&F7_LQRaw);
			tree->Branch("F7_RQRaw",&F7_RQRaw);
			tree->Branch("SBT1_LTRaw",&SBT1_LTRaw);
			tree->Branch("SBT1_RTRaw",&SBT1_RTRaw);
			tree->Branch("SBT1_LTSlew",&SBT1_LTSlew);
			tree->Branch("SBT1_RTSlew",&SBT1_RTSlew);
			tree->Branch("SBT1_LQRaw",&SBT1_LQRaw);
			tree->Branch("SBT1_RQRaw",&SBT1_RQRaw);
			tree->Branch("SBT2_LTRaw",&SBT2_LTRaw);
			tree->Branch("SBT2_RTRaw",&SBT2_RTRaw);
			tree->Branch("SBT2_LTSlew",&SBT2_LTSlew);
			tree->Branch("SBT2_RTSlew",&SBT2_RTSlew);
			tree->Branch("SBT2_LQRaw",&SBT2_LQRaw);
			tree->Branch("SBT2_RQRaw",&SBT2_RQRaw);
			tree->Branch("SBV_RQRaw",&SBV_RQRaw);
			tree->Branch("SBV_RTRaw",&SBV_RTRaw);
			tree->Branch("SBV_RTSlew",&SBV_RTSlew);
			tree->Branch("F3_Charge",&F3_Charge);
			tree->Branch("F3_Time",&F3_Time);
			tree->Branch("F7_Charge",&F7_Charge);
			tree->Branch("F7_Time",&F7_Time);
			tree->Branch("F13_Charge",&F13_Charge);
			tree->Branch("F13_Time",&F13_Time);
			tree->Branch("SBV_Charge",&SBV_Charge);
			tree->Branch("SBV_Time",&SBV_Time);
			tree->Branch("SBT1_Charge",&SBT1_Charge);
			tree->Branch("SBT1_Time",&SBT1_Time);
			tree->Branch("SBT2_Charge",&SBT2_Charge);
			tree->Branch("SBT2_Time",&SBT2_Time);


		}

		MergePLA(){}
		MergePLA(int run){
			env = new TEnv("configMerger.prm");
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


		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}
		Double_t getF3Time(){
			return F3_Time;
		}
		Double_t getF7Time(){
			return F7_Time;
		}
		Double_t getF13Time(){
			return F13_Time;
		}


};
