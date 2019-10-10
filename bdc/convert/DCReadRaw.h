class DCReadRaw{
	private:
		int tdcMax;
		int tdcMin;

		int nHits;
		vector<int> nLayerHits;
		//vector<double> tdc;
		//vector<double> layerId;
		//vector<double> wireId;

		vector<int> tdc;
		vector<int> layerId;
		vector<int> wireId;

		void init(){
			nHits=0;
			nLayerHits.clear();
			nLayerHits.resize(8,0);
			tdc.clear();
			layerId.clear();
			wireId.clear();


		}
	public:

		TString dcName;
		DCReadRaw(){
		}
		~DCReadRaw(){}
		void setBranch(TTree *tree){
			tree->Branch(dcName + "NHits"   ,&nHits);
			tree->Branch(dcName + "NLayerHits"   ,&nLayerHits);
			tree->Branch(dcName + "Tdc"     ,&tdc);
			tree->Branch(dcName + "LayerId" ,&layerId);
			tree->Branch(dcName + "Wireid"  ,&wireId);
		}
		void readRaw(TClonesArray *dcHit ){
			init();
			//DC
			// Initialize Array
			//nHits= dcHit->GetEntries();
			for(int i=0;i<dcHit->GetEntries();i++){
				TArtDCHit *hit = (TArtDCHit *)dcHit->At(i);
				int layer = hit->GetLayer();
				int wire = hit->GetWireID();
				int val = hit->GetTDC();
				if(checkTdcUnderAndOverflow(val)){
					nHits++;
					nLayerHits[layer] = nLayerHits[layer] + 1;
					if(nLayerHits[layer]>16) cout<<dcName<<":"<<nLayerHits[layer]<<endl;
					//cout<< layer<<"  "<<wire<<"  "<<val<<"  "<<nLayerHits[layer]<<endl;
					tdc.push_back(val);
					layerId.push_back(layer);
					wireId.push_back(wire);
				}
			}
		}
		bool checkTdcUnderAndOverflow(int tdcVal){
			if(tdcVal<=tdcMax&&tdcVal>=tdcMin) return true;	
			else return false;
		}
		void loadTdcRange(){
			tdcMin = env->GetValue(dcName+"TdcMin",1600);
			tdcMax = env->GetValue(dcName+"TdcMax",2000);
			cout<<"Detector Name: "<<dcName<<" Underflow TDC="<<tdcMin<<" Overflow TDC="<<tdcMax<<endl;
		}

		void print(){
			cout<<dcName<<" total Hits:"<<nHits<<endl;
			for (int i = 0; i < (int)nLayerHits.size(); ++i) {
				cout<<"Layer "<<i<<":"<<nLayerHits[i]<<endl;

			}
			for (int i = 0; i < (int)tdc.size(); ++i) {
				cout<< layerId[i]<<":"<<wireId[i]<<":"<<tdc[i]<<endl;

			}
		}

		int getNHits(){
			return nHits;
		}
		int getLayerId(int i){
			return layerId[i];
		}
		int getWireId(int i){
			return wireId[i];
		}
		int getTdc(int i){
			return tdc[i];
		}

};
class BDC1ReadRaw:public DCReadRaw{
	private:
	public:
		BDC1ReadRaw(){
			dcName = "bdc1";
			loadTdcRange();
		}
		~BDC1ReadRaw(){}
};
class BDC2ReadRaw:public DCReadRaw{
	private:
	public:
		BDC2ReadRaw(){
			dcName = "bdc2";
			loadTdcRange();

		}
		~BDC2ReadRaw(){}
};
class FDC0ReadRaw:public DCReadRaw{
	private:
	public:
		FDC0ReadRaw(){
			dcName = "fdc0";
			loadTdcRange();

		}
		~FDC0ReadRaw(){}
};
