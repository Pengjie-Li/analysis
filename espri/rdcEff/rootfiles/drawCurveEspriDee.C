{
	TFile *fCurve = new TFile("../../../plot/protonDEE/dEECurve.root","READ");
	TGraph *dEE = (TGraph *)gDirectory->Get("dEE");
	dEE->Draw("psame");
	_file0->cd();


}
