{
	TFile *fCurve = new TFile("../../../plot/esLabAngle/Be14Curve.root","READ");
	TGraph *ppBe14 = (TGraph *)gDirectory->Get("ppBe14");
	ppBe14->Draw("l");
	_file0->cd();


}
