{
	TFile *fCurve1 = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe10Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	TGraph *sn = (TGraph *)gDirectory->Get("sn");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");

	gs->SetLineColor(1);
	gs->SetLineWidth(1);
	//gs->SetLineStyle(3);
	
	fex->SetLineColor(1);
	fex->SetLineWidth(1);
	//fex->SetLineStyle(3);
	
//	gs->Draw("l");
	fex->Draw("l");
//	sn->Draw("l");
//	mex->Draw("l");
	_file0->cd();

	delete fCurve1;
}
