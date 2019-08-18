class HistoToGraph{
	private:
	public:
		HistoToGraph(){}
		~HistoToGraph(){}
		TGraph * convert(TH1 *h){
		}
};
void convertBDC1(){
	TString detectorName = "BDC1";
	HistoToGraph *hToG = new HistoToGraph();
	for (int i = 0; i < 8; ++i) {
		
		TString hName = detectorName+ Form("tdc%d",i);	
		TH1 *hTemp = (TH1*)gDirectory->Get(hName);	
		TGraph *gTemp = hToG->convert(hTemp);
		//gTemp->Draw("apl");
	}	
}
void histogramIntoTGraph(){
	convertBDC1();
	//convertBDC2();
	//convertFDC0();
}
