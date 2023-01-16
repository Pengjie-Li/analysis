{
	int nBins =100;
	int xMin = -2;
	int xMax = 2;
	TCanvas *cBDCSubstract = new TCanvas("cBDCSubstract","cBDCSubstract",900,800);
	cBDCSubstract->Divide(2,2);
	cBDCSubstract->cd(1);
	tree->Draw(Form("BDC1_X-vBDC1_X>>hBDC1X(%d,%d,%d)",nBins,xMin,xMax));
	cBDCSubstract->cd(2);
	tree->Draw(Form("BDC1_Y-vBDC1_Y>>hBDC1Y(%d,%d,%d)",nBins,xMin,xMax));
	cBDCSubstract->cd(3);
	tree->Draw(Form("BDC2_X-vBDC2_X>>hBDC2X(%d,%d,%d)",nBins,xMin,xMax));
	cBDCSubstract->cd(4);
	tree->Draw(Form("BDC2_Y-vBDC2_Y>>hBDC2Y(%d,%d,%d)",nBins,xMin,xMax));

}
