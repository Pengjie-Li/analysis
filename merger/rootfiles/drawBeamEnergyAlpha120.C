{
	gROOT->ProcessLine(".x cutBeamAlpha120.C"); 
	tree->Draw("Ek713>>hEk(100,115,125)","Trig_DSB&&Beam");
	TH1F *hEk = (TH1F*)gDirectory->Get("hEk");
	hEk->Fit("gaus","","R",119.5,121.5);

}
