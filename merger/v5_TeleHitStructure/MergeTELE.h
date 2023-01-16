class MergeTELE:public Convert{
	private:
		bool kWriteStatus;
	public:
		//Declaration of leaves types

		Int_t           dssdQRaw[4][32];
		Int_t           dssdTRaw[2][32];
		Int_t           RefTime1;
		Int_t           RefTime2;
		Int_t           csiQRaw[7];
		Int_t           csiTRaw[7];

		Int_t           dssdQHit;
		Int_t           dssdQHitSide[10];
		Int_t           dssdQHitStripId[10];
		Double_t        dssdQHitQPed[10];
		Double_t        dssdQPed[4][32];

		Int_t           dssdTHit;
		Int_t           dssdTHitSide[10];
		Int_t           dssdTHitStripId[10];
		Double_t        dssdTHitTCal[10];

		Int_t         dssdHit;
		Int_t           dssdHitSide[0];
		Int_t           dssdHitFid[0];
		Int_t           dssdHitBid[0];
		Double_t        dssdHitFQPed[0];
		Double_t        dssdHitBQPed[0];
		Double_t        dssdHitTCal[0];

		Int_t           csiQHit;
		Int_t           csiQHitId[5];
		Double_t        csiQHitQPed[5];
		Double_t        csiQPed[7];

		Int_t           csiTHit;
		Int_t           csiTHitId[4];
		Double_t        csiTHitTCal[4];

		Int_t	        csiHit;
		Int_t           csiHitId[3];
		Double_t        csiHitQPed[3];
		Double_t        csiHitTCal[3];

		Int_t           teleHit;
		Int_t           teleHitSide[3];
		Int_t           teleHitFid[3];
		Int_t           teleHitBid[3];
		Double_t        teleHitDssdFQPed[3];
		Double_t        teleHitDssdBQPed[3];
		Double_t        teleHitDssdTCal[3];
		Int_t           teleHitCid[3];
		Double_t        teleHitCsiQPed[3];
		Double_t        teleHitCsiTCal[3];


		void setBranch(){
			// Set branch addresses.
		
			inputTree->SetBranchAddress("dssdQRaw",dssdQRaw);
			inputTree->SetBranchAddress("dssdTRaw",dssdTRaw);
			inputTree->SetBranchAddress("RefTime1",&RefTime1);
			inputTree->SetBranchAddress("RefTime2",&RefTime2);
			inputTree->SetBranchAddress("csiQRaw",csiQRaw);
			inputTree->SetBranchAddress("csiTRaw",csiTRaw);
			inputTree->SetBranchAddress("dssdQHit",&dssdQHit);
			inputTree->SetBranchAddress("dssdQHitSide",dssdQHitSide);
			inputTree->SetBranchAddress("dssdQHitStripId",dssdQHitStripId);
			inputTree->SetBranchAddress("dssdQHitQPed",dssdQHitQPed);
			inputTree->SetBranchAddress("dssdQPed",dssdQPed);
			inputTree->SetBranchAddress("dssdTHit",&dssdTHit);
			inputTree->SetBranchAddress("dssdTHitSide",dssdTHitSide);
			inputTree->SetBranchAddress("dssdTHitStripId",dssdTHitStripId);
			inputTree->SetBranchAddress("dssdTHitTCal",dssdTHitTCal);
			inputTree->SetBranchAddress("dssdHit",&dssdHit);
			inputTree->SetBranchAddress("dssdHitSide",&dssdHitSide);
			inputTree->SetBranchAddress("dssdHitFid",&dssdHitFid);
			inputTree->SetBranchAddress("dssdHitBid",&dssdHitBid);
			inputTree->SetBranchAddress("dssdHitFQPed",&dssdHitFQPed);
			inputTree->SetBranchAddress("dssdHitBQPed",&dssdHitBQPed);
			inputTree->SetBranchAddress("dssdHitTCal",&dssdHitTCal);
			inputTree->SetBranchAddress("csiQHit",&csiQHit);
			inputTree->SetBranchAddress("csiQHitId",csiQHitId);
			inputTree->SetBranchAddress("csiQHitQPed",csiQHitQPed);
			inputTree->SetBranchAddress("csiQPed",csiQPed);
			inputTree->SetBranchAddress("csiTHit",&csiTHit);
			inputTree->SetBranchAddress("csiTHitId",csiTHitId);
			inputTree->SetBranchAddress("csiTHitTCal",csiTHitTCal);
			inputTree->SetBranchAddress("csiHit",&csiHit);
			inputTree->SetBranchAddress("csiHitId",&csiHitId);
			inputTree->SetBranchAddress("csiHitQPed",&csiHitQPed);
			inputTree->SetBranchAddress("csiHitTCal",&csiHitTCal);
			inputTree->SetBranchAddress("teleHit",&teleHit);
			inputTree->SetBranchAddress("teleHitSide",teleHitSide);
			inputTree->SetBranchAddress("teleHitFid",teleHitFid);
			inputTree->SetBranchAddress("teleHitBid",teleHitBid);
			inputTree->SetBranchAddress("teleHitDssdFQPed",teleHitDssdFQPed);
			inputTree->SetBranchAddress("teleHitDssdBQPed",teleHitDssdBQPed);
			inputTree->SetBranchAddress("teleHitDssdTCal",teleHitDssdTCal);
			inputTree->SetBranchAddress("teleHitCid",teleHitCid);
			inputTree->SetBranchAddress("teleHitCsiQPed",teleHitCsiQPed);
			inputTree->SetBranchAddress("teleHitCsiTCal",teleHitCsiTCal);



		}
		void setOutputBranchRaw(TTree *tree){

			tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
			tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[2][32]/I");

			tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");

			tree->Branch("RefTime1",&RefTime1);
			tree->Branch("RefTime2",&RefTime2);

			tree->Branch("dssdQPed",dssdQPed,"dssdQPed[4][32]/D");
                        tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
		}


		void setOutputBranch(TTree *tree){

			if(kWriteStatus) setOutputBranchRaw(tree);
                        tree->Branch("dssdQHit",&dssdQHit,"dssdQHit/I");
                        tree->Branch("dssdQHitSide",dssdQHitSide,"dssdQHitSide[dssdQHit]/I");
                        tree->Branch("dssdQHitStripId",dssdQHitStripId,"dssdQHitStripId[dssdQHit]/I");
                        tree->Branch("dssdQHitQPed",dssdQHitQPed,"dssdQHitQPed[dssdQHit]/D");

                        tree->Branch("dssdTHit",&dssdTHit,"dssdTHit/I");
                        tree->Branch("dssdTHitSide",dssdTHitSide,"dssdTHitSide[dssdTHit]/I");
                        tree->Branch("dssdTHitStripId",dssdTHitStripId,"dssdTHitStripId[dssdTHit]/I");
                        tree->Branch("dssdTHitTCal",dssdTHitTCal,"dssdTHitTCal[dssdTHit]/D");

                        tree->Branch("dssdHit",&dssdHit,"dssdHit/I");
                        tree->Branch("dssdHitSide",&dssdHitSide,"dssdHitSide[dssdHit]/I");
                        tree->Branch("dssdHitFid",&dssdHitFid,"dssdHitFid[dssdHit]/I");
                        tree->Branch("dssdHitBid",&dssdHitBid,"dssdHitBid[dssdHit]/I");
                        tree->Branch("dssdHitFQPed",&dssdHitFQPed,"dssdHitFQPed[dssdHit]/D");
                        tree->Branch("dssdHitBQPed",&dssdHitBQPed,"dssdHitBQPed[dssdHit]/D");
                        tree->Branch("dssdHitTCal",&dssdHitTCal,"dssdHitTCal[dssdHit]/D");

                        tree->Branch("csiQHit",&csiQHit,"csiQHit/I");
                        tree->Branch("csiQHitId",csiQHitId,"csiQHitId[csiQHit]/I");
                        tree->Branch("csiQHitQPed",csiQHitQPed,"csiQHitQPed[csiQHit]/D");

                        tree->Branch("csiTHit",&csiTHit,"csiTHit/I");
                        tree->Branch("csiTHitId",csiTHitId,"csiTHitId[csiTHit]/I");
                        tree->Branch("csiTHitTCal",csiTHitTCal,"csiTHitTCal[csiTHit]/D");

                        tree->Branch("csiHit",&csiHit,"csiHit/I");
                        tree->Branch("csiHitId",&csiHitId,"csiHitId[csiHit]/I");
                        tree->Branch("csiHitQPed",&csiHitQPed,"csiHitQPed[csiHit]/D");
                        tree->Branch("csiHitTCal",&csiHitTCal,"csiHitTCal[csiHit]/D");

                        tree->Branch("teleHit",&teleHit,"teleHit/I");
                        tree->Branch("teleHitSide",&teleHitSide,"teleHitSide[teleHit]/I");
                        tree->Branch("teleHitFid",&teleHitFid,"teleHitFid[teleHit]/I");
                        tree->Branch("teleHitBid",&teleHitBid,"teleHitBid[teleHit]/I");

                        tree->Branch("teleHitDssdFQPed",&teleHitDssdFQPed,"teleHitDssdFQPed[teleHit]/D");
                        tree->Branch("teleHitDssdBQPed",&teleHitDssdBQPed,"teleHitDssdBQPed[teleHit]/D");
                        tree->Branch("teleHitDssdTCal",&teleHitDssdTCal,"teleHitDssdTCal[teleHit]/D");

                        tree->Branch("teleHitCid",&teleHitCid,"teleHitCid[teleHit]/I");
                        tree->Branch("teleHitCsiQPed",&teleHitCsiQPed,"teleHitCsiQPed[teleHit]/D");
                        tree->Branch("teleHitCsiTCal",&teleHitCsiTCal,"teleHitCsiTCal[teleHit]/D");

		}

		MergeTELE(){}
		MergeTELE(int run){
			kWriteStatus  = true;
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
		void init(){
		}
		void print(){
			cout<<"Tele Hit:"<<endl;
			for (int i = 0; i < teleHit; ++i) {
				cout<<" Hit"<<i<<" Side= "<<teleHitSide[i]<<" fid="<<"\t"<<teleHitFid[i]<<" bid="<<"\t"<<teleHitBid[i]<<"\t"<<teleHitDssdFQPed[i]<<"\t"<<teleHitDssdBQPed[i]<<"\t"<<teleHitDssdTCal[i]<<"\t"<<teleHitCid[i]<<"\t"<<teleHitCsiQPed[i]<<"\t"<<teleHitCsiTCal[i]<<endl;
			}
		}
		int getHit(){
			return teleHit;
		}
		int getHitSide(int i){
			return teleHitSide[i];
		}
		int getHitFid(int i){
			return teleHitFid[i];
		}
		int getHitBid(int i){
			return teleHitBid[i];
		}
		int getHitCid(int i){
			return teleHitCid[i];
		}
		double getHitCsiQPed(int i){
			return teleHitCsiQPed[i];
		}
		double getHitCsiTCal(int i){
			return teleHitCsiTCal[i];
		}
		double getHitDssdTCal(int i){
			return teleHitDssdTCal[i];
		}
		double getHitDssdFQPed(int i){
			return teleHitDssdFQPed[i];
		}
		double getHitDssdBQPed(int i){
			return teleHitDssdBQPed[i];
		}

};
