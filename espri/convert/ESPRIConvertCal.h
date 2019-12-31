//TEnv *calib =new TEnv("configCalibESPRI_Be12.prm");

TEnv *calib;
class ESPRIRdcCal{
	private:
		double rdcChi2[2];
		double rdcDL[2][7];
		double rdcTch[2][7];
		double rdcRes[2][7];

		double rdcX[2];
		double rdcY[2];
		double rdcA[2];
		double rdcB[2];
	public:
		ESPRIRdcCal(){}
		void convertCal(ESPRITdcRaw *rdcRaw){
		}
		void init(){
			for(int i=0;i<2;i++){
				rdcX[i]=-9999;
				rdcY[i]=-9999;
				rdcA[i]=-9999;
				rdcB[i]=-9999;
				rdcChi2[i]=-9999;
				for(int j=0;j<7;j++){
					rdcDL[i][j]=-9999;	
					rdcTch[i][j]=-9999;	
					rdcRes[i][j]=-9999;	
				}
			}
		}
		void readReconstructedData(TClonesArray *rdcArray){
			init();
			for(int i=0;i<rdcArray->GetEntries();i++){
				TArtRDC *rdc = (TArtRDC*)rdcArray->At(i);
				setCalibratedRdc(rdc);
				setTrackCheck(rdc);
			}
		}
		void setTrackCheck(TArtRDC *rdc){

			if(rdc->GetRDCX()>-1&&rdc->GetRDCY()>-1){
				rdcChi2[rdc->GetLayer()-1]= rdc->GetCHI2();
				rdc->GetRes(rdcRes[rdc->GetLayer()-1]);
				rdc->GetDrf(rdcDL[rdc->GetLayer()-1]);
				rdc->GetTch(rdcTch[rdc->GetLayer()-1]);
				//cout<<"Chi2="<<rdc->GetCHI2()<<" Res1="<<rdcRes[rdc->GetLayer()-1][1]<<" Drf1="<<rdcDL[rdc->GetLayer()-1][1]<<endl;
			}	
		}
		void setCalibratedRdc(TArtRDC *rdc){
			if(rdc){
				if(rdc->GetLayer()>0 && rdc->GetLayer()<3) {
					// ESPRI_RDC_Side=rdc->GetLayer();
					rdcX[rdc->GetLayer()-1]=rdc->GetRDCX();
					rdcA[rdc->GetLayer()-1]=rdc->GetRDCA();
					rdcY[rdc->GetLayer()-1]=rdc->GetRDCY();
					rdcB[rdc->GetLayer()-1]=rdc->GetRDCB();
					
				}
			}

		}

		void setBranch(TTree *tree){
			tree->Branch("rdcX",rdcX,"rdcX[2]/D");
			tree->Branch("rdcY",rdcY,"rdcY[2]/D");
			tree->Branch("rdcA",rdcA,"rdcA[2]/D");
			tree->Branch("rdcB",rdcB,"rdcB[2]/D");
			tree->Branch("rdcChi2",rdcChi2,"rdcChi2[2]/D");
			tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
			tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
			tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");
		}
		void print(){

			cout<<"Left RDC: "<<rdcX[0]<<" "<<rdcY[0]<<endl;
			cout<<"Right RDC:"<<rdcX[1]<<" "<<rdcY[1]<<endl;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					cout<<"i = "<<i<<" j = "<<j<<"\t"<<" ch = "<<"\t"<<rdcTch[i][j]<<"\t"<<" dl = "<<"\t"<<rdcDL[i][j]<<endl;
				}
			}
		}
};
class ESPRINaiCalPara{
	private:
		double naiPedestal[4][7];
	public:
		ESPRINaiCalPara(){
			init();
			load();
			print();
		}
		void load(){
			loadPedestal();
		}
		void loadPedestal(){
			ifstream in;
			TString inputName = calib->GetValue("naiPedestal","naiPedestal.txt");
			cout<<calibFileName<<endl;
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double ped;
			while(1){
				in >>side>>barID>>ped;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiPedestal[side][barID] = ped;
			}
			in.close();
		}
		void print(){
			cout<<" Nai QCal Pedestal Para:"<<endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 7; ++j) {
						
					cout<<i<<":"<<j<<":"<<naiPedestal[i][j]<<endl;
				}
			}	
		}
		~ESPRINaiCalPara(){}
		void init(){
			for(int i =0;i<4;i++){
				for(int j = 0;j<7;j++){
					naiPedestal[i][j] = 0;
				}
			}
		}
		double getPedestal(int i, int j){
			return naiPedestal[i][j];
		}
};
class ESPRINaiCal{
	private:
		int runNumber;
		ESPRINaiRaw *naiRaw;
		ESPRINaiCalPara *naiPara;

