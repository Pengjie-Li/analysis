{

	tree->Draw("vTarget.Y():vTarget.X()>>hTarget(1000,-50,50,1000,-50,50)",gate,"colz");
	//gROOT->ProcessLine(".x drawTargetEllipse.C");

}
