
void generateHistogram(){
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {
			generateHistogram(i,j);
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {
			write(i,j);
		}
	}



}

void generateHistogram(int side, int barId){

	TChain *tree = new TChain("tree");

//	int runStart = 298;
//	int runStop = 330;
//	int runStart =334;
//	int runStop = 365;
	int runStart =366;
	int runStop = 456;
//	
//	int runStart = 380;
//	int runStop = runStart+1;

	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
	}

	tree->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
	tree->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {

			tree->SetAlias(Form("naiBarQPed%d%d",i,j),Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d])",2*i,j,2*i+1,j));
		}

	}

	TString targetArea="sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<13";

	tree->Draw(Form("plasBarQPed%d:naiBarQPed%d%d>>hQPed%d%d(1000,0,4000,1000,0,4000)",side,side,barId,side,barId),Form("Trig_BxESPRI&&isEspriLR==%d&&",side)+targetArea,"");

}
void write(int side, int barId){

	TH2F *hQPed = (TH2F *)gDirectory->Get(Form("hQPed%d%d",side,barId));
	TFile *outputFile = new TFile(Form("geneRootfiles/naiBarDEE%d%d_Be14.root",side,barId),"RECREATE");
	hQPed->Write();
	outputFile->Close();
}
