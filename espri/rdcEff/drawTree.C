#include "../DrawTree.h"
#include "../DrawCurve.h"
#include "../LoadCut.h"

class HodGate{
		private:
		public:
				HodGate(){}
				~HodGate(){}
				TString hodGateBe14He4(){
						TString hodGateBe14He4 = "(Be14Bar3He4||Be14Bar4He4||Be14Bar5He4||Be14Bar6He4||Be14Bar7He4||Be14Bar8He4||Be14Bar9He4||Be14Bar10He4||Be14Bar11He4||Be14Bar12He4||Be14Bar13He4||Be14Bar14He4||Be14Bar15He4||Be14Bar16He4||Be14Bar17He4)";
						//TString hodGateBe14He4 = "(Be14Bar7He4||Be14Bar8He4||Be14Bar9He4||Be14Bar10He4||Be14Bar11He4||Be14Bar12He4||Be14Bar13He4||Be14Bar14He4||Be14Bar15He4||Be14Bar16He4||Be14Bar17He4)";
						//TString hodGateBe14He4 = "(Be14Bar7He4||Be14Bar8He4||Be14Bar9He4||Be14Bar10He4||Be14Bar11He4||Be14Bar12He4||Be14Bar13He4||Be14Bar14He4||Be14Bar15He4||Be14Bar16He4||Be14Bar17He4)";
						return hodGateBe14He4;

				}
				TString hodGateBe14He6(){
						TString hodGateBe14He6 = "(Be14Bar11He6||Be14Bar12He6||Be14Bar13He6||Be14Bar14He6||Be14Bar15He6||Be14Bar16He6||Be14Bar17He6||Be14Bar18He6||Be14Bar19He6||Be14Bar20He6||Be14Bar21He6||Be14Bar22He6||Be14Bar23He6||Be14Bar24He6||Be14Bar26He6||Be14Bar27He6||Be14Bar28He6||Be14Bar29He6||Be14Bar30He6||Be14Bar31He6||Be14Bar32He6)";
						return hodGateBe14He6;
				}
				TString hodGateBe14He8(){
						//TString hodGateBe14He8 = "(Be14Bar33He8||Be14Bar34He8||Be14Bar35He8||Be14Bar36He8||Be14Bar37He8||Be14Bar38He8)";
						TString hodGateBe14He8 = "(Be14Bar31He8||Be14Bar32He8||Be14Bar33He8||Be14Bar34He8||Be14Bar35He8||Be14Bar36He8||Be14Bar37He8||Be14Bar38He8||Be14Bar39He8)";
						return  hodGateBe14He8;
				}
				TString hodGateBe12He8(){
						TString hodGateBe12He8  = "(Be12Bar28He8||Be12Bar29He8||Be12Bar30He8||Be12Bar31He8||Be12Bar32He8||Be12Bar33He8||Be12Bar34He8||Be12Bar35He8||Be12Bar36He8)";
						return  hodGateBe12He8;
				}
				TString hodGateBe12He6(){
						TString hodGateBe12He6 = "(Be12Bar9He6||Be12Bar10He6||Be12Bar11He6||Be12Bar12He6||Be12Bar13He6||Be12Bar14He6||Be12Bar15He6||Be12Bar16He6||Be12Bar17He6||Be12Bar18He6||Be12Bar19He6||Be12Bar20He6||Be12Bar21He6||Be12Bar22He6||Be12Bar23He6||Be12Bar24He6)";
						//TString hodGateBe12He6 = "(Be12Bar9He6||Be12Bar10He6||Be12Bar11He6||Be12Bar12He6||Be12Bar13He6||Be12Bar14He6||Be12Bar15He6||Be12Bar16He6||Be12Bar17He6||Be12Bar18He6||Be12Bar19He6||Be12Bar20He6)";
						//TString hodGateBe12He6 = "(Be12Bar21He6||Be12Bar22He6||Be12Bar23He6||Be12Bar24He6)";

						return hodGateBe12He6;
				}
				TString hodGateBe12He4(){
						TString hodGateBe12He4 = "(Be12Bar3He4||Be12Bar4He4||Be12Bar5He4||Be12Bar6He4||Be12Bar7He4||Be12Bar8He4||Be12Bar9He4||Be12Bar10He4||Be12Bar11He4||Be12Bar12He4||Be12Bar13He4||Be12Bar14He4||Be12Bar15He4)";

						return hodGateBe12He4;
				}

