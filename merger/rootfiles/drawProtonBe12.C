{
	gROOT->ProcessLine(".x cutBeamBe12.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("plasQ[0]:naiQ[0]>>(1000,0,100,1000,0,40)","BeamBe12&&"+peak5,"colz");
	gROOT->ProcessLine(".x cutProtonBe12.C");
}
