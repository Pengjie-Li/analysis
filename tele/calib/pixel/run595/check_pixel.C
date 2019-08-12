{
	TCanvas *c=new TCanvas("checking pixel","checking pixel");

	c->Divide(3,3);
	c->cd(1);

	tree->Draw("pixelF>>hF(1000,500,25000)");

	c->cd(2);
	tree->Draw("pixelB>>hB(1000,500,25000)");

	c->cd(3);
	tree->Draw("pixelLL>>hLL(1000,500,2500)");

	c->cd(4);
	tree->Draw("pixelLRT>>hLRT(1000,500,2500)");

	c->cd(5);
	tree->Draw("pixelLRB>>hLRB(1000,500,2500)");

	c->cd(6);
	tree->Draw("Target_Y:Target_X>>hXY(1000,-50,50,1000,-50,50)","","colz");
	gROOT->ProcessLine(".x draw_ellipse.C");

	c->cd(7);
	tree->Draw("Target_ThetaY:Target_ThetaX>>hTXY(1000,-0.05,0.05,1000,-0.05,0.05)","","colz");

	c->cd(8);
	tree->Draw("Beam.Theta()*TMath::RadToDeg()>>hTheta(100,0,5)");





}
