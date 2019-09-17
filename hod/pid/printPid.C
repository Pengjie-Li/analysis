{
	gStyle->SetOptStat(0);
	gPad->SetLogz();
	for (int i = 0; i < 1; ++i) {
		TH2F *hTemp = (TH2F*)gDirectory->Get(Form("hHod%d",i));	
		hTemp->Draw("colz");
		TLatex *tex = new TLatex(1290,3600,Form("Bar%d",i));
		tex->SetTextSize(0.25);
		tex->Draw();
		gPad->Print(Form("./png/hodPidBar%d.png",i));
	}
}
