{
	TCanvas *c1 = new TCanvas("Plastic Slew Effect","Plastic Slew Effect",800,700);
	c1->Divide(2,2);
	int nBin = 1000;
	int tMin = -30000;
	int tMax = -20000;
	//int tMax = 25000;
	int qMin = 50;
	int qMax = 4050;
	for(int i=0;i<4;i++){
		c1->cd(i+1);
		CalTreeESPRI->Draw(Form("plasTCal[%d]:plasQCal[%d]>>hSlewPlas%d(%d,%d,%d,%d,%d,%d)",i,i,i,nBin,qMin,qMax,nBin,tMin,tMax),"","colz");
	}
}
