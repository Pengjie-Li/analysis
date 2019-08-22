{
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("plasQ[0]:naiQ[0]>>(1000,0,100,1000,0,40)","BeamBe10&&"+peak5,"colz");
	gROOT->ProcessLine(".x cutProtonBe10.C");
}
