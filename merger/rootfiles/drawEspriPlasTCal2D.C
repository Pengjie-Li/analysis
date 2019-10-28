{
	int nBin = 1000;
	int tMax = -550;
	int tMin = -700;

	int threshold = 0;
	TCanvas *c4 = new TCanvas("Plastic Cal Up vs Down","Plastic Cal TDC Up vs Down",1600,700);
	c4->Divide(2,1);
	for(int i=0;i<2;i++){
		c4->cd(i+1);
		//TString gate = Form("plasQCal[%d]>%d&&plasQCal[%d]>%d",2*i,threshold,2*i+1,threshold);
		TString gate = "";
		tree->Draw(Form("plasTCal[%d]:plasTCal[%d]>>hTPlasUpDown%d(%d,%d,%d,%d,%d,%d)",2*i,2*i+1,i,nBin,tMin,tMax,nBin,tMin,tMax),gate,"colz");
	}

}
