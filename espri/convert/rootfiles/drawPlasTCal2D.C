{
	int nBin = 1000;
	int tMin = -700;
	//int tMax = -20000;
	//int tMax = -450;
	int tMax = 600;
	//int tMin = -30000;
	//int tMax = 25000;

	TCanvas *c1 = new TCanvas("Left Plastic Cal TDC vs TDC","Left Plastic Cal TDC vs TDC",800,700);
	c1->cd();
	CalTreeESPRI->Draw(Form("plasTCal[0]:plasTCal[1]>>hTPlas0(%d,%d,%d,%d,%d,%d)",nBin,tMin,tMax,nBin,tMin,tMax),"","colz");

	TCanvas *c2 = new TCanvas("Right Plastic Cal TDC vs TDC","Right Plastic Cal TDC vs TDC",800,700);
	c2->cd();
	CalTreeESPRI->Draw(Form("plasTCal[2]:plasTCal[3]>>hTPlas1(%d,%d,%d,%d,%d,%d)",nBin,tMin,tMax,nBin,tMin,tMax),"","colz");
	
}
