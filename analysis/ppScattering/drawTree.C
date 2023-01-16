#include "../DrawTree.h"
TString getGate(){
	gROOT->ProcessLine(".x cutPPEA.C");

	TString planeOfBPA = "(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))";
	//return "abs(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))<0.05";
	//return "(csiHit==1)&&((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
	//return "(PPEA)&&((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
	//return "((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
	//return "((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
	//return "(PPEA)";
	return "1";
	//return "(abs(exEnergy-5.5)<0.15)";
}
void draw2D(){

	DrawTree *dt = new DrawTree();
	dt->addFile("ppBe10.root");
	dt->setAlias();
	dt->loadCut();
	dt->setGate(getGate());
	//dt->addGate(getHodGate());
	dt->setVar("protonEnergy","protonAngle");
	dt->setBin(200,50,80,200,0,200);

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	dt->draw2D();
}

void drawH(){

	DrawTree *dt = new DrawTree();
	dt->addFile("ppBe10.root");
	dt->setAlias();
	dt->loadCut();
	dt->setGate(getGate());
	//dt->addGate(getHodGate());
	dt->setVar("abs(espriPhi-fdc0Phi)");
	dt->setBin(100,150,210);

	TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
	dt->drawH();
}
void drawTree(){
	//drawH();
	draw2D();
}

