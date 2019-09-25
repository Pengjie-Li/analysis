class DSSDRaw{
	private:
		/********************************
		 * Silicon: 0 = LF; 1 = LB; 2 = RF; 3 = RB; 
		 *******************************/
		
		int dssdEnergyRaw[4][32];	
		int dssdTimeRaw[4][32];	
		int RefTime1;// TDC 1
		int RefTime2;// TDC 2 corresponding to 2 moudle

		void init(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdEnergyRaw[i][j] = -1;
					dssdTimeRaw[i][j] = -1;
				}
			}
			RefTime1 = -1;
			RefTime2 = -1;
		}
		void setRawDataHit(int teleId,int adc,int tdc){
			if(teleId>0&&teleId<33) { 
				dssdEnergyRaw[0][teleId-1 ]= adc;
				dssdTimeRaw[0][teleId-1 ]= tdc;
			}

			if(teleId>32&&teleId<65){ 
				dssdEnergyRaw[1][teleId-33]= adc;
				dssdTimeRaw[1][teleId-33]= tdc;
			}
			if(teleId>64&&teleId<97){
				dssdEnergyRaw[2][teleId-65]= adc;
				dssdTimeRaw[2][teleId-65]= tdc;
			}
			if(teleId>96&&teleId<129) {
				dssdEnergyRaw[3][teleId-97]= adc;
				dssdTimeRaw[3][teleId-97]= tdc;
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
			tree->Branch("dssdEnergyRaw",dssdEnergyRaw,"dssdEnergyRaw[4][32]/I");
			tree->Branch("dssdTimeRaw",dssdTimeRaw,"dssdTimeRaw[4][32]/I");
			tree->Branch("RefTime1",&RefTime1,"RefTime1/I");
			tree->Branch("RefTime2",&RefTime2,"RefTime2/I");

		}
		double getDssdQRaw(int side,int id){
			return dssdEnergyRaw[side][id];
		}



};
class CsIRaw{
	private:
		/********************************
		 * CsI: 0 = RLT; 1 = RRT; 2 = RLB; 3 = RRB; 4 = LL; 5 =LRT; 6 = LRB;
		 ********************************/
		int csiEnergyRaw[7];
		int csiTimeRaw[7];
		void init(){
			for(int k = 0;k<7;k++){
				csiEnergyRaw[k] = -1;
				csiTimeRaw[k] = -1;
			}
		}
		void setRawDataHit(int teleId,int adc,int tdc){
			if(teleId>=129&&teleId<=135) { 
				csiEnergyRaw[teleId-129]=adc; 
				csiTimeRaw[teleId-129]=tdc;
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
			tree->Branch("csiEnergyRaw",csiEnergyRaw,"csiEnergyRaw[7]/I");
			tree->Branch("csiTimeRaw",csiTimeRaw,"csiTimeRaw[7]/I");
		}

		double getCsIQRaw(int id){
			return csiEnergyRaw[id];
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

