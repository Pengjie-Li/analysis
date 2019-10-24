
class ESPRIRdcRaw{
	private:
                vector<int> rdcTDC;// for each hits, no matter layer, wireid
                vector<int> rdcPlaneID;// for each hits, no matter layer, wireid
                vector<int>	rdcPlaneNHit;// for each hits, no matter layer, wireid
                vector<int> rdcWireID;// for each hits, no matter layer, wireid
		int plasTimeRef;
		
	public:
		ESPRIRdcRaw(){}
		void init(){
			plasTimeRef = 0;
			rdcTDC.clear();
			rdcPlaneID.clear();
			rdcWireID.clear();
			//rdcLayerID.clear();
			rdcPlaneNHit.clear();
			rdcPlaneNHit.resize(14,0);
		}
		void readRaw(TClonesArray *tdcArray){
			init();
			for(int i=0;i<tdcArray->GetEntries();i++){
				TArtTDCHit *tdc = (TArtTDCHit *)tdcArray->At(i);
				//cout<<"RawData:"<<tdc->GetPlaneID()<<" "<<tdc->GetLayer()<<" "<<tdc->GetWireID()<<" "<<tdc->GetTDC()<<" "<<tdc->GetTrailTDC()<<endl;
				//cout<<"RawData:\t"<<tdc->GetPlaneID()<<"\t"<<tdc->GetLayer()<<"\t"<<tdc->GetWireID()<<"\t"<<tdc->GetTDC()<<endl;
				if(tdc->GetPlaneID()==0){
					plasTimeRef = tdc->GetTDC();
					continue;
				}
				int planeId=tdc->GetPlaneID()-17;
				//int planeId=tdc->GetPlaneID();
				int layerId=tdc->GetLayer();
				int wireId=tdc->GetWireID();
				int TDC = tdc->GetTDC();
				rdcTDC.push_back(TDC);
				rdcPlaneID.push_back(planeId);
				rdcWireID.push_back(wireId);
				if(planeId>=0&&planeId<14){
				 	rdcPlaneNHit[planeId]+=1;
					//cout<<"NHit:"<<planeId<<":"<<rdcPlaneNHit[planeId]<<endl;
				}

			}
		}
		int getPlasTimeRef(){
			return plasTimeRef;
		}
		
		void setBranch(TTree *tree){
			tree->Branch("rdcTDC",&rdcTDC);
			tree->Branch("rdcPlaneID",&rdcPlaneID);
			//tree->Branch("rdcLayerID",&rdcLayerID);
			tree->Branch("rdcWireID",&rdcWireID);
			tree->Branch("rdcPlaneNHit",&rdcPlaneNHit);
		}
};
class ESPRINaiRaw{
	/**
	 * NaI time =-1, s12 don't use TDC for NaI
	 */
	private:
		int naiQRaw[4][7];// 0:LL, 1:LR, 2:RL,3:RR no need to save ID
		int naiMult[4];
		
	public:
		ESPRINaiRaw(){}
		void init(){
			for(int i=0;i<4;i++)
				for(int j=0;j<7;j++){
					naiQRaw[i][j]=-9999;
				}
		}
		void printQ(){
			cout<<"Nai Raw[4][7]:"<<endl;
			for(int i=0;i<4;i++)
				for(int j=0;j<7;j++){
					cout<<i<<" "<<j<<" "<<naiQRaw[i][j]<<endl;;
				}
		}

