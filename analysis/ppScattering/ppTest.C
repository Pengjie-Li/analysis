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
			//protonGate = "Proton";

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
			protonGate = "abs("+planeOfBPR+")<0.008";
			//protonGate = "espriNaiEnergy>5&&espriPlasDeltaE>1";
		}
		void defineHodGate(){};
		void defineBeamGate(){};
		void defineTargetArea(){
			targetArea="sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<13";
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
			//TString drawVar = "(2*naiQ[1]+plasQ[1]):protonTheta>>";
			TString drawVar = "espriEnergy:espriAngle>>";
			//TString drawVar = "(naiQ[1]+plasQRPed/(342.653 -0.0507624*plasQRPed)):protonTheta>>";
			//TString drawVar = "(naiQ[1]+plasQRPed/(257.172 -0.0467016*plasQRPed)):protonTheta>>";
			//TString drawVar = "2*espriNaiEnergy+espriPlasDeltaE:protonTheta>>";
			TString drawRange = "(200,40,80,200,0,200)";
			//TString drawVar = "plasQ[1]:naiQ[1]>>";
			//TString drawVar = "espriPlasDeltaE:espriNaiEnergy>>";
			//TString drawRange = "(200,0,150,200,0,40)";
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
			outputName = "ppBe10Histo.root";
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
			gROOT->ProcessLine(".x rootfiles/cutProtonBe14.C");
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
			outputName = "ppBe14HistoBe10Bar27-29.root";
			//cout<<outputName<<endl;
		}
		void defineHodGate(){
			//hodGate = "(Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
			//hodGate = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
			hodGate = "(Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
			//hodGate = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14||Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
			//
			//hodGate = "(Be14Bar26Be12||Be14Bar25Be12||Be14Bar24Be12||Be14Bar23Be12||Be14Bar22Be12||Be14Bar21Be12||Be14Bar20Be12||Be14Bar19Be12)";
			//hodGate = "(Be14Bar23Be11||Be14Bar22Be11||Be14Bar21Be11||Be14Bar20Be11||Be14Bar19Be11)";
			//hodGate = "(Be14Bar23Be10||Be14Bar22Be10||Be14Bar21Be10||Be14Bar20Be11||Be14Bar19Be10)";
		}
		void defineBeamGate(){
			beamGate = "BeamBe14";
			//beamGate = "SmallBeamBe14";
		}
};

void ppTest(){

	//PPBe10 *ppBe = new PPBe10();
	//ppBe->loadTChain(310,311);
	//ppBe->loadTChain(298,330);
	//PPBe12 *ppBe = new PPBe12();
	//ppBe->loadTChain(341,342);
	//ppBe->loadTChain(334,365);
	//ppBe->loadTChain(334,363);
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
