#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"
//#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawCurve.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/LoadCut.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/HodGate.h"



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
	//dt->addFile("../convert/rootfiles/run0596_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0597_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0600_analysed.root_test");


	gROOT->ProcessLine(".x rootfiles/cutBeamAlpha150.C");
	gROOT->ProcessLine(".x rootfiles/cutAlpha.C");
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";
	TString hName;

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");


	for (int i = 0; i < 1; ++i) {

		int cid =i;
		hName = Form("hCsi%d", cid);

		dt->setGate("1");
		// 1. BeamGate
		dt->addGate("(Trig_DSB)");
		//dt->addGate("(Beam)");
		dt->addGate(targetArea);
		dt->addGate("(Alpha)");
		dt->addGate(Form("(teleHit==1&&teleCsiId==%d)",cid));
		//dt->addGate("(teleDssdFid<=11&&teleDssdBid>=18)");

		dt->setName(hName);
		dt->setVar("teleDssdFid", "teleDssdBid");
		dt->setBin(32,-0.5,31.5, 32,-0.5,31.5);
		dt->draw2D();
		dt->saveH2Root();
	}


}
