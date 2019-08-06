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
		int rdcMult;
	public:
		ESPRIRdcCal(){}
		void convertCal(ESPRIRdcRaw *rdcRaw){
		}
		void init(){
			rdcMult = 0;
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
			rdcChi2[rdc->GetLayer()-1]= rdc->GetCHI2();
			rdc->GetRes(rdcRes[rdc->GetLayer()-1]);
			rdc->GetDrf(rdcDL[rdc->GetLayer()-1]);
			rdc->GetTch(rdcTch[rdc->GetLayer()-1]);
			//cout<<"Chi2="<<rdc->GetCHI2()<<" Res1="<<rdcRes[rdc->GetLayer()-1][1]<<" Drf1="<<rdcDL[rdc->GetLayer()-1][1]<<endl;
			
		}
		void setCalibratedRdc(TArtRDC *rdc){
			if(rdc){
				if(rdc->GetLayer()>0 && rdc->GetLayer()<3) {
					// ESPRI_RDC_Side=rdc->GetLayer();
					rdcX[rdc->GetLayer()-1]=rdc->GetRDCX();
					rdcA[rdc->GetLayer()-1]=rdc->GetRDCA();
					rdcY[rdc->GetLayer()-1]=rdc->GetRDCY();
					rdcB[rdc->GetLayer()-1]=rdc->GetRDCB();
					rdcMult++;
					
					//cout<<"Calibrated: Layer ="<<rdc->GetLayer()<<" x="<<rdc->GetRDCX()<<" Y="<<rdc->GetRDCY()<<endl;
				}
			}

		}

		void setBranch(TTree *tree){
			tree->Branch("rdcMult",rdcMult,"rdcMult/I");
			tree->Branch("rdcX",rdcX,"rdcX[2]/D");
			tree->Branch("rdcY",rdcY,"rdcY[2]/D");
			tree->Branch("rdcA",rdcA,"rdcA[2]/D");
			tree->Branch("rdcB",rdcB,"rdcB[2]/D");
			tree->Branch("rdcChi2",rdcChi2,"rdcChi2[2]/D");
			tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
			tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
			tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");
			
		}
};
class ESPRINaiCalPara{
	private:
		double naiPedestal[4][7];
		double naiBarGain[2][7];
		double naiPol3P0[2][7];
		double naiPol3P1[2][7];
		double naiPol3P2[2][7];
	public:
		ESPRINaiCalPara(){
			init();
			load();
			print();
		}
		void load(){
			loadPedestal();
			loadGain();
			loadPol3Gain();
		}
		void loadPol3Gain(){
			ifstream in;
			TString inputName = calib->GetValue("naiPol3Calib","naiPol3Calib.txt");
			cout<<calibFileName<<endl;
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double p0;
			double p1;
			double p2;
			while(1){
				in >>side>>barID>>p0>>p1>>p2;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiPol3P0[side][barID] = p0;
				naiPol3P1[side][barID] = p1;
				naiPol3P2[side][barID] = p2;
			}

		}
		void loadGain(){
			ifstream in;
			TString inputName = calib->GetValue("naiBarGain","naiBarGain.txt");
			cout<<calibFileName<<endl;
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double gain;
			while(1){
				in >>side>>barID>>gain;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				naiBarGain[side][barID] = gain;
			}
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
		}
		void print(){
			cout<<" Nai QCal Pedestal Para:"<<endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 7; ++j) {
						
					cout<<i<<":"<<j<<":"<<naiPedestal[i][j]<<endl;
				}
			}	
			cout<<" Nai QCal Gain Para:"<<endl;
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
						
					cout<<i<<":"<<j<<":"<<naiBarGain[i][j]<<endl;
				}
			}	

		}
		~ESPRINaiCalPara(){}
		void init(){
			for(int i =0;i<4;i++){
				for(int j = 0;j<7;j++){
					naiPedestal[i][j] = 0;
					if(i<2){
						naiBarGain[i][j] = 1;
						naiPol3P0[i][j] = 1;
						naiPol3P1[i][j] = 0;
						naiPol3P2[i][j] = 0;
					}
				}
			}
		}
		double getPedestal(int i, int j){
			return naiPedestal[i][j];
		}
		double getBarGain(int i, int j){
			return naiBarGain[i][j];
		}
		double getPol3P0(int i, int j){
			return naiPol3P0[i][j];
		}
		double getPol3P1(int i, int j){
			return naiPol3P1[i][j];
		}
		double getPol3P2(int i, int j){
			return naiPol3P2[i][j];
		}
};
class ESPRINaiCal{
	private:
		ESPRINaiRaw *naiRaw;
		ESPRINaiCalPara *naiPara;

