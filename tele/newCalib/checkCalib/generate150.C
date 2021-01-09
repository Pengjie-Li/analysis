#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"
//#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawCurve.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/LoadCut.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/HodGate.h"


void generate150(){

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
	//dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0600_analysed.root_test");

	TCanvas *cPad = new TCanvas("cPad","cPad",900, 900);
	//cPad->Divide(2,1);

	// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
	// 1. Total Gate
	dt->setGate("1");
	gROOT->ProcessLine(".x rootfiles/cutBeamAlpha150.C");
	gROOT->ProcessLine(".x rootfiles/cutAlpha.C");
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";
	// 1. BeamGate
	dt->addGate("(Trig_DSB)");
	dt->addGate("(Beam)");
	dt->addGate(targetArea);
	dt->addGate("(Alpha)");

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");

	//cPad->cd(1);
	dt->setName("hBeam");
	dt->setVar("beamEnergy");
	dt->setBin(900,140,170);
	dt->drawH();
	dt->saveH1Root();

	//cPad->cd(2);
	dt->setName("hAlpha");
	dt->setVar("alphaEnergy/4.001506179127");
	dt->setBin(200,140,170);
	dt->drawH();
	dt->saveH1Root();

	for (int i = 0; i < 7; ++i) {

		int cid = i;
		dt->setGate("1");
		dt->addGate("(Trig_DSB)");
		dt->addGate("(Beam)");
		dt->addGate(targetArea);
		dt->addGate("(Alpha)");


		dt->addGate(Form("(teleCsiId==%d)", cid));

		dt->setName(Form("hAlpha%d",cid));
		dt->setVar("alphaEnergy/4.001506179127");
		dt->setBin(100,140,170);
		dt->drawH();
		dt->saveH1Root();

	}

	TH1F *h1D[2];
	h1D[0] = (TH1F*)outputFile->Get("hBeam");
	h1D[1] = (TH1F*)outputFile->Get("hAlpha");

	h1D[0]->SetLineColor(1);
	h1D[1]->SetLineColor(1);
	h1D[1]->SetLineStyle(2);
	h1D[0]->Draw();
	h1D[1]->Draw("same");

	TH1F *hCsi[7];
	for (int i = 0; i < 7; ++i) {

		int cid = i;
		hCsi[i] = (TH1F*)outputFile->Get(Form("hAlpha%d",cid));
		hCsi[i]->SetLineColor(i+1);
		hCsi[i]->Draw("same");
	}

}
