
void drawHistoLine(){
	//TFile *fCurve = new TFile("../../../plot/esBe10Excitation/protonCurve.root","READ");
	TFile *fCurve = new TFile("../../../plot/esBe12Excitation/protonCurve.root","READ");
	//TFile *fCurve = new TFile("../../../plot/esBe14Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	//TGraph *sn = (TGraph *)gDirectory->Get("s2n");
	TGraph *sn = (TGraph *)gDirectory->Get("sn");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");
	//gs->SetLineColor("");

	//TString fileName = "v5_ppBe10Histo.root_Bar19-23_Be9";
	//TString fileName = "v5_ppBe10Histo.root_Bar19-23_Be10";
	//TString fileName = "ppBe10Histo.root";
	TString fileName = "ppBe12Histo.root";
	//TString fileName = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar19-32";
	//TString fileName = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar27-29";
	//TString fileName = "v2_ppBe14HistoBe10.root_UsingBe10Calib_Bar19-23";
	//TString fileName = "v8_ppBe10Histo.root_newCalibration_Be10";
	//TString fileName = "v9_ppBe10Histo.root_Be9_gs";
	//TString fileName = "v9_ppBe10Histo.root_Be10_gs";
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
		fex->Draw("l");
		sn->Draw("l");
		mex->Draw("l");
	}
}