		double naiQCal[4][7];
		double naiQPed[4][7];
		double naiBarQCal[2][7];
		//double naiBarQPed[2][7];
		double naiQ[2];
		int    naiQId[2];
	public:

		ESPRINaiCal(){
			naiPara = new ESPRINaiCalPara();
		}
		~ESPRINaiCal(){
			delete naiPara;
		}
		void init(){
			naiQ[0] = -9999;
			naiQ[1] = -9999;
			naiQId[0] = -1;
			naiQId[1] = -1;
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					naiQCal[i][j] = -9999;
					naiQPed[i][j] = -9999;
					if(i%2==0) naiBarQCal[i/2][j] = -9999;
				}
			}
		}
		void convertCal(ESPRINaiRaw *raw){
			init();
			naiRaw = raw;
			calibrateQ();
			setNaiBarQ();
			setESPRISideQL();
			setESPRISideQR();

			//printRawQ();
			//printQ();

		}
		void setESPRISideQL(){
			setESPRISideQ(0);
		}
		void setESPRISideQR(){
			setESPRISideQ(1);
		}
		void setESPRISideQ(int side){
			double max = -9999;
			for (int i = 0; i < 7; ++i) {
				if(naiBarQCal[side][i]> max){
					max = naiBarQCal[side][i];
					naiQId[side] = i;
				}
			}
			naiQ[side] = max;
		}
		void calibrateQ(){
			for(int i=0;i<4;i++){
				for(int j=0;j<7;j++){
					naiQPed[i][j] = getQRaw(i,j) - getPedestal(i,j);
					naiQCal[i][j] = getCalibPar(i,j)*naiQPed[i][j];
				}
			}

		}
		double getCalibPar(int i,int j){
			return 1;
		}
		double getQRaw(int i,int j){
			return naiRaw->getQRaw(i,j);
		}
		double getPedestal(int i,int j){
			return naiPara->getPedestal(i,j);
		}
		double getBarGain(int i,int j){
			return naiPara->getBarGain(i,j);
		}
		double linearCalibNaiBar(int i,int j,double ped){
			return getBarGain(i,j)*ped;
		}
		double getPol3P0(int i,int j){
			return naiPara->getPol3P0(i,j);
		}
		double getPol3P1(int i,int j){
			return naiPara->getPol3P1(i,j);
		}
		double getPol3P2(int i,int j){
			return naiPara->getPol3P2(i,j);
		}
		double pol3CalibNaiBar(int i,int j,double ped){

			//cout<<i<<":"<<j<<":"<<ped<<":"<<getPol3P0(i,j)<<":"<<getPol3P1(i,j)<<":"<<getPol3P2(i,j)<<":"<<endl;
			return getPol3P0(i,j)*ped + getPol3P1(i,j)*ped*ped+getPol3P2(i,j)*ped*ped*ped;
		}

		void setNaiBarQ(){
			for (int i = 0; i < 2; ++ i) {
				for (int j = 0; j < 7; ++ j) {

					//if(naiQCal[i*2][j]>0&&naiQCal[i*2+1][j]>0)  naiBarQCal[i][j] = sqrt(naiQCal[i*2][j]*naiQCal[i*2+1][j]);
					//if(naiQPed[i*2][j]>0&&naiQPed[i*2+1][j]>0)  naiBarQCal[i][j] = getBarGain(i,j)*sqrt(naiQPed[i*2][j]*naiQPed[i*2+1][j]);
					//if(naiQPed[i*2][j]>0&&naiQPed[i*2+1][j]>0)  naiBarQCal[i][j] = linearCalibNaiBar(i,j,sqrt(naiQPed[i*2][j]*naiQPed[i*2+1][j]));
					if(naiQPed[i*2][j]>0&&naiQPed[i*2+1][j]>0)  naiBarQCal[i][j] = pol3CalibNaiBar(i,j,sqrt(naiQPed[i*2][j]*naiQPed[i*2+1][j]));

				}
			}
		}

		void printQ(){
			cout<<"Nai Cal[4][7]:"<<endl;
			for(int i=0;i<4;i++)
				for(int j=0;j<7;j++){
		
					cout<<i<<" "<<j<<" "<<naiQCal[i][j]<<endl;
				}
			cout<<"Nai QL/R:"<<naiQ[0]<<":"<<naiQ[1]<<endl;

		}
		void printRawQ(){
			naiRaw->printQ();
		}
		void setBranch(TTree *tree){
			tree->Branch("naiQCal", naiQCal, "naiQCal[4][7]/D");
			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
			tree->Branch("naiBarQCal", naiBarQCal, "naiBarQCal[2][7]/D");

			tree->Branch("naiQ", &naiQ, "naiQ[2]/D");
			tree->Branch("naiQId", &naiQId, "naiQId[2]/I");

		}
};