		int naiHit;
		int naiSide[5];// Maximum 5 bar Hit
		int naiBarId[5];
		double naiHitQPed[5];

		double naiQPed[4][7];
		double naiBarQPed[2][7]; // Magnet

		void setQPed(){
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					if(getQRaw(i,j)!=-9999){
						naiQPed[i][j] = getQRaw(i,j) - getPedestal(i,j);
					}
				}
			}

		}
		void setBarQPed(){
			double naiQPedTh = 50;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					if(naiQPed[2*i][j]>0&&naiQPed[2*i+1][j]>0){
						naiBarQPed[i][j]= sqrt(naiQPed[2*i][j]*naiQPed[2*i+1][j]);
						if(naiBarQPed[i][j]>naiQPedTh){
							naiSide[naiHit] = i;
							naiBarId[naiHit] = j;
							naiHitQPed[naiHit] = naiBarQPed[i][j];
							naiHit++;
						}
					}
				}
			}
		}
		double getQRaw(int i,int j){
			return naiRaw->getQRaw(i,j);
		}
		double getPedestal(int i,int j){
			return naiPara->getPedestal(i,j);
		}

	public:

		ESPRINaiCal(){
			naiPara = new ESPRINaiCalPara();
		}
		~ESPRINaiCal(){
			delete naiPara;
		}
		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void init(){
			naiRaw = NULL;

			naiHit = 0;
			for (int i = 0; i < 5; ++i) {
				naiSide[i] = -1;	
				naiBarId[i] = -1;	
				naiHitQPed[i] = -9999;	
			}
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					naiQPed[i][j] = -9999;
					if(i%2==0){
						naiBarQPed[i/2][j] = -9999;
					}
				}
			}
		}
		void convertCal(ESPRINaiRaw *raw){
			init();
			naiRaw = raw;
			setQPed();
			setBarQPed();
			//printRawQ();
			//printQ();
		}
		void print(){

			//naiRaw->printQ();
			//cout<<"Nai QPed:"<<endl;
			//for (int i = 0; i < 2; ++i) {
			//	for (int j = 0; j < 7; ++j) {
			//		cout<<i<<" "<<j<<" "<<naiQPed[2*i][j]<<" "<<naiQPed[2*i+1][j]<<" "<<naiBarQPed[i][j]<<endl;
			//	}
			//}
			for (int i = 0; i < naiHit; ++i) {
				cout<<"naiQ Hit"<<i<<endl;	
				cout<<naiSide[i]<<" "<<naiBarId[i]<<" "<<naiHitQPed[i]<<endl;	
			}

		}
		void setBranch(TTree *tree){
				
			tree->Branch("naiHit", &naiHit, "naiHit/I");
			tree->Branch("naiSide", naiSide, "naiSide[naiHit]/I");
			tree->Branch("naiBarId", naiBarId, "naiBarId[naiHit]/I");
			tree->Branch("naiHitQPed", naiHitQPed, "naiHitQPed[naiHit]/I");

			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
			tree->Branch("naiBarQPed", naiBarQPed, "naiBarQPed[2][7]/D");
		}
};

class ESPRIPlasCalPara{
	private: 
		double plasPedestal[4];
		double plasPedSigma[4];

	public:
		ESPRIPlasCalPara(){
			init();
			load();
			print();
		}
		void init(){
			for (int i = 0; i < 4; ++i) {
				plasPedestal[i] = 0;	
				plasPedSigma[i] = 0;	
			}
		}
		double getPedestal(int i){
			return plasPedestal[i];
		}
		void load(){
			ifstream in;
			TString inputName = calib->GetValue("plasPedestal","plasPedestal.txt");
			in.open(inputName);
			int side;
			double ped;
			double sigma;
			while(1){
				in >>side>>ped>>sigma;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				plasPedestal[side] = ped;
				plasPedSigma[side] = sigma;
			}

		}
		void print(){
			cout<<"Plas Pedestal Para:"<<endl;		
			for (int i = 0; i < 4; ++i) {
				cout<<i<<"Pedestal = "<<plasPedestal[i]<<" Sigma = "<<plasPedSigma[i]<<endl;
			}
		}
		
};
class ESPRIPlasCal{
	private:
		int runNumber;
		ESPRIPlasRaw *plasRaw;
		ESPRIPlasCalPara *plasPara;
	
		double plasTRef[4];	
		double plasTCal[4];	

		double plasQPed[4];
		double plasBarQPed[2];

		int plasHit;
		int plasSide[2];

		double getTCalSlope(int i){
			return 0.025;
		}

