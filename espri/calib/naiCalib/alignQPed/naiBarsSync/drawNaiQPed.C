void drawNaiQPed(){
	int refSide = 0;
	int refBarId = 0;
	TString fileName1 = Form("./geneRootfiles/naiBarDEE%d%d_Be10.root",refSide,refBarId);
	TFile *f1 = new TFile(fileName1,"READ");
	TH2F *hQPed1 = (TH2F *)f1->Get(Form("hQPed%d%d",refSide,refBarId));
	hQPed1->SetMarkerColor(2);
	//hQPed1->SetMarkerSize(30);
	hQPed1->SetMarkerStyle(6);
	hQPed1->Draw();


	int side = refSide;
	int barId = 1;
	TString fileName2 = Form("naiBarDEE%d%d_Be10.root",side,barId);
	//TString fileName2 = Form("./geneRootfiles/naiBarDEE%d%d_Be10.root",side,barId);
	TFile *f2 = new TFile(fileName2,"READ");
	TH2F *hQPed2 = (TH2F *)f2->Get(Form("hQPed%d%d",side,barId));
	hQPed2->SetMarkerColor(3);
	//hQPed2->SetMarkerSize(50);
	hQPed2->SetMarkerStyle(2);
	hQPed2->Draw("same");

}
