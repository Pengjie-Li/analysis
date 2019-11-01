
void checkSyncLRPlasTime(){

	//int runNumber = 310;
	//int runNumber = 340;
	int runNumber = 436;

	TString fileName = Form("./rootfiles/run0%d_analysed.root_3",runNumber);
	TFile *inputFile = new TFile(fileName,"READ");	
	TTree *tree =(TTree *) inputFile->Get("tree");
	double tOffset = 1.5;
	tree->Draw(Form("plasT[0]+%f>>h0(1000,-700,-500)",tOffset));
	tree->Draw("plasT[1]>>h1(1000,-700,-500)");
	TH1F *h0 = (TH1F*)gDirectory->Get("h0");
	TH1F *h1 = (TH1F*)gDirectory->Get("h1");

	h0->SetLineColor(1);
	h1->SetLineColor(2);
	TCanvas *cPad = new TCanvas("cPad","cPad",900,700);
	cPad->SetLogy();
	h0->Draw();
	h1->Draw("same");
}
