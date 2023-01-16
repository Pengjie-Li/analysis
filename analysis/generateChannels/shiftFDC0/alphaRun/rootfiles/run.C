{
	gROOT->ProcessLine(".x setAlias.C");
	gStyle->SetOptFit(1);
	TCanvas *c1 = new TCanvas("c1","c1",1400,600);
	c1->Divide(2,1);
	c1->cd(1);
	TF1 *fit = new TF1("fit","gaus",-1.5,1.5);
	tree->Draw("dBDC2X-bdc2X>>hX(100,-5,5)",targetArea);
	TH1F *hX = (TH1F*)gDirectory->Get("hX");
	hX->Fit(fit,"R");
	
	c1->cd(2);
	tree->Draw("dBDC2Y-bdc2Y>>hY(100,-5,5)",targetArea);
	TH1F *hY = (TH1F*)gDirectory->Get("hY");
	hY->Fit(fit,"R");
	
}
