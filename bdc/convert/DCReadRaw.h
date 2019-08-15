class DCReadRaw{
	private:
		int nHits;
		vector<int> nLayerHits;
		vector<double> tdc;
		vector<double> layerId;
		vector<double> wireId;

		//	vector<int> tdc;
		//	vector<int> layer;
		//	vector<int> wire;

		void init(){
			nHits=-1;
			nLayerHits.clear();
			nLayerHits.resize(8,0);
			tdc.clear();
			layerId.clear();
			wireId.clear();


		}
	public:

		TString dcName;

		DCReadRaw(){}
		~DCReadRaw(){}
		void setBranch(TTree *tree){
		}
		void readRaw(TClonesArray *dcHit ){
			init();
			//DC
			// Initialize Array
			nHits= dcHit->GetEntries();
			for(int i=0;i<dcHit->GetEntries();i++){
				TArtDCHit *hit = (TArtDCHit *)dcHit->At(i);
				int layer = hit->GetLayer();
				int wire = hit->GetWireID();
				int val = hit->GetTDC();
				nLayerHits[layer] = nLayerHits[layer] + 1;
				if(nLayerHits[layer]>16) cout<<dcName<<":"<<nLayerHits[layer]<<endl;
				cout<< layer<<"  "<<wire<<"  "<<val<<"  "<<nLayerHits[layer]<<endl;
				tdc.push_back(val);
				layerId.push_back(layer);
				wireId.push_back(wire);


			}
		}


};

class BDC1ReadRaw:public DCReadRaw{
	private:
	public:
		BDC1ReadRaw(){
			dcName = "BDC1";
		}
		~BDC1ReadRaw(){}
};
class BDC2ReadRaw:public DCReadRaw{
	private:
	public:
		BDC2ReadRaw(){
			dcName = "BDC2";
		}
		~BDC2ReadRaw(){}
};
class FDC0ReadRaw:public DCReadRaw{
	private:
	public:
		FDC0ReadRaw(){
			dcName = "FDC0";
		}
		~FDC0ReadRaw(){}
};
