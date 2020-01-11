{
	bool checkLeft = false;
	//bool checkLeft = true;

	TH1F *h[7];
	if(checkLeft){
		for (int i = 4; i < 7; ++i) {

			tree->Draw(Form("teleCsiE>>h%d(1000,0,1000)",i),Form("teleHit==1&&teleHitCid[0]==%d",i));
		}
		for (int i = 4; i < 7; ++i) {

			h[i] = (TH1F *)gDirectory->Get(Form("h%d",i));
			h[i]->SetLineColor(i+1);
			if(i==4) h[i]->Draw();
			else h[i]->Draw("same");
			gPad->SetLogy();
		}

	}else{

		for (int i = 0; i < 4; ++i) {

			tree->Draw(Form("teleCsiE>>h%d(1000,0,1000)",i),Form("teleHit==1&&teleHitCid[0]==%d",i));
		}
		for (int i = 0; i < 4; ++i) {

			h[i] = (TH1F *)gDirectory->Get(Form("h%d",i));
			h[i]->SetLineColor(i+1);
			if(i==0) h[i]->Draw();
			else h[i]->Draw("same");
			gPad->SetLogy();
		}
	}
}
