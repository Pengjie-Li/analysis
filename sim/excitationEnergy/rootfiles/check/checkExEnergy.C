void checkExEnergy(){

	double sigmaE = 0.005;
	double sigmaTheta = 0.2;
	//TString fileName1 = Form("../rootfiles/exPPBe14_%4.3f_%4.3f.root",sigmaE,sigmaTheta);
//	TString fileName1 = "../exPPBe14_0.005_0.250.root";
//	TString fileName2 = "../exPPBe14_0.005_0.300.root";
//	TString fileName3 = "../exPPBe14_0.005_0.350.root";
//	TString fileName4 = "../exPPBe14_0.005_0.400.root";
//
	TString fileName1 = "../exPPBe14_0.035_0.300.root";
	TString fileName2 = "../exPPBe14_0.040_0.300.root";
	TString fileName3 = "../exPPBe14_0.045_0.300.root";
	TString fileName4 = "../exPPBe14_0.050_0.300.root";



	TFile *f1 = new TFile(fileName1,"READ");
	TTree *tree1 = (TTree*)f1->Get("tree");
	tree1->Draw("exEnergy>>h1(1000,-10,10)");
	TH1F *h1 = (TH1F *)gDirectory->Get("h1");
	h1->SetLineColor(1);
	//f1->Close();

	TFile *f2 = new TFile(fileName2,"READ");
	TTree *tree2 = (TTree*)f2->Get("tree");
	tree2->Draw("exEnergy>>h2(1000,-10,10)");
	TH1F *h2 = (TH1F *)gDirectory->Get("h2");
	h2->SetLineColor(2);
	//f2->Close();

	TFile *f3 = new TFile(fileName3,"READ");
	TTree *tree3 = (TTree*)f3->Get("tree");
	tree3->Draw("exEnergy>>h3(1000,-10,10)");
	TH1F *h3 = (TH1F *)gDirectory->Get("h3");
	h3->SetLineColor(3);
	//f3->Close();

	TFile *f4 = new TFile(fileName4,"READ");
	TTree *tree4 = (TTree*)f4->Get("tree");
	tree4->Draw("exEnergy>>h4(1000,-10,10)");
	TH1F *h4 = (TH1F *)gDirectory->Get("h4");
	h4->SetLineColor(4);
	//f4->Close();


	h1->Draw();
	h2->Draw("same");
	h3->Draw("same");
	h4->Draw("same");

}
