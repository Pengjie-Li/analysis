{
	gROOT->ProcessLine(".x cutBeamAlpha150.C"); 
	tree->Draw("Ek713>>hEk(100,153,162)","Trig_DSB&&Beam");
	TH1F *hEk = (TH1F*)gDirectory->Get("hEk");
	hEk->Fit("gaus","","R",156,158.5);

}
