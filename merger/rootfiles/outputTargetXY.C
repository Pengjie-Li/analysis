void outputTargetXY(){

	TChain *tree = new TChain("tree");
	TString hName = "Be14TargetXY";
	tree->Add("run0380_analysed.root");

	TString gate = "Trig_DSB";
	tree->Draw("targetPosition.Y():targetPosition.X()>>"+hName+"(1000,-50,50,1000,-50,50)",gate,"colz");
	TH2F *h = (TH2F*)gDirectory->Get(hName);

	TFile *output = new TFile("BeamXYProfile.root", "UPDATE");
	h->Write();
}
