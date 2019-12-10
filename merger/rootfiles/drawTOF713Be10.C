{
	
	tree->SetAlias("tof713","F13T-f7t_slew+570");
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x setAlias.C");
	tree->Draw("tof713>>htof(500,230,235)","Trig_DSB&&Beam");
	TH1F *htof = gDirectory->Get("htof");
	htof->Fit("gaus");
}
