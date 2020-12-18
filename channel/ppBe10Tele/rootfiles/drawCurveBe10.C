{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/curve/TeleProtonBe10Curve.root","READ");
	TGraph *ppBe10_gs = (TGraph *)gDirectory->Get("ppBe10_gs");
	ppBe10_gs->Draw("lsame");
	_file0->cd();


}
