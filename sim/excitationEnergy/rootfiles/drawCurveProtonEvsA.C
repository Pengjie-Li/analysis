{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *s2n = (TGraph *)gDirectory->Get("s2n");
	s2n->SetLineColor(1);
	gs->Draw("same");
	s2n->Draw("same");
	_file0->cd();
}