		void readRaw(TClonesArray *naiArray){
			init();
			for(int i=0;i<naiArray->GetEntries();i++){
				TArtRNaI *nai = (TArtRNaI*)naiArray->At(i);
				{
					//cout<<nai->GetID()<<" "<<nai->GetLayer()<<" "<<nai->GetRawADC()<<endl; 
					//cout<<endl;

					int ID=nai->GetID();
					int layer=nai->GetLayer();
					int ADC=nai->GetRawADC();

					if(layer==1&&ID%2==0){
						naiQRaw[0][(ID-2)/2]=ADC;
						naiMult[0]++;
					}else if(layer==1&&ID%2==1){
						naiQRaw[1][(ID-1)/2]=ADC;
						naiMult[1]++;
					}else if(layer==2&&ID%2==0){
						naiQRaw[2][(ID-16)/2]=ADC;
						naiMult[2]++;
					}else{
						naiQRaw[3][(ID-15)/2]=ADC;
						naiMult[3]++;
					}
				}
			}
			//print();
		}
		int getQRaw(int i,int j){
			return naiQRaw[i][j];
		}
		void setBranch(TTree *tree){
			tree->Branch("naiQRaw",naiQRaw,"naiQRaw[4][7]/I");
		}
};
class ESPRIPlasRaw{
	private:
		int plasQRaw[4];// 0:LU, 1:LD, 2:RU, 3:RD
		int plasTRaw[4];
		int plasTimeRef;
	public:
		ESPRIPlasRaw(){}
		void init(){
			plasTimeRef = 0;
			for(int i=0;i<4;i++){
				plasQRaw[i] = -9999;
				plasTRaw[i] = 0;
			}
		}

		void printQ(){
			cout<<"Plastic QRaw[4]: ";
			for(int i=0;i<4;i++){
				cout<<plasQRaw[i]<<":";
			}
			cout<<endl;
		}
		void printT(){
			cout<<"Plastic TRaw[4]: ";
			for(int i=0;i<4;i++){
				cout<<plasTRaw[i]<<":";
			}
			cout<<endl;
			cout<<"Time Ref: "<<plasTimeRef<<endl;
		}
		void print(){
			printQ();
			printT();
		}
		void readRaw(TClonesArray *plasArray){
			init();
			//cout<<endl;
			for(int i=0;i<plasArray->GetEntries();i++){
				TArtPlas *plas = (TArtPlas*)plasArray->At(i);
				//cout << plas->GetPlaneID() <<" "<< plas->GetLayer()<<" "<<plas->GetRawADC()<<" "<<plas->GetTime() << endl; 
				int ID= plas->GetID();
				int layer = plas->GetLayer();
				int ADC = plas->GetRawADC();
				int TDC = plas->GetTime();
				plasQRaw[ID-1]=ADC;
				plasTRaw[ID-1]=TDC;
			}
		}
		void setPlasTimeRef(int ref){
			plasTimeRef = ref;
		}
		int getPlasTimeRef(){
			return plasTimeRef;
		}
		int getQRaw(int i){
			return plasQRaw[i];
		}
		int getTRaw(int i){
			return plasTRaw[i];
		}

		void setBranch(TTree *tree){
			tree->Branch("plasQRaw",plasQRaw,"plasQRaw[4]/I");
			tree->Branch("plasTRaw",plasTRaw,"plasTRaw[4]/I");
			tree->Branch("plasTimeRef",&plasTimeRef,"plasTimeRef/I");
		}
};

class ESPRIReadRaw{
	private:
		ESPRIRdcRaw *rdcRaw;
		ESPRINaiRaw *naiRaw;
		ESPRIPlasRaw *plasRaw;
	public:

		ESPRIReadRaw(){
			rdcRaw	 = new ESPRIRdcRaw();
			naiRaw	 = new ESPRINaiRaw();
			plasRaw	 = new ESPRIPlasRaw();
		}
		~ESPRIReadRaw(){
			delete rdcRaw;
			delete naiRaw;
			delete plasRaw;
		}

		void readRaw(TClonesArray *rdc,TClonesArray *nai,TClonesArray *plas){
			rdcRaw->readRaw(rdc);
			naiRaw->readRaw(nai);
			plasRaw->readRaw(plas);
			plasRaw->setPlasTimeRef(getPlasTimeRef());
		}
		ESPRIRdcRaw * getRdcRaw(){
			return rdcRaw;
		}
		ESPRINaiRaw * getNaiRaw(){
			return naiRaw;
		}
		ESPRIPlasRaw * getPlasRaw(){
			return plasRaw;
		}
		int getPlasTimeRef(){
			return rdcRaw->getPlasTimeRef();
		}
	
		void setBranch(TTree *tree){
			rdcRaw->setBranch(tree);
			naiRaw->setBranch(tree); 
			plasRaw->setBranch(tree);
		}
};

