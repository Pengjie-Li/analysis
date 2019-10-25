{
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("espriPlasDeltaE:espriNaiEnergy>>hProton(1000,0,200,1000,0,40)","BeamBe10&&"+peak5,"colz");
	gROOT->ProcessLine(".x cutProtonBe10.C");
}
