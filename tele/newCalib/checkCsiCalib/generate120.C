#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"
//#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawCurve.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/LoadCut.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/HodGate.h"

void drawLeftAlphaEnergy(){

	tree->Draw(Form("alphaEnergy>>hPeak%d(700,0,1000)",peakId),"teleHit==1&&"+gate);
	TString hName;

	int cid =4;
	hName = Form("hCsi%d", cid);
	Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate

	dt->setName(hName);
	dt->setVar("beamEnergy");
	dt->setBin(700,100,130);
	dt->drawH();
	dt->saveH1Root();


	hCheck[0] = (TH1F*)gDirectory->Get(Form("hPeak%d",peakId));
	hCheck[0]->SetLineColor(1);

	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(700,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[1] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[1]->SetLineColor(2);
	hCheck[1]->Draw();

	cid =5;
	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(700,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[2] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[2]->SetLineColor(3);

	cid =6;
	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(700,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[3] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[3]->SetLineColor(4);

	hCheck[0]->Draw();
	hCheck[1]->Draw("same");
	hCheck[2]->Draw("same");
	hCheck[3]->Draw("same");
}

void drawRightAlphaEnergy(int peakId){
	tree->Draw(Form("alphaEnergy>>hPeak%d(1200,0,1000)",peakId),"teleHit==1&&"+gate);
	hCheck[0] = (TH1F*)gDirectory->Get(Form("hPeak%d",peakId));
	hCheck[0]->SetLineColor(1);

	int cid =0;
	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[1] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[1]->SetLineColor(2);
	hCheck[1]->Draw();

	cid =1;
	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[2] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[2]->SetLineColor(3);

	cid =2;
	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[3] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[3]->SetLineColor(4);

	cid =3;
	tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
	hCheck[4] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
	hCheck[4]->SetLineColor(5);


	hCheck[0]->Draw();
	hCheck[1]->Draw("same");
	hCheck[2]->Draw("same");
	hCheck[3]->Draw("same");
	hCheck[4]->Draw("same");
}

void generate(){

	gStyle->SetOptStat(1111111);
	TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

	LoadCut *lc = new LoadCut();
	//lc->loadHodBe10He6();
	//lc->loadHodBe10He4();
	//lc->loadHodBe12He8();
	//lc->loadHodBe12He6();
	//lc->loadHodBe12He4();
	//lc->loadHodBe14He8();
	//lc->loadHodBe14He6();
	//lc->loadHodBe14He4();
	HodGate *hg = new HodGate();

	DrawTree *dt = new DrawTree();
	//dt->addFile("../convert/rootfiles/run0595_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0596_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0597_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0600_analysed.root_test");

	TCanvas *cPad = new TCanvas("cPad","cPad",900, 900);
	cPad->Divide(2,1);
	cPad->cd(1);
	drawLeftAlphaEnergy(dt);
	drawRightAlphaEnergy(dt);

	// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
	// 1. Total Gate
	//dt->setGate("1");
	//gROOT->ProcessLine(".x rootfiles/cutBeamAlpha120.C");
	//// 1. BeamGate
	//dt->addGate("(Trig_DSB)");
	//dt->addGate("(Beam)");

	//TString fileName = "output/generate.root";
	//TFile *outputFile = new TFile(fileName,"UPDATE");

	////cPad->cd(1);
	//dt->setName("hBeam");
	//dt->setVar("beamEnergy");
	//dt->setBin(700,100,130);
	//dt->drawH();
	//dt->saveH1Root();

	////cPad->cd(2);
	//dt->setName("hAlpha");
	//dt->setVar("alphaEnergy/4.001506179127");
	//dt->setBin(300,100,130);
	//dt->drawH();
	//dt->saveH1Root();

	//TH1F *h1D[2];
	//h1D[0] = (TH1F*)outputFile->Get("hBeam");
	//h1D[1] = (TH1F*)outputFile->Get("hAlpha");
	//h1D[0]->SetLineColor(1);
	//h1D[1]->SetLineColor(2);
	//h1D[0]->Draw();
	//h1D[1]->Draw("same");


}
