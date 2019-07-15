#include <TFile.h>
class PPScattering{
	private:

		TChain *tree;
		TString gate[8];
		TString hName[8];
		TH2F *h[8];

	protected:
		TString targetArea ;
		TString hodGate ;
		TString beamGate;
		TString defaultGate;
		TString protonGate;

		TFile *outputFile;
		TString outputName;

	public:
		PPScattering(){

			tree = new TChain("tree");
			defineName();
		}
		void loadTChain(int runStart = 310,int runStop = 311){
			for (int i = runStart; i < runStop; ++i) {

				tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}

		}
		void defineGate(){
			defineDefaultGate();
			defineTargetArea();	
			defineProtonGate();
			defineHodGate();
			defineBeamGate();
			gate[0] = "Trig_BxESPRI";
			gate[1] = defaultGate + protonGate;
			gate[2] = defaultGate + targetArea;
			gate[3] = protonGate +"&&"+ gate[2];
			gate[4] = defaultGate + beamGate;
			gate[5] = beamGate +"&&"+ gate[3];
			gate[6] = defaultGate + hodGate;
			gate[7] = gate[5] +"&&"+ hodGate;
			printGate();

		}
		void printGate(){
			for (int i = 0; i < 8; ++i) {
				cout<<gate[i]<<endl;
			}
		}
		void defineDefaultGate(){
			defaultGate = "Trig_BxESPRI&&";
			//defaultGate = "";
		}
		void defineProtonGate(){
			protonGate = "Proton";
		}
		void defineHodGate(){};
		void defineBeamGate(){};
		void defineTargetArea(){
			targetArea = "sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
		}
		void defineName(){
			hName[0] = "h";
			hName[1] = "hP";
			hName[2] = "hT";
			hName[3] = "hPT";
			hName[4] = "hB";
			hName[5] = "hBPT";
			hName[6] = "hH";
			hName[7] = "hBPTH";
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
			c->Divide(4,2);

			//TString drawVar = "(2*naiQ[0]+plasQ[0]):protonTheta>>";
			TString drawVar = "2*naiQ[0]:protonTheta>>";
			TString drawRange = "(200,40,80,200,0,200)";
			for (int i = 0; i < 8; ++i) {
				c->cd(i+1);	
				TString draw = drawVar + hName[i] + drawRange;
				tree->Draw(draw,gate[i],"colz");
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
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe10.C");

			gROOT->ProcessLine(".x rootfiles/cutBar23Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar22Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar21Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar20Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar19Be10.C");
		}

		void assignOutputName(){
			outputName = "ppBe10Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Bar23Be10||Bar22Be10||Bar21Be10||Bar20Be10||Bar19Be10)";
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
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe12.C");

			gROOT->ProcessLine(".x rootfiles/cutBar23Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBar22Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBar21Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBar20Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBar19Be12.C");
		}

		void assignOutputName(){
			outputName = "ppBe12Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Bar23Be12||Bar22Be12||Bar21Be12||Bar20Be12||Bar19Be12)";
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
			gROOT->ProcessLine(".x rootfiles/cutProtonBe14.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe14.C");

			gROOT->ProcessLine(".x rootfiles/cutBar32Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar31Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar30Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar29Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar28Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar27Be14.C");
	
			gROOT->ProcessLine(".x rootfiles/cutBar23Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar22Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar21Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar20Be14.C");
			gROOT->ProcessLine(".x rootfiles/cutBar19Be14.C");
		}

		void assignOutputName(){
			outputName = "ppBe14Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			//hodGate = "(Bar23Be14||Bar22Be14||Bar21Be14||Bar20Be14||Bar19Be14)";
			//hodGate = "(Bar32Be14||Bar31Be14||Bar30Be14||Bar29Be14||Bar28Be14||Bar27Be14)";
			hodGate = "(Bar29Be14||Bar28Be14||Bar27Be14)";
		}
		void defineBeamGate(){
			beamGate = "BeamBe14";
		}
};

void ppBe(){

	//PPBe10 *ppBe = new PPBe10();
	//ppBe->loadTChain(298,330);
	//PPBe12 *ppBe = new PPBe12();
	//ppBe->loadTChain(334,365);
	//ppBe->loadTChain(360,361);
	PPBe14 *ppBe = new PPBe14();
	ppBe->loadTChain(436,437);
	//ppBe->loadTChain(366,456);

	//ppBe->loadTChain();
	ppBe->defineHodGate();
	ppBe->defineBeamGate();
	ppBe->defineGate();
	ppBe->loadCut();
	ppBe->assignOutputName();
	ppBe->createOutputFile();
	ppBe->draw();

}
