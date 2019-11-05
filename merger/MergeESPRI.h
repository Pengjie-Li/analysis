class MergeESPRI:public Convert{
	private:

		//Declaration of leaves types
		Int_t           EventNumber;
		Int_t           RunNumber;

		vector<int>     *plasTdcRaw0;
		vector<int>     *plasTdcRaw1;
		vector<int>     *plasTdcRaw2;
		vector<int>     *plasTdcRaw3;

		vector<int>     *rdcTdc;
		vector<int>     *rdcPlaneId;
		vector<int>     *rdcWireId;
		vector<int>     *rdcLayerId;
		vector<int>     *rdcPlaneNHit;

		Int_t           naiQRaw[4][7];
		Int_t           plasQRaw[4];
		Int_t           plasTRaw[4];
		Int_t           plasTimeRef;
		Int_t           rdcMult;
		Double_t        rdcX[2];
		Double_t        rdcY[2];
		Double_t        rdcA[2];
		Double_t        rdcB[2];

		Double_t        rdcChi2[2];
		Double_t        rdcDL[2][7];
		Double_t        rdcTch[2][7];
		Double_t        rdcRes[2][7];

		Double_t	naiQCal[4][7];
                Double_t	naiQPed[4][7];
                Double_t	naiBarQCal[2][7];
                Double_t	naiQ[2];
                Int_t		naiQId[2];

		Double_t        plasQCal[4];
		Double_t        plasQPed[4];
		Double_t        plasTCal[4];
		Double_t	plasQ[2];
		Double_t	plasT[2];

	public:

		MergeESPRI(int run){
			env = new TEnv("configMerger.prm");
			detector = "ESPRI";
			treeName = "CalTreeESPRI";
			runNumber = run;
		}
		void init(){
		}
		void setBranch(){

			// when you have vector in your tree
			rdcTdc		= 0;
			rdcPlaneId	= 0;
			rdcLayerId	= 0;
			rdcWireId	= 0;
			rdcPlaneNHit	= 0;

			plasTdcRaw0 = 0;
			plasTdcRaw1 = 0;
			plasTdcRaw2 = 0;
			plasTdcRaw3 = 0;

			// Set branch addresses.
			inputTree->SetBranchAddress("EventNumber",&EventNumber);
			inputTree->SetBranchAddress("RunNumber",&RunNumber);
			inputTree->SetBranchAddress("plasTdcRaw0",&plasTdcRaw0);
			inputTree->SetBranchAddress("plasTdcRaw1",&plasTdcRaw1);
			inputTree->SetBranchAddress("plasTdcRaw2",&plasTdcRaw2);
			inputTree->SetBranchAddress("plasTdcRaw3",&plasTdcRaw3);
			inputTree->SetBranchAddress("rdcTdc",&rdcTdc);
			inputTree->SetBranchAddress("rdcPlaneId",&rdcPlaneId);
			inputTree->SetBranchAddress("rdcWireId",&rdcWireId);
			inputTree->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
			inputTree->SetBranchAddress("naiQRaw",naiQRaw);
			inputTree->SetBranchAddress("plasQRaw",plasQRaw);
			inputTree->SetBranchAddress("plasTRaw",plasTRaw);
			inputTree->SetBranchAddress("plasTimeRef",&plasTimeRef);
			inputTree->SetBranchAddress("rdcMult",&rdcMult);
			inputTree->SetBranchAddress("rdcX",rdcX);
			inputTree->SetBranchAddress("rdcY",rdcY);
			inputTree->SetBranchAddress("rdcA",rdcA);
			inputTree->SetBranchAddress("rdcB",rdcB);
			inputTree->SetBranchAddress("rdcChi2",rdcChi2);
			inputTree->SetBranchAddress("rdcDL",rdcDL);
			inputTree->SetBranchAddress("rdcTch",rdcTch);
			inputTree->SetBranchAddress("rdcRes",rdcRes);

                        inputTree->SetBranchAddress("naiQPed", naiQPed);
                        inputTree->SetBranchAddress("naiBarQCal", naiBarQCal);
                        inputTree->SetBranchAddress("naiQId", &naiQId);
			inputTree->SetBranchAddress("naiQCal",naiQCal);
			inputTree->SetBranchAddress("naiQ",naiQ);

			inputTree->SetBranchAddress("plasQCal",plasQCal);
			inputTree->SetBranchAddress("plasQPed",plasQPed);
			inputTree->SetBranchAddress("plasTCal",plasTCal);
			inputTree->SetBranchAddress("plasQ",&plasQ);
			inputTree->SetBranchAddress("plasT",&plasT);
		//	inputTree->SetBranchAddress("plasQL",&plasQL);
		//	inputTree->SetBranchAddress("plasQR",&plasQR);
		//	inputTree->SetBranchAddress("plasTL",&plasTL);
		//	inputTree->SetBranchAddress("plasTR",&plasTR);

		}
		void setOutputBranch(TTree *tree){
			// Set branch addresses.
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);

			tree->Branch("plasTdcRaw0",&plasTdcRaw0);
			tree->Branch("plasTdcRaw1",&plasTdcRaw1);
			tree->Branch("plasTdcRaw2",&plasTdcRaw2);
			tree->Branch("plasTdcRaw3",&plasTdcRaw3);
	
			tree->Branch("rdcTdc",&rdcTdc);
			tree->Branch("rdcPlaneId",&rdcPlaneId);
			tree->Branch("rdcWireId",&rdcWireId);
			tree->Branch("rdcPlaneNHit",&rdcPlaneNHit);
			tree->Branch("naiQRaw",naiQRaw,"naiQRaw[4][7]/I");
			tree->Branch("plasQRaw",plasQRaw,"plasQRaw[4]/I");
			tree->Branch("plasTRaw",plasTRaw,"plasTRaw[4]/I");
			tree->Branch("plasTimeRef",&plasTimeRef);
			tree->Branch("rdcMult",&rdcMult);
			tree->Branch("rdcX",rdcX,"rdcX[2]/D");
			tree->Branch("rdcY",rdcY,"rdcY[2]/D");
			tree->Branch("rdcA",rdcA,"rdcA[2]/D");
			tree->Branch("rdcB",rdcB,"rdcB[2]/D");
			tree->Branch("rdcChi2",rdcChi2,"rdcChi2[2]/D");
			tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
			tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
			tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");

                        tree->Branch("naiQCal", naiQCal, "naiQCal[4][7]/D");
                        tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
                        tree->Branch("naiBarQCal", naiBarQCal, "naiBarQCal[2][7]/D");
                        tree->Branch("naiQ", &naiQ, "naiQ[2]/D");
                        tree->Branch("naiQId", &naiQId, "naiQId[2]/I");

			tree->Branch("plasQCal",plasQCal,"plasQCal[4]/D");
			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");
			tree->Branch("plasQ",&plasQ,"plasQ[2]/D");
			tree->Branch("plasT",&plasT,"plasT[2]/D");

		}
		double getESPRINaiEnergy(int isLR){
			return isLR>0?naiQ[1]:naiQ[0];
		}
		double getESPRIPlasTime(int isLR){
			return isLR>0?plasT[1]:plasT[0]; 
		}
		double getESPRIPlasDeltaE(int isLR){
			return isLR>0?plasQ[1]:plasQ[0];
		}
		~MergeESPRI(){
		}

		double getNaiBarQCal(int side,int id){
			return naiBarQCal[side][id];
		}
		double getPlasBarQCal(int side){
			return plasQ[side];
		}
		double getRdcX(int side){
			return rdcX[side];
		}
		double getRdcY(int side){
			return rdcY[side];
		}
		double getPlasQ(int side){
			return plasQ[side];
		}
		double getPlasT(int side){
			return plasT[side];
		}
		void print(){
			printRdc();
			printPlas();
			printNai();
		}
		void printRdc(){
			cout<<"RDC Position:"<<endl;
			cout<<"Left :"<<rdcX[0]<<":"<<rdcY[0]<<endl;
			cout<<"Right:"<<rdcX[1]<<":"<<rdcY[1]<<endl;
		}
		void printPlas(){
			cout<<"Plas Q and T"<<endl;
			cout<<"Left :"<< plasQ[0]<<":"<<plasT[0]<<endl; 
			cout<<"Right:"<< plasQ[1]<<":"<<plasT[1]<<endl; 
		}
		void printNai(){
			cout<<"Nai Bar QCal:"<<endl;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					if(naiBarQCal[i][j]>1) cout<<"side = "<<i<<" barId = "<<j<<" naiQ = "<<naiBarQCal[i][j]<<endl;
				}
			}
		}
};
