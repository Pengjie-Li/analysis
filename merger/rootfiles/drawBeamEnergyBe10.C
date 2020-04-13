{
	gROOT->ProcessLine(".x cutBeamBe10.C"); 
	//tree->Draw("Ek713>>hEk(100,150,156)","Trig_DSB&&Beam");
	tree->Draw("beamEnergy>>hEk(100,145,155)","Trig_DSB&&Beam");
	TH1F *hEk = (TH1F*)gDirectory->Get("hEk");
	hEk->Fit("gaus","","R",149.5,150.6);

}
