{
	TFile *fCurve = new TFile("../../../plot/esLabAngle/Be10Curve.root","READ");
	TGraph *ppBe10_gs = (TGraph *)gDirectory->Get("ppBe10_gs");
	ppBe10_gs->Draw("lsame");
	TGraph *ppBe10_fex = (TGraph *)gDirectory->Get("ppBe10_fex");
	ppBe10_fex->Draw("lsame");
	TGraph *ppBe10_sex = (TGraph *)gDirectory->Get("ppBe10_sex");
	ppBe10_sex->Draw("lsame");
	
	_file0->cd();


}
