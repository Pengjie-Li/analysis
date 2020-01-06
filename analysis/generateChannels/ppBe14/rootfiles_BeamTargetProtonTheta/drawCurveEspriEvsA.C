{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
	tot = (TGraph *)gDirectory->Get("tot");
	fCurve->Close();
	tot->Draw("pl");
}
