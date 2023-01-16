#include "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/DrawTree.h"


void generate(){

		gStyle->SetOptStat(1111111);
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

		DrawTree *dt = new DrawTree();
		dt->addFile("rootfiles/run0380_analysed.root");//Be14
		//dt->addFile("rootfiles/run0582_analysed.root");//Be14
		//dt->addFile("rootfiles/run0340_analysed.root");//Be14
		//dt->addFile("rootfiles/run0380_analysed.root");//Be14
		//dt->addFile("rootfiles/run0595_analysed.root");//He4

		// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
		// 1. Total Gate
		// 2. TrigGate
		// 3. BeamGate
		//gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
		//gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
		//gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
		//gROOT->ProcessLine(".x rootfiles/cutBeamAlpha150.C");//He4
		// 4. TargertArea
		TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";

		TString fileName = "output/generate.root";
		TFile *outputFile = new TFile(fileName,"UPDATE");

		dt->setGate("Trig_DSB");
        dt->addGate(targetArea);
		dt->setName("hBeamThetaBe14");
		dt->setVar("vBeam.Theta()*TMath::RadToDeg()");
		dt->setBin(1000,0,1); 
		dt->drawH();
		dt->saveH1Root();


		dt->setGate("Trig_DSB");
        dt->addGate(targetArea);
		dt->setName("hBeamPhiBe14");
		dt->setVar("vBeam.Phi()*TMath::RadToDeg()");
		dt->setBin(1000,-180,180); 
		dt->drawH();
		dt->saveH1Root();


		dt->setGate("Trig_DSB");
		dt->setName("hTargetXYBe14");
        dt->addGate(targetArea);
		dt->setVar("targetPosition.Y()","targetPosition.X()");
		dt->setBin(1000,-50,50,1000,-50,50); 
		dt->draw2D();
		dt->saveH2Root();



		dt->setGate("Trig_DSB");
        dt->addGate(targetArea);
		dt->setName("hTargetThetaXYBe14");
		dt->setVar("TMath::ATan(vBeam.Y()/vBeam.Z())*TMath::RadToDeg()","TMath::ATan(vBeam.X()/vBeam.Z())*TMath::RadToDeg()");
		dt->setBin(200,-3,3,200,-3,3); 
		dt->draw2D();
		dt->saveH2Root();


}
