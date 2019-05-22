void drawDEE(int runNumber = 360){
	
	TString inputName = Form("../convert/rootfiles/run0%d_ESPRI.root",runNumber);
	TFile *f =new TFile(inputName,"UPDATE");
	TTree *tree = (TTree *)f->Get("CalTreeESPRI");
	tree->Print();
	TCanvas *cDEE = new TCanvas("dE(plas) vs E(nai)","dE(plas) vs E(nai)",1400,800);
	cDEE->Divide(2,1);
	cDEE->cd(1);
	tree->Draw("plasQL:naiQL>>hdEEL(1000,0,4000,1000,0,4000)","","colz");
	cDEE->cd(2);
	tree->Draw("plasQR:naiQR>>hdEER(1000,0,4000,1000,0,4000)","","colz");

	
}
