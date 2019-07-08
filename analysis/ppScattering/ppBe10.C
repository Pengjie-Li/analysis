{

	bool isDrawEAng = true;
	bool isDrawTOFAng = false;

	int runStart = 298;
	//int runStop = 330;
	int runStop = 311;

	TString gate[8];
	TString hName[8];
	TH2F *h[8];

	TString targetArea = "sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
	TString hodGate = "(Bar23Be10||Bar22Be10||Bar21Be10||Bar20Be10||Bar19Be10)";
	gate[0] = "";
	gate[1] = "Proton";
	gate[2] = targetArea;
	gate[3] = "Proton&&"+gate[2];
	gate[4] = "BeamBe10";
	gate[5] = "BeamBe10&&"+gate[3];
	gate[6] = hodGate;
	gate[7] = gate[5] +"&&"+hodGate;

	hName[0] = "h";
	hName[1] = "hP";
	hName[2] = "hT";
	hName[3] = "hPT";
	hName[4] = "hB";
	hName[5] = "hBPT";
	hName[6] = "hH";
	hName[7] = "hBPTH";

	TChain *tree = new TChain("tree");
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("rootfiles/run0%d_analysed.root",i));
	}

	gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
	gROOT->ProcessLine(".x rootfiles/cutProtonBe10.C");
	gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
	gROOT->ProcessLine(".x rootfiles/cutHodBe10.C");

	gROOT->ProcessLine(".x rootfiles/cutBar23Be10.C");
	gROOT->ProcessLine(".x rootfiles/cutBar22Be10.C");
	gROOT->ProcessLine(".x rootfiles/cutBar21Be10.C");
	gROOT->ProcessLine(".x rootfiles/cutBar20Be10.C");
	gROOT->ProcessLine(".x rootfiles/cutBar19Be10.C");
	

	TFile *g = new TFile("ppBe10Histo.root","recreate");
	if(isDrawEAng){
		TCanvas *c = new TCanvas("ppET","ppET",1500,900);
		c->Divide(4,2);

		TString drawVar = "2*naiQ[0]:protonTheta>>";
		TString drawRange = "(200,40,80,200,0,200)";
		for (int i = 0; i < 8; ++i) {
			c->cd(i+1);	
			TString draw = drawVar + hName[i] + drawRange;
			tree->Draw(draw,gate[i],"colz");
			h[i] = (TH2F*)gDirectory->Get(hName[i]);
			h[i]->Write();
		}
		
	}

	c->Write();
	g->Close();
	
}