class ESPRIPlasCalPara{
	private: 
		double plasPedestal[4];
		double plasGain[4];

		double plasBirksParA[2];
		double plasBirksParB[2];

	public:
		ESPRIPlasCalPara(){
			init();
			load();
			loadBirksPara();
			print();
		}
		double getPedestal(int i){
			return plasPedestal[i];
		}
		double getCalibPar(int i){
			return plasGain[i];
		}
		void load(){
			ifstream in;
			TString inputName = calib->GetValue("plasCalib","plasCalib.txt");
			in.open(inputName);
			int side;
			double ped;
			double gain;
			while(1){
				in >>side>>ped>>gain;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				plasPedestal[side] = ped;
				plasGain[side] = gain;
			}

		}
		double getBirksParA(int i){
			return plasBirksParA[i];
		}
		double getBirksParB(int i){
			return plasBirksParB[i];
		}
		void loadBirksPara(){
			ifstream in;
			TString inputName = calib->GetValue("plasBirksCalib","plasBirksCalib.txt");
			in.open(inputName);
			int side;
			double parA;
			double parB;
			while(1){
				in >>side>>parA>>parB;
				if(!in.good()) break;
				//cout<<side<<":"<<barID<<":"<<ped<<endl;
				plasBirksParA[side] = parA;
				plasBirksParB[side] = parB;
			}

		}
		void init(){

			plasBirksParA[0] = NAN;
			plasBirksParA[1] = NAN;
			plasBirksParB[0] = NAN;
			plasBirksParB[1] = NAN;

			for (int i = 0; i < 4; ++i) {

				plasPedestal[i] = 0;
				plasGain[i] = 1;
			}
		}
		void print(){
			cout<<"Plas QCal Para:"<<endl;		
			for (int i = 0; i < 4; ++i) {
				cout<<i<<":"<<plasPedestal[i]<<":"<<plasGain[i]<<endl;
			}

			cout<<"Plas Birks Para:"<<endl;		
			for (int i = 0; i < 2; ++i) {
				cout<<i<<":"<<plasBirksParA[i]<<":"<<plasBirksParB[i]<<endl;
			}
		}
		
};
class ESPRIPlasCal{
	private:
		ESPRIPlasRaw *plasRaw;
		ESPRIPlasCalPara *plasPara;
		
		double plasQCal[4];	
		double plasQPed[4];
		double plasTCal[4];	
		double plasQ[2];
		double plasT[2];
	//	double plasQL;
	//	double plasQR;
	//	double plasTL;
	//	double plasTR;

	public:

