#include <vector>
class HistoToGraph{
	private:
		const static int pitch = 5; // 5mm drift lenth max = 2.5 mm
		int windowStart;
		int windowStop;
		vector<double> driftLenth;
		vector<double> tdc;
	public:
		
		HistoToGraph(){
		}
		~HistoToGraph(){}
		void setWindow(int start,int stop){
			windowStart = start;
			windowStop = stop;
		}
		void init(){
			driftLenth.clear();
			tdc.clear();
		}
		TGraph * convert(TH1 *h){
			init();
			double totalCount = (double)h->Integral(h->FindBin(windowStart),h->FindBin(windowStop));
			cout<<totalCount<<endl;
			for(int i=windowStart;i<windowStop+1;i++){
				tdc.push_back((double)i);
				double tdc2mm = (double)pitch * 0.5 * (double)h->Integral(h->FindBin(i),h->FindBin(windowStop))/totalCount;
				//double tdc2mm = (double)pitch * 0.5 ;
				driftLenth.push_back(tdc2mm);
				cout<<i<<":"<<tdc2mm<<endl;
			}
			//cout<<<<endl;
			TGraph *gr = new TGraph(tdc.size(),&tdc[0],&driftLenth[0]);
			gr->SetName(h->GetName());
			return gr;
		}

};
void convert(TString detectorName,int windowStart,int windowStop){
	HistoToGraph *hToG = new HistoToGraph();
	//hToG->setWindow(1769,1860);
	hToG->setWindow(windowStart,windowStop);
	TGraph *gr[8];
	detectorName.ToUpper();
	for (int i = 0; i < 8; ++i) {
		
		TString hName = detectorName + Form("tdc%d",i);	
		TH1 *hTemp = (TH1*)gDirectory->Get(hName);	
		gr[i] = hToG->convert(hTemp);
		//gTemp->Draw("apl");
	}	
	detectorName.ToLower();
	TString fileName = "./calib/"+detectorName+"TDCCalibSpectrum.root_new";
	TFile *outputFile = new TFile(fileName,"recreate");
	for (int i = 0; i < 8; ++i) {
		gr[i]->SetName(detectorName+Form("tdc%d",i));
		gr[i]->Write();
	}
	outputFile->Close();
	delete hToG;
}
void convertBDC1(){
	convert("bdc1",1769,1860);
}
void convertBDC2(){
	convert("bdc2",1750,1852);
}
void convertFDC0(){
	convert("fdc0",1746,1830);
}
void histogramIntoTGraph(){
	//convertBDC1();
	//convertBDC2();
	convertFDC0();
}
