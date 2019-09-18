{
	TFile *fCurve = new TFile("../../../plot/esBe14Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	TGraph *sn = (TGraph *)gDirectory->Get("s2n");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");
	gs->Draw("l");
	fex->Draw("l");
	sn->Draw("l");
	mex->Draw("l");
	_file0->cd();


}
