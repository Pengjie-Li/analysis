{
	TFile *fCurve = new TFile("../../../plot/esLabAngle/Be12Curve.root","READ");
	TGraph *ppBe12 = (TGraph *)gDirectory->Get("ppBe12");
	ppBe12->Draw("l");
	_file0->cd();


}
