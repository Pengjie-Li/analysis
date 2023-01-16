
void drawHistoLine(){
	//TFile *fCurve = new TFile("../../../plot/esBe10Excitation/protonCurve.root","READ");
	TFile *fCurve[4];
	TGraph *gCurve[4];
	fCurve[0] = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/protonCurve.root","READ");
	gCurve[0] = (TGraph *)gDirectory->Get("ProtonEnergyAngle");
	fCurve[1] = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/alphaCurve.root","READ");
	gCurve[1] = (TGraph *)gDirectory->Get("AlphaEnergyAngle");
	fCurve[2] = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/angleCurve.root","READ");
	gCurve[2] = (TGraph *)gDirectory->Get("angle");
	fCurve[3] = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/energyCurve.root","READ");
	gCurve[3] = (TGraph *)gDirectory->Get("energy");


	for (int i = 0; i < 4; ++i) {
		gCurve[i]->SetLineColor(1);
	}

	//TString fileName = "v2_ppaBe12Histo.root_TargetXReversed";
	//TString fileName = "v3_ppaBe12Histo.root_GateOnlyHe8";
	TString fileName = "v3_ppaBe14HistoHe4Bar3-17.root_BeamGateSBT1AndSBT2";
	//TString fileName = "ppaBe10Histo.root";
	TFile *g =new TFile(fileName,"read");
	TCanvas *cPad = new TCanvas("ppBe","ppBe",1400,900);
	cPad->Divide(2,2);
	TH2F *h[4];
	TString hName[4];
	hName[0] = "hEspriEvsA";
	hName[1] = "hTeleEvsA";
	hName[2] = "hEspriAvsTeleA";
	hName[3] = "hEspriEvsTeleE";

	for (int i = 0; i < 4; ++i) {

		cPad->cd(i+1);
		h[i] =(TH2F *)gDirectory->Get(hName[i]);
		h[i]->Draw("colz");
		gCurve[i]->Draw("plsame*");
	}
}
