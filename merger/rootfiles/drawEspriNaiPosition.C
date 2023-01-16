{
	int side = 0;
	TCanvas *cNai = new TCanvas("cNai","cNai",1900,100);
	cNai->Divide(7,1);
	for (int i = 0; i < 7; ++i) {
		cNai->cd(i+1);
		//gPad->SetMaximum(20);
		tree->Draw(Form("rdcY[%d]:rdcX[%d]>>h%d(1000,0,500,1000,0,500)",side,side,i),Form("plasQ[%d]>0&&naiBarQCal[%d][%d]>4",side,side,i),"colz");
		TH2F *hTemp = (TH2F *)gDirectory->Get(Form("h%d",i));
		hTemp->SetMaximum(200);
	}
}
