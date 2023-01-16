{
	gStyle->SetStatH(0.15);
	gStyle->SetStatW(0.18);
	gStyle->SetOptFit(1);
	
	TString leftCsI = "(CsILL_CAL>400||CsILRT_CAL>400||CsILRB_CAL>400)";
	TString rightCsI = "(CsIRLT_CAL>400||CsIRLB_CAL>400||CsIRRT_CAL>400||CsIRRB_CAL>400)";
	TString R1="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";
	TString multi = "multiplicityLB==1&&multiplicityLF==1";
	TString hName = gDirectory->GetName();
	//tree->Draw("pixelX>>"+hName+"(200,-20,20)",multi+"&&"+R1+"&&"+leftCsI,"colz");
	tree->Draw("pixelX>>"+hName+"(200,-20,20)",multi+"&&"+R1,"colz");
	TH1F *hCurrent =(TH1F *)gDirectory->Get(hName);
	hCurrent->Fit("gaus");
}
