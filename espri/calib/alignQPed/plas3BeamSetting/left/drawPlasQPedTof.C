void drawPlasQPedTof(){
	//TString fileName1 = "espriQPedTof_Be10.root";
//	TString fileName1 = "espriQPedTof294_330.root";
//	//TString fileName1 = "espri1.1QPedTof320.root";
//	TFile *f1 = new TFile(fileName1,"READ");
//	TH2F *hQPed1 = (TH2F *)f1->Get("hQPed");
//	hQPed1->SetMarkerColor(2);
//	//hQPed1->SetMarkerSize(30);
//	hQPed1->Draw();

	TString fileName2 = "espri1.1QPedTof334_365.root";
	//Gain
	//TString fileName2 = "espriQPedTof340.root";
	//TString fileName2 = "espri1.15QPedTof340.root";
	//TString fileName2 = "espri1.05QPedTof340.root";
	//TString fileName2 = "espri1.1QPedTof340.root";
	//TString fileName2 = "espri1.1QPedTof340.root";
	TFile *f2 = new TFile(fileName2,"READ");
	TH2F *hQPed2 = (TH2F *)f2->Get("hQPed");
	hQPed2->SetMarkerColor(3);
	//hQPed2->SetMarkerSize(50);
	//hQPed2->SetMarkerStyle(6);
	hQPed2->Draw("same");

	//TString fileName3 = "espriQPedTof366_456.root";
	TString fileName3 = "espriQPedTof420.root";
	//TString fileName3 = "espriQPedTof_Be14.root";
	TFile *f3 = new TFile(fileName3,"READ");
	TH2F *hQPed3 = (TH2F *)f3->Get("hQPed");
	hQPed3->SetMarkerColor(4);
	//hQPed3->SetMarkerSize(40);
	hQPed3->Draw("same");
}
