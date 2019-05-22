{
	TCanvas *c[4];
	for(int i=0;i<4;i++){
		c[i] = new TCanvas(Form("Nai%d QRaw",i),Form("Nai%d QRaw",i),800,700);
		c[i]->Divide(3,3);
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<7;j++){
			c[i]->cd(j+1);
			CalTreeESPRI->Draw(Form("naiRaw[%d][%d]>>hNai%d_%d(1000,200,4200)",i,j,i,j));	
		}
	}

	
}
