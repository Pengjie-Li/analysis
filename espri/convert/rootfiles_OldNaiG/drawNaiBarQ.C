{
	int nBin = 1000;
	int min = 10;
	int max = 150;
	TCanvas *c[2];
	for(int i=0;i<2;i++){
		c[i] = new TCanvas(Form("Nai%d QCal",i),Form("Nai%d QCal",i),800,700);
		c[i]->Divide(3,3);
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<7;j++){
			c[i]->cd(j+1);
			CalTreeESPRI->Draw(Form("naiBarQCal[%d][%d]>>hNai%d_%d(%d,%d,%d)",i,j,i,j,nBin,min,max));	
		}
	}
	
}
