#include <TFile.h>
class PPScattering{
	private:

		TChain *tree;
		TString gate;

		TString hName[4];
		TH2F *h[4];

		TString drawRange[4];

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
				tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root",i));
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
			//gate = trigger+"&&"+protonGate+"&&"+alphaGate+"&&"+hodGate+"&&"+targetArea+"&&"+dssdFB+"&&"+csiHit+"&&"+lrSelect;
			//gate = trigger+"&&"+protonGate+"&&"+hodGate+"&&"+targetArea;
			//gate = trigger+"&&"+alphaGate+"&&"+hodGate+"&&"+targetArea;
			gate = trigger+"&&"+hodGate+"&&"+targetArea;
			//gate = hodGate+"&&"+targetArea;
			printGate();

		}
		void defineLRSelect(){
			lrSelect = "((plasQ[0]>2&&dssdSideQ[2]>2)||(plasQ[1]>2&&dssdSideQ[0]>2))";
		}
		void defineDssdFB(){
			dssdFB = "((abs(dssdSideQ[0]-dssdSideQ[1])<1)||(abs(dssdSideQ[2]-dssdSideQ[3])<1))";
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
			targetArea = "sqrt((Target_X+2.0)*(Target_X+2.0)+(Target_Y+1.1)*(Target_Y+1.1))<13";
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

		void assignOutputName(){}
		virtual setDrawRange(){}
		void draw(){
			TCanvas *c = new TCanvas("ppET","ppET",1500,900);
			c->Divide(2,2);
			TString drawVar[4];
			drawVar[0] = "espriEnergy:espriAngle>>";
			drawVar[1] = "teleEnergy:teleAngle>>";
			drawVar[2] = "espriAngle:teleAngle>>";
			drawVar[3] = "espriEnergy:teleEnergy>>";

			setDrawRange();
			
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
			gROOT->ProcessLine(".x rootfiles/cutSBT1Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutSBT2Be10.C");
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

		void setDrawRange(){
			drawRange[0] = "(200,40,80,200,0,150)";
			drawRange[1] = "(200,0,18,200,200,700)";
			drawRange[2] = "(200,0,18,200,40,80)";
			drawRange[3] = "(200,200,700,200,0,150)";
		}

		void assignOutputName(){
			outputName = "ppaBe10Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be10Bar29He6||Be10Bar30He6||Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";	
		}
		void defineBeamGate(){
			//beamGate = "BeamBe10";
			beamGate = "(SBT1Be10||SBT2Be10)";
		}
};
class PPBe12:public PPScattering {
	private:
	public:
		PPBe12(){
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutSBT1Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutSBT2Be12.C");
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
		void setDrawRange(){
			drawRange[0] = "(200,40,80,200,0,150)";
			drawRange[1] = "(200,0,18,200,200,700)";
			drawRange[2] = "(200,0,18,200,40,80)";
			drawRange[3] = "(200,200,700,200,0,150)";
		}


		void assignOutputName(){
			outputName = "ppaBe12Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be12Bar30He8||Be12Bar31He8||Be12Bar32He8||Be12Bar33He8||Be12Bar34He8||Be12Bar35He8||Be12Bar36He8)";
		}
		void defineBeamGate(){
			//beamGate = "BeamBe12";
			beamGate = "(SBT1Be12||SBT2Be12)";
		}
};

class PPBe14:public PPScattering {
	private:
	public:
		PPBe14(){
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutSBT1Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutSBT2Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutSmallBeamBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutAlphaBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe14.C");


			gROOT->ProcessLine(".x rootfiles/cutBe14Bar3He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar4He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar5He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar6He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar7He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar8He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar9He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar10He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He4.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He4.C");

			gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar18He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar19He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar20He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar21He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar22He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar23He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar24He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar26He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar27He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar28He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar29He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar30He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar31He6.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar32He6.C");

			gROOT->ProcessLine(".x rootfiles/cutBe14Bar33He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar34He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar35He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar36He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar37He8.C");
			gROOT->ProcessLine(".x rootfiles/cutBe14Bar38He8.C");


		}

		void assignOutputName(){
			//outputName = "ppSmallBe14HistoBe10Bar19-23.root";
			outputName = "ppaBe14HistoHe4He6He8.root";
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
			//hodGate = "(Be14Bar23Be10||Be14Bar22Be10||Be14Bar21Be10||Be14Bar20Be11||Be14Bar19Be10)";
			//hodGate = "(Be14Bar23Be10||Be14Bar22Be10||Be14Bar21Be10||Be14Bar20Be11||Be14Bar19Be10)";
			TString hodGateHe4 = "(Be14Bar3He4||Be14Bar4He4||Be14Bar5He4||Be14Bar6He4||Be14Bar7He4||Be14Bar8He4||Be14Bar9He4||Be14Bar10He4||Be14Bar11He4||Be14Bar12He4||Be14Bar13He4||Be14Bar14He4||Be14Bar15He4||Be14Bar16He4||Be14Bar17He4)";
			TString hodGateHe6 = "(Be14Bar11He6||Be14Bar12He6||Be14Bar13He6||Be14Bar14He6||Be14Bar15He6||Be14Bar16He6||Be14Bar17He6||Be14Bar18He6||Be14Bar19He6||Be14Bar20He6||Be14Bar21He6||Be14Bar22He6||Be14Bar23He6||Be14Bar24He6||Be14Bar26He6||Be14Bar27He6||Be14Bar28He6||Be14Bar29He6||Be14Bar30He6||Be14Bar31He6||Be14Bar32He6)";
			TString hodGateHe8 = "(Be14Bar33He8||Be14Bar34He8||Be14Bar35He8||Be14Bar36He8||Be14Bar37He8||Be14Bar38He8)";
			//hodGate = hodGateHe4;
			//hodGate = hodGateHe6;
			//hodGate = hodGateHe8;
			hodGate = "("+hodGateHe4+"||"+hodGateHe6+"||"+hodGateHe8+")";
		}
		void setDrawRange(){
			drawRange[0] = "(200,40,80,200,0,150)";
			drawRange[1] = "(200,0,18,200,50,700)";
			drawRange[2] = "(200,0,18,200,40,80)";
			drawRange[3] = "(200,50,700,200,0,150)";
		}

		void defineBeamGate(){
			//beamGate = "BeamBe14";
			//beamGate = "SmallBeamBe14";
			beamGate = "(SBT1Be14||SBT2Be14)";
		}
};

void ppaBe(){

	PPBe10 *ppBe = new PPBe10();
	//ppBe->loadTChain(310,311);
	//ppBe->loadTChain(298,330);
	//PPBe12 *ppBe = new PPBe12();
	//ppBe->loadTChain(341,342);
	//ppBe->loadTChain(334,365);
	//PPBe14 *ppBe = new PPBe14();
	////ppBe->loadTChain(436,437);
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
