{
	gROOT->ProcessLine(".x cutBeamBe14.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	//tree->Draw("plasQ[0]:naiQ[0]>>(1000,0,100,1000,0,40)","BeamBe14&&"+peak5,"colz");
	//tree->Draw("plasQ[1]:naiQ[1]>>(1000,0,100,1000,0,40)","BeamBe14&&"+peak5,"colz");
	tree->Draw("espriPlasE:espriNaiE>>(1000,0,200,1000,0,40)","Beam&&"+targetArea,"colz");
	gROOT->ProcessLine(".x cutProton.C");
}
