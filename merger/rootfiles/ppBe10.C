{

	TChain *tree = new TChain("tree");

//	tree->Add("run0361_analysed.root");
//	tree->Add("run0361_analysed.root");

	bool isDrawEAng = true;
	bool isDrawTOFAng = false;

	int runStart = 310;
	//int runStop = 330;
	int runStop = 311;
	for (int i = runStart; i < runStop; ++i) {
		
		tree->Add(Form("run0%d_analysed.root",i));
	}

	TString drawETheta = "2*naiQ[0]:protonTheta>>(500,40,80,500,0,140)";
	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutProtonBe10.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutHodBe10.C");

	gROOT->ProcessLine(".x cutBar23Be10.C");
	gROOT->ProcessLine(".x cutBar22Be10.C");
	gROOT->ProcessLine(".x cutBar21Be10.C");
	gROOT->ProcessLine(".x cutBar20Be10.C");
	gROOT->ProcessLine(".x cutBar19Be10.C");
	
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
		tree->Draw("plasT[0]-F13T:protonTheta>>hB(200,40,80,200,-900,-840)","BeamBe10","colz");
		c->cd(6);
		tree->Draw("plasT[0]-F13T:protonTheta>>hPTB(200,40,80,200,-900,-840)","BeamBe10&&Proton&&"+peak5,"colz");
		c->cd(7);
		tree->Draw("plasT[0]-F13T:protonTheta>>hH(200,40,80,200,-900,-840)","HodBe10","colz");
		c->cd(8);
		tree->Draw("plasT[0]-F13T:protonTheta>>hPTBH(200,40,80,200,-900,-840)","BeamBe10&&Proton&&HodBe10&&"+peak5,"colz");

	}
	if(isDrawEAng){
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

		TString hodGate = "(!Trig_BxTEL)&&(Bar23Be10||Bar22Be10||Bar21Be10||Bar20Be10||Bar19Be10)";
		tree->Draw("2*naiQ[0]:protonTheta>>hH(200,40,80,200,0,200)",hodGate,"colz");
		c->cd(8);
		tree->Draw("2*naiQ[0]:protonTheta>>hBPTH(200,40,80,200,0,200)","BeamBe10&&Proton&&"+hodGate+"&&"+peak5,"colz");
	}

	TH2F *h = (TH2F*)gDirectory->Get("h");
	TH2F *hP = (TH2F*)gDirectory->Get("hP");
	TH2F *hT = (TH2F*)gDirectory->Get("hT");
	TH2F *hPT = (TH2F*)gDirectory->Get("hPT");
	TH2F *hB = (TH2F*)gDirectory->Get("hB");
	TH2F *hBPT = (TH2F*)gDirectory->Get("hBPT");
	TH2F *hH = (TH2F*)gDirectory->Get("hH");
	TH2F *hBPTH = (TH2F*)gDirectory->Get("hBPTH");
	TFile *g = new TFile("ppBe10Histo.root","recreate");
	h->Write();
	hP->Write();
	hT->Write();
	hPT->Write();
	hB->Write();
	hBPT->Write();
	hH->Write();
	hBPTH->Write();
	c->Write();
	g->Close();
	
}
