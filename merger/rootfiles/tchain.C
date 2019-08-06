{

	TChain *tree = new TChain("tree");

//	tree->Add("run0361_analysed.root");
//	tree->Add("run0361_analysed.root");

	int runStart = 300;
	int runStop = 310;


	//int runStart = 350;
	//int runStop = 365;

	//int runStart = 366;
	//int runStop = 440;
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("run0%d_analysed.root",i));
	}

}
