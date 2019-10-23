{

	TChain *tree = new TChain("tree");

//	tree->Add("run0361_analysed.root");
//	tree->Add("run0361_analysed.root");

//	int runStart = 310;
//	int runStop = 320;


//	int runStart = 330;
//	int runStop = 365;
//	int runStart = 330;
//	int runStop = 345;



//	int runStart = 366;
//	int runStop = 445;
	
	int runStart = 435;
	int runStop = 440;
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("run0%d_analysed.root_3",i));
		//tree->Add(Form("run0%d_analysed.root",i));
	}

	//tree->Add(Form("run0%d_analysed.root_2",596));
	//tree->Add(Form("run0%d_analysed.root_2",599));
	//tree->Add(Form("run0%d_analysed.root_2",597));
	//tree->Add(Form("run0%d_analysed.root_2",598));
	//tree->Add(Form("run0%d_analysed.root",310));
	//tree->Add(Form("run0%d_analysed.root",340));
	//tree->Add(Form("run0%d_analysed.root",360));
	//tree->Add(Form("run0%d_analysed.root",588));
	//tree->Add(Form("run0%d_analysed.root",596));
	//tree->Add(Form("run0%d_analysed.root",598));
	//tree->Add(Form("run0%d_analysed.root_2",336));
	//tree->Add(Form("run0%d_analysed.root_2",337));
	//tree->Add(Form("run0%d_analysed.root_2",338));
	//tree->Add(Form("run0%d_analysed.root_2",339));

	gROOT->ProcessLine(".x cutBe12Bar30He8.C");
	gROOT->ProcessLine(".x cutBe12Bar31He8.C");
	gROOT->ProcessLine(".x cutBe12Bar32He8.C");
	gROOT->ProcessLine(".x cutBe12Bar33He8.C");
	gROOT->ProcessLine(".x cutBe12Bar34He8.C");
	gROOT->ProcessLine(".x cutBe12Bar35He8.C");
	gROOT->ProcessLine(".x cutBe12Bar36He8.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutBeamBe14.C");
	gROOT->ProcessLine(".x cutBeamBe12.C");
	gROOT->ProcessLine(".x cutBeamBe10.C");
	
	TString trigger = "Trig_BxESPRI>0&&Trig_DSB==0&&Trig_BxESPRIxTEL==0&&Trig_BxNEBULA==0&&Trig_BxTEL==0";
	TString drawETheta = "2*naiQ[0]:protonTheta>>(500,40,80,500,0,140)";
	TString drawEspriPid = "plasQ[0]:2*naiQ[0]>>(100,0,140,100,0,40)";
//	gROOT->ProcessLine(".x cutBeamPid.C");
//	gROOT->ProcessLine(".x cutBar31Be14.C");
//	gROOT->ProcessLine(".x cutBar30Be14.C");
//	gROOT->ProcessLine(".x cutProton.C");
}