				TString hodGateBe10He4(){
						TString hodGateBe10He4 = "(Be10Bar9He4||Be10Bar10He4||Be10Bar11He4||Be10Bar12He4||Be10Bar13He4||Be10Bar10He4||Be10Bar15He4||Be10Bar16He4||Be10Bar17He4||Be10Bar18He4||Be10Bar19He4||Be10Bar20He4||Be10Bar21He4||Be10Bar22He4||Be10Bar23He4)";
						//TString hodGateBe10He4 = "(Be10Bar20He4||Be10Bar21He4||Be10Bar22He4||Be10Bar23He4)";
						//TString hodGateBe10He4 = "(Be10Bar21He4||Be10Bar22He4||Be10Bar23He4)";
						//TString hodGateBe10He4 = "(Be10Bar22He4||Be10Bar23He4)";
						//TString hodGateBe10He4 = "(Be10Bar20He4||Be10Bar21He4)";
						//TString hodGateBe10He4 = "(Be10Bar16He4||Be10Bar17He4||Be10Bar18He4||Be10Bar19He4)";
						//TString hodGateBe10He4 = "(Be10Bar9He4||Be10Bar10He4||Be10Bar11He4||Be10Bar12He4||Be10Bar13He4||Be10Bar14He4||Be10Bar15He4)";
						//TString hodGateBe10He4 = "(Be10Bar21He4)";
						return hodGateBe10He4;
				}
				TString hodGateBe10He6(){	
						//TString hodGateBe10He6 = "(Be10Bar27He6||Be10Bar28He6||Be10Bar29He6||Be10Bar30He6)";
						//TString hodGateBe10He6 = "(Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";
						TString hodGateBe10He6 = "(Be10Bar27He6||Be10Bar28He6||Be10Bar29He6||Be10Bar30He6||Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";
						return hodGateBe10He6;
				}


};
TString getGate(){
		//return "(espriAngle>66.5)";
		//return "(espriAngle>67.5)";
		//return "(espriAngle>66.5&&espriAngle<67.5)";
		//return "(espriAngle>65.5&&espriAngle<66.5)";
		//return "(espriAngle>64.5&&espriAngle<65.5)";
		//return "(espriAngle<66.5&&espriAngle>63.5)";
		//return "(espriAngle<67&&espriAngle>65&&teleAngle>6&&teleAngle<8)";
		//return "(espriAngle<63.5)";
		gROOT->ProcessLine(".x cutProtonEA.C");
		//return "(AABe10)&&((abs(protonEnergy-40)<10&&abs(alphaEnergy-550)<10))";
		//return "((abs(protonEnergy-40)<10&&abs(alphaEnergy-550)<10))";

		TString planeOfBPA = "(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))";
		//return "abs(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))<0.05";
		//return "(csiHit==1)&&((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
		//return "((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
		//return "(ProtonEA)&&((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
		return "(espriHitSide==1)";
		//return "((espriHitSide==0&&teleHitSide==1))";
		//return "((espriHitSide==1&&teleHitSide==0))";
		//return "(abs(exEnergy-5.5)<0.15)";
}
void draw2D(DrawTree *dt){

		//Draw
		//dt->setVar("protonEnergy","espriAngle");
		dt->setVar("protonEnergy_Birks","espriAngle");
		//dt->setVar("protonEnergy","espriAngleS[0][6]");
		dt->setBin(400,55,75,400,0,150);
		//dt->setBin(200,55,75,200,0,150);
		///dt->setVar("espriAngle","fdc0Angle");
		//dt->setBin(200,1,6,200,55,75);
		//dt->setVar("fdc0Position.Y()","fdc0Position.X()");
		//dt->setBin(500,-100,100,500,-100,100);
		//
		//dt->setVar("naiHitQPed[0]","espriAngle");
		//dt->setBin(400,55,75,500,0,3500);
		//
		//	dt->setVar("exEnergy","espriAngle");
		//	dt->setBin(400,55,75,400,-10,10);
		//
		//dt->setVar("abs(espriPhi-fdc0Phi)","rdcHitY[0]");
		//dt->setBin(100,0,500,200,150,210);
		//
		//dt->setVar("espriPhi","fdc0Phi");
		//dt->setBin(120,-180,180,120,-180,180);
		//fdc X vs Y
		//dt->setVar("fdc0Position.Y()","fdc0Position.X()");
		//dt->setBin(500,-100,100,500,-100,100);

		//protonEnergy vs TofTargetEspri	
		//dt->setName("hTof");
		////dt->setVar("tofP","espriTOF");
		//dt->setVar("kineT","espriAngle");
		//dt->setBin(350,55,75,300,0,150);

		dt->draw2D();
		//dt->proj2DAndFit();
}

