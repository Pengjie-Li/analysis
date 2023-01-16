
void oneRunGenerate(){

	TChain *tree = new TChain("tree");

	int side = 1;
	int barId = 3;
	int runStart = 445;
	int runStop = runStart+5;

	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
	}

	double gain = 1.7;
	gROOT->ProcessLine(".x rootfiles/setAlias.C");
	TString targetArea="sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<13";

	double plasGain = 1.0;
	if(runStart>330&&runStop<366) plasGain = 1.05;
	tree->Draw(Form("%f*plasBarQPed%d:%4f*naiBarQPed%d%d>>hQPed%d%d(1000,0,4000,1000,0,4000)",plasGain,side,gain,side,barId,side,barId),Form("Trig_BxESPRI&&isEspriLR==%d&&",side)+targetArea,"");

	TH2F *hQPed = (TH2F *)gDirectory->Get(Form("hQPed%d%d",side,barId));
	TFile *outputFile = new TFile(Form("geneRootfiles/naiBar%2fDEE%d%d_%d.root",gain,side,barId,runStart),"RECREATE");
	hQPed->Write();
	outputFile->Close();
}
