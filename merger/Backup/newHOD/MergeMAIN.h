class MergeMAIN:public Convert{
	private :
	public :
		Int_t           RunNumber;
		Long64_t        EventNumber;
	
		Int_t CoincidenceTrigger;

		void setBranch(){
			inputTree->SetBranchAddress("RunNumber",&RunNumber);
			inputTree->SetBranchAddress("EventNumber",&EventNumber);
			inputTree->SetBranchAddress("CoincidenceTrigger",&CoincidenceTrigger);
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("RunNumber",&RunNumber,"RunNumber/I");
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("CoincidenceTrigger",&CoincidenceTrigger);
		}
		MergeMAIN(){}
		MergeMAIN(int run){
			env = new TEnv("configMerger.prm");
			detector = "MAIN";
			treeName = "CalTree";
			runNumber = run;
			//cout<<"Main run ="<<run<<endl;
		}
		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (MAIN):\t" << inputTree->GetEntries() << endl;
		}


		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		void init(){
		}
		Int_t getCoincidenceTrigger(){
			return CoincidenceTrigger;
		}
	
};
