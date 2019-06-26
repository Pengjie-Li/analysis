{

	TChain *tree = new TChain("tree");

//	tree->Add("run0361_analysed.root");
//	tree->Add("run0361_analysed.root");

	int runStart = 361;
	int runStop = 450;
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("run0%d_analysed.root",i));
	}

	TString drawETheta = "2*naiQ[0]:protonTheta>>(500,40,80,500,0,140)";
	TString drawEspriPid = "plasQ[0]:2*naiQ[0]>>(100,0,140,100,0,40)";
	gROOT->ProcessLine(".x cutBeamPid.C");
	gROOT->ProcessLine(".x cutBar31Be14.C");
	gROOT->ProcessLine(".x cutBar30Be14.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutProton.C");
}
