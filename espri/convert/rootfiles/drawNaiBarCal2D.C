{
	TCanvas *c[2];
	for(int i=0;i<2;i++){
		c[i] = new TCanvas(Form("Nai%d QCal",i),Form("Nai%d QCal",i),800,700);
		c[i]->Divide(3,3);
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<7;j++){
			c[i]->cd(j+1);
			CalTreeESPRI->Draw(Form("naiQCal[%d][%d]:naiQCal[%d][%d]>>hNaiBar%d_%d(1000,0,4000,1000,0,4000)",2*i,j,2*i+1,j,i,j),"","colz");	
		}
	}

	
}
