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
		Int_t           dssdEnergyRaw[4][32];
		Int_t           dssdTimeRaw[4][32];
		Int_t           csiEnergyRaw[7];
		Int_t           csiTimeRaw[7];
		Int_t           RefTime1;
		Int_t           RefTime2;
		Double_t        dssdEnergyCal[4][32];
		Double_t        dssdTimeCal[4][32];
		Double_t        csiEnergyCal[7];
		Double_t        csiTimeCal[7];


		void setBranch(){
			// Set branch addresses.
			inputTree->SetBranchAddress("dssdEnergyRaw",dssdEnergyRaw);
			inputTree->SetBranchAddress("dssdTimeRaw",dssdTimeRaw);
			inputTree->SetBranchAddress("csiEnergyRaw",csiEnergyRaw);
			inputTree->SetBranchAddress("csiTimeRaw",csiTimeRaw);
			inputTree->SetBranchAddress("RefTime1",&RefTime1);
			inputTree->SetBranchAddress("RefTime2",&RefTime2);
			inputTree->SetBranchAddress("dssdEnergyCal",dssdEnergyCal);
			inputTree->SetBranchAddress("dssdTimeCal",dssdTimeCal);
			inputTree->SetBranchAddress("csiEnergyCal",csiEnergyCal);
			inputTree->SetBranchAddress("csiTimeCal",csiTimeCal);


		}
		void setOutputBranch(TTree *tree){

                        tree->Branch("dssdEnergyRaw",dssdEnergyRaw,"dssdEnergyRaw[4][32]/I");
                        tree->Branch("dssdTimeRaw",dssdTimeRaw,"dssdTimeRaw[4][32]/I");
                        tree->Branch("dssdEnergyCal",dssdEnergyCal,"dssdEnergyCal[4][32]/D");
                        tree->Branch("dssdTimeCal",dssdTimeCal,"dssdTimeCal[4][32]/D");

			tree->Branch("csiEnergyRaw",csiEnergyRaw,"csiEnergyRaw[7]/I");
			tree->Branch("csiTimeRaw",csiTimeRaw,"csiTimeRaw[7]/I");
			tree->Branch("csiEnergyCal",csiEnergyCal,"csiEnergyCal[7]/D");
			tree->Branch("csiTimeCal",csiTimeCal,"csiTimeCal[7]/D");

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
		void init(){
		}
		Int_t getMultiplicity(int side){
	
			double siliconHitThreshold = env->GetValue("siliconHitThreshold",500.);
			int nHit = 0;
			for(int i = 0;i<32;i++){
				if(dssdEnergyCal[side][i]>siliconHitThreshold) nHit++; 
			}
			return nHit;
		}
		double getSiliconRawADC(int side, int id){
			return dssdEnergyRaw[side][id];
		}
		double getCsiQCal(int id){
			return csiEnergyCal[id];
		}
		double getDssdEnergyCal(int side, int id){
			return dssdEnergyCal[side][id];
		}
	

};

