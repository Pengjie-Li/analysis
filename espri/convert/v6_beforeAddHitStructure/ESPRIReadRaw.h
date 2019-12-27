
class ESPRITdcRaw{
	private:
                vector<int> tdc;// for each hits, no matter layer, wireid
                vector<int> tdcWireId;// for each hits, no matter layer, wireid
                vector<int> tdcLayerId;// for each hits, no matter layer, wireid
                vector<int> tdcPlaneId;// for each hits, no matter layer, wireid
                vector<int> tdcPlaneNHit;// for each hits, no matter layer, wireid

		vector<int> rdcTdc;// for each hits, no matter layer, wireid
                vector<int> rdcWireId;// for each hits, no matter layer, wireid
                vector<int> rdcLayerId;// for each hits, no matter layer, wireid
                vector<int> rdcPlaneId;// for each hits, no matter layer, wireid
                vector<int> rdcPlaneNHit;// for each hits, no matter layer, wireid


		int plasTimeRef;
		vector<vector<int> > plasTRaw;

		
	public:
		ESPRITdcRaw(){
			plasTRaw.resize(4);
		}
		void init(){
			plasTimeRef = 0;
			plasTRaw.clear();
			plasTRaw.resize(4);

			tdc.clear();
			tdcPlaneId.clear();
			tdcWireId.clear();
			tdcLayerId.clear();
			//tdcLayerId.clear();
			tdcPlaneNHit.clear();
			tdcPlaneNHit.resize(16,0);

			rdcTdc.clear();
			rdcPlaneId.clear();
			rdcWireId.clear();
			rdcLayerId.clear();
			rdcPlaneNHit.clear();
			rdcPlaneNHit.resize(14,0);

		}
		void readRaw(TClonesArray *tdcArray){
			init();
			for(int i=0;i<tdcArray->GetEntries();i++){
				TArtTDCHit *tdcHit = (TArtTDCHit *)tdcArray->At(i);
				//cout<<"RawData:"<<tdc->GetPlaneId()<<" "<<tdc->GetLayer()<<" "<<tdc->GetWireId()<<" "<<tdc->Get()<<" "<<tdc->GetTrail()<<endl;
				//cout<<"RawData:\t"<<tdc->GetPlaneId()<<"\t"<<tdc->GetLayer()<<"\t"<<tdc->GetWireId()<<"\t"<<tdc->Get()<<endl;
				if(tdcHit->GetPlaneID()==0){
					plasTimeRef = tdcHit->GetTDC();
					continue;
				}
				int planeId=tdcHit->GetPlaneID()-17;
				//int planeId=tdcHit->GetPlaneId();
				int layerId=tdcHit->GetLayer();
				int wireId=tdcHit->GetWireID();
				int tdcVal = tdcHit->GetTDC();
				tdc.push_back(tdcVal);
				tdcPlaneId.push_back(planeId);
				tdcWireId.push_back(wireId);
				tdcLayerId.push_back(layerId);
				tdcPlaneNHit[planeId]+=1;
				//cout<<"NHit:"<<planeId<<":"<<tdcPlaneNHit[planeId]<<endl;

				if(planeId>=0&&planeId<14){
					rdcTdc.push_back(tdcVal);
					rdcPlaneId.push_back(planeId);
					rdcWireId.push_back(wireId);
					rdcLayerId.push_back(layerId);
					rdcPlaneNHit[planeId]+=1;
				}else if(planeId==14){
					plasTRaw[wireId-1].push_back(tdcVal);
				}else if(planeId ==15){
					plasTRaw[wireId+1].push_back(tdcVal);
				}else{
					cout<<"planeId = "<<planeId<<endl;
				}

			}
		}
		int getPlasTimeRef(){
			return plasTimeRef;
		}
		vector<vector<int> > getPlasRaw(){
			return plasTRaw;
		}
		void printRDC(){

			cout<<"RDC TDC Raw Data:"<<endl;
			for (int i = 0; i < rdcTdc.size(); ++i) {
				cout<<"\t"<<rdcPlaneId[i]<<"\t"<<rdcLayerId[i]<<"\t"<<rdcWireId[i]<<"\t"<<rdcTdc[i]<<endl;
			}
		}
		void printPlas(){
			cout<<"Plas TDC Raw Data:"<<endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < plasTRaw[i].size(); j++) {
					cout<<"\t"<<i<<"\t"<<plasTRaw[i][j]<<endl;	
				}
			}
		}
		void print(){
			printRDC();
			//printPlas();
		}
		
		void setBranch(TTree *tree){
			tree->Branch("plasTdcRaw0",&plasTRaw[0]);
			tree->Branch("plasTdcRaw1",&plasTRaw[1]);
			tree->Branch("plasTdcRaw2",&plasTRaw[2]);
			tree->Branch("plasTdcRaw3",&plasTRaw[3]);
			tree->Branch("rdcTdc",&rdcTdc);
			tree->Branch("rdcPlaneId",&rdcPlaneId);
			tree->Branch("rdcWireId",&rdcWireId);
			tree->Branch("rdcLayerId",&rdcLayerId);
			tree->Branch("rdcPlaneNHit",&rdcPlaneNHit);
			//tree->Branch("plasTimeRef",&plasTimeRef);
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
			plasTimeRef = -9999;
			for(int i=0;i<4;i++){
				plasQRaw[i] = -9999;
				plasTRaw[i] = -9999;
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
		void readRaw(TClonesArray *plasArray,ESPRITdcRaw *tdcRaw){
			init();
			//cout<<endl;
			for(int i=0;i<plasArray->GetEntries();i++){
				TArtPlas *plas = (TArtPlas*)plasArray->At(i);
				//cout << plas->GetPlaneID() <<" "<< plas->GetLayer()<<" "<<plas->GetRawADC()<<" "<<plas->GetTime() << endl; 
				int ID= plas->GetID();
				int layer = plas->GetLayer();
				int ADC = plas->GetRawADC();
				//int TDC = plas->GetTime();
				plasQRaw[ID-1]=ADC;
				//plasTRaw[ID-1]=TDC;
			}
			plasTimeRef = tdcRaw->getPlasTimeRef();
			vector<vector<int> > tdcPlasRaw = tdcRaw->getPlasRaw();	
			for (int i = 0; i < tdcPlasRaw.size(); ++i) {
				for (int j = 0; j < tdcPlasRaw[i].size(); ++j) {
					//cout<<i<<":"<<j<<":"<<tdcPlasRaw[i][j]<<endl;	
					if(tdcPlasRaw[i].size() ==1) plasTRaw[i] = tdcPlasRaw[i][j];
					else if((tdcPlasRaw[i][j]-plasTimeRef)<-25600){
						plasTRaw[i] = tdcPlasRaw[i][j];
					}else {}
				}
				//cout<<"plasTRaw "<<i<<":"<<plasTRaw[i]<<endl;
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
		ESPRITdcRaw *tdcRaw;
		ESPRINaiRaw *naiRaw;
		ESPRIPlasRaw *plasRaw;
	public:

		ESPRIReadRaw(){
			tdcRaw	 = new ESPRITdcRaw();
			naiRaw	 = new ESPRINaiRaw();
			plasRaw	 = new ESPRIPlasRaw();
		}
		~ESPRIReadRaw(){
			delete tdcRaw;
			delete naiRaw;
			delete plasRaw;
		}

		void readRaw(TClonesArray *tdc,TClonesArray *nai,TClonesArray *plas){
			tdcRaw->readRaw(tdc);
			naiRaw->readRaw(nai);
			plasRaw->readRaw(plas,tdcRaw);
		}
		ESPRITdcRaw * getTdcRaw(){
			return tdcRaw;
		}
		ESPRINaiRaw * getNaiRaw(){
			return naiRaw;
		}
		ESPRIPlasRaw * getPlasRaw(){
			return plasRaw;
		}
		void printTDC(){
			tdcRaw->print();
		}
		void printPlas(){
			plasRaw->print();
		}
	
	
		void setBranch(TTree *tree){
			tdcRaw->setBranch(tree);
			naiRaw->setBranch(tree); 
			plasRaw->setBranch(tree);
		}
};