void drawH(DrawTree *dt){


		dt->setName("hEx");
		//dt->setName("hEx1");
		dt->setVar("(exEnergy)");
		//dt->setBin(150,-20,20);
		dt->setBin(800,-20,20);

		dt->drawH();
		dt->saveH1Root();


}
void drawP2Prime(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
		cPad->Divide(2,2);
		cPad->cd(1);

		dt->setName("hP2X");
		dt->setVar("P2X");
		dt->setBin(100,-250,250);
		dt->drawH();
		dt->saveH1Root();

		cPad->cd(2);
		dt->setName("hP2Y");
		dt->setVar("P2Y");
		dt->setBin(100,-250,250);
		dt->drawH();
		dt->saveH1Root();

		cPad->cd(3);
		dt->setName("hP2Z");
		dt->setVar("P2Z");
		dt->setBin(100,-250,250);
		dt->drawH();
		dt->saveH1Root();

		cPad->cd(4);
		dt->setName("hP2");
		dt->setVar("P2Prime");
		dt->setBin(100,-250,250);
		dt->drawH();


		dt->saveH1Root();

}

void drawOpenAngle(DrawTree *dt){
		dt->setName("hOpenAngle");
		dt->setVar("acos(cosTheta12)*TMath::RadToDeg()");
		dt->setBin(100,50,100);
		dt->drawH();

}
void drawT3Prime(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
		cPad->Divide(2,2);
		cPad->cd(1);
		dt->setName("hT3Theta3");
		dt->setVar("T3Prime","(theta3Prime*TMath::RadToDeg())");
		dt->setBin(180,0,180,100,0,10);
		dt->draw2D();

		cPad->cd(2);
		dt->setName("hT3Theta3FDC0");
		//dt->setVar("T3Prime","asin(P3*sin(fdc0Angle*TMath::DegToRad())/abs(P3Prime))*TMath::RadToDeg()");
		dt->setVar("T3Prime","acos((Ea*P3*cos(fdc0Angle*TMath::DegToRad())-Pa*E3)/(Ma*abs(P3Prime)))*TMath::RadToDeg()");
		dt->setBin(100,0,180,100,0,10);
		dt->draw2D();

		cPad->cd(3);
		dt->setName("hT3");
		dt->setVar("T3Prime");
		dt->setBin(100,0,10);
		dt->drawH();

}

