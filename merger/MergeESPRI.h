class EspriEnergyPara{
	private:
		double plasGain[2][7];
		double plasDead[2][7];
		double naiGain[2][7];
		double naiDead[2][7];

		void init(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j< 7; ++j) {
					plasGain[i][j]= 0;
					plasDead[i][j]= 0;
					naiGain[i][j]= 0;
					naiDead[i][j]= 0;
				}

			}

		}
		void loadCalibPara(){
			init();
			ifstream in;
			TString inputName = "txt/espriEnergyCalibParaBe14.txt";
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barId;
			double gPlas;
			double dPlas;
			double gNai;
			double dNai;
			while(1){
				if(!in.good()) break;
				in>>side>>barId>>gPlas>>dPlas>>gNai>>dNai;
				naiGain[side][barId] = gNai;
				naiDead[side][barId] = dNai;
				plasGain[side][barId] = gPlas;
				plasDead[side][barId] = dPlas;
			}
		}
		void print(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j< 7; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<plasGain[i][j]<<"\t"<<plasDead[i][j]<<"\t"<<naiGain[i][j]<<"\t"<<naiDead[i][j]<<endl;
				}

			}
		}
	public:
		EspriEnergyPara(){
			loadCalibPara();
			print();
		}
		~EspriEnergyPara(){}
		double getNaiGain(int side,int barId){
			return naiGain[side][barId];
		}
		double getNaiDead(int side,int barId){
			return naiDead[side][barId];
		}
		double getPlasGain(int side){
			return plasGain[side][0];
		}
		double getPlasDead(int side){
			return plasDead[side][0];
		}
};
class EspriEnergy{
	private:
		EspriEnergyPara *calibPara;
		double getPlasGain(int side){
			return calibPara->getPlasGain(side);
		}
		double getPlasDead(int side){
			return calibPara->getPlasDead(side);
		}
		double getNaiGain(int side,int barId){
			return calibPara->getNaiGain(side,barId);
		}
		double getNaiDead(int side,int barId){
			return calibPara->getNaiDead(side,barId);
		}
	public:
		EspriEnergy(){
			calibPara = new EspriEnergyPara();
		}
		~EspriEnergy(){}
		double getPlasEnergy(int side,double plasBarQPed){
			return getPlasGain(side)*plasBarQPed+getPlasDead(side);
		}
		double getNaiEnergy(int side, int barId,double naiBarQPed){
			return getNaiGain(side,barId)*naiBarQPed+getNaiDead(side,barId);
		}

};
class EspriEnergyCorr{
	private:
		double naiQCorr[2][7];
		double plasQCorr[2];
	public:
		EspriEnergyCorr(){}
		~EspriEnergyCorr(){}

		void init(){
			for (int i = 0; i < 2; ++i) {
				plasQCorr[i] = NAN;
				for (int j = 0; j < 7; ++j) {
					naiQCorr[i][j] = NAN;
				}	
			}
		}

		void setPlasQCorr(int side,double plasQ){
			plasQCorr[side] = plasQ;	
		}
		void setNaiQCorr(int side,int barId,double naiQ){
			naiQCorr[side][barId] = naiQ;	
		}
		void setBranch(TTree *tree){
			tree->Branch("plasQCorr",plasQCorr,"plasQCorr[2]/D");
			tree->Branch("naiQCorr",naiQCorr,"naiQCorr[2][7]/D");
		}
};
class EspriPlasTime{
	private:

		double posPara[2];	
		double timeOffset[2];
		double plasTCorr[2];
		void init(){
			plasTCorr[0] = -9999;
			plasTCorr[1] = -9999;
		}
	public:
		EspriPlasTime(){
			timeOffset[0] = 691.382;
			timeOffset[1] = 691.082;
			posPara[0] = -0.01;
			posPara[1] = -0.0115;
		}
		~EspriPlasTime(){}
		void setBranch(TTree *tree){
			tree->Branch("plasTCorr",plasTCorr,"plasTCorr[2]/D");
		}

		void corrPlasTime(double *plasT,double *rdcY){
			init();
			if(plasT[0]!=-9999) plasTCorr[0] = plasT[0]+timeOffset[0]+posPara[0]*(rdcY[0]-225);
			if(plasT[1]!=-9999) plasTCorr[1] = plasT[1]+timeOffset[1]+posPara[1]*(rdcY[1]-225);
			//print();

		}
		double getPlasT(int side){
			return plasTCorr[side];
		}
		void print(){
			cout<<"plasTCorr[0] = "<<plasTCorr[0]<<"plasTCorr[1] = "<<plasTCorr[1]<<endl;
		}
};

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

		}
		~MergeESPRI(){
		}
};
