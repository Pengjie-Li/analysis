{

	TString smallArea="sqrt((-Target_X+6)*(-Target_X+6)+(Target_Y)*(Target_Y))<3";
	gROOT->ProcessLine(".x cutTargetArea.C");
	for (int i = 0; i < 7; ++i) {
		//tree->Draw(Form("csiEnergyRaw[%d]>>hCsI%d(1000,0,4000)",i,i),targetArea);
		tree->Draw(Form("csiTRaw[%d]>>hCsI%d(200,0,200)",i,i),targetArea);
	}

	//TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
	TH1F *hTemp[7];
	TLegend *legends=new TLegend(0.2,0.4,0.5,0.9); // the numbers determine the position of the box    
	// setting for legend
	legends->SetFillColor(0);    
	legends->SetHeader("CsI Energy"); 
	legends->SetTextFont(72);
	legends->SetTextSize(0.04);
	TString nameCsi[7] = {"RLT","RRT","RLB","RRB","LL","LRT","LRB"};

	for (int i = 0; i < 7; ++i) {
		hTemp[i] = (TH1F*)gDirectory->Get(Form("hCsI%d",i));	
		hTemp[i]->SetLineColor(i+1);
		//int binmax = hTemp[i]->GetMaximumBin(); double x = hTemp[i]->GetXaxis()->GetBinCenter(binmax);
		hTemp[i]->Scale(1./hTemp[i]->GetMaximum());
		hTemp[i]->GetYaxis()->SetRangeUser(0,2);
		if(i>0) hTemp[i]->Draw("same");
		else hTemp[i]->Draw();

		//legends->AddEntry(hTemp[i], Form("hCsI%d",i),"l");
		legends->AddEntry(hTemp[i], nameCsi[i],"l");
	}

	legends->Draw();
}
