{
	gROOT->ProcessLine(".x cutBeamBe12.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("espriPlasDeltaE:espriNaiE>>(1000,0,200,1000,0,40)","BeamBe12&&"+peak5,"colz");
	gROOT->ProcessLine(".x cutProtonBe12.C");
}
