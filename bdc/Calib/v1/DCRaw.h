#include "header.h"
#ifdef __MAKECINT__ 
#pragma link C++ class 
std::vector < std::vector<int> >+;
#endif

class DCRaw{
	private: 
		const static bool kOneHitInOneLayer = true; // App wants to check one hit event, isOneHit means checking one hit, both condition will make a good one hit event

	public : 

		int NumberOfLayer;
		TString detectorName;


		// DC Raw Data
		// Each Drift Chamber raw Data 
		// * hit1 (layerid,wireid,TDC)
		// * hit2
		// * hit3
		// * ...
		Int_t nhits;
		vector<int> TDC;// for each hits, no matter layer, wireid
		vector<int> layerid;// for each hits, no matter layer, wireid
		vector<int> wireid;// for each hits, no matter layer, wireid

		// Each Layer: how many hits, each TDC
		vector<int> layer_hits;
		vector<vector<int> > layer_TDC;


		DCRaw(){
		}
		DCRaw(int nlayer){
			NumberOfLayer = nlayer;	
		}

		void initialize(){
			// Initialize Array
			nhits=-1;
			layer_hits.clear();
			layer_hits.resize(NumberOfLayer,0);
			TDC.clear();
			layerid.clear();
			wireid.clear();

			layer_TDC.clear();
			layer_TDC.resize(NumberOfLayer);

		}

		void setNHits(int n){
			nhits = n;
		}
		void fillHit(int layer,int wire,int val){

			layer_hits[layer]++;
			TDC.push_back(val);
			layerid.push_back(layer);
			wireid.push_back(wire);
			layer_TDC[layer].push_back(val);

		}

		void printRaw(){
			cout<<" Printing Raw Info:"<<endl;
			for(int i = 0; i<layerid.size(); i++)
				cout<<"Layer = "<< layerid[i]<<" wireid = "<<wireid[i]<<" TDC = "<<TDC[i]<<" nhit of layer ="<<layer_hits[layerid[i]]<<endl;

			for(int i=0;i<layer_TDC.size();i++){
				for(int j=0;j<layer_TDC[i].size();j++){
					cout<<"Layer ="<<i<<" val = "<<layer_TDC[i][j]<<endl;
				}
			}

		}

		void fillTDC(TH1* h[8]){
			for (int i=0;i<nhits;i++){
				int layer = layerid[i];
				if((kOneHitInOneLayer) && (!isLayerOneHit(layer))) continue;
				h[layer]->Fill(TDC[i]);
			}

		}

		void fillTDCvsWire(TH2* h[8]){
			for (int i=0;i<nhits;i++){
				int layer = layerid[i];
				if((kOneHitInOneLayer) && (!isLayerOneHit(layer))) continue;
				h[layer]->Fill(TDC[i],wireid[i]);
			}

		}

		void fillAdjcentLayerTDC(TH2* h[4]){
			for(int i=0; i<NumberOfLayer/2;i++){
				for(int j=0;j<layer_TDC[2*i].size();j++)
					for(int k=0;k<layer_TDC[2*i+1].size();k++){
						if((kOneHitInOneLayer) && (!isLayerOneHit(2*i))&& (!isLayerOneHit(2*i+1))) continue;
						h[i]->Fill(layer_TDC[2*i][j],layer_TDC[2*i+1][k]);
					}
			}

		}
		bool isLayerOneHit(int layer){
			return (layer_hits[layer]==1);
		}


		void setRawDataBranch(TTree *tree){
			tree->Branch(detectorName+"TDC",&TDC);
			tree->Branch(detectorName+"layerid",&layerid);
			tree->Branch(detectorName+"wireid",&wireid);

			tree->Branch(detectorName+"nhits",&nhits);
			tree->Branch(detectorName+"layer_hits",&layer_hits);
			tree->Branch(detectorName+"layer_TDC",&layer_TDC);
	

}




};
class BDC1Raw:public DCRaw{
	private:
	public:
		BDC1Raw(){
			NumberOfLayer = 8;
			detectorName = "BDC1";
		}




};
class BDC2Raw:public DCRaw{
	private:
	public:
		BDC2Raw(){
			NumberOfLayer = 8;
			detectorName = "BDC2";
		}
};
class FDC0Raw:public DCRaw{
	private:
	public:
		FDC0Raw(){
			NumberOfLayer = 8;
			detectorName = "FDC0";
		}
};
class FDC2Raw:public DCRaw{
	private:
	public:
		FDC2Raw(){
			NumberOfLayer = 14;
			detectorName = "FDC2";
		}


	//	void fillTDC(TH1* h[8]){
	//		for (int i=0;i<nhits;i++){
	//			int layer = layerid[i];
	//			h[layer]->Fill(TDC[i]);
	//		}

	//	}

	//	void fillTDCvsWire(TH2* h[14]){
	//		for (int i=0;i<nhits;i++){
	//			int layer = layerid[i];
	//			h[layer]->Fill(TDC[i],wireid[i]);
	//		}

	//	}

	//	void fillAdjcentLayerTDC(TH2* h[14]){
	//		for(int i=0; i<NumberOfLayer/2;i++){
	//			for(int j=0;j<layer_TDC[2*i].size();j++)
	//				for(int k=0;k<layer_TDC[2*i+1].size();k++){
	//					h[i]->Fill(layer_TDC[2*i][j],layer_TDC[2*i+1][k]);
	//				}
	//		}

	//	}



};
