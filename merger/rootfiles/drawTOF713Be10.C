{
	
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x setAlias.C");
	tree->Draw("tof713Be10>>htof(500,230,235)","Trig_DSB&&Beam");
	TH1F *htof = gDirectory->Get("htof");
	htof->Fit("gaus");
}
