#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"
//#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawCurve.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/LoadCut.h"
#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/HodGate.h"

void drawLeftAlphaEnergy(){

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
	//dt->addFile("../convert/rootfiles/run0596_analysed.root_test");
	//dt->addFile("../convert/rootfiles/requiredPPAlpha/run0596_analysed.root_test");
	dt->addFile("../convert/rootfiles/run0597_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0598_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0599_analysed.root_test");
	//dt->addFile("../convert/rootfiles/run0600_analysed.root_test");


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
	for (int i = 2; i < 3; ++i) {

		int cid =i;
		hName = Form("hCsi%d", cid);

		dt->setGate("1");
		// 1. BeamGate
		dt->addGate("(Trig_DSB)");
		//dt->addGate("(Beam)");
		dt->addGate(targetArea);
		dt->addGate("(Alpha)");
		dt->addGate(Form("(teleHit==1&&teleCsiId==%d)",cid));
		dt->addGate(stripLimit[cid]);

		dt->setName(hName);
		dt->setVar("alphaEnergy/4.001506179127");
		dt->setBin(200,100,170);
		dt->drawH();
		dt->saveH1Root();
	}
}
