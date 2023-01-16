{

	TChain *tree = new TChain("tree");

//	tree->Add("run0361_analysed.root");
//	tree->Add("run0361_analysed.root");

	bool isDrawEAng = true;
	bool isDrawTOFAng = false;

	int runStart = 450;
	int runStop = 451;
	//int runStop = 456;
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("run0%d_analysed.root",i));
	}

	TString drawETheta = "2*naiQ[0]:protonTheta>>(500,40,80,500,0,140)";
	gROOT->ProcessLine(".x cutBeamBe14.C");
	gROOT->ProcessLine(".x cutProtonBe14.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutHodBe14.C");

	gROOT->ProcessLine(".x cutBar32Be14.C");
	gROOT->ProcessLine(".x cutBar31Be14.C");
	gROOT->ProcessLine(".x cutBar30Be14.C");
	gROOT->ProcessLine(".x cutBar29Be14.C");
	gROOT->ProcessLine(".x cutBar28Be14.C");

	gROOT->ProcessLine(".x cutBar23Be14.C");
	gROOT->ProcessLine(".x cutBar22Be14.C");
	gROOT->ProcessLine(".x cutBar21Be14.C");
	gROOT->ProcessLine(".x cutBar20Be14.C");
	gROOT->ProcessLine(".x cutBar19Be14.C");
	
	if(isDrawTOFAng){
		TCanvas *c = new TCanvas("ppToFAng"," ppToFAng",1500,900);
		c->Divide(4,2);
		c->cd(1);
		tree->Draw("plasT[0]-F13T:protonTheta>>h(200,40,80,200,-900,-840)","","colz");
		c->cd(2);
		tree->Draw("plasT[0]-F13T:protonTheta>>hProton(200,40,80,200,-900,-840)","Proton","colz");
		c->cd(3);
		tree->Draw("plasT[0]-F13T:protonTheta>>hT(200,40,80,200,-900,-840)",peak5,"colz");
		c->cd(4);
		tree->Draw("plasT[0]-F13T:protonTheta>>hPT(200,40,80,200,-900,-840)","Proton&&"+peak5,"colz");
		c->cd(5);
		tree->Draw("plasT[0]-F13T:protonTheta>>hB(200,40,80,200,-900,-840)","BeamBe14","colz");
		c->cd(6);
		tree->Draw("plasT[0]-F13T:protonTheta>>hPTB(200,40,80,200,-900,-840)","BeamBe14&&Proton&&"+peak5,"colz");
		c->cd(7);
		tree->Draw("plasT[0]-F13T:protonTheta>>hH(200,40,80,200,-900,-840)","HodBe14","colz");
		c->cd(8);
		tree->Draw("plasT[0]-F13T:protonTheta>>hPTBH(200,40,80,200,-900,-840)","BeamBe14&&Proton&&HodBe14&&"+peak5,"colz");

	}
	if(isDrawEAng){
		TCanvas *c = new TCanvas("ppET","ppET",1500,900);
		c->Divide(4,2);

		c->cd(1);
		tree->Draw("2*naiQ[0]:protonTheta>>h(200,40,80,200,0,200)","(!Trig_BxTEL)","colz");
		c->cd(2);
		tree->Draw("2*naiQ[0]:protonTheta>>hP(200,40,80,200,0,200)","(!Trig_BxTEL)&&Proton","colz");
		c->cd(3);
		tree->Draw("2*naiQ[0]:protonTheta>>hT(200,40,80,200,0,200)","(!Trig_BxTEL)&&"+peak5,"colz");
		c->cd(4);
		tree->Draw("2*naiQ[0]:protonTheta>>hPT(200,40,80,200,0,200)","(!Trig_BxTEL)&&Proton&&"+peak5,"colz");
		c->cd(5);
		tree->Draw("2*naiQ[0]:protonTheta>>hB(200,40,80,200,0,200)","(!Trig_BxTEL)&&BeamBe14","colz");
		c->cd(6);
		tree->Draw("2*naiQ[0]:protonTheta>>hBPT(200,40,80,200,0,200)","(!Trig_BxTEL)&&BeamBe14&&Proton&&"+peak5,"colz");
		c->cd(7);
		//tree->Draw("2*naiQ[0]:protonTheta>>hH(200,40,80,200,0,200)","Bar32Be14||Bar31Be14||Bar30Be14||Bar29Be14||Bar28Be14","colz");
		//TString hodGate = "(Bar32Be14||Bar31Be14||Bar30Be14||Bar29Be14||Bar28Be14)";
		//TString hodGate = "(Bar30Be14||Bar29Be14||Bar28Be14)";
		//TString hodGate = "(Bar31Be14||Bar30Be14)";
		//TString hodGate = "(Bar23Be14||Bar22Be14||Bar21Be14||Bar20Be14||Bar19Be14)";
		TString hodGate = "(!Trig_BxTEL)&&(Bar23Be14||Bar22Be14||Bar21Be14||Bar20Be14||Bar19Be14)";
		tree->Draw("2*naiQ[0]:protonTheta>>hH(200,40,80,200,0,200)",hodGate,"colz");
		c->cd(8);
		//tree->Draw("2*naiQ[0]:protonTheta>>hBPTH(200,40,80,200,0,200)","BeamBe14&&Proton&&HodBe14&&"+peak5,"colz");
		tree->Draw("2*naiQ[0]:protonTheta>>hBPTH(200,40,80,200,0,200)","BeamBe14&&Proton&&"+hodGate+"&&"+peak5,"colz");
	}
}
