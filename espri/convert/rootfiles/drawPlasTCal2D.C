{
	int nBin = 1000;
	int tMin = -700;
	//int tMax = -20000;
	int tMax = -450;
	//int tMax = 600;
	//int tMin = -30000;
	//int tMax = 25000;

	TCanvas *c1 = new TCanvas(" Plastic Cal TDC vs TDC","Left Plastic Cal TDC vs TDC",1500,700);
	c1->Divide(2,1);
	c1->cd(1);
	CalTreeESPRI->Draw(Form("plasTCal[0]:plasTCal[1]>>hTPlas0(%d,%d,%d,%d,%d,%d)",nBin,tMin,tMax,nBin,tMin,tMax),"","colz");

	c1->cd(2);
	CalTreeESPRI->Draw(Form("plasTCal[2]:plasTCal[3]>>hTPlas1(%d,%d,%d,%d,%d,%d)",nBin,tMin,tMax,nBin,tMin,tMax),"","colz");
	
}
