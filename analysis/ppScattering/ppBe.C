#include <TFile.h>

class PPScattering{
	private:

		TString gate;
		TString hName;
		TH2F *h;
		TString drawVar;
		TString drawRange;

	protected:
		TChain *tree;
		TString triggerGate;
		TString targetArea ;
		TString beamGate;
		TString protonGate;
		TString phiGate;
		TString thetaGate;
		TString hodGate ;
		TString protonEAGate;

		TFile *outputFile;
		TString outputName;

	public:
		PPScattering(){

			tree = new TChain("tree");
			defineName();
		}
		void loadTChain(int runStart = 310,int runStop = 311){
			for (int i = runStart; i < runStop; ++i) {

				tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root_2",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}

		}
		void defineGate(){
			defineTargetArea();	
			defineProtonGate();
			defineHodGate();
			defineBeamGate();
			definePhiGate();
			defineThetaGate();
			defineTriggerGate();
			defineProtonEAGate();

			gate = triggerGate;

		}
		void addProtonGate(){
			gate = gate +"&&"+ protonGate;
		}
		void addTargetArea(){
			gate = gate +"&&"+ targetArea;
		}
		void addBeamGate(){
			gate = gate +"&&"+ beamGate;
		}
		void addPhiGate(){
			gate = gate +"&&"+ phiGate;
		}
		void addProtonEAGate(){
			gate = gate +"&&"+ protonEAGate;
		}
		void addThetaGate(){
			gate = gate +"&&"+ thetaGate;
		}
		void addHodGate(){
			gate = gate +"&&"+ hodGate;
		}
		void printGate(){
				cout<<gate<<endl;
		}
		void defineTriggerGate(){
			TString trigger = "(Trig_BxESPRI>0)";
			triggerGate = trigger;
		}
		void defineProtonGate(){
			protonGate = "(Proton)";
			//protonGate = "espriNaiEnergy>5&&espriPlasDeltaE>1";
		}
		void defineProtonEAGate(){
			protonEAGate = "PPEA";
		}
		void definePhiGate(){
			tree->SetAlias("xB","vBeam.X()");
			tree->SetAlias("yB","vBeam.Y()");
			tree->SetAlias("zB","vBeam.Z()");

			tree->SetAlias("xP","vESPRI.X()");
			tree->SetAlias("yP","vESPRI.Y()");
			tree->SetAlias("zP","vESPRI.Z()");

			tree->SetAlias("xR","vFDC0.X()");
			tree->SetAlias("yR","vFDC0.Y()");
			tree->SetAlias("zR","vFDC0.Z()");

			TString planeOfBPR = "(xB*(yR*zP-yP*zR)+yB*(zR*xP-zP*xR)+zB*(xR*yP-xP*yR))";
			phiGate = "(abs("+planeOfBPR+")<0.01)";
	
		}
		void defineThetaGate(){
			thetaGate = "(PRAngle)";
		}
		void defineHodGate(){};
		void defineBeamGate(){};
		void defineTargetArea(){
			targetArea="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<13)";
		}
		void defineName(){
			hName = "hBPTH";
		}
		void loadCut(){
		}
                void defineAlias(){
			
                        tree->SetAlias("AMU","931.49410242*1");
                        tree->SetAlias("MassH","1.007276*1");

                        tree->SetAlias("beamMass","MassBe*AMU");
                        tree->SetAlias("protonMass","MassH*AMU");
                        tree->SetAlias("beamEk","Ek713*MassBe");

                        tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
                        tree->SetAlias("protonEk","espriEnergy");
                        tree->SetAlias("protonMomentum","sqrt(protonEk*protonEk+2*protonEk*protonMass)");

                        tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(espriAngle*TMath::DegToRad()))");
                        tree->SetAlias("residueEnergy","beamEk + beamMass - protonEk");
                        tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
                        tree->SetAlias("excitationEnergy","residueMass-beamMass");

                }
		void createOutputFile(){
			cout<<outputName<<endl;
			outputFile = new TFile(outputName,"recreate");
		}
		void createOutputFile(TString name){
			outputName = name;
			outputFile = new TFile(outputName,"recreate");
		}

		virtual void assignOutputName();
		void defineDrawVar(TString var1,TString var2){
			drawVar = var1+":"+var2+">>";
		}
		void defineDrawRange(int xBin,int xMin,int xMax,int yBin,int yMin,int yMax){
			drawRange = Form("(%d,%d,%d,%d,%d,%d)",xBin,xMin,xMax,yBin,yMin,yMax);
		}
		void defineDrawVar(TString var){
			drawVar = var+">>";
		}
		void defineDrawRange(int xBin,int xMin,int xMax){
			drawRange = Form("(%d,%d,%d)",xBin,xMin,xMax);
		}

