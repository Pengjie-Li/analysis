{
	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/ppAlphaCurve.root","READ");
	TGraph *alphaEA = (TGraph *)gDirectory->Get("AlphaEnergyAngle");
	fCurve->Close();
	alphaEA->Draw("plsame");
	
}
