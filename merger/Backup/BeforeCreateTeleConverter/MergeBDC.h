class MergeBDC:public Convert{
	private:
	public:

		//Declaration of leaves types
		Int_t           RunNumber;
		Long64_t        EventNumber;
		Int_t           BDC1_nhits;
		vector<double>  *BDC1_TDC;
		vector<double>  *BDC1_layerid;
		vector<double>  *BDC1_wireid;
		vector<int>     *BDC1_layer_hits;
		Int_t           BDC1_nlayerx;
		Int_t           BDC1_nlayery;
		vector<double>  *BDC1_Track_dl;
		vector<double>  *BDC1_Track_XY;
		vector<double>  *BDC1_Track_Z;
		vector<double>  *BDC1_Track_dXY;
		Double_t        BDC1_X;
		Double_t        BDC1_Y;
		Double_t        BDC1_ThetaX;
		Double_t        BDC1_ThetaY;
		Int_t           BDC2_nhits;
		vector<double>  *BDC2_TDC;
		vector<double>  *BDC2_layerid;
		vector<double>  *BDC2_wireid;
		vector<int>     *BDC2_layer_hits;
		Int_t           BDC2_nlayerx;
		Int_t           BDC2_nlayery;
		vector<double>  *BDC2_Track_dl;
		vector<double>  *BDC2_Track_XY;
		vector<double>  *BDC2_Track_Z;
		vector<double>  *BDC2_Track_dXY;
		Double_t        BDC2_X;
		Double_t        BDC2_Y;
		Double_t        BDC2_ThetaX;
		Double_t        BDC2_ThetaY;


		void setBranch(){

			 BDC1_TDC       = 0;  
			 BDC1_layerid   = 0;
			 BDC1_wireid    = 0;
			 BDC1_layer_hits= 0;

			 BDC1_Track_dl  = 0;
			 BDC1_Track_XY  = 0;
			 BDC1_Track_Z   = 0;
			 BDC1_Track_dXY = 0;


			 BDC2_TDC       = 0;  
			 BDC2_layerid   = 0;
			 BDC2_wireid    = 0;
			 BDC2_layer_hits= 0;

			 BDC2_Track_dl  = 0;
			 BDC2_Track_XY  = 0;
			 BDC2_Track_Z   = 0;
			 BDC2_Track_dXY = 0;


			// Set branch addresses.
			inputTree->SetBranchAddress("RunNumber",&RunNumber);
			inputTree->SetBranchAddress("EventNumber",&EventNumber);
			inputTree->SetBranchAddress("BDC1_nhits",&BDC1_nhits);
			inputTree->SetBranchAddress("BDC1_TDC",&BDC1_TDC);
			inputTree->SetBranchAddress("BDC1_layerid",&BDC1_layerid);
			inputTree->SetBranchAddress("BDC1_wireid",&BDC1_wireid);
			inputTree->SetBranchAddress("BDC1_layer_hits",&BDC1_layer_hits);
			inputTree->SetBranchAddress("BDC1_nlayerx",&BDC1_nlayerx);
			inputTree->SetBranchAddress("BDC1_nlayery",&BDC1_nlayery);
			inputTree->SetBranchAddress("BDC1_Track_dl",&BDC1_Track_dl);
			inputTree->SetBranchAddress("BDC1_Track_XY",&BDC1_Track_XY);
			inputTree->SetBranchAddress("BDC1_Track_Z",&BDC1_Track_Z);
			inputTree->SetBranchAddress("BDC1_Track_dXY",&BDC1_Track_dXY);
			inputTree->SetBranchAddress("BDC1_X",&BDC1_X);
			inputTree->SetBranchAddress("BDC1_Y",&BDC1_Y);
			inputTree->SetBranchAddress("BDC1_ThetaX",&BDC1_ThetaX);
			inputTree->SetBranchAddress("BDC1_ThetaY",&BDC1_ThetaY);
			inputTree->SetBranchAddress("BDC2_nhits",&BDC2_nhits);
			inputTree->SetBranchAddress("BDC2_TDC",&BDC2_TDC);
			inputTree->SetBranchAddress("BDC2_layerid",&BDC2_layerid);
			inputTree->SetBranchAddress("BDC2_wireid",&BDC2_wireid);
			inputTree->SetBranchAddress("BDC2_layer_hits",&BDC2_layer_hits);
			inputTree->SetBranchAddress("BDC2_nlayerx",&BDC2_nlayerx);
			inputTree->SetBranchAddress("BDC2_nlayery",&BDC2_nlayery);
			inputTree->SetBranchAddress("BDC2_Track_dl",&BDC2_Track_dl);
			inputTree->SetBranchAddress("BDC2_Track_XY",&BDC2_Track_XY);
			inputTree->SetBranchAddress("BDC2_Track_Z",&BDC2_Track_Z);
			inputTree->SetBranchAddress("BDC2_Track_dXY",&BDC2_Track_dXY);
			inputTree->SetBranchAddress("BDC2_X",&BDC2_X);
			inputTree->SetBranchAddress("BDC2_Y",&BDC2_Y);
			inputTree->SetBranchAddress("BDC2_ThetaX",&BDC2_ThetaX);
			inputTree->SetBranchAddress("BDC2_ThetaY",&BDC2_ThetaY);


		}
		void setOutputBranch(TTree *tree){
			// Set branch addresses.
			tree->Branch("BDC1_nhits",&BDC1_nhits);
			tree->Branch("BDC1_TDC",&BDC1_TDC);
			tree->Branch("BDC1_layerid",&BDC1_layerid);
			tree->Branch("BDC1_wireid",&BDC1_wireid);
			tree->Branch("BDC1_layer_hits",&BDC1_layer_hits);
			tree->Branch("BDC1_nlayerx",&BDC1_nlayerx);
			tree->Branch("BDC1_nlayery",&BDC1_nlayery);
			tree->Branch("BDC1_Track_dl",&BDC1_Track_dl);
			tree->Branch("BDC1_Track_XY",&BDC1_Track_XY);
			tree->Branch("BDC1_Track_Z",&BDC1_Track_Z);
			tree->Branch("BDC1_Track_dXY",&BDC1_Track_dXY);
			tree->Branch("BDC1_X",&BDC1_X);
			tree->Branch("BDC1_Y",&BDC1_Y);
			tree->Branch("BDC1_ThetaX",&BDC1_ThetaX);
			tree->Branch("BDC1_ThetaY",&BDC1_ThetaY);

			tree->Branch("BDC2_nhits",&BDC2_nhits);
			tree->Branch("BDC2_TDC",&BDC2_TDC);
			tree->Branch("BDC2_layerid",&BDC2_layerid);
			tree->Branch("BDC2_wireid",&BDC2_wireid);
			tree->Branch("BDC2_layer_hits",&BDC2_layer_hits);
			tree->Branch("BDC2_nlayerx",&BDC2_nlayerx);
			tree->Branch("BDC2_nlayery",&BDC2_nlayery);
			tree->Branch("BDC2_Track_dl",&BDC2_Track_dl);
			tree->Branch("BDC2_Track_XY",&BDC2_Track_XY);
			tree->Branch("BDC2_Track_Z",&BDC2_Track_Z);
			tree->Branch("BDC2_Track_dXY",&BDC2_Track_dXY);
			tree->Branch("BDC2_X",&BDC2_X);
			tree->Branch("BDC2_Y",&BDC2_Y);
			tree->Branch("BDC2_ThetaX",&BDC2_ThetaX);
			tree->Branch("BDC2_ThetaY",&BDC2_ThetaY);

		}

		MergeBDC(){}
		MergeBDC(int run){
			env = new TEnv("configMerger.prm");
			detector = "BDC";
			treeName = "CalTreeBDC";
			runNumber = run;
		}

		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (BDC):\t" << inputTree->GetEntries() << endl;
		}
		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}
		Double_t getBDC1X(){
			return BDC1_X;
		}
		Double_t getBDC1Y(){
			return BDC1_Y;
		}
		Double_t getBDC2X(){
			return BDC2_X;
		}
		Double_t getBDC2Y(){
			return BDC2_Y;
		}

};
