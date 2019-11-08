void generateHistogram(){

	TChain *tree = new TChain("tree");

//	int runStart = 298;
//	int runStop = 330;
	int runStart =334;
	int runStop = 365;
//	int runStart =366;
//	int runStop = 456;
//	
//	int runStart = 320;
//	int runStop = runStart+1;
//	int runStop = 360;
//	int runStart = 370;
//	int runStop = 375;
//	int runStop = 400;

	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("rootfiles/run0%d_analysed.root_test",i));
	}

	gROOT->ProcessLine(".x rootfiles/setAlias.C");
	TString targetArea="sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<13";

	tree->Draw("1.1*plasBarQPed0:espriLTOF>>hQPed(1000,0,50,1000,0,4100)","Trig_BxESPRI&&isEspriLR==0&&"+targetArea,"");
	//tree->Draw("plasBarQPed0:espriLTOF>>hQPed(1000,0,50,1000,0,4100)","Trig_BxESPRI&&isEspriLR==0&&"+targetArea,"");

	TH2F *hQPed = (TH2F *)gDirectory->Get("hQPed");
	TFile *outputFile = new TFile(Form("espri1.1QPedTof%d.root",runStart),"RECREATE");
	hQPed->Write();
}
