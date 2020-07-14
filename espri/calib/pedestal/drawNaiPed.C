{
	TCanvas *c[4];
	TH1F *hNai[4][7];
	TF1 *hFit[4][7];
	for(int i=0;i<4;i++){
		c[i] = new TCanvas(Form("Nai%d QRaw",i),Form("Nai%d QRaw",i),800,700);
		c[i]->Divide(3,3);
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<7;j++){
			c[i]->cd(j+1);
			CalTreeESPRI->Draw(Form("naiQRaw[%d][%d]>>hNai%d_%d(100,50,150)",i,j,i,j));	
			hNai[i][j] = (TH1F *)gDirectory->Get(Form("hNai%d_%d",i,j));
			hNai[i][j]->Fit("gaus","Q");
			hFit[i][j] = (TF1 *)hNai[i][j]->GetFunction("gaus");
			cout<<"\t"<<i<<"\t"<<j<<"\t"<<hFit[i][j]->GetParameter(1)<<"\t"<<hFit[i][j]->GetParError(1)<<endl;
			gPad->Modified();
			gPad->Update();
		}
	}

	
}
