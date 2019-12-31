{
	int nBin = 1000;
	int tMin = -1000;
	int tMax = 5000;
	TCanvas *c1 = new TCanvas("Plastic Raw TDC","Plastic Raw TDC",800,700);
	c1->Divide(2,2);
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		//gPad->SetLogy();
		CalTreeESPRI->Draw(Form("plasTRaw[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
	}

}
