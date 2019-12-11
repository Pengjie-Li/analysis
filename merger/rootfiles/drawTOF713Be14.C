{
	
	gROOT->ProcessLine(".x cutBeamBe14.C");
	gROOT->ProcessLine(".x setAlias.C");
	tree->Draw("tof713>>htof(500,225,245)","Trig_DSB&&Beam");
	TH1F *htof = (TH1F *)gDirectory->Get("htof");
	htof->Fit("gaus");
}
