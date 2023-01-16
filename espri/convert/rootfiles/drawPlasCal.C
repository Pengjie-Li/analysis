{
	TCanvas *c1 = new TCanvas("Plastic Cal TDC","Plastic Cal TDC",800,700);
	c1->Divide(2,2);
	int nBin = 1000;
	int tMin = -30000;
	//int tMax = -20000;
	int tMax = 25000;
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		CalTreeESPRI->Draw(Form("plasTCal[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
	}

	TCanvas *c3 = new TCanvas("Plastic Cal TDC vs TDC","Plastic Cal TDC vs TDC",800,700);
	c3->Divide(2,1);
	c3->cd(1);	
	CalTreeESPRI->Draw(Form("plasTCal[0]:plasTCal[1]>>hTPlas0(%d,%d,%d,%d,%d,%d)",nBin,tMin,tMax,nBin,tMin,tMax));
	c3->cd(2);
	CalTreeESPRI->Draw(Form("plasTCal[2]:plasTCal[3]>>hTPlas1(%d,%d,%d,%d,%d,%d)",nBin,tMin,tMax,nBin,tMin,tMax));
	TCanvas *c2 = new TCanvas("Plastic Cal QDC","Plastic Cal QDC",800,700);
	c2->Divide(2,2);
	for(int i=0;i<4;i++){
		c2->cd(i+1);
		CalTreeESPRI->Draw(Form("plasQCal[%d]>>hQPlas%d(1000,-100,3900)",i,i));
	}

}
