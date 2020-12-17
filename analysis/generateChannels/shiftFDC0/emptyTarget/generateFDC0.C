#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/LoadCut.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/HodGate.h"

void generateFDC0(){

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

	//dt->addFile("rootfiles/run0310_analysed.root");
	//dt->addFile("rootfiles/run0311_analysed.root");
	//dt->addFile("rootfiles/run0312_analysed.root");
	//dt->addFile("rootfiles/run0313_analysed.root");
	//gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");


	//dt->addFile("rootfiles/run0340_analysed.root");
	//dt->addFile("rootfiles/run0341_analysed.root");
	//dt->addFile("rootfiles/run0342_analysed.root");
	//gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");

	dt->addFile("rootfiles/run0380_analysed.root");
	dt->addFile("rootfiles/run0381_analysed.root");
	dt->addFile("rootfiles/run0382_analysed.root");
	dt->addFile("rootfiles/run0383_analysed.root");
	dt->addFile("rootfiles/run0384_analysed.root");
	dt->addFile("rootfiles/run0385_analysed.root");
	gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");




	//dt->addFile("rootfiles/run0587_analysed.root");
	//dt->addFile("rootfiles/run0588_analysed.root");
	//dt->addFile("rootfiles/run0589_analysed.root");
	//dt->addFile("rootfiles/run0590_analysed.root");
	//dt->addFile("rootfiles/run0591_analysed.root");
	//dt->addFile("rootfiles/run0592_analysed.root");
	//gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");


	// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
	// 1. Total Gate
	dt->setGate("1");
	// 1. BeamGate
	dt->addGate("(Beam)");
	dt->addGate("(Trig_DSB)");
	// 2. TargetGate
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";	
	dt->addGate(targetArea);
	// 3. Parellel to Z axis
	dt->addGate("((1.0-vBeam.Z())<1e-7)");

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");
	TCanvas *cPad = new TCanvas("cPad","cPad", 700, 700);
	cPad->Divide(2,2);

	cPad->cd(1);
	dt->setName("fdc0XY");
	dt->setVar("fdc0Position.Y()", "fdc0Position.X()");
	dt->setBin(500,-50,50,500, -50, 50);
	dt->draw2D();
	cPad->cd(2);
	dt->setName("targetXY");
	dt->setVar("targetPosition.Y()", "targetPosition.X()");
	dt->setBin(500,-50,50,500, -50, 50);
	dt->draw2D();

	cPad->cd(3);
	dt->setName("fdc0Y");
	dt->setVar("fdc0Position.Y()");
	dt->setBin(500,-50,50);
	dt->drawH();
	
	cPad->cd(4);
	dt->setName("fdc0X");
	dt->setVar("fdc0Position.X()");
	dt->setBin(500,-50,50);
	dt->drawH();

}
