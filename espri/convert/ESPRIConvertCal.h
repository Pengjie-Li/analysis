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
		void convertCal(ESPRITdcRaw *rdcRaw){
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
					rdcMult++;
					
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
class ESPRIConvertCal{
	private:
		int runNumber;
		ESPRIRdcCal *rdcCal;
	public:

		ESPRIConvertCal(){
			cout<<"Create: rdcCal:naiCal:plasCal"<<endl;
			rdcCal	 = new ESPRIRdcCal();
		}
		~ESPRIConvertCal(){
			delete rdcCal;
		}

		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void convertCal(ESPRIReadRaw *espriRaw){
			rdcCal->convertCal(espriRaw->getTdcRaw());
		}
		void readReconstructedData(TClonesArray *rdcArray){
			rdcCal->readReconstructedData(rdcArray);
		}

		void setBranch(TTree *tree){
			rdcCal->setBranch(tree);
		}
		void printRdc(){
			rdcCal->print();
		}
	
};
