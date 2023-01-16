{
	int nBin = 1000;
	int tMin = -1000;
	int tMax = 55000;

	int threshold = 0;
	TCanvas *c4 = new TCanvas("Plastic Raw Up vs Down","Plastic Raw TDC Up vs Down",1600,700);
	c4->Divide(2,1);
	for(int i=0;i<2;i++){
		c4->cd(i+1);
		TString gate = Form("plasQCal[%d]>%d&&plasQCal[%d]>%d",2*i,threshold,2*i+1,threshold);
		CalTreeESPRI->Draw(Form("plasTRaw[%d]:plasTRaw[%d]>>hTPlasUpDown%d(%d,%d,%d,%d,%d,%d)",2*i,2*i+1,i,nBin,tMin,tMax,nBin,tMin,tMax),gate,"colz");
	}

}
