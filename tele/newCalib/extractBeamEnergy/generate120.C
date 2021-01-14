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
	dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0600_analysed.root_test");


	gROOT->ProcessLine(".x rootfiles/cutBeamAlpha120.C");
	gROOT->ProcessLine(".x rootfiles/cutAlpha.C");
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<14.5"; 
// Events may hit on the frame, but it's okay, because we are looking for highest energy.
	TString hName;

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");


	TH1F hCheck[7];
	TString stripLimit[7];
	stripLimit[0] = "(teleDssdFid<=14&&teleDssdBid>=19)";
	stripLimit[1] = "(teleDssdFid<=12&&teleDssdBid<=12)";
	stripLimit[2] = "(teleDssdFid>=18&&teleDssdBid>=17)";
	stripLimit[3] = "(teleDssdFid>=19&&teleDssdBid<=13)";
	stripLimit[4] = "(teleDssdBid<=13)";
	stripLimit[5] = "(teleDssdFid<=13&&teleDssdBid>=18)";
	stripLimit[6] = "(teleDssdFid>=18&&teleDssdBid>=18)";
	for (int i = 0; i < 7; ++i) {

		int cid =i;
		hName = Form("hAlpha120Csi%d", cid);

		dt->setGate("1");
		// 1. BeamGate
		dt->addGate("(Trig_DSB)");
		dt->addGate("(Beam)");
		dt->addGate(targetArea);
		dt->addGate("(Alpha)");
		dt->addGate("(teleHit==1)");
		dt->addGate(Form("(teleHit==1&&teleCsiId==%d)",cid));
		dt->addGate(stripLimit[cid]);

		dt->setName(hName);
		dt->setVar("beamEnergy");
		dt->setBin(100,115,125);
		dt->drawH();
		dt->saveH1Root();
	}
}
