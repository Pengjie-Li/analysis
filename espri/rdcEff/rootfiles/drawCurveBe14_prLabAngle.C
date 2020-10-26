{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esLabAngle/Be14Curve.root","READ");
	TGraph *ppBe14_gs = (TGraph *)gDirectory->Get("ppBe14_gs");
	ppBe14_gs->Draw("l");
	TGraph *ppBe14_s2n = (TGraph *)gDirectory->Get("ppBe14_s2n");
	ppBe14_s2n->Draw("l");
	
	_file0->cd();


}
