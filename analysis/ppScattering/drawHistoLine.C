
void drawHistoLine(){
	TFile *fCurve = new TFile("../../../plot/esBe10Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");

	TFile *g =new TFile("v2_ppBe10Histo.root","read");
	TCanvas *cPad = new TCanvas("ppBe10L","ppBe10L",1400,900);
	cPad->Divide(4,2);
	TH2F *h[8];
        TString hName[8];
        hName[0] = "h";
        hName[1] = "hP";
        hName[2] = "hT";
        hName[3] = "hPT";
        hName[4] = "hB";
        hName[5] = "hBPT";
        hName[6] = "hH";
        hName[7] = "hBPTH";

	for (int i = 0; i < 8; ++i) {

		cPad->cd(i+1);
		h[i] =(TH2F *)gDirectory->Get(hName[i]);
		h[i]->Draw("colz");
		gs->Draw("l");
		fex->Draw("l");
		mex->Draw("l");
	}
}
