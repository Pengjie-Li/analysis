{
	//gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("espriPlasE:espriNaiE>>hProton(1000,0,200,1000,0,20)",targetArea,"colz");
	gROOT->ProcessLine(".x cutProton.C");
}
