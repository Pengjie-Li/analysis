{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/energyCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("energy");
	gs->SetLineColor(1);
	gs->Draw("plsame*");
	_file0->cd();
}
