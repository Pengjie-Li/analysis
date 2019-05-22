{
	TCanvas *c=new TCanvas("c","c",800,800);
	c->Divide(2,2);
	int nBin = 1000;
	int x = 50;
	c->cd(1);
	tree->Draw(Form("BDC1_Y:BDC1_X>>hBDC1(%d,%d,%d,%d,%d,%d)",nBin,-x,x,nBin,-x,x),"","colz");
	c->cd(2);
	tree->Draw(Form("BDC2_Y:BDC2_X>>hBDC2(%d,%d,%d,%d,%d,%d)",nBin,-x,x,nBin,-x,x),"","colz");
	c->cd(3);
	tree->Draw(Form("Target_Y:Target_X>>hTarget(%d,%d,%d,%d,%d,%d)",nBin,-x,x,nBin,-x,x),"","colz");
	c->cd(4);
	tree->Draw(Form("DSSD_Y:DSSD_X>>hDSSD(%d,%d,%d,%d,%d,%d)",nBin,-x,x,nBin,-x,x),"","colz");

}
