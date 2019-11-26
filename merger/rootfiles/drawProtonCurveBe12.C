{
	TFile *fCurve = new TFile("../../../plot/esBe12Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	TGraph *sn = (TGraph *)gDirectory->Get("sn");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");
	gs->SetLineColor(1);
	gs->SetLineWidth(1);
	gs->SetLineStyle(1);
	
	gs->Draw("l");

//	fex->SetLineColor(1);
//	fex->SetLineWidth(1);
//	fex->SetLineStyle(1);
//	fex->Draw("l");
//
//	sn->SetLineColor(1);
//	sn->SetLineWidth(1);
//	sn->SetLineStyle(1);
//	sn->Draw("l");
	//mex->Draw("l");
	_file0->cd();


}
