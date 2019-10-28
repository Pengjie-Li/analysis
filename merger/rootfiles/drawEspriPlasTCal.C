{
	TCanvas *c1 = new TCanvas("Plastic Cal TDC","Plastic Cal TDC",800,700);
	c1->Divide(2,2);
	int nBin = 1000;
	//int tMax = 8000;
	int tMax = -600;
	//int tMin = -1000;
	int tMin = -700;
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		gPad->SetLogy();
		tree->Draw(Form("plasTCal[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
		//tree->Draw(Form("plasTCal[%d]-plasTimeRef>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax),"Proton");
		//tree->Draw(Form("plasTCal[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
	}


}
