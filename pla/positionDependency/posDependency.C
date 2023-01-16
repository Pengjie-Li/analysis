// define a function with 2 parameters
Double_t fitfunc(Double_t *x,Double_t *par) {

	//cout<<par[0]<<":"<<par[1]<<":"<<par[2]<<endl;
	Double_t fitval = par[0]/TMath::Sqrt(x[0]+400)+par[1];

	return fitval;
}

class PosDepend{
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
		PosDepend(){
			tree = new TChain("tree");
		}
		~PosDepend(){}
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

		void setAlias(){
			tree->SetAlias("F7TDiff","(F7TCal[0]-F7TCal[1]-2.8)");
			tree->SetAlias("SBT1TDiff","(SBT1TCal[0]-SBT1TCal[1]-1.24)");
			tree->SetAlias("SBT2TDiff","(SBT2TCal[0]-SBT2TCal[1])");
		}
		void setAlias(TString var1,TString var2){
			tree->SetAlias(var1,var2);
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
void posDependency(){

//	int runNumber = 310;
//	gROOT->ProcessLine(".x rootfiles/cutBeamBe10.C");
//	gROOT->ProcessLine(".x rootfiles/cutBeamMixed1Be10.C");
//	gROOT->ProcessLine(".x rootfiles/cutBeamMixed2Be10.C");
	//int runNumber = 320;
	int runNumber = 340;
	gROOT->ProcessLine(".x rootfiles/cutBeamBe12.C");
	
	//int runNumber = 436;
	//gROOT->ProcessLine(".x rootfiles/cutBeamBe14.C");

	//int runNumber = 380;
	//int runNumber = 595;
	TString fileName = Form("correctPosDependency%d.root",runNumber);


	TFile *outputFile = new TFile(fileName,"UPDATE");


//	PosDepend *pdSBT1 = new PosDepend();
//	pdSBT1->loadRun(runNumber);
//	//pdSBT1->loadGate("Trig_DSB&&(Beam)");
//	//pdSBT1->loadGate("Trig_DSB&&(BeamH3||BeamHe6||BeamLi9||BeamB15||Beam)");
//	pdSBT1->loadGate("Trig_DSB&&(Beam)");
//	pdSBT1->setAlias();
//	pdSBT1->setCanvas(Form("SBT1Corr_%d",runNumber));
//	//pdSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])+0.0005*SBT1QRaw[0]+0.0004*SBT1QRaw[1]-5/sqrt(sqrt(SBT1QRaw[1]))","SBT1QRaw[0]", "hSBT11");
//	//pdSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])+0.0008*SBT1QRaw[0]","SBT1QRaw[1]", "hSBT11");
//	pdSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])","SBT1TDiff", Form("hSBT1_%d",runNumber));
//	pdSBT1->setRange(200,-2,2,500,215,225);
//	pdSBT1->drawBefore();
//	pdSBT1->setVar("0.5*(SBT1TCal[0]+SBT1TCal[1])+0.5*SBT1TDiff","SBT1TDiff", Form("hSBT1_%d",runNumber));
//	pdSBT1->drawAfter(0);



	PosDepend *pdF7 = new PosDepend();
	pdF7->loadRun(runNumber);
	//pdF7->loadGate("Trig_DSB&&(BeamMixed1||BeamMixed2||Beam)");
	pdF7->loadGate("Trig_DSB&&(Beam)");
	pdF7->setCanvas("F7Corr");

	pdF7->setAlias();
	pdF7->setAlias("f7t_slew","(0.5*(F7TCal[0]+F7TCal[1])-(-1.06072e-03*F7Q+1.15839e+00/sqrt(sqrt(sqrt(F7Q+92.5)))))");
	pdF7->setVar("F13T-f7t_slew+570","F7TDiff", "hF71");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]-5/sqrt(sqrt(F7QRaw[0]))","F7QRaw[1]", "hF71");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]","F7QRaw[0]", "hF70");
	//Linear pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]+0.0004*F7QRaw[1]","F7QRaw[0]", "hF70");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0004*F7QRaw[1]","F7QRaw[0]", "hF70");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0005*F7QRaw[0]","F7QRaw[1]", "hF71");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0003*F7QRaw[1]","F7QRaw[0]", "hF70");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])+0.0008*F7QRaw[0]","F7QRaw[1]", "hF71");
	//pdF7->setVar("0.5*(F7TCal[0]+F7TCal[1])","F7QRaw[0]", "hF70");
	pdF7->setRange(200,-2,2,500,225,245);
	pdF7->drawBefore();
	pdF7->setVar("F13T-f7t_slew-1.1*F7TDiff+570","F7TDiff", "hF71");
	pdF7->drawAfter(0);

}
