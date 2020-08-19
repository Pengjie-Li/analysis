{

	tree->Draw("targetPosition.Y():targetPosition.X()>>hTarget(1000,-50,50,1000,-50,50)",gate,"colz");
	
	//gROOT->ProcessLine(".x drawTargetEllipse.C");
}
