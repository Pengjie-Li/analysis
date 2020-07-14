class ESPRIHit{
	private:
		int espriHit;
		int espriSide;
		double espriRdcX;
		double espriRdcY;
		double espriPlasQPed;
		double espriNaiQPed;
	public:
		ESPRIHit(){}
		~ESPRIHit(){}

		void init(){
			espriHit = 0;
			espriSide = -1;
			espriRdcX = -9999;
			espriRdcY = -9999;
			espriPlasQPed = -9999;
			espriNaiQPed = -9999;
		}
		void hitEvent(ESPRIDetHit *espriDetHit){
			if(espriDetHit->getRdcHit()==1&&espriDetHit->getPlasHit()==1){
				if(espriDetHit->getRdcSide(0) == espriDetHit->getPlasSide(0)){
					espriSide = espriDetHit->getRdcSide(0);
					espriHit++; // espriHit = 1;
				}else{
					espriHit = -1; // rdc and plas not in the same side, check
				}
			}else if(espriDetHit->getRdcHit()==2&&espriDetHit->getPlasHit()==1){
				espriSide = espriDetHit->getPlasSide(0);
				espriHit++;
			}else if(espriDetHit->getRdcHit()==1&&espriDetHit->getPlasHit()==2){
				espriSide = espriDetHit->getRdcSide(0);
				espriHit++;
			}else if(espriDetHit->getRdcHit()==2&&espriDetHit->getPlasHit()==2){
				espriHit == 2;
			}else{
				espriHit = 0;
			}
			if(espriSide!=-1){
				espriRdcX = espriDetHit->getRdcX(espriSide);
				espriRdcY = espriDetHit->getRdcY(espriSide);
				espriPlasQPed = espriDetHit->getPlasQPed(espriSide);
				if(espriDetHit->getNaiHit()>0) espriNaiQPed = espriDetHit->getNaiQPed(espriSide); 
			}
		}
		void setBranch(TTree *tree){
			tree->Branch("espriHit",&espriHit,"espriHit/I");
			tree->Branch("espriSide",&espriSide,"espriSide/I");
			tree->Branch("espriRdcX",&espriRdcX,"espriRdcX/D");
			tree->Branch("espriRdcY",&espriRdcY,"espriRdcY/D");
			tree->Branch("espriPlasQPed",&espriPlasQPed,"espriPlasQPed/D");
			tree->Branch("espriNaiQPed",&espriNaiQPed,"espriNaiQPed/D");
		}
		void print(){
			for (int i = 0; i < espriHit; ++i) {
				cout<<" ESPRI Hit"<<i<<" Side = "<<espriSide<<" rdcX ="<<espriRdcX<<" rdcY ="<<espriRdcY<<" plasQPed = "<<espriPlasQPed<<" naiQPed = "<<espriNaiQPed<<endl;
			}
		}
		int getHit(){
			return espriHit;
		}
		int getSide(){
			return espriSide;
		}

};
