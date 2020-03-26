{

	TChain *tree = new TChain("tree");

//	tree->Add("run0596_analysed.root");
//	tree->Add("run0599_analysed.root");

//	tree->Add("run0597_analysed.root");
//	tree->Add("run0598_analysed.root");


//	int runStart = 294;
//	int runStop = 329;
//	int runStart = 310;
//	int runStop = 320;
//	int runStart = 340;
//	int runStop = 360;
//	int runStart = 370;
//	int runStop = 400;






//	int runStart = 330;
//	int runStop = 365;
//	int runStart = 340;
//	int runStop = 345;

	int runStart = 587;
	int runStop = 595;



//	int runStart = 366;
//	int runStop = 376;
	
//	int runStart = 300;
//	int runStop = 310;
//	int runStart = 425;
//	int runStop = 440;
	for (int i = runStart; i < runStop; ++i) {
		
		//tree->Add(Form("run0%d_analysed.root_3",i));
		tree->Add(Form("run0%d_analysed.root",i));
	}

	//tree->Add(Form("run0%d_analysed.root_test",596));
	//tree->Add(Form("run0%d_analysed.root_2",599));
	//tree->Add(Form("run0%d_analysed.root_test",597));
	//tree->Add(Form("run0%d_analysed.root_2",598));
	//tree->Add(Form("run0%d_analysed.root_test",310));
	//tree->Add(Form("run0%d_analysed.root_test",311));
	//tree->Add(Form("run0%d_analysed.root_test",312));
	//tree->Add(Form("run0%d_analysed.root_test",313));
	//tree->Add(Form("run0%d_analysed.root_test",314));
	//tree->Add(Form("run0%d_analysed.root_test",315));
	//tree->Add(Form("run0%d_analysed.root_test",316));
	//tree->Add(Form("run0%d_analysed.root_test",389));
	//tree->Add(Form("run0%d_analysed.root_test",408));
	//tree->Add(Form("run0%d_analysed.root",340));
	//tree->Add(Form("run0%d_analysed.root",360));
	//tree->Add(Form("run0%d_analysed.root",588));
	//tree->Add(Form("run0%d_analysed.root",596));
	//tree->Add(Form("run0%d_analysed.root",598));
	//tree->Add(Form("run0%d_analysed.root_2",336));
	//tree->Add(Form("run0%d_analysed.root_2",337));
	//tree->Add(Form("run0%d_analysed.root_2",338));
	//tree->Add(Form("run0%d_analysed.root_2",339));


}
