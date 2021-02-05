void drawPad(){

	//gStyle->SetOptStat(0);
	//gROOT->SetStyle("BABAR");
	//TString fileName = "output/generate.root";
	//TString fileName = "run0300_330_ppBe.root_test";
	TString fileName = "run0331_365_ppBe.root_test";
	TFile *outputFile = new TFile(fileName,"READ");

	TH1 *hBDC1[8];
	TH1 *hBDC2[8];
	TH1 *hFDC0[8];
	for (int i = 0; i < 8; ++i) {
		hBDC1[i] = (TH1*)gDirectory->Get(Form("hbdc1tdc%d",i));
		hBDC2[i] = (TH1*)gDirectory->Get(Form("hbdc2tdc%d",i));
		hFDC0[i] = (TH1*)gDirectory->Get(Form("hfdc0tdc%d",i));
	}

	//drawCurve(hBDC1);
	//drawCurve(hBDC2);
	drawCurve(hFDC0);
}
void drawCurve(TH1 *h1D[8]){

	TCanvas *cPad = new TCanvas("cPad","cPad",1000,900);
	//cPad->Divide(4,2);

	for (int i = 0; i < 8; ++i) {

		//cPad->cd(i+1);
		cPad->SetFillColor(0);
		cPad->SetFillStyle(4000);

		TGaxis::SetMaxDigits(4);
		h1D[i]->SetTitle("");
		h1D[i]->GetYaxis()->SetTitle("Counts");
		h1D[i]->GetXaxis()->SetTitle("TDC (ch) ");
		h1D[i]->GetXaxis()->CenterTitle();
		h1D[i]->GetYaxis()->CenterTitle();
		h1D[i]->SetLineColor(i+1);
		if(i==0) h1D[i]->Draw();
		else h1D[i]->Draw("same");
		//drawText(Form("(FDC0 X%d)",i));
		//drawText(Form("#sigma = %4.2f um",1000*f->GetParameter(2)), 0.7, 0.8);



	}

}
