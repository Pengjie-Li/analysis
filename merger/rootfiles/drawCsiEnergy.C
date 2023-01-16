{
	for (int i = 0; i < 7; ++i) {
		tree->Draw(Form("csiEnergyCal[%d]>>hCsI%d(1000,10,700)",i,i));
	}

	TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
	TH1F *hTemp[7];
	TLegend *legends=new TLegend(0.2,0.4,0.5,0.9); // the numbers determine the position of the box    
	// setting for legend
	legends->SetFillColor(0);    
	legends->SetHeader("CsI Energy"); 
	legends->SetTextFont(72);
	legends->SetTextSize(0.04);
	TString nameCsi[7] = {"RLT","RRT","RLB","RRB","LL","LRT","LRB"}

	for (int i = 0; i < 7; ++i) {
		hTemp[i] = (TH1F*)gDirectory->Get(Form("hCsI%d",i));	
		hTemp[i]->SetLineColor(i+1);
		int binmax = hTemp[i]->GetMaximumBin(); double x = hTemp[i]->GetXaxis()->GetBinCenter(binmax);
		hTemp[i]->Scale(1./x);
		hTemp[i]->GetYaxis()->SetRangeUser(0,20);
		if(i>0) hTemp[i]->Draw("same");
		else hTemp[i]->Draw();

		//legends->AddEntry(hTemp[i], Form("hCsI%d",i),"l");
		legends->AddEntry(hTemp[i], nameCsi[i],"l");
	}

	legends->Draw();
}
