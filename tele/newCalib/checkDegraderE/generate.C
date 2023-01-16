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
	dt->addFile("../convert/rootfiles/run0596_analysed.root_test");
	//dt->addFile("../convert/rootfiles/requiredPPAlpha/run0596_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0597_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0600_analysed.root_test");


	gROOT->ProcessLine(".x rootfiles/cutBeamAlpha150.C");
	gROOT->ProcessLine(".x rootfiles/cutAlpha.C");
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<14.5"; 
// Events may hit on the frame, but it's okay, because we are looking for highest energy.
	TString hName;

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");


	TH1F hCheck[7];
	TString stripLimit[7];
	stripLimit[0] = "(teleDssdFid<=13&&teleDssdBid>=20)";
	stripLimit[1] = "(teleDssdFid<=12&&teleDssdBid<=11)";
	stripLimit[2] = "(teleDssdFid>=20&&teleDssdBid>=19)";
	stripLimit[3] = "(teleDssdFid>=21&&teleDssdBid<=11)";
	stripLimit[4] = "(teleDssdBid<=11)";
	stripLimit[5] = "(teleDssdFid<=10&&teleDssdBid>=20)";
	stripLimit[6] = "(teleDssdFid>=20&&teleDssdBid>=21)";

	TString csiGate;
	for (int i = 0; i < 7; ++i) {

		int cid =i;
		//TString csi = "(" + Form("(teleCsiId==%d)&&",cid) + stripLimit[cid] + ")";
		TString csi = Form("(teleCsiId==%d)&&",cid);
		csi = "(" + csi + stripLimit[cid] + ")";
		if(i == 0) {
			csiGate = csi;
		}else{
			csiGate = csi+"||" + csiGate;
		}
	}
	csiGate = "("+csiGate + ")";
	cout<<csiGate<<endl;

	//for (int i = 0; i < 7; ++i) {

	//	int cid =i;
	//	hName = Form("hDssd%d", cid);

	//	dt->setGate("1");
	//	// 1. BeamGate
	//	dt->addGate("(Trig_DSB)");
	//	//dt->addGate("(Beam)");
	//	dt->addGate(targetArea);
	//	dt->addGate("(Alpha)");
	//	dt->addGate(Form("(teleHit==1&&teleCsiId==%d)",cid));
	//	dt->addGate(stripLimit[cid]);

	//	dt->setName(hName);
	//	dt->setVar("teleDssdE");
	//	dt->setBin(100,0,20);
	//	dt->drawH();
	//	dt->saveH1Root();
	//}

	for (int i = 0; i < 2; ++i) {

		hName = Form("hApDeg%d", i);

		dt->setGate("1");
		// 1. BeamGate
		dt->addGate("(Trig_DSB)");
		//dt->addGate("(Beam)");
		//dt->addGate(targetArea);
		dt->addGate("(Alpha)");
		dt->addGate(Form("(teleHit==1&&teleSide==%d)", i));
		dt->addGate(csiGate);

		dt->setName(hName);
		dt->setVar("apDegraderE");
		dt->setBin(300,50,200);
		dt->drawH();
		dt->saveH1Root();
	}

}
