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

		// Second analysis on calibration
		EspriPlasTime *plasTime;
		EspriEnergy *espriEnergy;
		EspriEnergyCorr *saveEspriEnergy;

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

                Double_t	naiQPed[4][7];
		Double_t	naiBarMQPed[2][7];  // Magnet Correction for each beam setting
		Double_t	naiBarMQSync[2][7]; // Sync QPed in each Bar to ref Bar00 and Bar10
		Double_t	naiBarMQCal[2][7];  // Cal Parameter from each bar under Be10 setting
		Double_t	naiBarMSQCal[2][7]; // Cal Parameter from Bar00 and Bar10 

                Double_t	naiBarQCal[2][7];   // Old calib, Be14 using Be10 parameter, from pp Scattering
                Double_t	naiQ[2];
                Int_t		naiQId[2];

		Double_t        plasQCal[4];
		Double_t        plasQPed[4];
		Double_t	plasBarMQPed[2];// plasMQPed -> M Magnet
		Double_t	plasMQ[2];      // plasMQ  Magnet correction
		Double_t	plasQ[2];

		Double_t        plasTCal[4];
		Double_t	plasT[2];

	public:

		MergeESPRI(int run){
			env = new TEnv("configMerger.prm");
			detector = "ESPRI";
			treeName = "CalTreeESPRI";
			runNumber = run;
			plasTime = new EspriPlasTime();
			espriEnergy = new EspriEnergy();
			saveEspriEnergy = new EspriEnergyCorr();
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
                        inputTree->SetBranchAddress("naiBarMQPed", naiBarMQPed);
                        inputTree->SetBranchAddress("naiBarMQSync", naiBarMQSync);
                        inputTree->SetBranchAddress("naiBarMQCal", naiBarMQCal);
                        inputTree->SetBranchAddress("naiBarMSQCal", naiBarMSQCal);
                        inputTree->SetBranchAddress("naiBarQCal", naiBarQCal);
                        inputTree->SetBranchAddress("naiQId", &naiQId);
			inputTree->SetBranchAddress("naiQ",naiQ);

			inputTree->SetBranchAddress("plasQCal",plasQCal);
			inputTree->SetBranchAddress("plasQPed",plasQPed);
			inputTree->SetBranchAddress("plasBarMQPed",plasBarMQPed);
			inputTree->SetBranchAddress("plasTCal",plasTCal);
			inputTree->SetBranchAddress("plasMQ",&plasMQ);
			inputTree->SetBranchAddress("plasQ",&plasQ);
			inputTree->SetBranchAddress("plasT",&plasT);

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

                        tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
                        tree->Branch("naiBarMQPed", naiBarMQPed, "naiBarMQPed[2][7]/D");
                        tree->Branch("naiBarMQSync", naiBarMQSync, "naiBarMQSync[2][7]/D");
                        tree->Branch("naiBarMQCal", naiBarMQCal, "naiBarMQCal[2][7]/D");
                        tree->Branch("naiBarMSQCal", naiBarMSQCal, "naiBarMSQCal[2][7]/D");
                        tree->Branch("naiBarQCal", naiBarQCal, "naiBarQCal[2][7]/D");
                        tree->Branch("naiQ", &naiQ, "naiQ[2]/D");
                        tree->Branch("naiQId", &naiQId, "naiQId[2]/I");

			tree->Branch("plasQCal",plasQCal,"plasQCal[4]/D");
			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
			tree->Branch("plasBarMQPed",plasBarMQPed,"plasBarMQPed[4]/D");
			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");
			tree->Branch("plasMQ",&plasMQ,"plasMQ[2]/D");
			tree->Branch("plasQ",&plasQ,"plasQ[2]/D");
			tree->Branch("plasT",&plasT,"plasT[2]/D");
			plasTime->setBranch(tree);
			saveEspriEnergy->setBranch(tree);
		}
		~MergeESPRI(){
		}


		double getRdcX(int side){
			return rdcX[side];
		}
		double getRdcY(int side){
			return rdcY[side];
		}
		double getPlasQ(int side){
			//return plasQ[side];
			//cout<<side<<":"<<sqrt(plasQPed[2*side]*plasQPed[2*side+1])<<endl;
			return espriEnergy->getPlasEnergy(side,sqrt(plasQPed[2*side]*plasQPed[2*side+1]));
		}
		double getPlasT(int side){
			//return plasT[side];
			return plasTime->getPlasT(side);
		}
		double getNaiQ(int side,int id){
			//return naiBarQCal[side][id];
			return espriEnergy->getNaiEnergy(side,id,getNaiQPed(side,id));
		}
		double getNaiQPed(int side,int id){
			return sqrt(naiQPed[2*side][id]*naiQPed[2*side+1][id]);
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

		void corrPlasTime(){
			plasTime->corrPlasTime(plasT,rdcY);
		}
		void corrEnergy(){
			saveEspriEnergy->init();
			for (int i = 0; i < 2; ++i) {
				saveEspriEnergy->setPlasQCorr(i,getPlasQ(i));
				for (int j = 0; j < 7; ++j) {
					saveEspriEnergy->setNaiQCorr(i,j,getNaiQ(i,j));
				}
			}
		}

};
