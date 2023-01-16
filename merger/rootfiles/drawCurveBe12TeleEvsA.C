{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/alphaCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("AlphaEnergyAngle");
	gs->SetLineColor(1);
	gs->Draw("plsame*");
	_file0->cd();
}
