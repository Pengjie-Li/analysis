#include <TFile.h>
class PPScattering{
	private:

		TChain *tree;
		TString gate;

		TString hName[4];
		TH2F *h[4];

	protected:
		TString trigger;
		TString csiHit;
		TString dssdFB;
		TString lrSelect;
		TString targetArea ;
		TString hodGate ;
		TString beamGate;
		TString defaultGate;
		TString protonGate;
		TString alphaGate;

		TFile *outputFile;
		TString outputName;

	public:
		PPScattering(){

			tree = new TChain("tree");
			defineName();
		}
		void loadTChain(int runStart = 310,int runStop = 311){
			for (int i = runStart; i < runStop; ++i) {

				//tree->Add(Form("rootfiles/run0%d_analysed.root_2",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root_2",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}

		}
		void defineGate(){
			defineTargetArea();	
			defineProtonGate();
			defineAlphaGate();
			defineLRSelect();
			defineDssdFB();
			defineCsiHit();
			defineHodGate();
			defineBeamGate();
			defineTrigger();
			//gate = trigger+"&&"+beamGate+"&&"+protonGate+"&&"+alphaGate+"&&"+hodGate+"&&"+targetArea+"&&"+dssdFB+"&&"+csiHit+"&&"+lrSelect;
			//gate = trigger+"&&"+hodGate+"&&"+targetArea;
			gate = hodGate+"&&"+targetArea;
			printGate();

		}
		void defineLRSelect(){
			lrSelect = "((plasQ[0]>2&&dssdSideQ[2]>2)||(plasQ[1]>2&&dssdSideQ[0]>2))";
		}
		void defineDssdFB(){
			dssdFB = "((abs(dssdSideQ[0]-dssdSideQ[1])<1)||(abs(dssdSideQ[0]-dssdSideQ[1])<1))";
		}
		void defineCsiHit(){
			csiHit = "csiNHit==1";
		}
		void printGate(){
				cout<<gate<<endl;
		}
		void defineTrigger(){
			trigger = "Trig_BxESPRIxTEL";
		}
		void defineProtonGate(){
			protonGate = "Proton";
		}
		void defineAlphaGate(){
			alphaGate = "Alpha";
		}
	
		void defineHodGate(){};
		void defineBeamGate(){};
		void defineTargetArea(){
			targetArea = "sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
		}
		void defineName(){
			hName[0] = "hEspriEvsA";
			hName[1] = "hTeleEvsA";
			hName[2] = "hEspriAvsTeleA";
			hName[3] = "hEspriEvsTeleE";
		}
		void loadCut(){
		}
		void createOutputFile(){
			assignOutputName();
			cout<<outputName<<endl;
			outputFile = new TFile(outputName,"recreate");
		}
		void createOutputFile(TString name){
			outputName = name;
			outputFile = new TFile(outputName,"recreate");
		}

		void assignOutputName(){};
		void draw(){
			TCanvas *c = new TCanvas("ppET","ppET",1500,900);
			c->Divide(2,2);
			TString drawVar[4];
			drawVar[0] = "espriEnergy:espriAngle>>";
			drawVar[1] = "teleEnergy:teleAngle>>";
			drawVar[2] = "espriAngle:teleAngle>>";
			drawVar[3] = "espriEnergy:teleEnergy>>";

			TString drawRange[4];
			drawRange[0] = "(200,40,80,200,0,150)";
			drawRange[1] = "(200,0,18,200,0,1000)";
			drawRange[2] = "(200,0,18,200,40,80)";
			drawRange[3] = "(200,0,1000,200,0,150)";
			
			TString drawCurve[4];
			drawCurve[0] = ".x rootfiles/drawCurveBe12EspriEvsA.C";
			drawCurve[1] = ".x rootfiles/drawCurveBe12TeleEvsA.C";
			drawCurve[2] = ".x rootfiles/drawCurveBe12EspriAvsTeleA.C";
			drawCurve[3] = ".x rootfiles/drawCurveBe12EspriEvsTeleE.C";
			for (int i = 0; i < 4; ++i) {
				c->cd(i+1);	
				TString draw = drawVar[i] + hName[i] + drawRange[i];
				tree->Draw(draw,gate,"colz");
				
				//gROOT->ProcessLine(drawCurve[i]);
				h[i] = (TH2F*)gDirectory->Get(hName[i]);
				h[i]->Write();
			}

			c->Write();
		}

};
class PPBe10:public PPScattering {
	private:
	public:
		PPBe10(){
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutAlphaBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/setAlias.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar29He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar30He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar31He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar32He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar33He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe10Bar34He6.C");

		}

		void assignOutputName(){
			outputName = "ppaBe10Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be10Bar29He6||Be10Bar30He6||Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";	
		}
		void defineBeamGate(){
			beamGate = "BeamBe10";
		}
};
class PPBe12:public PPScattering {
	private:
	public:
		PPBe12(){
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutAlphaBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe12.C");

			gROOT->ProcessLine(".x rootfiles/cutBe12Bar30He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar31He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar32He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar33He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar34He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar35He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar36He8.C");

		}

		void assignOutputName(){
			outputName = "ppaBe12Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be12Bar30He8||Be12Bar31He8||Be12Bar32He8||Be12Bar33He8||Be12Bar34He8||Be12Bar35He8||Be12Bar36He8)";
		}
		void defineBeamGate(){
			beamGate = "BeamBe12";
		}
};

class PPBe14:public PPScattering {
	private:
	public:
		PPBe14(){
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutSmallBeamBe14.C");
			//gROOT->ProcessLine(".x rootfiles/cutProtonBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe14_1.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe14.C");

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
			outputName = "ppSmallBe14HistoBe10Bar19-23.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			//hodGate = "(Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
			//hodGate = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
			//hodGate = "(Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
			//hodGate = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14||Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
			//
			//hodGate = "(Be14Bar26Be12||Be14Bar25Be12||Be14Bar24Be12||Be14Bar23Be12||Be14Bar22Be12||Be14Bar21Be12||Be14Bar20Be12||Be14Bar19Be12)";
			//hodGate = "(Be14Bar23Be11||Be14Bar22Be11||Be14Bar21Be11||Be14Bar20Be11||Be14Bar19Be11)";
			hodGate = "(Be14Bar23Be10||Be14Bar22Be10||Be14Bar21Be10||Be14Bar20Be11||Be14Bar19Be10)";
		}
		void defineBeamGate(){
			//beamGate = "BeamBe14";
			beamGate = "SmallBeamBe14";
		}
};

void ppaBe(){

	//PPBe10 *ppBe = new PPBe10();
	//ppBe->loadTChain(310,311);
	//ppBe->loadTChain(298,330);
	PPBe12 *ppBe = new PPBe12();
	//ppBe->loadTChain(341,342);
	ppBe->loadTChain(334,365);
	//PPBe14 *ppBe = new PPBe14();
	//ppBe->loadTChain(436,437);
	//ppBe->loadTChain(366,456);

	//ppBe->loadTChain();
	ppBe->defineTrigger();
	ppBe->defineHodGate();
	ppBe->defineBeamGate();
	ppBe->defineGate();
	ppBe->loadCut();
	ppBe->assignOutputName();
	ppBe->createOutputFile();
	ppBe->draw();

}
