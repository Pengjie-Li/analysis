{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x loadCut.C");
	TString gate = "Proton&&"+targetArea+"&&" + hodBe14Bar28_33Be14;
	tree->Draw("espriAngle:fdc0Angle>>hAngle(100,1,5,100,55,75)",gate,"colz");
	gROOT->ProcessLine(".x cutPRAngleBe14.C");
	gROOT->ProcessLine(".x drawCurveBe14_prLabAngle.C");
}
