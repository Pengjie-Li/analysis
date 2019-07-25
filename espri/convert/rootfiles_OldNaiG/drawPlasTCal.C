{
	TCanvas *c1 = new TCanvas("Plastic Cal TDC","Plastic Cal TDC",800,700);
	c1->Divide(2,2);
	int nBin = 1000;
	int tMin = -750;
	//int tMax = -20000;
	int tMax = 250;
	//int tMax = 25000;
	//int tMin = -30000;
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		gPad->SetLogy();
		CalTreeESPRI->Draw(Form("plasTCal[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
	}


}
