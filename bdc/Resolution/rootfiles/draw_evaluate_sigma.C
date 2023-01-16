{
	TCanvas *cBDC=new TCanvas("cBDC","cBDC",800,800);
	cBDC->Divide(2,2);
	int nBin = 1000;
	int x = 50;

	cBDC->cd(1);
	tree->Draw(Form("BDC1_X>>hBDC1X(%d,%d,%d)",nBin,-x,x),"","");
	cBDC->cd(2);
	tree->Draw(Form("BDC1_Y>>hBDC1Y(%d,%d,%d)",nBin,-x,x),"","");
	cBDC->cd(3);
	tree->Draw(Form("BDC2_X>>hBDC2X(%d,%d,%d)",nBin,-x,x),"","");
	cBDC->cd(4);
	tree->Draw(Form("BDC2_Y>>hBDC2Y(%d,%d,%d)",nBin,-x,x),"","");


	TCanvas *c=new TCanvas("c","c",800,800);
	c->Divide(2,2);
	c->cd(1);
	tree->Draw(Form("Target_X>>hTargetX(%d,%d,%d)",nBin,-x,x),"","");
	c->cd(2);
	tree->Draw(Form("Target_Y>>hTargetY(%d,%d,%d)",nBin,-x,x),"","");
	c->cd(3);
	tree->Draw(Form("DSSD_X>>hDSSDX(%d,%d,%d)",nBin,-x,x),"","");
	c->cd(4);
	tree->Draw(Form("DSSD_Y>>hDSSDY(%d,%d,%d)",nBin,-x,x),"","");

}
