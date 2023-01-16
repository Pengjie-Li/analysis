{
	TFile *fCurve = new TFile("../../../plot/esLabAngle/Be12Curve.root","READ");
	TGraph *ppBe12_gs = (TGraph *)gDirectory->Get("ppBe12_gs");
	ppBe12_gs->Draw("l");
	TGraph *ppBe12_fex = (TGraph *)gDirectory->Get("ppBe12_fex");
	ppBe12_fex->Draw("l");
	TGraph *ppBe12_sn = (TGraph *)gDirectory->Get("ppBe12_sn");
	ppBe12_sn->Draw("l");
	_file0->cd();


}
