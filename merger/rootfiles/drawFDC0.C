{
	TCanvas *cPad = new TCanvas("cPad","cPad",1400, 700);
	cPad->Divide(2,1);
	gROOT->ProcessLine(".x dcAlias.C");
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<2";

	TF1 *f = new TF1("f", "gaus", -1.5,1.5);
	TH1F *h[2];
	cPad->cd(1);
	tree->Draw("dFDC0X - fdc0X>>hFDC0X(100,-10,10)","Trig_DSB&&"+targetArea);
	h[0] = (TH1F*)gDirectory->Get("hFDC0X");
	h[0]->Fit(f, " ","QRB",  -1.5, 1.5);
	
	cPad->cd(2);
	tree->Draw("dFDC0Y - fdc0Y>>hFDC0Y(100,-10,10)","Trig_DSB&&"+targetArea);
	h[1] = (TH1F*)gDirectory->Get("hFDC0Y");
	h[1]->Fit(f, " ","QRB",  -1.5, 1.5);
	

}
