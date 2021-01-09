#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"
//#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawCurve.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/LoadCut.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/HodGate.h"


void generate120(){

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
	//dt->addFile("../convert/rootfiles/run0596_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0597_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0600_analysed.root_test");

	TCanvas *cPad = new TCanvas("cPad","cPad",900, 900);
	//cPad->Divide(2,1);

	// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
	// 1. Total Gate
	dt->setGate("1");
	gROOT->ProcessLine(".x rootfiles/cutBeamAlpha120.C");
	// 1. BeamGate
	dt->addGate("(Trig_DSB)");
	dt->addGate("(Beam)");

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");

	//cPad->cd(1);
	dt->setName("hBeam");
	dt->setVar("beamEnergy");
	dt->setBin(700,100,130);
	dt->drawH();
	dt->saveH1Root();

	//cPad->cd(2);
	dt->setName("hAlpha");
	dt->setVar("alphaEnergy/4.001506179127");
	dt->setBin(300,100,130);
	dt->drawH();
	dt->saveH1Root();

	TH1F *h1D[2];
	h1D[0] = (TH1F*)outputFile->Get("hBeam");
	h1D[1] = (TH1F*)outputFile->Get("hAlpha");
	h1D[0]->SetLineColor(1);
	h1D[1]->SetLineColor(2);
	h1D[0]->Draw();
	h1D[1]->Draw("same");


}
