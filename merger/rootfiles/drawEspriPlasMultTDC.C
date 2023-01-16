{
	TCanvas *c1 = new TCanvas("Plastic Raw TDC","Plastic Raw TDC",800,700);
	c1->Divide(2,2);
	int nBin = 1000;
	//int tMax = 8000;
	int tMax = -21000;
	//int tMin = -1000;
	int tMin = -28000;
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		gPad->SetLogy();
		tree->Draw(Form("plasTdcRaw%d-plasTimeRef>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
		//tree->Draw(Form("plasTdcRaw%d-plasTimeRef>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax),"Proton");
		//tree->Draw(Form("plasTRaw[%d]>>hTPlas%d(%d,%d,%d)",i,i,nBin,tMin,tMax));
	}


}
