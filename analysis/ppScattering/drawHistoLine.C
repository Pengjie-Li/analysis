
void drawHistoLine(){
	//TFile *fCurve = new TFile("../../../plot/esBe10Excitation/protonCurve.root","READ");
	TFile *fCurve = new TFile("../../../plot/esBe12Excitation/protonCurve.root","READ");
	//TFile *fCurve = new TFile("../../../plot/esBe14Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	//TGraph *sn = (TGraph *)gDirectory->Get("s2n");
	TGraph *sn = (TGraph *)gDirectory->Get("sn");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");
	gs->SetLineColor(1);
	gs->SetLineWidth(1);
	gs->SetLineStyle(1);

	//TString fileName = "v10_ppBe10Histo.root_TargetXReversed";
	TString fileName = "v8_ppBe10Histo.root_newCalibration_Be10";
	//TString fileName = "v1_ppBe12Histo.root_Be12_fexCalib";
	//TString fileName = "v10_ppBe12Histo.root_TargetXReversed";
	//TString fileName = "ppBe10Histo.root";
	//TString fileName = "ppBe12Histo.root";
	TFile *g =new TFile(fileName,"read");
	TCanvas *cPad = new TCanvas("ppBe","ppBe",1400,900);
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
		//fex->Draw("l");
		//sn->Draw("l");
		//mex->Draw("l");
	}
}
