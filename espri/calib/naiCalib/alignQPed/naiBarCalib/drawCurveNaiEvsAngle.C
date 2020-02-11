{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
	TGraph *nai = (TGraph *)gDirectory->Get("nai");
	nai->SetMarkerColor(1);
	nai->SetLineColor(1);
	nai->Draw("plsame");
}