		void draw(){

			printGate();
			TCanvas *c = new TCanvas("ppET","ppET",1300,900);

			//TString draw = drawVar;
			TString draw = drawVar + hName + drawRange;
			cout<<draw<<endl;
			tree->Draw(draw,gate,"colz");
			//tree->Scan(draw,gate);
			h = (TH2F*)gDirectory->Get(hName);
			TH1D *hpx = h->ProjectionX();
			hpx->SetName("hpx");
			hpx->Write();
			TH1D *hpy = h->ProjectionY();
			hpy->SetName("hpy");
			hpy->Write();
			h->Write();
			c->Write();
		}

};
class PPBe10:public PPScattering {
	private:
	public:
		PPBe10(){
			tree->SetAlias("MassBe","10.0113*1");
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutPRAngleBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutPPEABe10.C");

			gROOT->ProcessLine(".x rootfiles/cutBe10Bar23Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar22Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar21Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar20Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar19Be10.C");

			gROOT->ProcessLine(".x rootfiles/cutBe10Bar23Be9.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar22Be9.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar21Be9.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar20Be9.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar19Be9.C");

		}

		void assignOutputName(){
			outputName = "v11_ppBe10Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be10Bar23Be10||Be10Bar22Be10||Be10Bar21Be10||Be10Bar20Be10||Be10Bar19Be10)";
			//hodGate = "(Be10Bar23Be9||Be10Bar22Be9||Be10Bar21Be9||Be10Bar20Be9||Be10Bar19Be9)";
		}
		void defineBeamGate(){
			beamGate = "(BeamBe10)";
		}
};
class PPBe12:public PPScattering {
	private:
	public:
		PPBe12(){
			tree->SetAlias("MassBe","12.0247*1");
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutPRAngleBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutPPEABe12.C");

			gROOT->ProcessLine(".x rootfiles/cutBe12Bar23Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar22Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar21Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar20Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar19Be12.C");
		}

		void assignOutputName(){
			outputName = "ppBe12Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be12Bar23Be12||Be12Bar22Be12||Be12Bar21Be12||Be12Bar20Be12||Be12Bar19Be12)";
		}
		void defineBeamGate(){
			beamGate = "(BeamBe12)";
		}
};

class PPBe14:public PPScattering {
	private:
	public:
		PPBe14(){
			tree->SetAlias("MassBe","14.0407*1");
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutSmallBeamBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutPRAngleBe14.C");
			

			gROOT->ProcessLine(".x rootfiles/cutBe14Bar33Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar32Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar31Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar30Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar29Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar28Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar27Be14.C");
	                                                        
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be14.C");

			gROOT->ProcessLine(".x rootfiles/cutBe14Bar26Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar25Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar24Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be12.C");

			gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be11.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be11.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be11.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be11.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be11.C");

			gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be10.C");


		}

		void assignOutputName(){
			outputName = "ppBe14HistoBar28.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			//hodGate = "(Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
			hodGate = "(Be14Bar33Be14||Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14)";
			//hodGate = "(Be14Bar28Be14)";
			//hodGate = "(Be14Bar30Be14)";
			//hodGate = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14)";
			//hodGate = "(Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
			//hodGate = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14||Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
			//
			//hodGate = "(Be14Bar26Be12||Be14Bar25Be12||Be14Bar24Be12||Be14Bar23Be12||Be14Bar22Be12||Be14Bar21Be12||Be14Bar20Be12||Be14Bar19Be12)";
			//hodGate = "(Be14Bar23Be11||Be14Bar22Be11||Be14Bar21Be11||Be14Bar20Be11||Be14Bar19Be11)";
			//hodGate = "(Be14Bar23Be10||Be14Bar22Be10||Be14Bar21Be10||Be14Bar20Be11||Be14Bar19Be10)";
		}
		void defineBeamGate(){
			beamGate = "(BeamBe14)";
			//beamGate = "SmallBeamBe14";
		}
};

void ppBe(){

	//PPBe10 *ppBe = new PPBe10();
	//ppBe->loadTChain(310,311);
	//ppBe->loadTChain(298,330);
	//PPBe12 *ppBe = new PPBe12();
	//ppBe->loadTChain(341,342);
	//ppBe->loadTChain(334,365);
	PPBe14 *ppBe = new PPBe14();
	//ppBe->loadTChain(436,437);
	ppBe->loadTChain(366,456);


	// Proton dE vs E
	//ppBe->defineDrawVar("espriPlasE","espriNaiE");
	//ppBe->defineDrawRange(200,0,200,200,0,40);

	// Proton Angle vs Residue Angle
	ppBe->defineDrawVar("espriAngle","resAngle");
	ppBe->defineDrawRange(500,1,5,500,55,75);

	// Proton E vs A
	//ppBe->defineDrawVar("espriEnergy","espriAngle");
	//ppBe->defineDrawRange(500,40,80,500,0,200);

	// Excitation spectrum 
	//ppBe->defineDrawVar("excitationEnergy","espriAngle");
	//ppBe->defineDrawRange(500,40,80,1000,-20,80);


	ppBe->defineAlias();
	
	ppBe->defineHodGate();
	ppBe->defineBeamGate();
	ppBe->defineGate();
	ppBe->loadCut();

	
	//Gate select
	ppBe->addBeamGate();
	ppBe->addProtonGate();
	ppBe->addTargetArea();
	ppBe->addPhiGate();
	//ppBe->addProtonEAGate();
	//ppBe->addThetaGate();
	ppBe->addHodGate();

	ppBe->assignOutputName();
	ppBe->createOutputFile();
	ppBe->draw();

}
