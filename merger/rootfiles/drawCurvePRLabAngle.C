{
	TFile *fCurve = new TFile("../../../plot/esLabAngle/Be10Curve.root","READ");
	TGraph *ppBe10 = (TGraph *)gDirectory->Get("ppBe10");
	ppBe10->Draw("l");
	_file0->cd();


}
