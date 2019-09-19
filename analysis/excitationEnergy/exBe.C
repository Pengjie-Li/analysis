#include <TFile.h>

class EXSpectrum{
	private:

		TChain *tree;
		TString gate[8];
		TString hName[8];
		TH1F *h[8];

	protected:
		TString targetArea ;
		TString hodGate ;
		TString beamGate;
		TString defaultGate;
		TString protonGate;

		TFile *outputFile;
		TString outputName;

	public:
		EXSpectrum(){

			tree = new TChain("tree");
			defineName();
		}
		void loadTChain(int runStart = 310,int runStop = 311){
			for (int i = runStart; i < runStop; ++i) {

				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root_2",i));
			}

		}
		void defineAlias(){
			tree->SetAlias("AMU","931.49410242*1");
			tree->SetAlias("MassH","1.007276*1");

			tree->SetAlias("beamMass","MassBe*AMU");
			tree->SetAlias("protonMass","MassH*AMU");
			tree->SetAlias("beamEk","Ek713*MassBe");

			tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
			tree->SetAlias("protonEk","espriPlasDeltaE+espriNaiEnergy");
			tree->SetAlias("protonMomentum","sqrt(protonEk*protonEk+2*protonEk*protonMass)");

			tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(protonTheta*TMath::DegToRad()))");
			tree->SetAlias("residueEnergy","beamEk + beamMass - protonEk");
			tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
			tree->SetAlias("excitationEnergy","residueMass-beamMass");

		}
		void defineGate(){
			defineTargetArea();	
			defineProtonGate();
			defineHodGate();
			defineBeamGate();
			defineDefaultGate();
			gate[0] = defaultGate;

	//		gate[1] = defaultGate + "&&Bar32Be14"; 
	//		gate[2] = defaultGate + "&&Bar31Be14"; 
	//		gate[3] = defaultGate + "&&Bar30Be14"; 
	//		gate[4] = defaultGate + "&&Bar29Be14"; 
	//		gate[5] = defaultGate + "&&Bar28Be14"; 
	//		gate[6] = defaultGate + "&&(Bar28Be14||Bar29Be14||Bar30Be14||Bar31Be14||Bar32Be14)"; 
	//		gate[7] = defaultGate + "&&(Bar28Be14||Bar29Be14||Bar30Be14)"; 


			gate[1] = defaultGate +"&&"+ protonGate;
			gate[2] = defaultGate +"&&"+ targetArea;
			gate[3] = protonGate +"&&"+ gate[2];
			gate[4] = defaultGate +"&&"+ beamGate;
			gate[5] = beamGate +"&&"+ gate[3];
			gate[6] = defaultGate+"&&" + hodGate;
			gate[7] = gate[5] +"&&"+ hodGate;
			printGate();

		}
		void printGate(){
			for (int i = 0; i < 8; ++i) {
				cout<<gate[i]<<endl;
			}
		}
		void defineDefaultGate(){
			//defaultGate = "Trig_BxESPRI>0&&Trig_DSB==0&&Trig_BxESPRIxTEL==0&&Trig_BxNEBULA==0&&Trig_BxTEL==0";
			TString trigger = "Trig_BxESPRI>0&&Trig_DSB==0&&Trig_BxESPRIxTEL==0&&Trig_BxNEBULA==0&&Trig_BxTEL==0";
			defaultGate = trigger;
			//defaultGate = trigger + "&&" + protonGate + "&&" + targetArea + "&&" + beamGate;
		//	gate[1] = defaultGate +"&&"+ protonGate;
		//	gate[2] = defaultGate +"&&"+ targetArea;
		//	gate[3] = protonGate +"&&"+ gate[2];
		//	gate[4] = defaultGate +"&&"+ beamGate;
		//	gate[5] = beamGate +"&&"+ gate[3];
	
			//defaultGate = "Trig_BxESPRI";
			//defaultGate = "";
		}
		void defineProtonGate(){
			protonGate = "Proton";
			//protonGate = "espriNaiEnergy>5&&espriPlasDeltaE>1";
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
			//TString drawVar = "2*naiQ[1]:protonTheta>>";
			TString drawVar = "excitationEnergy>>";
			//TString drawVar = "espriNaiEnergy:protonTheta>>";
			TString drawRange = "(1000,-20,80)";
			//TString drawVar = "plasQ[1]:naiQ[1]>>";
			//TString drawVar = "espriPlasDeltaE:espriNaiEnergy>>";
			//TString drawRange = "(200,0,150,200,0,40)";
			for (int i = 0; i < 8; ++i) {
				c->cd(i+1);	
				TString draw = drawVar + hName[i] + drawRange;
				cout<<draw<<endl;
				tree->Draw(draw,gate[i],"colz");
				//gPad->Modified();
				//gPad->Update();
				h[i] = (TH1F*)gDirectory->Get(hName[i]);
				h[i]->Write();
			}

			c->Write();
			delete c;
		}
		void scan(){
			//TString scanVar = "excitationEnergy:residueMass:beamMass";
			TString scanVar = "excitationEnergy:residueMass:residueEnergy:residueMomentum";
			cout<<gate[7]<<endl;
			tree->Scan(scanVar,gate[7]);

		}

};
class EXBe10:public EXSpectrum {
	private:
	public:
		EXBe10(){
			tree->SetAlias("MassBe","10.0113*1");
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe10.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe10.C");

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
			outputName = "exBe10Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be10Bar23Be10||Be10Bar22Be10||Be10Bar21Be10||Be10Bar20Be10||Be10Bar19Be10)";
			//hodGate = "(Be10Bar23Be9||Be10Bar22Be9||Be10Bar21Be9||Be10Bar20Be9||Be10Bar19Be9)";
		}
		void defineBeamGate(){
			beamGate = "BeamBe10";
		}
};
class EXBe12:public EXSpectrum {
	private:
	public:
		EXBe12(){
			tree->SetAlias("MassBe","12.0247*1");
		}
		void loadCut(){
			gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutProtonBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
			gROOT->ProcessLine(".x rootfiles/cutHodBe12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar23Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar22Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar21Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar20Be12.C");
			gROOT->ProcessLine(".x rootfiles/cutBe12Bar19Be12.C");
	
		}

