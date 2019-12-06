// define a function with 2 parameters
Double_t fitfunc(Double_t *x,Double_t *par) {

	//cout<<par[0]<<":"<<par[1]<<":"<<par[2]<<endl;
	Double_t fitval = par[0]/TMath::Sqrt(x[0]+400)+par[1];

	return fitval;
}

class SlewCorrection{
	private:
		int runNumber;
		TChain *tree;

		TString timeVar;
		TString energyVar;
		TString drawVar;
		TString hName;
		TString drawRange;
		TString draw;
		TString gate;

		TCanvas *cPad;
		TH2F *hBefore;
		TH2F *hAfter;
	public:
		SlewCorrection(){
			tree = new TChain("tree");
		}
		~SlewCorrection(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i < runStop; ++i) {
				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root_3",i));
			}
		}
		void loadRun(int run){
			runNumber = run;
			loadChain(run,run+1);
		}
		void loadRuns(int runStart,int runStop){
			loadChain(runStart,runStop+1);
		}
		void loadGate(TString g){
			gate = g;
		}


		
		void setCanvas(TString cPadName){
			cPad = new TCanvas(cPadName,cPadName,1400,700);
			cPad->Divide(2,1);
		}
		void setVar(TString t,TString q, TString h){
			timeVar = t;
			energyVar = q;
			hName = h;
		}
		void setRange(int x1, int x2, int x3, int y1, int y2, int y3){
			int xBin = x1;
			int xMin = x2;
			int xMax = x3;
			int yBin = y1;
			int yMin = y2;
			int yMax = y3;
			drawRange = Form("(%d,%d,%d,%d,%d,%d)",xBin,xMin,xMax,yBin,yMin,yMax);
		}
		void drawBefore(){
			cPad->cd(1);
			gPad->SetLogz();
			TString hNameBefore = hName  + "Before";
			drawVar = timeVar+ ":"+ energyVar + ">>" + hNameBefore;
			draw = drawVar + drawRange;
			TString color = "colz";
			tree->Draw(draw,gate,color);
			hBefore = (TH2F*)gDirectory->Get(hNameBefore);
			hBefore->Write();
		}

		void drawAfter(double corrPara){
			cPad->cd(2);
			gPad->SetLogz();
			timeVar = timeVar + Form("+ (%f/sqrt(sqrt(",corrPara)+energyVar+")))";
			TString hNameAfter = hName  + "After";
			drawVar = timeVar+ ":"+ energyVar + ">>" + hNameAfter;
			draw = drawVar + drawRange;
			TString color = "colz";
			tree->Draw(draw,gate,color);
			hAfter = (TH2F*)gDirectory->Get(hNameAfter);
			hAfter->Write();
	
		}
		void printPNG(){
			TString printName ="./png/"+hName+Form("run%d.png",runNumber);
			cPad->Print(printName);
		}
};
void slewEffect(){

//	int runNumber = 310;
//	gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
//	gROOT->ProcessLine(".x rootfiles/cutBeamMixed1Be10.C");
//	gROOT->ProcessLine(".x rootfiles/cutBeamMixed2Be10.C");
	//int runNumber = 320;
	int runNumber = 340;
	gROOT->ProcessLine(".x rootfiles/cutBeamB15.C");
	gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
	gROOT->ProcessLine(".x rootfiles/cutBeamLi9.C");
	gROOT->ProcessLine(".x rootfiles/cutBeamHe6.C");
	gROOT->ProcessLine(".x rootfiles/cutBeamH3.C");
	//int runNumber = 360;

	//int runNumber = 380;
	//int runNumber = 595;
	TString fileName = Form("correctSlewEffect%d.root",runNumber);


	TFile *outputFile = new TFile(fileName,"UPDATE");

//	SlewCorrection *scSBT2 = new SlewCorrection();
//	scSBT2->loadRun(runNumber);
//	//scSBT2->loadGate("Trig_DSB&&(Beam)");
//	scSBT2->loadGate("Trig_DSB&&(BeamH3||BeamHe6||BeamLi9||BeamB15||Beam)");
//	scSBT2->setCanvas("SBT2Corr");
//	//scSBT2->setVar("0.5*(SBT2TCal[0]+SBT2TCal[1])+0.0005*SBT2QRaw[0]+0.0004*SBT2QRaw[1]-5/sqrt(sqrt(SBT2QRaw[1]))","SBT2QRaw[0]", "hSBT21");
//	//scSBT2->setVar("0.5*(SBT2TCal[0]+SBT2TCal[1])+0.0008*SBT2QRaw[0]","SBT2QRaw[1]", "hSBT21");
//	scSBT2->setVar("0.5*(SBT2TCal[0]+SBT2TCal[1])","SBT2QRaw[0]", "hSBT20");
//	scSBT2->setRange(1000,0,2000,1000,210,230);
//	scSBT2->drawBefore();
//	scSBT2->setVar("0.5*(SBT2TCal[0]+SBT2TCal[1])","SBT2QRaw[1]", "hSBT20");
//	scSBT2->drawAfter(0);


	SlewCorrection *scSBT1 = new SlewCorrection();
	scSBT1->loadRun(runNumber);
	//scSBT1->loadGate("Trig_DSB&&(Beam)");
	scSBT1->loadGate("Trig_DSB&&(BeamH3||BeamHe6||BeamLi9||BeamB15||Beam)");
	scSBT1->setCanvas("SBT1Corr");
	//scSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])+0.0005*SBT1QRaw[0]+0.0004*SBT1QRaw[1]-5/sqrt(sqrt(SBT1QRaw[1]))","SBT1QRaw[0]", "hSBT11");
	//scSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])+0.0008*SBT1QRaw[0]","SBT1QRaw[1]", "hSBT11");
	scSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])","SBT1QRaw[0]", "hSBT10");
	scSBT1->setRange(1000,0,2000,1000,210,230);
	scSBT1->drawBefore();
	scSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])","SBT1QRaw[1]", "hSBT10");
	scSBT1->drawAfter(0);



//	SlewCorrection *scF7 = new SlewCorrection();
//	scF7->loadRun(runNumber);
//	//scF7->loadGate("Trig_DSB&&(BeamMixed1||BeamMixed2||Beam)");
//	scF7->loadGate("Trig_DSB&&(BeamH3||BeamHe6||BeamLi9||BeamB15||Beam)");
//	scF7->setCanvas("F7Corr");
//	scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]-5/sqrt(sqrt(F7QRaw[1]))","F7QRaw[0]", "hF71");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]-5/sqrt(sqrt(F7QRaw[0]))","F7QRaw[1]", "hF71");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]","F7QRaw[0]", "hF70");
//	//Linear scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]","F7QRaw[0]", "hF70");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0004*F7QRaw[1]","F7QRaw[0]", "hF70");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]","F7QRaw[1]", "hF71");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0003*F7QRaw[1]","F7QRaw[0]", "hF70");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0008*F7QRaw[0]","F7QRaw[1]", "hF71");
//	//scF7->setVar("0.5*(F7TCal[0]+F7TCal[1])","F7QRaw[0]", "hF70");
//	scF7->setRange(1000,0,4000,1000,550,570);
//	scF7->drawBefore();
//	scF7->drawAfter(-5);

}
