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
		Int_t           dssdQRaw[4][32];
		Int_t           dssdTRaw[4][32];
		Int_t           csiQRaw[7];
		Int_t           RefTime1;
		Int_t           RefTime2;

		int 	teleHit;	
		int 	teleHitSide[2];//left or right or both

		int 	dssdHit; // how many strips?
		int 	dssdHitSide[128];// 0 LF,1 LB,2RF,3RB
		double	dssdQScm[128];
		double	dssdTCal[128];

		int 	csiHit;
		int	csiHitSide[7]; // map CsI
		double	csiQPed[7];
		
		void setBranch(){
			// Set branch addresses.
			inputTree->SetBranchAddress("dssdQRaw",dssdQRaw);
			inputTree->SetBranchAddress("dssdTRaw",dssdTRaw);
			inputTree->SetBranchAddress("csiQRaw",csiQRaw);
			inputTree->SetBranchAddress("RefTime1",&RefTime1);
			inputTree->SetBranchAddress("RefTime2",&RefTime2);

			inputTree->SetBranchAddress("csiQPed",csiQPed);
		}
		void setOutputBranch(TTree *tree){

                        tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
                        tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[4][32]/I");
                        tree->Branch("dssdQScm",dssdQScm,"dssdQScm[4][32]/D");
                        tree->Branch("dssdQCal",dssdQCal,"dssdQCal[4][32]/D");
                        tree->Branch("dssdTCal",dssdTCal,"dssdTCal[4][32]/D");

			tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
			tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
			tree->Branch("csiQSync",csiQSync,"csiQSync[7]/D");
			tree->Branch("csiQCal",csiQCal,"csiQCal[7]/D");
			tree->Branch("csiTCal",csiTCal,"csiTCal[7]/D");

		}


		MergeTELE(){}
		MergeTELE(int run){
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
				if(dssdQCal[side][i]>siliconHitThreshold) nHit++; 
			}
			return nHit;
		}
		double getSiliconRawADC(int side, int id){
			return dssdQRaw[side][id];
		}
		double getCsiQCal(int id){
			return csiQCal[id];
		}
		double getDssdEnergyCal(int side, int id){
			return dssdQCal[side][id];
		}
	
		void print(){
		}

};