void drawP3Prime2D(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
		cPad->Divide(2,2);
		cPad->cd(1);

		dt->setName("hP3XY");
		dt->setVar("P3Y","P3X");
		dt->setBin(100,-250,250,100,-250,250);
		dt->draw2D();

		cPad->cd(2);
		dt->setName("hP3XZ");
		dt->setVar("P3Z","P3X");
		dt->setBin(100,-250,250,100,-250,250);
		dt->draw2D();

		cPad->cd(3);
		dt->setName("hP3YZ");
		dt->setVar("P3Z","P3Y");
		dt->setBin(100,-250,250,100,-250,250);
		dt->draw2D();

		cPad->cd(4);
		dt->setName("hP3");
		//dt->setVar("abs(P3Prime)");
		dt->setVar("P3Z","(P3Prime)");
		dt->setBin(100,-250,250,100,-250,250);
		dt->draw2D();

		dt->saveH2Root();

}
void drawT3P3(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
		cPad->Divide(2,2);
		cPad->cd(2);
		dt->setName("hP3");
		dt->setVar("abs(P3Prime)");
		//dt->setVar("(P3Prime)");
		dt->setBin(50,0,350);
		dt->drawH();
		dt->saveH1Root();

		cPad->cd(1);
		dt->setName("hT1");
		dt->setVar("(T1)");
		dt->setBin(25,20,70);// 2MeV/bin
		dt->drawH();
		dt->saveH1Root();

		cPad->cd(1);
		dt->setName("hT3");
		dt->setVar("T3Prime");
		dt->setBin(50,0,10);
		dt->drawH();
		dt->saveH1Root();


}
void drawP3Prime(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
		cPad->Divide(2,2);
		cPad->cd(1);

		dt->setName("hP3X");
		dt->setVar("P3X");
		dt->setBin(100,-250,250);
		dt->drawH();

		cPad->cd(2);
		dt->setName("hP3Y");
		dt->setVar("P3Y");
		dt->setBin(100,-250,250);
		dt->drawH();

		cPad->cd(3);
		dt->setName("hP3Z");
		dt->setVar("P3Z");
		dt->setBin(100,-250,250);
		dt->drawH();

		cPad->cd(4);
		dt->setName("hP3");
		dt->setVar("abs(P3Prime)");
		//dt->setVar("(P3Prime)");
		dt->setBin(50,0,250);
		dt->drawH();

		//dt->setBin(50,0,250);
		//
		//dt->setVar("(M3)");
		//dt->setBin(100,5580,5640);
		//dt->setVar("(E3)");
		//dt->setBin(100,5580,5640);



		dt->saveH1Root();

}
void drawPhi(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

		dt->setBin(160,100,260);
		//dt->setBin(800,-20,20);

		dt->drawH();
		dt->saveH1Root();

}
void drawSE(DrawTree *dt){
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

		dt->setVar("Ta-T1-T2-T3");
		dt->setBin(400,-10,40);

		dt->drawH();
		dt->saveH1Root();


}
void drawExEnergy(DrawTree *dt){

		//TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

		dt->setVar("(exEnergy)");
		//dt->setVar("(exE)");
		//dt->setBin(150,-20,20);
		dt->setBin(500,-20,20);
		//dt->setBin(1000,-20,20);

		dt->drawH();
		dt->saveH1Root();
}
void drawAngularCorrelation(DrawTree *dt){

		TCanvas *cPad = new TCanvas("cPad","cPad",1200,600);
		cPad->Divide(2,2);

		//protonEnergy vs Angle 	
		cPad->cd(1);
		dt->setName("hThetaAP");
		dt->setVar("protonAngle","teleAngle");
		dt->setBin(200,2,14,200,50,75);
		dt->draw2D();

		cPad->cd(2);
		dt->setName("hPhiAP");
		dt->setVar("espriPhi","telePhi");
		dt->setBin(180,0,360,180,0,360);
		dt->draw2D();


		cPad->cd(3);
		dt->setName("hThetaRP");
		dt->setVar("protonAngle","fdc0Angle");
		dt->setBin(200,0,6,200,50,75);
		dt->draw2D();

		cPad->cd(4);
		dt->setName("hPhiRP");
		dt->setVar("espriPhi","fdc0Phi");
		dt->setBin(180,0,360,180,0,360);
		dt->draw2D();

}
void drawEnergyCorrelation(DrawTree *dt){

		DrawCurve *dc = new DrawCurve();

		TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
		cPad->Divide(2,2);

		cPad->cd(1);
		dt->setName("hTheta1Theta2");
		dt->setVar("theta2*TMath::RadToDeg()","theta1*TMath::RadToDeg()");
		dt->setBin(200,55,70,200,0,15);
		dt->draw2D();
		//dc->drawTheta1Theta2Be10T48();
		dc->drawTheta1Theta2Be12T41();

		cPad->cd(2);
		dt->setName("hTheta1P3\'");
		dt->setVar("abs(P3Prime)","theta1*TMath::RadToDeg()");
		dt->setBin(200,55,70,200,0,300);
		dt->draw2D();
		//dc->drawTheta1P3PrimeBe10T48();
		dc->drawTheta1P3PrimeBe12T41();

		cPad->cd(3);
		dt->setName("hP3\'Theta3");
		dt->setVar("(theta3*TMath::RadToDeg())","abs(P3Prime)");
		//dt->setVar("(fdc0Angle)","abs(P3Prime)");
		dt->setBin(200,0,300,200,0,5);
		dt->draw2D();
		//dc->drawP3PrimeTheta3Be10T48();
		dc->drawP3PrimeTheta3Be12T41();

		cPad->cd(4);
		dt->setName("hTheta1Theta3");
		dt->setVar("(theta3*TMath::RadToDeg())","theta1*TMath::RadToDeg()");
		//dt->setVar("fdc0Angle","theta1*TMath::RadToDeg()");
		dt->setBin(200,55,70,200,0,5);
		dt->draw2D();
		//dc->drawTheta1Theta3Be10T48();
		dc->drawTheta1Theta3Be12T41();

}
void drawFixedAngTheta3Distribution(DrawTree *dt){
		DrawCurve *dc = new DrawCurve();
		dt->setName("hTheta3");
		dt->setVar("(theta3*TMath::RadToDeg())");
		//dt->setVar("(fdc0Angle)");
		dt->setBin(25,0,3);// 2MeV/bin
		dt->drawH();
		dt->scaleH(10);
		dc->drawTheta3Be10Th65();
}

