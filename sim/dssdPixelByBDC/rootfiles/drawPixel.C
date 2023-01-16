{
        gStyle->SetStatH(0.15);
        gStyle->SetStatW(0.18);
        gStyle->SetOptFit(1);

	int fid =15;
	int bid = 15;

	int nBin = 100;
	int min = -5;
	int max = 8;
	TString condition = Form("DSSD_Fid==%d&&DSSD_Bid==%d",fid,bid);
	TCanvas *cPixel = new TCanvas("cPixel","cPixel",900,900);
	cPixel->Divide(2,2);
	cPixel->cd(1);
	tree->Draw("BDC1_Y:BDC1_X>>hBDC1(100,-50,50,100,-50,50)",condition,"colz");
	cPixel->cd(2);
	tree->Draw("BDC2_Y:BDC2_X>>hBDC2(100,-50,50,100,-50,50)",condition,"colz");

	TCanvas *cDSSD = new TCanvas("cDSSD","cDSSD",900,900);
	cDSSD->Divide(2,2);
	cDSSD->cd(1);
	tree->Draw(Form("DSSD_Y:DSSD_X>>hDSSD(%d,%d,%d,%d,%d,%d)",nBin,min,max,nBin,min,max),condition,"colz");
	cDSSD->cd(2);
	tree->Draw(Form("vDSSD_Y:vDSSD_X>>hvDSSD(%d,%d,%d,%d,%d,%d)",nBin,min,max,nBin,min,max),condition,"colz");

	cDSSD->cd(3);
	tree->Draw(Form("DSSD_X>>hDSSDX(%d,%d,%d)",nBin,min,max),condition,"colz");
	cDSSD->cd(4);
	tree->Draw(Form("DSSD_Y>>hDSSDY(%d,%d,%d)",nBin,min,max),condition,"colz");

        TH1F *hDSSDX =(TH1F *)gDirectory->Get("hDSSDX");
	hDSSDX->Fit("gaus","Q");

	TH1F *hDSSDY =(TH1F *)gDirectory->Get("hDSSDY");
        hDSSDY->Fit("gaus","Q");
	

}
