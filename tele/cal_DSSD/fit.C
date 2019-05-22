void fit()
{

	TF1 *g1 = new TF1 ("m1", "gaus", 9500, 11200);
	g1->SetLineColor(kRed);
	TF1 *g2 = new TF1 ("m2", "gaus", 12000, 15000);
	g2->SetLineColor(kGreen);
	TF1 *f1 = new TF1("double_gaus", "gaus(0) + gaus(3)", 9000, 16000);
	f1->SetParNames("Constant 1", "Mean 1", "Sigma 1",
			"Constant 2", "Mean 2", "Sigma 2");
	//f1->SetLineColor(kYellow);
	//f1->SetLineColor(kMagenta);
	f1->SetLineColor(7);

	gStyle->SetOptFit(1);
	TH1F *h=(TH1F*)gDirectory->Get("h"); 
	h->Fit(g1, "R");
	h->Fit(g2, "R+");

	Double_t par[6];
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	f1->SetParameters(par);
	h->Fit(f1, "R+");
	// h->Fit(f1, "+", "e1", 4, 16);
	//h->Draw("e1");
	h->Draw("");



}
