void drawPlasQPedTof(){
	TString fileName1 = "espriQPedTof_Be10.root";
	TFile *f1 = new TFile(fileName1,"READ");
	TH2F *hQPed1 = (TH2F *)f1->Get("hQPed");
	hQPed1->SetMarkerColor(2);
	//hQPed1->SetMarkerSize(30);
	hQPed1->Draw();

//	TString fileName2 = "espriQPedTof_Be12.root";
//	TFile *f2 = new TFile(fileName2,"READ");
//	TH2F *hQPed2 = (TH2F *)f2->Get("hQPed");
//	hQPed2->SetMarkerColor(3);
//	hQPed2->SetMarkerSize(30);
//	hQPed2->Draw("same");

	TString fileName3 = "espriQPedTof_Be14.root";
	TFile *f3 = new TFile(fileName3,"READ");
	TH2F *hQPed3 = (TH2F *)f3->Get("hQPed");
	hQPed3->SetMarkerColor(4);
	hQPed3->SetMarkerSize(40);
	hQPed3->Draw("same");


}