void drawFixedAngP3BDistribution(DrawTree *dt){
		DrawCurve *dc = new DrawCurve();
		dt->setName("hP3B");
		dt->setVar("(P3B)");
		dt->setBin(40,-280,280);// 2MeV/bin
		dt->drawH();
		dt->scaleH(10);
		dc->drawP3BBe10Th65();
}
void drawFixedAngT1Distribution(DrawTree *dt){
		DrawCurve *dc = new DrawCurve();
		dt->setName("hT1");
		dt->setVar("(T1)");
		dt->setBin(25,20,70);// 2MeV/bin
		dt->drawH();
		dt->scaleH(10);
		dc->drawT1Be10Th65();
}
void drawFixedAngCorrelation(DrawTree *dt){

		DrawCurve *dc = new DrawCurve();

		TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
		cPad->Divide(2,2);

		cPad->cd(1);
		dt->setName("hT1T2");
		dt->setVar("T2","T1");
		dt->setBin(200,0,100,200,400,700);
		dt->draw2D();
		dc->drawE1E2Be10Th65();

		cPad->cd(2);
		dt->setName("hT1P3\'");
		dt->setVar("P3B","T1");
		//dt->setBin(200,0,100,200,0,300);
		dt->setBin(200,0,100,200,-300,300);
		dt->draw2D();
		dc->drawT1P3PrimeBe10Th65();

		cPad->cd(3);
		dt->setName("hP3\'Theta3");
		dt->setVar("(theta3*TMath::RadToDeg())","P3B");
		//dt->setVar("(fdc0Angle)","abs(P3Prime)");
		//dt->setBin(200,0,300,200,0,5);
		dt->setBin(200,-300,300,200,0,5);
		dt->draw2D();
		dc->drawP3PrimeTheta3Be10Th65();

		cPad->cd(4);
		dt->setName("hTheta1Theta3");
		//dt->setVar("(theta3*TMath::RadToDeg())","theta1*TMath::RadToDeg()");
		dt->setVar("(theta3*TMath::RadToDeg())","T1");
		//dt->setVar("fdc0Angle","T1");
		dt->setBin(200,0,100,200,0,5);
		dt->draw2D();
		dc->drawT1Theta3Be10Th65();

}
void drawPACorrelationCurve(DrawTree *dt){

		DrawCurve *dc = new DrawCurve();
		TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
		cPad->Divide(2,2);

		//protonEnergy vs Angle 	
		cPad->cd(1);
		dt->setName("hProtonEA");
		//dt->setVar("protonEnergy","protonAngle");
		dt->setVar("protonEk","protonAngle");
		dt->setBin(200,52,75,200,0,160);
		dt->draw2D();
		dc->drawT1Theta1Be10();

		cPad->cd(2);
		dt->setName("hAlphaEA");
		dt->setVar("alphaEnergy","alphaAngle");
		dt->setBin(200,2,16,200,300,800);
		dt->draw2D();
		dc->drawT2Theta2Be10();

		cPad->cd(3);
		dt->setName("hAA");
		dt->setVar("alphaAngle","protonAngle");
		dt->setBin(200,52,75,200,2,16);
		dt->draw2D();
		dc->drawTheta1Theta2Be10();

		cPad->cd(4);
		dt->setName("hEE");
		//dt->setVar("protonEnergy","alphaEnergy");
		//dt->setVar("alphaEnergy","protonEnergy");
		dt->setVar("alphaEnergy","protonEk");
		dt->setBin(200,0,160,200,300,800);
		dt->draw2D();
		dc->drawT1T2Be10();
		dc->drawE1E2Be10Th65();
		//cout<<gDirectory->pwd()<<endl;
		//gDirectory->Cd("/Volumes/LPJ/S12/analysis/kinetics/");
		//gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/kinetics/drawFixedAnglePoint.C");
		////TString fileName = "/Volumes/LPJ/S12/analysis/kinetics/output/be10_theta65_ex0.root_AME2016";
		////TFile *input = new TFile(fileName,"READ");
		////TGraph *gr = (TGraph*)input->Get("T1T2");
		//TGraph *gr = (TGraph*)gDirectory->Get("T1T2");
		//gr->Draw("psame");
}

