{
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("espriPlasE:espriNaiE>>hProton(1000,0,200,1000,0,40)","BeamBe10&&"+targetArea,"colz");
	gROOT->ProcessLine(".x cutProtonBe10.C");
}
