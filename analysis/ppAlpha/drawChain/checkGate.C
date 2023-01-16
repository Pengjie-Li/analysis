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
		}
		void loadTChain(int runStart = 310,int runStop = 311){
			for (int i = runStart; i < runStop; ++i) {

				//tree->Add(Form("rootfiles/run0%d_analysed.root_2",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root_2",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
				//tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}

		}
		void checkBeamGate(){
		}


};
class PPBe10:public PPScattering {
	private:
	public:
		PPBe10(){
		}
		void checkBeamGate(){
			gROOT->ProcessLine(".x rootfiles/drawBeam.C");
			gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
		}

};
class PPBe12:public PPScattering {
	private:
	public:
		PPBe12(){
		}
		void checkBeamGate(){
			gROOT->ProcessLine(".x rootfiles/drawBeam.C");
			gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
		}

};

class PPBe14:public PPScattering {
	private:
	public:
		PPBe14(){
		}
		void checkBeamGate(){
			gROOT->ProcessLine(".x rootfiles/drawBeam.C");
			gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");
		}

};

void checkGate(){

	//PPBe10 *ppBe = new PPBe10();
	//ppBe->loadTChain(310,311);
	//ppBe->loadTChain(298,330);
	//PPBe12 *ppBe = new PPBe12();
	//ppBe->loadTChain(341,342);
	//ppBe->loadTChain(334,365);
	PPBe14 *ppBe = new PPBe14();
	ppBe->loadTChain(436,437);
	//ppBe->loadTChain(366,456);

	ppBe->checkBeamGate();
//	ppBe->checkProtonGate();
//	ppBe->checkAlphaGate();
}
