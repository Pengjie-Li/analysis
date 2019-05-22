class MergeTELE:public Convert{
	private:
	public:
		/*
		 * DSSD Class
		 * isLeftRight
		 * frontStrip,backStrip 1,2,3 ...
		 * nHitFront,nHitBack // With Threshold
		 * Etot
		 * Time
		 */
		/*
		 * Strip Class
		 * isFrontBack
		 * stripId
		 * raw ADC
		 * raw TDC
		 * Energy
		 * Time
		 */
		/*
		 * Pixel Class
		 * 3D Postion(X,Y,Z)
		 * frontEnergy, backEnergy
		 */
		//Declaration of leaves types
		vector<int>     *Silicons_ID;
		vector<double>  *Silicons_Time;
		vector<double>  *Silicons_Energy;
		Int_t           Silicons_Multiplicity;

		vector<double>  *SiLF_rawADC;
		vector<double>  *SiLB_rawADC;
		vector<double>  *SiRF_rawADC;
		vector<double>  *SiRB_rawADC;
		vector<double>  *SiLF_rawTDC;
		vector<double>  *SiLB_rawTDC;
		vector<double>  *SiRF_rawTDC;
		vector<double>  *SiRB_rawTDC;

		Double_t        CsILL_rawADC;
		Double_t        CsILRT_rawADC;
		Double_t        CsILRB_rawADC;
		Double_t        CsIRLT_rawADC;
		Double_t        CsIRLB_rawADC;
		Double_t        CsIRRT_rawADC;
		Double_t        CsIRRB_rawADC;
		Double_t        CsILL_rawTDC;
		Double_t        CsILRT_rawTDC;
		Double_t        CsILRB_rawTDC;
		Double_t        CsIRLT_rawTDC;
		Double_t        CsIRLB_rawTDC;
		Double_t        CsIRRT_rawTDC;
		Double_t        CsIRRB_rawTDC;

		void setBranch(){
			// Set branch addresses.
			//Declaration of leaves types
			Silicons_ID	= 0;
			Silicons_Time	= 0;
			Silicons_Energy	= 0;

			SiLF_rawADC = 0;
			SiLB_rawADC = 0;
			SiRF_rawADC = 0;
			SiRB_rawADC = 0;
			SiLF_rawTDC = 0;
			SiLB_rawTDC = 0;
			SiRF_rawTDC = 0;
			SiRB_rawTDC = 0;


			inputTree->SetBranchAddress("Silicons_ID",&Silicons_ID);
			inputTree->SetBranchAddress("Silicons_Time",&Silicons_Time);
			inputTree->SetBranchAddress("Silicons_Energy",&Silicons_Energy);
			inputTree->SetBranchAddress("Silicons_Multiplicity",&Silicons_Multiplicity);
			inputTree->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
			inputTree->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
			inputTree->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
			inputTree->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);
			inputTree->SetBranchAddress("SiLF_rawTDC",&SiLF_rawTDC);
			inputTree->SetBranchAddress("SiLB_rawTDC",&SiLB_rawTDC);
			inputTree->SetBranchAddress("SiRF_rawTDC",&SiRF_rawTDC);
			inputTree->SetBranchAddress("SiRB_rawTDC",&SiRB_rawTDC);
			inputTree->SetBranchAddress("CsILL_rawADC",&CsILL_rawADC);
			inputTree->SetBranchAddress("CsILRT_rawADC",&CsILRT_rawADC);
			inputTree->SetBranchAddress("CsILRB_rawADC",&CsILRB_rawADC);
			inputTree->SetBranchAddress("CsIRLT_rawADC",&CsIRLT_rawADC);
			inputTree->SetBranchAddress("CsIRLB_rawADC",&CsIRLB_rawADC);
			inputTree->SetBranchAddress("CsIRRT_rawADC",&CsIRRT_rawADC);
			inputTree->SetBranchAddress("CsIRRB_rawADC",&CsIRRB_rawADC);
			inputTree->SetBranchAddress("CsILL_rawTDC",&CsILL_rawTDC);
			inputTree->SetBranchAddress("CsILRT_rawTDC",&CsILRT_rawTDC);
			inputTree->SetBranchAddress("CsILRB_rawTDC",&CsILRB_rawTDC);
			inputTree->SetBranchAddress("CsIRLT_rawTDC",&CsIRLT_rawTDC);
			inputTree->SetBranchAddress("CsIRLB_rawTDC",&CsIRLB_rawTDC);
			inputTree->SetBranchAddress("CsIRRT_rawTDC",&CsIRRT_rawTDC);
			inputTree->SetBranchAddress("CsIRRB_rawTDC",&CsIRRB_rawTDC);

		}
		void setOutputBranch(TTree *tree){

			tree->Branch("Silicons_ID",&Silicons_ID);
			tree->Branch("Silicons_Time",&Silicons_Time);
			tree->Branch("Silicons_Energy",&Silicons_Energy);
			tree->Branch("SiLF_rawTDC",&SiLF_rawTDC);
			tree->Branch("SiLB_rawTDC",&SiLB_rawTDC);
			tree->Branch("SiRF_rawTDC",&SiRF_rawTDC);
			tree->Branch("SiRB_rawTDC",&SiRB_rawTDC);
			tree->Branch("CsILL_ADC",&CsILL_rawADC);
			tree->Branch("CsILRT_ADC",&CsILRT_rawADC);
			tree->Branch("CsILRB_ADC",&CsILRB_rawADC);
			tree->Branch("CsIRLT_ADC",&CsIRLT_rawADC);
			tree->Branch("CsIRLB_ADC",&CsIRLB_rawADC);
			tree->Branch("CsIRRT_ADC",&CsIRRT_rawADC);
			tree->Branch("CsIRRB_ADC",&CsIRRB_rawADC);
			tree->Branch("CsILL_rawTDC",&CsILL_rawTDC);
			tree->Branch("CsILRT_rawTDC",&CsILRT_rawTDC);
			tree->Branch("CsILRB_rawTDC",&CsILRB_rawTDC);
			tree->Branch("CsIRLT_rawTDC",&CsIRLT_rawTDC);
			tree->Branch("CsIRLB_rawTDC",&CsIRLB_rawTDC);
			tree->Branch("CsIRRT_rawTDC",&CsIRRT_rawTDC);
			tree->Branch("CsIRRB_rawTDC",&CsIRRB_rawTDC);


		}


		MergeTELE(){}
		MergeTELE(int run){
			env = new TEnv("configMerger.prm");
			detector = "TELE";
			treeName = "CalTreeTELE";
			runNumber = run;
		}

		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (TELE):\t" << inputTree->GetEntries() << endl;
		}
		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}
		Int_t getMultiplicity(int side){
			return 1;
		}
		double getSiliconRawADC(int side, int id){
			switch(side){
				case 0: 
					return (*SiLF_rawADC)[id];
				case 1: 
					return (*SiLB_rawADC)[id];
				case 2: 
					return (*SiRF_rawADC)[id];
				case 3: 
					return (*SiRB_rawADC)[id];

			}
			return 0;

		}
		Double_t getCsILLRawADC(){
			return CsILL_rawADC;
		}
		Double_t getCsILRTRawADC(){
			return CsILRT_rawADC;
		}
		Double_t getCsILRBRawADC(){
			return CsILRB_rawADC;
		}
		Double_t getCsIRLTRawADC(){
			return CsIRLT_rawADC;
		}
		Double_t getCsIRLBRawADC(){
			return CsIRLB_rawADC;
		}
		Double_t getCsIRRTRawADC(){
			return CsIRRT_rawADC;
		}


		Double_t getCsIRRBRawADC(){
			return CsIRRB_rawADC;
		}






};

