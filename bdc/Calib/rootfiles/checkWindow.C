void checkWindow(TString detectorName){
	TH1 *h[8];
	double norm = 1E6;
	for (int i = 0; i < 8; ++i) {
		h[i]=(TH1*)gDirectory->Get(detectorName+Form("tdc%d",i));
		h[i]->Scale(norm/h[i]->GetEntries());
		h[i]->SetLineColor(i);
		if(i==0) h[i]->Draw();
		else h[i]->Draw("same");
	}
	gPad->SetLogy();
}
void checkWindow(){
	TString fileName = "run300_310_tdcCalib.root";
	TFile *input = new TFile(fileName,"READ");
	//checkWindow("BDC1");
	//checkWindow("BDC2");
	checkWindow("FDC0");
}
