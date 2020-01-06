{
	gROOT->ProcessLine(".x cutBeamBe12.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	tree->Draw("espriPlasE:espriNaiE>>(1000,0,200,1000,0,40)","Beam&&"+targetArea,"colz");
	gROOT->ProcessLine(".x cutProtonBe12.C");
}
