{

	TCanvas *c2 = new TCanvas("Plastic Raw QDC","Plastic Raw QDC",800,700);
	c2->Divide(2,2);
	for(int i=0;i<4;i++){
		c2->cd(i+1);
		CalTreeESPRI->Draw(Form("plasQRaw[%d]>>hQPlas%d(1000,150,4150)",i,i));
	}
	TCanvas *c3 = new TCanvas("Plastic Raw QPed","Plastic Raw QPed",800,700);
	c3->Divide(2,2);
	for(int i=0;i<4;i++){
		c3->cd(i+1);
		CalTreeESPRI->Draw(Form("plasQRaw[%d]>>hQPedPlas%d(150,50,200)",i,i));
	}



}
