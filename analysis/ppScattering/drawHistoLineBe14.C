
void drawHistoLineBe14(){
	//TFile *fCurve = new TFile("../../../plot/esBe10Excitation/protonCurve.root","READ");
	//TFile *fCurve = new TFile("../../../plot/esBe12Excitation/protonCurve.root","READ");
	TFile *fCurve = new TFile("../../../plot/esBe14Excitation/protonCurve.root","READ");
	TGraph *gs = (TGraph *)gDirectory->Get("gs");
	gs->SetLineColor(1);
	gs->SetLineStyle(2);
	gs->SetLineWidth(1);
	TGraph *fex = (TGraph *)gDirectory->Get("fex");
	TGraph *sn = (TGraph *)gDirectory->Get("s2n");
	TGraph *mex = (TGraph *)gDirectory->Get("mex");
	//gs->SetLineColor("");

	//TString fileName = "v5_ppBe10Histo.root_Bar19-23_Be9";
	//TString fileName = "v5_ppBe10Histo.root_Bar19-23_Be10";
	//TString fileName = "ppBe10Histo.root";
	//TString fileName1 = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar19-23";
	//TString fileName2 = "v2_ppBe14HistoBe12.root_UsingBe10Calib_Bar19-23";
	//TString fileName3 = "v2_ppBe14HistoBe11.root_UsingBe10Calib_Bar19-23";
	//TString fileName4 = "v2_ppBe14HistoBe10.root_UsingBe10Calib_Bar19-23";
	//TString fileName = "v8_ppBe10Histo.root_newCalibration_Be10";
	//TString fileName = "v9_ppBe10Histo.root_Be9_gs";
	//TString fileName = "v9_ppBe10Histo.root_Be10_gs";
	//TString fileName1 = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar19-32";
	//TString fileName2 = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar27-32";
	//TString fileName3 = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar27-29";
	//TString fileName4 = "v2_ppBe14HistoBe14.root_UsingBe10Calib_Bar19-23";

	//TString fileName1 = "v2_ppSmallBe14HistoBe14Bar19-32.root";
	//TString fileName2 = "v2_ppSmallBe14HistoBe14Bar27-32.root";
	//TString fileName3 = "v2_ppSmallBe14HistoBe14Bar27-29.root";
	//TString fileName4 = "v2_ppSmallBe14HistoBe14Bar19-23.root";

	TString fileName1 = "v2_ppSmallBe14HistoBe14Bar19-23.root";
	TString fileName2 = "v2_ppSmallBe14HistoBe12Bar19-26.root";
	TString fileName3 = "v2_ppSmallBe14HistoBe11Bar19-23.root";
	TString fileName4 = "v2_ppSmallBe14HistoBe10Bar19-23.root";
	

	TCanvas *cPad = new TCanvas("ppBe","ppBe",1400,900);
	cPad->Divide(2,2);
	TH2F *h[4];
        TString hName[8];
        hName[0] = "h";
        hName[1] = "hP";
        hName[2] = "hT";
        hName[3] = "hPT";
        hName[4] = "hB";
        hName[5] = "hBPT";
        hName[6] = "hH";
        hName[7] = "hBPTH";


	cPad->cd(1);
	TFile *g =new TFile(fileName1,"read");
	h[0] =(TH2F *)gDirectory->Get(hName[7]);
	h[0]->Draw("colz");
	//sn->Draw("l");
	gs->Draw("l");

	cPad->cd(2);
	TFile *g =new TFile(fileName2,"read");
	h[1] =(TH2F *)gDirectory->Get(hName[7]);
	h[1]->Draw("colz");
	//sn->Draw("l");
	gs->Draw("l");

	cPad->cd(3);
	TFile *g =new TFile(fileName3,"read");
	h[2] =(TH2F *)gDirectory->Get(hName[7]);
	h[2]->Draw("colz");
	//sn->Draw("l");
	gs->Draw("l");

	cPad->cd(4);
	TFile *g =new TFile(fileName4,"read");
	h[3] =(TH2F *)gDirectory->Get(hName[7]);
	h[3]->Draw("colz");
	//sn->Draw("l");
	gs->Draw("l");


}