void drawPACorrelation(DrawTree *dt){

		DrawCurve *dc = new DrawCurve();
		TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
		cPad->Divide(2,2);

		//protonEnergy vs Angle 	
		cPad->cd(1);
		dt->setName("hProtonEA");
		//dt->setVar("protonEnergy","protonAngle");
		dt->setVar("protonEk","protonAngle");
		dt->setBin(200,52,75,200,0,160);
		dt->draw2D();
		dc->drawT1Theta1Be10();

		cPad->cd(2);
		dt->setName("hAlphaEA");
		dt->setVar("alphaEnergy","alphaAngle");
		dt->setBin(200,2,16,200,300,800);
		dt->draw2D();
		dc->drawT2Theta2Be10();

		cPad->cd(3);
		dt->setName("hAA");
		dt->setVar("alphaAngle","protonAngle");
		dt->setBin(200,52,75,200,2,16);
		dt->draw2D();
		dc->drawTheta1Theta2Be10();
		//dc->drawTheta1Theta2Be10T48();
		//dc->drawTheta1Theta2Be12T41();

		cPad->cd(4);
		dt->setName("hEE");
		//dt->setVar("protonEnergy","alphaEnergy");
		//dt->setVar("alphaEnergy","protonEnergy");
		dt->setVar("alphaEnergy","protonEk");
		dt->setBin(200,0,160,200,300,800);
		dt->draw2D();
		dc->drawT1T2Be10();
		//dc->drawT1T2Be12();
		//dc->drawT1T2Be12Th66();
		//dc->drawT1T2Be12Th65();
		//cout<<gDirectory->pwd()<<endl;
		//gDirectory->Cd("/Volumes/LPJ/S12/analysis/kinetics/");
		//gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/kinetics/drawFixedAnglePoint.C");
		//TString fileName = "/Volumes/LPJ/S12/analysis/kinetics/output/be10_theta65_ex0.root_AME2016";
		//TFile *input = new TFile(fileName,"READ");
		//TGraph *gr = (TGraph*)input->Get("T1T2");
		//gr->Draw("psame");
}
void shiftTele(DrawTree *dt){
		for (int i = 0; i < 4; ++i) {
				if(i%2==0){
						for (int j = 9; j > -1; --j) {
								dt->setName(Form("hEx_%d_%d",i,j));
								dt->setTeleAngleAlias(i,j);
								drawExEnergy(dt);
								dt->fitPPAlpha(i,j);
						}

				}else{
						for (int j = 0; j < 10; ++j) {
								dt->setName(Form("hEx_%d_%d",i,j));
								dt->setTeleAngleAlias(i,j);
								drawExEnergy(dt);
								dt->fitPPAlpha(i,j);
						}
				}
		}
}
void drawTree(){

		gStyle->SetOptStat(1111111);
		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);
		DrawCurve *dc = new DrawCurve();

		LoadCut *lc = new LoadCut();
		lc->loadHodBe10He6();
		lc->loadHodBe10He4();
		lc->loadHodBe12He8();
		lc->loadHodBe12He6();
		lc->loadHodBe12He4();
		lc->loadHodBe14He8();
		lc->loadHodBe14He6();
		lc->loadHodBe14He4();
		HodGate *hg = new HodGate();

		DrawTree *dt = new DrawTree();
		dt->addFile("ppaBe10.root_convert");
		dt->setPPAlphaBe10Alias();


		// General Gate: 1. Total Gate; 2. Side Gate; 3. Phi Gate; 4. Hod Gate; 5. Degrader Gate
		// 1. Total Gate
		dt->setGate("1");
		// 1. BeamGate
		gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
        dt->addGate("(Beam)");
		// 2. TargetGate
		TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";	
        dt->addGate(targetArea);
		// 3. AlphaGate
		gROOT->ProcessLine(".x rootfiles/cutAlpha.C");
        dt->addGate("(Alpha)");
		// 4. Proton Gate
		gROOT->ProcessLine(".x rootfiles/cutProton.C");
        gROOT->ProcessLine(".x rootfiles/cutProtonToF.C");
        gROOT->ProcessLine(".x rootfiles/cutProtonNaiToF.C");
    
		TString naiProtonGate = "((!(ppDegENai>0)&&protonTheta>60)&&(Proton))";
		TString plasProtonGate = "((!(ppDegEPlas>0)&&protonTheta>60)&&(((!(espriNaiE>0))&&(ProtonToF))||((ProtonToF)&&(ProtonNaiToF))))";
		//TString protonGate = naiProtonGate;
		//TString protonGate = plasProtonGate;
		TString protonGate = "("+naiProtonGate+"||"+plasProtonGate+")";
        dt->addGate(protonGate);
		// 4. Side Gate
		dt->addGate("((espriSide==0&&teleHitSide==1)||(espriSide==1&&teleHitSide==0))");
		//dt->addGate("((espriHitSide==0&&teleHitSide==1))");
		//dt->addGate("((espriHitSide==1&&teleHitSide==0))");
		// 5. Phi Gate
		int dPhi = 50;
		dt->addGate(Form("(abs((espriPhi-telePhi)-180)<%d||abs((espriPhi-telePhi + 360)-180)<%d)",dPhi,dPhi));
		// 6. HodGate
		dt->addGate(hg->hodGateBe10He6());
		//dt->addGate(hg->hodGateBe10He4());
	
		//check Gate
		//drawBeam(dt);
		//drawProton(dt);
		//drawAlpha(dt);
		//drawTheta(dt);
		//drawPhi(dt);
		

		///checkPhysics
		//drawPACorrelation(dt);
		//checkExEnergy
		//dt->setName("hExHe6");
		//dt->setName("hExHe4");
		//dt->setName("hEx");
		//drawExEnergy(dt);
		//dt->fitPPAlpha();
		//
		//Angle Pixel 
		dt->addGate("abs(espriAngle-65)<1");
		dt->addGate("abs(teleAngle-7.7)<1");
		//drawPACorrelationCurve(dt);
		drawFixedAngCorrelation(dt);

		//drawFixedAngT1Distribution(dt);
		//drawFixedAngP3BDistribution(dt);
		//drawFixedAngTheta3Distribution(dt);
		//drawAngularCorrelation(dt);
		//drawEnergyCorrelation(dt);
	
		//dt->setVar("exE","protonEnergyNew");
		//dt->setBin(500,0,150,500,-5,30);
		//dt->draw2D();
		//dt->setVar("fdc0Position.Y()","fdc0Position.X()");
		//dt->setBin(500,-100,100,500,-100,100);
		//dt->draw2D();
		//dt->setVar("exEnergy");
		//dt->setBin(500,-5,30);
		//dt->drawH();
	
		//dt->setVar("exEnergy","protonEnergy");
		//dt->setBin(500,0,150,500,-5,30);
		//dt->draw2D();
	


		// Other Gate
		//dt->addGate("abs(T1-48.824)<10");
		//dt->addGate("abs(T2-542.821)<10");
		//dt->addGate("abs(espriAngle-66)<1");
		//dt->addGate("abs(teleAngle-7.08)<1");
		//dt->addGate("abs(T1-41.62)<10");
		//dt->addGate("abs(T2-548.23)<10");
		//dt->addGate("abs(espriAngle-65)<1");
		//dt->addGate("abs(teleAngle-7.448)<1");
	