		void assignOutputName(){
			outputName = "exBe12Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			hodGate = "(Be12Bar23Be12||Be12Bar22Be12||Be12Bar21Be12||Be12Bar20Be12||Be12Bar19Be12)";
		}
		void defineBeamGate(){
			beamGate = "BeamBe12";
		}
};

class EXBe14:public EXSpectrum {
	private:
	public:
		EXBe14(){
			tree->SetAlias("MassBe","14.0407*1");
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

			gROOT->ProcessLine(".x rootfiles/cutBar31Central.C");
			gROOT->ProcessLine(".x rootfiles/cutBar31Bottom.C");
			gROOT->ProcessLine(".x rootfiles/cutBar31Top.C");
			gROOT->ProcessLine(".x rootfiles/cutBar31Left.C");
			gROOT->ProcessLine(".x rootfiles/cutBar31Right.C");

			gROOT->ProcessLine(".x rootfiles/cutBar30Central.C");
			gROOT->ProcessLine(".x rootfiles/cutBar30Bottom.C");
			gROOT->ProcessLine(".x rootfiles/cutBar30Top.C");
			gROOT->ProcessLine(".x rootfiles/cutBar30Left.C");
			gROOT->ProcessLine(".x rootfiles/cutBar30Right.C");


			gROOT->ProcessLine(".x rootfiles/cutBar17Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar18Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar19Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar20Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar21Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar22Be10.C");
			gROOT->ProcessLine(".x rootfiles/cutBar23Be10.C");
		}

		void assignOutputName(){
			outputName = "exBe14Histo.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			//hodGate = "(Bar23Be14||Bar22Be14||Bar21Be14||Bar20Be14||Bar19Be14)";
			//hodGate = "(Bar32Be14||Bar31Be14||Bar30Be14||Bar29Be14||Bar28Be14||Bar27Be14)";
			//hodGate = "(Bar30Be14)";
			//hodGate = "(Bar32Be14||Bar31Be14||Bar30Be14||Bar29Be14)";
			//hodGate = "(Bar31Be14||Bar30Be14||Bar29Be14)";
			//hodGate = "(Bar29Be14)";
			//hodGate = "(Bar30Central||Bar30Top||Bar30Bottom||Bar30Left||Bar30Right||Bar31Central||Bar31Top||Bar31Bottom||Bar31Left||Bar31Right)";
			//hodGate = "(Bar30Top||Bar30Bottom||Bar30Left||Bar30Right||Bar31Top||Bar31Bottom||Bar31Left||Bar31Right)";
			hodGate = "(Bar17Be10||Bar18Be10||Bar19Be10||Bar20Be10||Bar21Be10||Bar22Be10||Bar23Be10)";
		}
		void defineBeamGate(){
			beamGate = "BeamBe14";
		}
};

void exBe(){

	//EXBe10 *exBe = new EXBe10();
	//exBe->loadTChain(310,311);
	//exBe->loadTChain(298,330);
	EXBe12 *exBe = new EXBe12();
	exBe->loadTChain(334,365);
	//exBe->loadTChain(360,361);
	//EXBe14 *exBe = new EXBe14();
	//exBe->loadTChain(436,437);
	//exBe->loadTChain(366,456);

	exBe->defineAlias();
	exBe->defineHodGate();
	exBe->defineBeamGate();
	exBe->defineGate();
	exBe->loadCut();
	exBe->assignOutputName();
	exBe->createOutputFile();
	exBe->draw();
	//exBe->scan();

}
