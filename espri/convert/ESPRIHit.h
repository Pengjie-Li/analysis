class ESPRIHit{
	private:
		int espriHit;
		int espriHitSide[2];
		void init(){
			espriHit = 0;
			espriHitSide[0] = -1;
			espriHitSide[1] = -1;
		}
	public:
		ESPRIHit(){}
		~ESPRIHit(){}

		void hitEvent(ESPRIConvertCal *espriCal){
			init();
			if(espriCal->getRdcHit()==1&&espriCal->getPlasHit()==1){
				if(espriCal->getRdcSide(0) == espriCal->getPlasSide(0)){
					espriHitSide[espriHit] = espriCal->getRdcSide(0);
					espriHit++; // espriHit = 1;
					
				}else{
					espriHit = 0;
				}
			}else if(espriCal->getRdcHit()==2&&espriCal->getPlasHit()==1){
				espriHitSide[espriHit] = espriCal->getPlasSide(0);
				espriHit++;

				espriCal->keepRdcSide(espriCal->getPlasSide(0)); // remove bad Hit on RDC
			}else if(espriCal->getRdcHit()==1&&espriCal->getPlasHit()==2){
				espriHitSide[espriHit] = espriCal->getRdcSide(0);
				espriHit++;

				espriCal->keepPlasSide(espriCal->getRdcSide(0)); // remove bad Hit on RDC
			}else if(espriCal->getRdcHit()==2&&espriCal->getPlasHit()==2){
				espriHitSide[0] = espriCal->getRdcSide(0);
				espriHitSide[1] = espriCal->getRdcSide(1);
				espriHit == 2;

				if(espriCal->getRdcSide(0) == espriCal->getPlasSide(0)) {}
				else{
					espriCal->swapPlasSide();
				}

			}else{
				espriHit = 0;
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("espriHit",&espriHit,"espriHit/I");
			tree->Branch("espriHitSide",espriHitSide,"espriHitSide[espriHit]/I");
		}
		void print(){
			for (int i = 0; i < espriHit; ++i) {
				cout<<"ESPI Hit"<<i<<" Side = "<<espriHitSide[i]<<endl;
			}
		}
		int getHit(){
			return espriHit;
		}
		int getSide(){
			return espriHitSide[0];
		}
		int getSide(int hitId){
			return espriHitSide[hitId];
		}



		
};
