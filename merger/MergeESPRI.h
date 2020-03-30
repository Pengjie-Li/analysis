class MergeESPRI:public Convert{
	private:

		bool isStoreRawData;
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

		Int_t           rdcHit;
		Int_t           rdcHitSide[2];
		Double_t        rdcHitX[2];
		Double_t        rdcHitY[2];
		Double_t        rdcHitChi2[2];

		Double_t        rdcX[2];
		Double_t        rdcY[2];
		Double_t        rdcA[2];
		Double_t        rdcB[2];
		Double_t        rdcChi2[2];
		Double_t        rdcDL[2][7];
		Double_t        rdcTch[2][7];
		Double_t        rdcRes[2][7];

		Int_t           naiHit;
		Int_t           naiHitSide[2];
		Int_t           naiHitBarId[2];
		Double_t        naiHitQPed[2];
		Double_t        naiQPed[4][7];
		Double_t        naiBarQPed[2][7];

		Int_t           plasHit;
		Int_t           plasHitSide[2];
		Double_t        plasHitQPed[2];

		Double_t        plasQPed[4];
		Double_t        plasBarQPed[2];
		Double_t        plasTCal[4];
		Double_t        plasTRef[4];

		Int_t           espriHit;
		Int_t           espriHitSide[2];


	public:

		MergeESPRI(int run){
			isStoreRawData = true;
			detector = "ESPRI";
			treeName = "CalTreeESPRI";
			runNumber = run;
		}
		~MergeESPRI(){}
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

			inputTree->SetBranchAddress("EventNumber",&EventNumber);
			inputTree->SetBranchAddress("RunNumber",&RunNumber);
			inputTree->SetBranchAddress("plasTdcRaw0",&plasTdcRaw0);
			inputTree->SetBranchAddress("plasTdcRaw1",&plasTdcRaw1);
			inputTree->SetBranchAddress("plasTdcRaw2",&plasTdcRaw2);
			inputTree->SetBranchAddress("plasTdcRaw3",&plasTdcRaw3);

			inputTree->SetBranchAddress("rdcTdc",&rdcTdc);
			inputTree->SetBranchAddress("rdcPlaneId",&rdcPlaneId);
			inputTree->SetBranchAddress("rdcWireId",&rdcWireId);
			inputTree->SetBranchAddress("rdcLayerId",&rdcLayerId);
			inputTree->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);

			inputTree->SetBranchAddress("naiQRaw",naiQRaw);
			inputTree->SetBranchAddress("plasQRaw",plasQRaw);
			inputTree->SetBranchAddress("plasTRaw",plasTRaw);
			inputTree->SetBranchAddress("plasTimeRef",&plasTimeRef);

			inputTree->SetBranchAddress("rdcHit",&rdcHit);
			inputTree->SetBranchAddress("rdcHitSide",rdcHitSide);
			inputTree->SetBranchAddress("rdcHitX",rdcHitX);
			inputTree->SetBranchAddress("rdcHitY",rdcHitY);
			inputTree->SetBranchAddress("rdcHitChi2",rdcHitChi2);

			inputTree->SetBranchAddress("rdcX",rdcX);
			inputTree->SetBranchAddress("rdcY",rdcY);
			inputTree->SetBranchAddress("rdcA",rdcA);
			inputTree->SetBranchAddress("rdcB",rdcB);
			inputTree->SetBranchAddress("rdcChi2",rdcChi2);
			inputTree->SetBranchAddress("rdcDL",rdcDL);
			inputTree->SetBranchAddress("rdcTch",rdcTch);
			inputTree->SetBranchAddress("rdcRes",rdcRes);

			inputTree->SetBranchAddress("naiHit",&naiHit);
			inputTree->SetBranchAddress("naiHitSide",naiHitSide);
			inputTree->SetBranchAddress("naiHitBarId",naiHitBarId);
			inputTree->SetBranchAddress("naiHitQPed",naiHitQPed);
			inputTree->SetBranchAddress("naiQPed",naiQPed);
			inputTree->SetBranchAddress("naiBarQPed",naiBarQPed);
			inputTree->SetBranchAddress("plasHit",&plasHit);
			inputTree->SetBranchAddress("plasHitSide",plasHitSide);
			inputTree->SetBranchAddress("plasHitQPed",plasHitQPed);
			inputTree->SetBranchAddress("plasQPed",plasQPed);
			inputTree->SetBranchAddress("plasBarQPed",plasBarQPed);
			inputTree->SetBranchAddress("plasTCal",plasTCal);
			inputTree->SetBranchAddress("plasTRef",plasTRef);

			inputTree->SetBranchAddress("espriHit",&espriHit);
			inputTree->SetBranchAddress("espriHitSide",espriHitSide);


		}
		void setOutputBranch(TTree *tree){
			// Set branch addresses.

			if(isStoreRawData == true) setOutputBranchRaw(tree);

			tree->Branch("rdcHit",&rdcHit,"rdcHit/I");
			tree->Branch("rdcHitSide",rdcHitSide,"rdcHitSide[rdcHit]/I");
			tree->Branch("rdcHitX",rdcHitX,"rdcHitX[rdcHit]/D");
			tree->Branch("rdcHitY",rdcHitY,"rdcHitY[rdcHit]/D");
			tree->Branch("rdcHitChi2",rdcHitChi2,"rdcHitChi2[rdcHit]/D");

			tree->Branch("naiHit",&naiHit,"naiHit/I");
			tree->Branch("naiHitSide",naiHitSide,"naiHitSide[naiHit]/I");
			tree->Branch("naiHitBarId",naiHitBarId,"naiHitBarId[naiHit]/I");
			tree->Branch("naiHitQPed",naiHitQPed,"naiHitQPed[naiHit]/D");

			tree->Branch("plasHit",&plasHit,"plasHit/I");
			tree->Branch("plasHitSide",plasHitSide,"plasHitSide[plasHit]/I");
			tree->Branch("plasHitQPed",plasHitQPed,"plasHitQPed[plasHit]/D");

			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");

			tree->Branch("espriHit",&espriHit,"espriHit/I");
			tree->Branch("espriHitSide",espriHitSide,"espriHitSide[espriHit]/I");
	
		}
		void setOutputBranchRaw(TTree *tree){
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

			tree->Branch("rdcX",rdcX,"rdcX[2]/D");
			tree->Branch("rdcY",rdcY,"rdcY[2]/D");
			tree->Branch("rdcA",rdcA,"rdcA[2]/D");
			tree->Branch("rdcB",rdcB,"rdcB[2]/D");
			tree->Branch("rdcChi2",rdcChi2,"rdcChi2[2]/D");
			tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
			tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
			tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");

			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
			tree->Branch("naiBarQPed",naiBarQPed,"naiBarQPed[2][7]/D");

			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
			tree->Branch("plasTRef",plasTRef,"plasTRef[4]/D");
		}

		double getRdcX(int side){
			return rdcX[side];
		}
		double getRdcY(int side){
			return rdcY[side];
		}
		int getHit(){
			return espriHit;
		}
		double getPlasT(int ud){
			int side = getSide();
			return plasTCal[2*side+ud];
		}
		double getRdcX(){
			return rdcHitX[0];
		}
		double getRdcY(){
			return rdcHitY[0];
		}
		double getPlasQPed(){
			return plasBarQPed[plasHitSide[0]];
		}
		double getNaiQPed(){
			return naiHitQPed[0];
		}
		double getSide(){
			return espriHitSide[0];
		}
		double getNaiId(){
			return naiHitBarId[0];
		}
		double getPlasQPed(int side){
			return plasBarQPed[side];
		}
		double getNaiQPed(int side,int id){
			//return sqrt(naiQPed[2*side][id]*naiQPed[2*side+1][id]);
			return naiBarQPed[side][id];
		}
		int getNaiHit(){
			return naiHit;
		}
		bool isGoodEvent(){
			if(getHit()==1) return true;
			else return false;
		}


		void print(){
                        for (int i = 0; i < espriHit; ++i) {
                                cout<<"ESPI Hit"<<i<<" Side = "<<espriHitSide[i]<<endl;
                        }
			printRdc();
			printPlas();
			printNai();
		}
		
		void printRdc(){
                        for (int i = 0; i < rdcHit; ++i) {
                                cout<<" rdc Hit"<<i<<" Side = "<<rdcHitSide[i]<< " X ="<<rdcHitX[i]<<" Y = "<<rdcHitY[i]<<" Chi2 = "<<rdcHitChi2[i]<<endl;
                        }
		}
		void printPlas(){
			for (int i = 0; i < plasHit; ++i) {
				int side = plasHitSide[i];
				cout<<"Plas Hit"<<i<<" Side = "<<side<<" QPed = "<<plasBarQPed[side]<<" TCal = "<<plasTCal[2*side]<<" : "<<plasTCal[2*side+1]<<endl;
			}
		}
		void printNai(){
                        for (int i = 0; i < naiHit; ++i) {
                                cout<<" nai Hit"<<i<<" Side = "<<naiHitSide[i]<<" BarId = "<<naiHitBarId[i]<<" QPed = "<<naiHitQPed[i]<<endl;
                        }
		}
};
