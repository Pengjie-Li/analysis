{
	TCanvas *cBDC=new TCanvas("cBDC","cBDC",800,800);
	cBDC->Divide(2,2);
	int nBin = 600;
	int x = 3;

	cBDC->cd(1);
	tree->Draw(Form("BDC1_X-vBDC1_X>>hBDC1X(%d,%d,%d)",nBin,-x,x),"","");
	cBDC->cd(2);                  
	tree->Draw(Form("BDC1_Y-vBDC1_Y>>hBDC1Y(%d,%d,%d)",nBin,-x,x),"","");
	cBDC->cd(3);                  
	tree->Draw(Form("BDC2_X-vBDC2_X>>hBDC2X(%d,%d,%d)",nBin,-x,x),"","");
	cBDC->cd(4);                  
	tree->Draw(Form("BDC2_Y-vBDC2_Y>>hBDC2Y(%d,%d,%d)",nBin,-x,x),"","");


	TCanvas *c=new TCanvas("c","c",800,800);
	c->Divide(2,2);
	c->cd(1);
	tree->Draw(Form("Target_X-vTarget_X>>hTargetX(%d,%d,%d)",nBin,-x,x),"","");
	c->cd(2);                          
	tree->Draw(Form("Target_Y-vTarget_Y>>hTargetY(%d,%d,%d)",nBin,-x,x),"","");
	c->cd(3);
	tree->Draw(Form("DSSD_X-vDSSD_X>>hDSSDX(%d,%d,%d)",nBin,-x,x),"","");
	c->cd(4);                      
	tree->Draw(Form("DSSD_Y-vDSSD_Y>>hDSSDY(%d,%d,%d)",nBin,-x,x),"","");

	TCanvas *cFDC=new TCanvas("cFDC","cFDC",800,800);
	cFDC->Divide(2,2);
	cFDC->cd(1);
	tree->Draw(Form("FDC0_X-vFDC0_X>>hFDC0X(%d,%d,%d)",nBin,-x,x),"","");
	cFDC->cd(2);                          
	tree->Draw(Form("FDC0_Y-vFDC0_Y>>hFDC0Y(%d,%d,%d)",nBin,-x,x),"","");
	cFDC->cd(3);
	tree->Draw(Form("dBDC2_X-BDC2_X>>hBDC2X1(%d,%d,%d)",nBin,-x,x),"","");
	cFDC->cd(4);                     
	tree->Draw(Form("dBDC2_Y-BDC2_Y>>hBDC2Y1(%d,%d,%d)",nBin,-x,x),"","");

	TCanvas *cBDC2=new TCanvas("cBDC2","cBDC2",800,800);
	cBDC2->Divide(2,2);
	cBDC2->cd(1);
	tree->Draw(Form("dBDC2_X-vBDC2_X>>hBDC2X2(%d,%d,%d)",nBin,-x,x),"","");
	cBDC2->cd(2);                          
	tree->Draw(Form("dBDC2_Y-vBDC2_Y>>hBDC2Y2(%d,%d,%d)",nBin,-x,x),"","");
	cBDC2->cd(3);
	tree->Draw(Form("dBDC2_X-BDC2_X>>hBDC2X3(%d,%d,%d)",nBin,-x,x),"","");
	cBDC2->cd(4);                     
	tree->Draw(Form("dBDC2_Y-BDC2_Y>>hBDC2Y3(%d,%d,%d)",nBin,-x,x),"","");




}
