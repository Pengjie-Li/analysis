{
	gROOT->ProcessLine(".x loadCut.C");
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutBeamBe12.C");
	gROOT->ProcessLine(".x cutProtonBe12.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	TString gate = "Beam&&Proton&&"+targetArea+"&&"+hodBe12Be12;
	tree->Draw("espriAngle:resAngle>>hAngle(200,1,5,200,55,75)",gate,"colz");
	gROOT->ProcessLine(".x cutPRAngleBe12.C");
}
