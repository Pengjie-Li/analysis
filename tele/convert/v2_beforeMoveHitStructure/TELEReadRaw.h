class DSSDRaw{
	private:
		/********************************
		 * Silicon: 0 = LF; 1 = LB; 2 = RF; 3 = RB; 
		 *******************************/
		
		int dssdQRaw[4][32];	
		int dssdTRaw[4][32];	
		int RefTime1;// TDC 1
		int RefTime2;// TDC 2 corresponding to 2 moudle

		void init(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdQRaw[i][j] = -1;
					dssdTRaw[i][j] = -1;
				}
			}
			RefTime1 = -1;
			RefTime2 = -1;
		}
		void setRawDataHit(int teleId,int adc,int tdc){
			if(teleId>0&&teleId<33) { 
				dssdQRaw[0][teleId-1 ]= adc;
				dssdTRaw[0][teleId-1 ]= tdc;
			}

			if(teleId>32&&teleId<65){ 
				dssdQRaw[1][teleId-33]= adc;
				dssdTRaw[1][teleId-33]= tdc;
			}
			if(teleId>64&&teleId<97){
				dssdQRaw[2][teleId-65]= adc;
				dssdTRaw[2][teleId-65]= tdc;
			}
			if(teleId>96&&teleId<129) {
				dssdQRaw[3][teleId-97]= adc;
				dssdTRaw[3][teleId-97]= tdc;
			}
			if(teleId==136) { RefTime1 = tdc;}
			if(teleId==137) { RefTime2 = tdc;}
		}
	
	public:
		DSSDRaw(){}
		~DSSDRaw(){}
		void readRaw(TClonesArray *rawDataArray){
			init();
			for(int i=0;i<rawDataArray->GetEntries();i++){
				TArtSILICONS *rawDataHit = (TArtSILICONS *)rawDataArray->At(i);
				int teleId=rawDataHit->GetID();
				int adc=rawDataHit->GetRawADC();
				int tdc=rawDataHit->GetRawTDC();
				setRawDataHit(teleId,adc,tdc);
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
			tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[4][32]/I");
			tree->Branch("RefTime1",&RefTime1,"RefTime1/I");
			tree->Branch("RefTime2",&RefTime2,"RefTime2/I");

		}
		double getDssdQRaw(int side,int id){
			return dssdQRaw[side][id];
		}



};
class CsIRaw{
	private:
		/********************************
		 * CsI: 0 = RLT; 1 = RRT; 2 = RLB; 3 = RRB; 4 = LL; 5 =LRT; 6 = LRB;
		 ********************************/
		int csiQRaw[7];
		int csiTRaw[7];
		void init(){
			for(int k = 0;k<7;k++){
				csiQRaw[k] = -1;
				csiTRaw[k] = -1;
			}
		}
		void setRawDataHit(int teleId,int adc,int tdc){
			if(teleId>=129&&teleId<=135) { 
				csiQRaw[teleId-129]=adc; 
				csiTRaw[teleId-129]=tdc;
			}
		}

	public:
		CsIRaw(){}
		~CsIRaw(){}
		void readRaw(TClonesArray *rawDataArray){
			init();
			for(int i=0;i<rawDataArray->GetEntries();i++){
				TArtSILICONS *rawDataHit = (TArtSILICONS *)rawDataArray->At(i);
				int teleId=rawDataHit->GetID();
				int adc=rawDataHit->GetRawADC();
				int tdc=rawDataHit->GetRawTDC();
				setRawDataHit(teleId,adc,tdc);
			}
		}

		void setBranch(TTree *tree){
			tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
			tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
		}

		double getCsIQRaw(int id){
			return csiQRaw[id];
		}
};


class TELEReadRaw{
	private:
		DSSDRaw *dssdRaw;
		CsIRaw *csiRaw;
	public:
		TELEReadRaw(){
			dssdRaw = new DSSDRaw();
			csiRaw  = new CsIRaw();
		}
		~TELEReadRaw(){
			delete dssdRaw;
			delete csiRaw;
		}
		void setBranch(TTree *tree){
			dssdRaw->setBranch(tree);
			csiRaw->setBranch(tree);
		}
		DSSDRaw * getDssdRaw(){
			return dssdRaw;
		}
		CsIRaw * getCsiRaw(){
			return csiRaw;
		}
		void readRaw(TClonesArray *rawDataArray){
			dssdRaw->readRaw(rawDataArray);
			csiRaw->readRaw(rawDataArray);
		}
		double getDssdQRaw(int side,int id){
			return dssdRaw->getDssdQRaw(side,id);
		}


		double getCsIQRaw(int id){
			return csiRaw->getCsIQRaw(id);
		}
};

