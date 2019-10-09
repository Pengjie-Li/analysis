
void checkConsistency(){
	check("BDC1tdc0");
	//check("BDC2tdc0");
	//check("FDC0tdc7");
}
void check(TString hName){
	TString fileName1 = "run300_310_tdcCalib.root";
	TString fileName2 = "run331_340_tdcCalib.root";
	TString fileName3 = "run430_439_tdcCalib.root";
	TFile *f1 = new TFile(fileName1,"READ");
	TH1 *f1Bdc1Tdc0 = (TH1*)f1->Get(hName);
	TFile *f2 = new TFile(fileName2,"READ");
	TH1 *f2Bdc1Tdc0 = (TH1*)f2->Get(hName);
	TFile *f3 = new TFile(fileName3,"READ");
	TH1 *f3Bdc1Tdc0 = (TH1*)f3->Get(hName);


	f1Bdc1Tdc0->SetLineColor(1);
	f2Bdc1Tdc0->SetLineColor(2);
	f3Bdc1Tdc0->SetLineColor(4);

	double norm = 1E6;
	f1Bdc1Tdc0->Scale(norm/f1Bdc1Tdc0->GetEntries());
	f2Bdc1Tdc0->Scale(norm/f2Bdc1Tdc0->GetEntries());
	f3Bdc1Tdc0->Scale(norm/f3Bdc1Tdc0->GetEntries());

	f1Bdc1Tdc0->Draw();
	f2Bdc1Tdc0->Draw("same");
	f3Bdc1Tdc0->Draw("same");
	gPad->SetLogy();
}
