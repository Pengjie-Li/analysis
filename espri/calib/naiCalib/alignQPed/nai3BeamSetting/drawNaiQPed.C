void drawNaiQPed(){
	int side = 1;
	int barId = 3;
	TString fileName1 = Form("./geneRootfiles/naiBarDEE%d%d_Be10.root",side,barId);
	TFile *f1 = new TFile(fileName1,"READ");
	TH2F *hQPed1 = (TH2F *)f1->Get(Form("hQPed%d%d",side,barId));
	hQPed1->SetMarkerColor(2);
	//hQPed1->SetMarkerSize(30);
	hQPed1->SetMarkerStyle(6);
	hQPed1->Draw();


//	TString fileName2 = Form("naiBarDEE%d%d_Be12.root",side,barId);
//	//TString fileName2 = Form("./geneRootfiles/naiBarDEE%d%d_Be12.root",side,barId);
//	TFile *f2 = new TFile(fileName2,"READ");
//	TH2F *hQPed2 = (TH2F *)f2->Get(Form("hQPed%d%d",side,barId));
//	hQPed2->SetMarkerColor(3);
//	//hQPed2->SetMarkerSize(50);
//	hQPed2->SetMarkerStyle(2);
//	hQPed2->Draw("same");

	TString fileName3 = Form("naiBarDEE%d%d_Be14.root",side,barId);
	//TString fileName3 = Form("./geneRootfiles/naiBarDEE%d%d_Be14.root",side,barId);
	TFile *f3 = new TFile(fileName3,"READ");
	TH2F *hQPed3 = (TH2F *)f3->Get(Form("hQPed%d%d",side,barId));
	hQPed3->SetMarkerColor(4);
	//hQPed3->SetMarkerSize(40);
	hQPed3->SetMarkerStyle(6);
	hQPed3->Draw("same");
}