//		TCanvas *cPad = new TCanvas("cPad","cPad",900,600);

		//drawP2Prime(dt);
		//drawP3Prime(dt);
		//drawP3Prime2D(dt);
		//drawT3Prime(dt);
		//drawT3P3(dt);
		//drawOpenAngle(dt);
//		dt->setName("hT1");
//		dt->setVar("(protonEnergy)");
//		dt->setBin(25,20,70);// 2MeV/bin
//		//dt->setBin(800,-20,20);
//
		//dt->setName("hTheta3FDC0He6");
		//dt->setName("hTheta3FDC0He4");
//		dt->setName("hTheta3FDC0");
//		dt->setVar("(fdc0Angle)");
	
//		dt->setName("hTheta3From12");
//		dt->setVar("(theta3*TMath::RadToDeg())");
//		dt->setBin(50,0,5);
		//dt->setBin(800,-20,20);
//		dt->setName("hTheta3Diff");
//		dt->setVar("(fdc0Angle - theta3*TMath::RadToDeg())");
//		dt->setBin(100,-5,5);

		//dt->setName("hP3Tranverse");
		//dt->setVar("(P3*sin(theta3))");
		//dt->setBin(100,0,200);

		
		//dt->setName("hP3Tranverse");
		//dt->setVar("(P3*sin(theta3))");
		//dt->setBin(100,0,200);


