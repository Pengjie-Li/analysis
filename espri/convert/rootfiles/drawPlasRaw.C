{


	int nBin = 1000;
	int tMin = -1000;
	int tMax = 55000;
	int threshold = 500;
	TCanvas *c1 = new TCanvas("Plastic Raw TDC","Plastic Raw TDC",800,700);
	c1->Divide(2,2);
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		CalTreeESPRI->Draw(Form("plasTRaw[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
	}
	TCanvas *c4 = new TCanvas("Plastic Raw Up vs Down","Plastic Raw TDC Up vs Down",1600,700);
	c4->Divide(2,1);
	for(int i=0;i<2;i++){
		c4->cd(i+1);
		TString gate = Form("plasQCal[%d]>%d&&plasQCal[%d]>%d",2*i,threshold,2*i+1,threshold);
		CalTreeESPRI->Draw(Form("plasTRaw[%d]:plasTRaw[%d]>>hTPlasUpDown%d(%d,%d,%d,%d,%d,%d)",2*i,2*i+1,i,nBin,tMin,tMax,nBin,tMin,tMax),gate,"colz");
	}



	TCanvas *c2 = new TCanvas("Plastic Raw QDC","Plastic Raw QDC",800,700);
	c2->Divide(2,2);
	for(int i=0;i<4;i++){
		c2->cd(i+1);
		CalTreeESPRI->Draw(Form("plasQRaw[%d]>>hQPlas%d(1000,150,4150)",i,i));
	}
	TCanvas *c3 = new TCanvas("Plastic Raw QPed","Plastic Raw QPed",800,700);
	c3->Divide(2,2);
	for(int i=0;i<4;i++){
		c3->cd(i+1);
		CalTreeESPRI->Draw(Form("plasQRaw[%d]>>hQPedPlas%d(150,50,200)",i,i));
	}



}
