{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
	TGraph *dEE = (TGraph *)gDirectory->Get("dEE");
	dEE->Draw("psame");
	fCurve->Close();
	_file0->cd();


}
