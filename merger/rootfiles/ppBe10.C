{

	TChain *tree = new TChain("tree");

//	tree->Add("run0361_analysed.root");
//	tree->Add("run0361_analysed.root");

	int runStart = 294;
	int runStop = 330;
	//int runStop = 295;
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("run0%d_analysed.root",i));
	}

	TString drawETheta = "2*naiQ[0]:protonTheta>>(500,40,80,500,0,140)";
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutBe10Pronton.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutBe10HodBe10.C");
	TCanvas *c = new TCanvas(" Proton E vs Theta  ","  Proton E vs Theta   ",1500,900);
	c->Divide(4,2);

	c->cd(1);
	tree->Draw("2*naiQ[0]:protonTheta>>h(200,40,80,200,0,200)","","colz");
	c->cd(2);
	tree->Draw("2*naiQ[0]:protonTheta>>hP(200,40,80,200,0,200)","Proton","colz");
	c->cd(3);
	tree->Draw("2*naiQ[0]:protonTheta>>hT(200,40,80,200,0,200)",peak5,"colz");
	c->cd(4);
	tree->Draw("2*naiQ[0]:protonTheta>>hPT(200,40,80,200,0,200)","Proton&&"+peak5,"colz");
	c->cd(5);
	tree->Draw("2*naiQ[0]:protonTheta>>hB(200,40,80,200,0,200)","BeamBe10","colz");
	c->cd(6);
	tree->Draw("2*naiQ[0]:protonTheta>>hBPT(200,40,80,200,0,200)","BeamBe10&&Proton&&"+peak5,"colz");
	c->cd(7);
	tree->Draw("2*naiQ[0]:protonTheta>>hH(200,40,80,200,0,200)","HodBe10","colz");
	c->cd(8);
	tree->Draw("2*naiQ[0]:protonTheta>>hBPTH(200,40,80,200,0,200)","BeamBe10&&Proton&&HodBe10&&"+peak5,"colz");
}
