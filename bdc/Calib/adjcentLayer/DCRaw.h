#include "header.h"
#ifdef __MAKECINT__ 
#pragma link C++ class 
std::vector < std::vector<int> >+;
#endif

class DCRaw{
	private: 
	public : 

		int nBin;
		int tdcMin;
		int tdcMax;
		int NumberOfLayer;
		TString detectorName;
		TH1 *h[16];
		TH2* hLayer[8];



		DCRaw(){
		}
		void createHistograms(){
			for (int i = 0; i < NumberOfLayer; ++i) {
				TString name = detectorName+Form("tdc%d",i);
				h[i] = new TH1I( name,name,nBin,tdcMin,tdcMax);
			}

                        for(int i=0; i<NumberOfLayer/2;i++){

				TString name = detectorName+Form("LayerTDC%d%d",2*i,2*i+1);
                                hLayer[i] = new TH2I(name,name,200,1700,1900,200,1700,1900);
                        }
		}
		void saveHistograms(){
			for (int i = 0; i < NumberOfLayer; ++i) {
				h[i]->Write();
			}
			for (int i = 0; i < NumberOfLayer/2; ++i) {
				hLayer[i]->Write();
			}

		}

		void fillTDC(vector<double> *layerId, vector<double> *tdc){
			for (int i=0;i<(*layerId).size();i++){
				int layer = (*layerId)[i];
				int Tdc = (*tdc)[i];
				//cout<<layer<<":"<<Tdc<<endl;
				if(Tdc<tdcMax && Tdc>tdcMin) h[layer]->Fill(Tdc);
			}

			for(int i=0; i<NumberOfLayer/2;i++){
				for(int j=0;j<(*layerId).size();j++){
					for(int k=0;k<(*layerId).size();k++){
						if((j==2*i)&&(k==2*i+1)){
							int tdcJ = (*tdc)[j];
							int tdcK = (*tdc)[k];
							hLayer[i]->Fill(tdcJ,tdcK);
						}
					}                  
				}                                  
			}
		}


};
class BDC1Raw:public DCRaw{
	private:
	public:
		BDC1Raw(){
			nBin = 200;
			tdcMin = 1700;
			tdcMax = 1900;
			NumberOfLayer = 8;
			detectorName = "bdc1";
			createHistograms();
		}




};
class BDC2Raw:public DCRaw{
	private:
	public:
		BDC2Raw(){
			nBin = 200;
			tdcMin = 1700;
			tdcMax = 1900;

			NumberOfLayer = 8;
			detectorName = "bdc2";
			createHistograms();
		}
};
class FDC0Raw:public DCRaw{
	private:
	public:
		FDC0Raw(){
			nBin = 300;
			tdcMin = 1600;
			tdcMax = 1900;

			NumberOfLayer = 8;
			detectorName = "fdc0";
			createHistograms();
		}
};
class FDC2Raw:public DCRaw{
	private:
	public:
		FDC2Raw(){
			nBin = 900;
			tdcMin = 1000;
			tdcMax = 1900;
			NumberOfLayer = 14;
			detectorName = "fdc2";
			createHistograms();
		}


};
