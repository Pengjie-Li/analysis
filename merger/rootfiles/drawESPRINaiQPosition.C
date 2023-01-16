{
	TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
	cPad->Divide(2,1);
	cPad->cd(1);	
	TH1 *hRdcY[2][7];
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {

			tree->Draw(Form("rdcY[%d]>>h%d_%d(100,0,500)",i,i,j),Form("naiQPed[%d][%d]>100&&naiQPed[%d][%d]>100",2*i,j,2*i+1,j));
			hRdcY[i][j] = (TH1 *)gDirectory->Get(Form("h%d_%d",i,j));
		}

	}
	for (int i = 0; i < 2; ++i) {
		cPad->cd(i+1);
		for (int j = 0; j < 7; ++j) {
			hRdcY[i][j]->SetLineColor(j+1);
			if(j>0) hRdcY[i][j]->Draw("same");
			else hRdcY[i][j]->Draw();
		}
	}


}