		int getTRaw(int i){
			return plasRaw->getTRaw(i);
		}
		double getPlasTimeRef(){
			return plasRaw->getPlasTimeRef();
		}


		void setPlasQ(int side){
			double plasHitTh = 50;
			if(plasQPed[2*side]>0&&plasQPed[2*side+1]>0){
				plasBarQPed[side] = sqrt(plasQPed[2*side]*plasQPed[2*side+1]);
				if(plasBarQPed[side]>plasHitTh){
					plasSide[plasHit] = side;
					plasHit++;
				}
			}
		}
		void setPlasQL(){
			setPlasQ(0);
		}
		void setPlasQR(){
			setPlasQ(1);
		}
		double getQRaw(int i){
			return plasRaw->getQRaw(i);
		}
		double getPedestal(int i){
			return plasPara->getPedestal(i);
		}

	public:

		ESPRIPlasCal(){
			plasPara = new ESPRIPlasCalPara();
		}
		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void init(){

			plasHit = 0;
			plasSide[0] = -1;
			plasSide[1] = -1;

			plasBarQPed[0] = -9999;
			plasBarQPed[1] = -9999;

			for(int i=0;i<4;i++){
				plasQPed[i] = -9999;
				plasTRef[i] = -9999;
				plasTCal[i] = -9999;
			}
		}
		void convertCal(ESPRIPlasRaw *raw){
			init();
			plasRaw = raw;
			calibrateQ();
			calibrateT();
		}
		void calibrateT(){
			for(int i=0;i<4;i++){
				if(getTRaw(i) == 0 ||getTRaw(i) == -1||getTRaw(i) == -9999) continue;
				plasTRef[i] = getTRaw(i) - getPlasTimeRef();
				plasTCal[i] = getTCalSlope(i)*plasTRef[i];
			}
		}
		void calibrateQ(){
			//plasRaw->printQ();
			for(int i=0;i<4;i++){
				if(getQRaw(i)!=-9999) {
					plasQPed[i] = (getQRaw(i) - getPedestal(i));
				}
			}
			setPlasQL();
			setPlasQR();
			//printQ();
		}
		void printQ(){
			cout<<"PlasBarQPed[2]: ";
			for(int i=0;i<2;i++){
				cout<<plasBarQPed[i]<<":";
			}
			cout<<endl;
		}
		void printT(){
			cout<<"Plastic TCal[4]: ";
			for(int i=0;i<4;i++){
				cout<<plasTCal[i]<<":";
			}
			cout<<endl;
		}
		void print(){
			for (int i = 0; i < plasHit; ++i) {
				//plasRaw->print();
				cout<<" Plas Hit"<<i<<endl;
				int side = plasSide[i];
				cout<<"Side = "<<side<<" QPed = "<<plasBarQPed[plasSide[i]]<<" TCal = "<<plasTCal[2*i]<<" : "<<plasTCal[2*i+1]<<endl;
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("plasHit",&plasHit,"plasHit/I");
			tree->Branch("plasSide",plasSide,"plasSide[plasHit]/I");

			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
			tree->Branch("plasBarQPed",plasBarQPed,"plasBarQPed[2]/D");
			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");
			tree->Branch("plasTRef",plasTRef,"plasTRef[4]/D");

		}
};
class ESPRIConvertCal{
	private:
		int runNumber;
		ESPRIRdcCal *rdcCal;
		ESPRINaiCal *naiCal;
		ESPRIPlasCal *plasCal;
	public:

		ESPRIConvertCal(){
			cout<<"Create: rdcCal:naiCal:plasCal"<<endl;
			rdcCal	 = new ESPRIRdcCal();
			naiCal	 = new ESPRINaiCal();
			plasCal	 = new ESPRIPlasCal();
		}
		~ESPRIConvertCal(){
			delete rdcCal;
			delete naiCal;
			delete plasCal;
		}

		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void convertCal(ESPRIReadRaw *espriRaw){
			rdcCal->convertCal(espriRaw->getTdcRaw());

			naiCal->updateRunNumber(runNumber);
			naiCal->convertCal(espriRaw->getNaiRaw());

			plasCal->updateRunNumber(runNumber);
			plasCal->convertCal(espriRaw->getPlasRaw());
		}
		void readReconstructedData(TClonesArray *rdcArray){
			rdcCal->readReconstructedData(rdcArray);
		}

		void setBranch(TTree *tree){
			rdcCal->setBranch(tree);
			naiCal->setBranch(tree); 
			plasCal->setBranch(tree);
		}
		void printRdc(){
			rdcCal->print();
		}
	
		void printPlas(){
			plasCal->print();
		}
		void printNai(){
			naiCal->print();
		}

};
