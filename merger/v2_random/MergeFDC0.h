class MergeFDC0:public Convert{
	private:
	public:

		//Declaration of leaves types
		Int_t           FDC0_nhits;
		vector<double>  *FDC0_TDC;
		vector<double>  *FDC0_layerid;
		vector<double>  *FDC0_wireid;
		vector<int>     *FDC0_layer_hits;
		Int_t           FDC0_nlayerx;
		Int_t           FDC0_nlayery;
		vector<double>  *FDC0_Track_dl;
		vector<double>  *FDC0_Track_XY;
		vector<double>  *FDC0_Track_Z;
		vector<double>  *FDC0_Track_dXY;
		Double_t        FDC0_X;
		Double_t        FDC0_Y;
		Double_t        FDC0_ThetaX;
		Double_t        FDC0_ThetaY;
		void setBranch(){
			FDC0_TDC	=0;
			FDC0_layerid	=0;
			FDC0_wireid	=0;
			FDC0_layer_hits	=0;

			FDC0_Track_dl   =0;
			FDC0_Track_XY   =0;
			FDC0_Track_Z    =0;
			FDC0_Track_dXY  =0;

			// Set branch addresses.
			inputTree->SetBranchAddress("FDC0_nhits",&FDC0_nhits);
			inputTree->SetBranchAddress("FDC0_TDC",&FDC0_TDC);
			inputTree->SetBranchAddress("FDC0_layerid",&FDC0_layerid);
			inputTree->SetBranchAddress("FDC0_wireid",&FDC0_wireid);
			inputTree->SetBranchAddress("FDC0_layer_hits",&FDC0_layer_hits);
			inputTree->SetBranchAddress("FDC0_nlayerx",&FDC0_nlayerx);
			inputTree->SetBranchAddress("FDC0_nlayery",&FDC0_nlayery);
			inputTree->SetBranchAddress("FDC0_Track_dl",&FDC0_Track_dl);
			inputTree->SetBranchAddress("FDC0_Track_XY",&FDC0_Track_XY);
			inputTree->SetBranchAddress("FDC0_Track_Z",&FDC0_Track_Z);
			inputTree->SetBranchAddress("FDC0_Track_dXY",&FDC0_Track_dXY);
			inputTree->SetBranchAddress("FDC0_X",&FDC0_X);
			inputTree->SetBranchAddress("FDC0_Y",&FDC0_Y);
			inputTree->SetBranchAddress("FDC0_ThetaX",&FDC0_ThetaX);
			inputTree->SetBranchAddress("FDC0_ThetaY",&FDC0_ThetaY);
		}
		void setOutputBranch(TTree *tree){

			// Set branch addresses.
			tree->Branch("FDC0_nhits",&FDC0_nhits);
			tree->Branch("FDC0_TDC",&FDC0_TDC);
			tree->Branch("FDC0_layerid",&FDC0_layerid);
			tree->Branch("FDC0_wireid",&FDC0_wireid);
			tree->Branch("FDC0_layer_hits",&FDC0_layer_hits);
			tree->Branch("FDC0_nlayerx",&FDC0_nlayerx);
			tree->Branch("FDC0_nlayery",&FDC0_nlayery);
			tree->Branch("FDC0_Track_dl",&FDC0_Track_dl);
			tree->Branch("FDC0_Track_XY",&FDC0_Track_XY);
			tree->Branch("FDC0_Track_Z",&FDC0_Track_Z);
			tree->Branch("FDC0_Track_dXY",&FDC0_Track_dXY);
			tree->Branch("FDC0_X",&FDC0_X);
			tree->Branch("FDC0_Y",&FDC0_Y);
			tree->Branch("FDC0_ThetaX",&FDC0_ThetaX);
			tree->Branch("FDC0_ThetaY",&FDC0_ThetaY);
		}

		MergeFDC0(){}
		MergeFDC0(int run){
			env = new TEnv("configMerger.prm");
			detector = "FDC0";
			treeName = "CalTreeFDC";
			runNumber = run;
		}

		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (FDC0):\t" << inputTree->GetEntries() << endl;
		}
		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}
		double getFDC0X(){
			return FDC0_X;
		}
		double getFDC0Y(){
			return FDC0_Y;
		}
		void print(){
			cout<<"FDC0_X = "<<FDC0_X<<"	FDC0_Y = "<<FDC0_Y<<endl;
		}

};
