void draw(){
	TString fileName1 = "v9_exBe10Histo.root_Be10";
	TFile *file1 = new TFile(fileName1,"READ");
	TH2F *hBPT1 = (TH2F*)gDirectory->Get("hBPT");
	TH2F *hBPTH1 = (TH2F*)gDirectory->Get("hBPTH");
	hBPT1->SetLineColor(1);
	hBPTH1->SetLineColor(2);

	TString fileName2 = "v9_exBe10Histo.root_Be9";
	TFile *file2 = new TFile(fileName2,"READ");
	TH2F *hT2 = (TH2F*)gDirectory->Get("hT");
	TH2F *hBPT2 = (TH2F*)gDirectory->Get("hBPT");
	TH2F *hBPTH2 = (TH2F*)gDirectory->Get("hBPTH");
	hT2->SetLineColor(1);
	hBPT2->SetLineColor(3);
	hBPTH2->SetLineColor(4);

	//hT2->Draw();
	//hBPT2->Draw("same");
	//hBPTH2->Draw("same");

	//hBPT1->Rebin(5);
	hBPT1->Draw();
	hBPTH1->Draw("same");
	hBPT2->Draw("same");
	hBPTH2->Draw("same");
	//
	//hBPTH1->Rebin(5);
	//hBPTH2->Rebin(5);
	//hBPTH1->Draw();
	//hBPTH2->Draw("same");
}
