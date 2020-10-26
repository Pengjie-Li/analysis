#include "DrawTree.h"


void generate(){

	gStyle->SetOptStat(1111111);
	TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

	DrawTree *dt = new DrawTree();
	dt->addFile("rootfiles/run0310_analysed.root");//Be10
	dt->addFile("rootfiles/run0311_analysed.root");//Be10
	dt->addFile("rootfiles/run0312_analysed.root");//Be10
	dt->addFile("rootfiles/run0313_analysed.root");//Be10
	dt->addFile("rootfiles/run0314_analysed.root");//Be10
	dt->addFile("rootfiles/run0315_analysed.root");//Be10
	//dt->addFile("rootfiles/run0340_analysed.root");//Be12
	//dt->addFile("rootfiles/run0380_analysed.root");//Be14
	//dt->addFile("rootfiles/run0595_analysed.root");//He4

	// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
	// 1. Total Gate
	// 2. TrigGate
	// 3. BeamGate
	gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
	//gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
	//gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
	//gROOT->ProcessLine(".x rootfiles/cutBeamAlpha150.C");//He4
	// 4. TargertArea
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";
	//dt->addGate(targetArea);
	//5. Proton dEE gate
	//gROOT->ProcessLine(".x rootfiles/cutProton.C"); // Proton gate couldn't be used because it contains RDC information
	gROOT->ProcessLine(".x cutProtonBar02.C");
	gROOT->ProcessLine(".x cutProtonBar03.C");
	gROOT->ProcessLine(".x cutProtonBar12.C");
	gROOT->ProcessLine(".x cutProtonBar13.C");

	//dt->addGate("Proton");
	//6. One NaiBar as ref
	//		TString leftBar = "";
	//		TString rightBar = "naiQPed[2][3]>0&&naiQPed[3][3]>0&&sqrt(naiQPed[2][3]*naiQPed[3][3])>200";
	//TString leftBar = "(espriPlasQPed>100&&espriNaiQPed>200)";
	//TString rightBar = "espriPlasQPed>100&&espriNaiQPed>200";

	TString leftBar02 = "(plasHit == 1&&plasHitSide[0] == 0 &&plasQPed[0]>10&&plasQPed[1]>10&&sqrt(plasQPed[0]*plasQPed[1])>100&&naiQPed[0][2]>10&&naiQPed[1][2]>10&&sqrt(naiQPed[0][2]*naiQPed[1][2])>100 && ProtonBar02 && abs(log(naiQPed[1][2]/naiQPed[0][2])+0.1)<0.2)";
	TString leftBar03 = "(plasHit == 1&&plasHitSide[0] == 0 &&plasQPed[0]>10&&plasQPed[1]>10&&sqrt(plasQPed[0]*plasQPed[1])>100&&naiQPed[0][3]>10&&naiQPed[1][3]>10&&sqrt(naiQPed[0][3]*naiQPed[1][3])>100 && ProtonBar03&& abs(log(naiQPed[1][3]/naiQPed[0][3])+0.1)<0.2)";
	TString rightBar12 = "(plasHit == 1&&plasHitSide[0] == 1 &&plasQPed[2]>10&&plasQPed[3]>10&&sqrt(plasQPed[2]*plasQPed[3])>100&&naiQPed[2][2]>10&&naiQPed[3][2]>10&&sqrt(naiQPed[2][2]*naiQPed[3][2])>100 && ProtonBar12&& abs(log(naiQPed[3][2]/naiQPed[2][2]) - 0.1)<0.2)";
	TString rightBar13 = "(plasHit == 1&&plasHitSide[0] == 1 &&plasQPed[2]>10&&plasQPed[3]>10&&sqrt(plasQPed[2]*plasQPed[3])>100&&naiQPed[2][3]>10&&naiQPed[3][3]>10&&sqrt(naiQPed[2][3]*naiQPed[3][3])>100 && ProtonBar13&& abs(log(naiQPed[3][3]/naiQPed[2][3]) - 0.0)<0.2)";
	//TString leftBar = leftBar03;
	//TString rightBar = rightBar13;

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");
	//&&abs(bdc2Position.Y())<17&&abs(bdc2Position.X())<17
	//dt->setGate("Trig_BxESPRI&&Beam&&rdcX[0]>50&&rdcX[0]<175&&rdcY[0]>25&&rdcY[0]<400&&"+targetArea+"&&"+leftBar);
	//dt->setGate("Trig_BxESPRI&&Beam&&Proton&&"+targetArea+"&&"+leftBar);
	dt->setGate("Trig_BxESPRI&&Beam&&"+targetArea+"&&"+leftBar02);
	dt->setName("hRdcL02");
	//dt->scan("rdcY[0]:rdcX[0]");
	dt->setVar("rdcY[0]","rdcX[0]");
	dt->setBin(500,0,500,500,0,500); 
	dt->draw2D();
	dt->saveH2Root();

	dt->setGate("Trig_BxESPRI&&Beam&&"+targetArea+"&&"+leftBar03);
	dt->setName("hRdcL03");
	//dt->scan("rdcY[0]:rdcX[0]");
	dt->setVar("rdcY[0]","rdcX[0]");
	dt->setBin(500,0,500,500,0,500); 
	dt->draw2D();
	dt->saveH2Root();

	//
	//		dt->setGate("Trig_BxESPRI&&Beam&&"+targetArea+"&&"+rightBar);
	//		dt->setName("hRDCR");
	//		dt->setVar("rdcY[1]","rdcX[1]");
	//		dt->setBin(500,0,500,500,0,500); 
	//		dt->draw2D();
	//		dt->saveH2Root();
	//
	dt->setGate("Trig_BxESPRI&&Beam&&"+targetArea+"&&"+rightBar12);
	dt->setName("hRdcR12");
	dt->setVar("rdcY[1]","rdcX[1]");
	dt->setBin(500,0,500,500,0,500); 
	dt->draw2D();
	dt->saveH2Root();

	dt->setGate("Trig_BxESPRI&&Beam&&"+targetArea+"&&"+rightBar13);
	dt->setName("hRdcR13");
	dt->setVar("rdcY[1]","rdcX[1]");
	dt->setBin(500,0,500,500,0,500); 
	dt->draw2D();
	dt->saveH2Root();

}