		ESPRIPlasCal(){
			plasPara = new ESPRIPlasCalPara();
		}
		void init(){
			plasQ[0] = -9999;
			plasQ[1] = -9999;
			plasT[0] = 0;
			plasT[1] = 0;

			for(int i=0;i<4;i++){
				plasQCal[i] = -9999;
				plasQPed[i] = -9999;
				plasTCal[i] = 0;
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
				if(getTRaw(i) == 0 ||getTRaw(i) == -1) continue;
				plasTCal[i] = getTRaw(i) - getPlasTimeRef();
				plasTCal[i] = getTCalSlope(i)*plasTCal[i] - getTCalOffset(i);
			}
			setPlasTL();
			setPlasTR();
			//plasRaw->printT();
			//printT();

		}
		double getTCalSlope(int i){
			return 0.025;
		}
		int getTRaw(int i){
			return plasRaw->getTRaw(i);
		}
		double getPlasTimeRef(){
			return plasRaw->getPlasTimeRef();
		}
		double getTCalOffset(int i){
			return 0;
		}
		void setPlasTL(){
			setPlasT(0);
		}
		void setPlasTR(){
			setPlasT(1);
		}
		void setPlasT(int side){
			if(getTRaw(2*side)!=0 && getTRaw(2*side+1)!=0 ){
				plasT[side] = 0.5*(plasTCal[2*side]+plasTCal[2*side+1]);
			}else if(getTRaw(2*side)==0 && getTRaw(2*side+1)!=0 ){
				plasT[side] = plasTCal[2*side+1];
			}else if(getTRaw(2*side+1)==0 && getTRaw(2*side)!=0 ){
				plasT[side] = plasTCal[2*side];
			}else{
			}
		}
		void calibrateQ(){
			//plasRaw->printQ();
			for(int i=0;i<4;i++){
				plasQPed[i] = (getQRaw(i) - getPedestal(i));
				plasQCal[i] = getCalibPar(i)*plasQPed[i];
			}
			setPlasQL();
			setPlasQR();
			//printQ();
		}
		void setPlasQL(){
			if(plasQPed[0]>0&&plasQPed[1]>0) plasQ[0] = sqrt(plasQPed[0]*plasQPed[1])/(getBirksParA(0)+getBirksParB(0)*sqrt(plasQPed[0]*plasQPed[1]));
		}
		void setPlasQR(){
			if(plasQPed[2]>0&&plasQPed[3]>0) plasQ[1] = sqrt(plasQPed[2]*plasQPed[3])/(getBirksParA(1)+getBirksParB(1)*sqrt(plasQPed[2]*plasQPed[3]));
		}
		double getQRaw(int i){
			return plasRaw->getQRaw(i);
		}
		double getPedestal(int i){
		//	double QPed[4] = {118.9,140.2,135.1,64.4};
		//	return QPed[i];
			return plasPara->getPedestal(i);
		}
		double getCalibPar(int i){
		//	double QCal[4] = {0.005481292918,0.008481058508,0.008006974455,0.008363636921};// gu gd left, gu gd right
		//	return QCal[i];
			return plasPara->getCalibPar(i);
		}
		double getBirksParA(int i){
			return plasPara->getBirksParA(i);
		}
		double getBirksParB(int i){
			return plasPara->getBirksParB(i);
		}

		void printQ(){
			cout<<"Plastic QCal[4]: ";
			for(int i=0;i<4;i++){
				cout<<plasQCal[i]<<":";
			}
			cout<<endl;
			cout<<"Plastic QL/R: "<<plasQ[0]<<":"<<plasQ[1]<<endl;
		}
		void printT(){
			cout<<"Plastic TCal[4]: ";
			for(int i=0;i<4;i++){
				cout<<plasTCal[i]<<":";
			}
			cout<<endl;
			cout<<"Plastic TL/R: "<<plasT[0]<<":"<<plasT[1]<<endl;
		}
		void setBranch(TTree *tree){
			tree->Branch("plasQCal",plasQCal,"plasQCal[4]/D");
			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");
			tree->Branch("plasQ",plasQ,"plasQ[2]/D");
			tree->Branch("plasT",plasT,"plasT[2]/D");

		}
};
class ESPRIConvertCal{
	private:
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

		void convertCal(ESPRIReadRaw *espriRaw){
			rdcCal->convertCal(espriRaw->getRdcRaw());
			naiCal->convertCal(espriRaw->getNaiRaw());
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
};