//		dt->drawH();
//		dt->saveH1Root();


		//dt->scan("RunNumber:EventNumber");
		//shiftTele(dt);
		//drawAngularCorrelation(dt);
		//drawEnergyCorrelation(dt);
		//drawFixedAngCorrelation(dt);
		//
		//dt->addGate("(abs(protonEnergyNew-20)<5)");
		//dt->addGate("(abs(protonEnergyNew-30)<5)");
		//dt->addGate("((protonEnergyNew>35)");
		//dt->setName("hEx");
		//dt->setName("hExLeft");
		//dt->setName("hExRight");
		//
		//dt->addGate("!((protonEnergy)>0)");
		//dt->setName("hExToF");
		//dt->addGate("((protonEnergy)>0)");
		//dt->setName("hExNai");
		//drawExEnergy(dt);
		//dt->fitPPAlpha();
		//drawPACorrelation(dt);

		//dt->setName("hSeparationEnergy");
		//drawSE(dt);
		//dt->fitPPAlpha();
		//
		//dt->setVar("plasProtonEnergy-protonEnergyNew","protonEnergyNew");
		//dt->setBin(500,0,150,500,-50,50);
		//dt->draw2D();
		//dt->setName("hPhiLeft");
		//dt->setVar("(espriPhi-telePhi)");
		//dt->setName("hPhiRight");
		//dt->setVar("(espriPhi-telePhiNew)+360");

		//drawPhi(dt);
		//dt->fitPhi();
}
