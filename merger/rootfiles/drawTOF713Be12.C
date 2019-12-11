{
	
	gROOT->ProcessLine(".x cutBeamBe12.C");
	gROOT->ProcessLine(".x setAlias.C");
	tree->Draw("tof713>>htof(500,233,240)","Trig_DSB&&Beam");
	TH1F *htof = gDirectory->Get("htof");
	htof->Fit("gaus");
}
