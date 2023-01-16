{
	TCanvas *cF13Time = new TCanvas("cF13Time","cF13Time",1200,900);
	gPad->SetLogy();
	//tree->Draw("F13T>>hF13T(1000,200,230)","Trig_DSB&&Beam");
	tree->Draw("F13T>>hF13T(1000,200,230)");
	TH1F *hF13T =(TH1F*) gDirectory->Get("hF13T");
	hF13T->Fit("gaus");
}
