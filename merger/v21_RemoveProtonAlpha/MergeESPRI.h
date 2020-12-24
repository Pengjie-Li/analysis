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
		Double_t        rdcX[2];
		Double_t        rdcY[2];
		Double_t        rdcA[2];
		Double_t        rdcB[2];
		Double_t        rdcChi2[2];
		Double_t        rdcDL[2][7];
		Double_t        rdcTch[2][7];
		Double_t        rdcRes[2][7];
		Int_t           naiHit;
		Int_t           naiHitSide[14];
		Int_t           naiHitBarId[14];
		Double_t        naiQPed[4][7];
		Int_t           plasHit;
		Int_t           plasHitSide[2];
		Int_t           plasTHit;
		Int_t           plasQHit;
		Double_t        plasQPed[4];

		Int_t           espriHit;
		Int_t           espriSide;
		Double_t        espriRdcX;
		Double_t        espriRdcY;
		Double_t        espriPlasQPed;
		Double_t        espriNaiQPed;
		Int_t 	       espriNaiBarId;


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
			inputTree->SetBranchAddress("rdcLayerId",&rdcLayerId);
			inputTree->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
			inputTree->SetBranchAddress("naiQRaw",naiQRaw);
			inputTree->SetBranchAddress("plasQRaw",plasQRaw);
			inputTree->SetBranchAddress("plasTRaw",plasTRaw);
			inputTree->SetBranchAddress("plasTimeRef",&plasTimeRef);
			inputTree->SetBranchAddress("rdcHit",&rdcHit);
			inputTree->SetBranchAddress("rdcHitSide",rdcHitSide);
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
			inputTree->SetBranchAddress("naiQPed",naiQPed);
			inputTree->SetBranchAddress("plasHit",&plasHit);
			inputTree->SetBranchAddress("plasHitSide",plasHitSide);
			inputTree->SetBranchAddress("plasTHit",&plasTHit);
			inputTree->SetBranchAddress("plasQHit",&plasQHit);
			inputTree->SetBranchAddress("plasQPed",plasQPed);
			inputTree->SetBranchAddress("espriHit",&espriHit);
			inputTree->SetBranchAddress("espriSide",&espriSide);
			inputTree->SetBranchAddress("espriRdcX",&espriRdcX);
			inputTree->SetBranchAddress("espriRdcY",&espriRdcY);
			inputTree->SetBranchAddress("espriPlasQPed",&espriPlasQPed);
			inputTree->SetBranchAddress("espriNaiQPed",&espriNaiQPed);
			inputTree->SetBranchAddress("espriNaiBarId",&espriNaiBarId);



		}
		void setOutputBranch(TTree *tree){
			// Set branch addresses.

			if(isStoreRawData == true) setOutputBranchRaw(tree);

			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");

			tree->Branch("rdcHit",&rdcHit,"rdcHit/I");
			tree->Branch("rdcHitSide",rdcHitSide,"rdcHitSide[rdcHit]/I");
	
			tree->Branch("naiHit",&naiHit,"naiHit/I");
			tree->Branch("naiHitSide",naiHitSide,"naiHitSide[naiHit]/I");
			tree->Branch("naiHitBarId",naiHitBarId,"naiHitBarId[naiHit]/I");
			tree->Branch("plasHit",&plasHit,"plasHit/I");
			tree->Branch("plasHitSide",plasHitSide,"plasHitSide[plasHit]/I");
			tree->Branch("plasTHit",&plasTHit,"plasTHit/I");
			tree->Branch("plasQHit",&plasQHit,"plasQHit/I");
			tree->Branch("espriHit",&espriHit,"espriHit/I");
			tree->Branch("espriSide",&espriSide,"espriSide/I");
			tree->Branch("espriRdcX",&espriRdcX,"espriRdcX/D");
			tree->Branch("espriRdcY",&espriRdcY,"espriRdcY/D");
			tree->Branch("espriPlasQPed",&espriPlasQPed,"espriPlasQPed/D");
			tree->Branch("espriNaiBarId",&espriNaiBarId,"espriNaiBarId/I");
			tree->Branch("espriNaiQPed",&espriNaiQPed,"espriNaiQPed/D");
	
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


		}

		int getRunNumber(){
			return RunNumber;
		}
		int getEventNumber(){
			return EventNumber;
		}
		double getRdcX(int side){
			return rdcX[side];
		}
		double getRdcY(int side){
			return rdcY[side];
		}
		double getRdcX(){
			return espriRdcX;
		}
		double getRdcY(){
			return espriRdcY;
		}
		bool isGoodEvent(){
			if(espriHit==1) return true;
			else return false;
		}
		int getHit(){
			return espriHit;
		}
		double getSide(){
			return espriSide;
		}
		double getPlasT(int ud){
			int side = getSide();
			return 0.025*(plasTRaw[2*side+ud]-plasTimeRef);
		}
		double getPlasQPed(){
			return espriPlasQPed;
		}
		double getNaiQPed(){
			return espriNaiQPed;
		}
		int getNaiId(){
			//return espriNaiBarId;
                        int barId = -1;
                        for (int i = 0; i < naiHit; ++i) {
                                if(naiHitSide[i] == getSide()){
                                        if(getNaiQPed(getSide(),naiHitBarId[i]) == espriNaiQPed){
                                                barId = naiHitBarId[i];
                                        }
                                }
                        }
                        return barId;
		}
		double getPlasQPed(int side){
			if(plasQPed[2*side]>0&&plasQPed[2*side+1]>0) return sqrt(plasQPed[2*side]*plasQPed[2*side+1]);
			else return 0;
		}
		double getNaiQPed(int side,int id){
			if(naiQPed[2*side][id]>0&&naiQPed[2*side+1][id]>0) return sqrt(naiQPed[2*side][id]*naiQPed[2*side+1][id]);
			else return 0;
		}
		int getNaiHit(){
			return naiHit;
		}

		void print(){
			if(espriHit==1){
				cout<<"ESPRI Hit: "<<espriHit<<" Side = "<<espriSide<<" rdcX="<<espriRdcX<<" rdcY="<<espriRdcY<<" plasQPed="<<espriPlasQPed<<" naiQPed="<<espriNaiQPed<<" barId="<<espriNaiBarId<<endl;
				printRdc();
				printPlas();
				printNai();
			}
		}
		
		void printRdc(){
                        for (int i = 0; i < rdcHit; ++i) {
                                cout<<" Rdc Hit: "<<i<<" Side = "<<rdcHitSide[i]<< " X ="<<rdcX[rdcHitSide[i]]<<" Y = "<<rdcY[rdcHitSide[i]]<<" Chi2 = "<<rdcChi2[rdcHitSide[i]]<<endl;
                        }
		}
		void printPlas(){
			for (int i = 0; i < plasHit; ++i) {
				int side = plasHitSide[i];
				cout<<" Plas Hit: "<<i<<" Side = "<<side<<" QPed = "<<getPlasQPed(side)<<" TRaw = "<<plasTRaw[2*side]<<" : "<<plasTRaw[2*side+1]<<endl;
			}
		}
		void printNai(){
                        for (int i = 0; i < naiHit; ++i) {
                                cout<<" Nai Hit"<<i<<" Side = "<<naiHitSide[i]<<" BarId = "<<naiHitBarId[i]<<" QPed = "<<getNaiQPed(naiHitSide[i],naiHitBarId[i])<<endl;
                        }
		}
};
