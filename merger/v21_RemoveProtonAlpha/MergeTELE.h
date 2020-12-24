class MergeTELE:public Convert{
	private:
		bool kWriteStatus;
	public:
		//Declaration of leaves types

		Int_t           dssdQRaw[4][32];
		Int_t           dssdTRaw[2][32];
		Double_t        dssdQPed[4][32];

		Int_t           RefTime1;
		Int_t           RefTime2;

		Int_t           csiQRaw[7];
		Int_t           csiTRaw[7];
		Double_t        csiQPed[7];

		Int_t           dssdTHit;
		Int_t           dssdTHitSide[64];
		Int_t           dssdTHitStripId[64];
		Double_t        dssdTHitTCal[64];

		Int_t           csiTHit;
		Int_t           csiTHitId[7];
		Double_t        csiTHitTCal[7];


		void setBranch(){
			// Set branch addresses.
		
			inputTree->SetBranchAddress("dssdQRaw",dssdQRaw);
			inputTree->SetBranchAddress("dssdTRaw",dssdTRaw);
			inputTree->SetBranchAddress("dssdQPed",dssdQPed);

			inputTree->SetBranchAddress("RefTime1",&RefTime1);
			inputTree->SetBranchAddress("RefTime2",&RefTime2);

			inputTree->SetBranchAddress("csiQRaw",csiQRaw);
			inputTree->SetBranchAddress("csiTRaw",csiTRaw);
			inputTree->SetBranchAddress("csiQPed",csiQPed);

			inputTree->SetBranchAddress("dssdTHit",&dssdTHit);
			inputTree->SetBranchAddress("dssdTHitSide",dssdTHitSide);
			inputTree->SetBranchAddress("dssdTHitStripId",dssdTHitStripId);
			inputTree->SetBranchAddress("dssdTHitTCal",dssdTHitTCal);

			inputTree->SetBranchAddress("csiTHit",&csiTHit);
			inputTree->SetBranchAddress("csiTHitId",csiTHitId);
			inputTree->SetBranchAddress("csiTHitTCal",csiTHitTCal);


		}
		void setOutputBranchRaw(TTree *tree){

			tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
			tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[2][32]/I");
			tree->Branch("dssdQPed",dssdQPed,"dssdQPed[4][32]/D");

			tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
			tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");

			tree->Branch("RefTime1",&RefTime1);
			tree->Branch("RefTime2",&RefTime2);

		}


		void setOutputBranch(TTree *tree){

			if(kWriteStatus) setOutputBranchRaw(tree);

			tree->Branch("dssdTHit",&dssdTHit,"dssdTHit/I");
                        tree->Branch("dssdTHitSide",dssdTHitSide,"dssdTHitSide[dssdTHit]/I");
                        tree->Branch("dssdTHitStripId",dssdTHitStripId,"dssdTHitStripId[dssdTHit]/I");
                        tree->Branch("dssdTHitTCal",dssdTHitTCal,"dssdTHitTCal[dssdTHit]/D");

			tree->Branch("csiTHit",&csiTHit,"csiTHit/I");
                        tree->Branch("csiTHitId",csiTHitId,"csiTHitId[csiTHit]/I");
                        tree->Branch("csiTHitTCal",csiTHitTCal,"csiTHitTCal[csiTHit]/D");


		}

		MergeTELE(){}
		MergeTELE(int run){
			kWriteStatus  = true;
			detector = "TELE";
			treeName = "CalTreeTELE";
			runNumber = run;
		}

		int getRunNumber(){
			return runNumber;
		}
		//using Convert::isFileExists;
		bool isFileExists(){
			return Convert::isFileExists(detector);
			//return isFileExists(detector);
		}
		void printTotalEventNumber(){
			cout << "N of entries (TELE):\t" << inputTree->GetEntries() << endl;
		}
		void init(){
		}
		void print(){
			cout<<"Csi THit:"<<endl;
			for (int i = 0; i < csiTHit; ++i) {
				cout<<" csiTHit"<<i<<" cid="<<"\t"<<csiTHitId[i]<<" csiTCal ="<<"\t"<<csiTHitTCal[i]<<endl;
			}
		}
		int getCsiTHit(){
			return csiTHit;
		}
		int getDssdTHit(){
			return dssdTHit;
		}
		double getCsiTHitTCal(int i){
			return csiTHitTCal[i] - RefTime1;
		}
		int getCsiTHitId(int i){
			return csiTHitId[i];
		}
		double getCsiQPed(int id){
			return csiQPed[id];
		}
		double getCsiTRef(int id){
			return (double)(csiTRaw[id] - RefTime1);
		}

		double getDssdTHitTCal(int i){
			return dssdTHitTCal[i];
		}
		int getDssdTHitStripId(int i){
			return dssdTHitStripId[i];
		}
		int getDssdTHitSide(int i){
			return dssdTHitSide[i];
		}
		double getDssdFQPed(int side, int fid){
			return dssdQPed[2*side][fid];
		}
		double getDssdBQPed(int side, int bid){
			return dssdQPed[2*side+1][bid];
		}
		

};
