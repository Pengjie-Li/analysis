class SlewCorrection{
	private:
		TChain *tree;
		TString timeVar;
		TString energyVar;
		TString drawVar;
		TString hName;
		TString drawRange;
		TString draw;
		TString gate;

		TH2F *hDraw;
	public:
		SlewCorrection(){
			tree = new TChain("tree");
		}
		~SlewCorrection(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i < runStop; ++i) {
				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}
		}
		void loadRun(int run){
			loadChain(run,run+1);
		}
		void loadRuns(int runStart,int runStop){
			loadChain(runStart,runStop+1);
		}
		void setVar(TString t,TString q, TString h){
			timeVar = t;
			energyVar = q;
			hName = h;
			drawVar = timeVar+ ":"+ energyVar + ">>" + hName;
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
		void setGate(TString g){
			gate = g;
		}
		void drawBeforeCorrection(){
			draw = drawVar + drawRange;
			TString color = "colz";
			tree->Draw(draw,gate,color);
			hDraw = (TH2F*)gDirectory->Get(hName);
			hDraw->Write();
		}
		void profileX(){
			//TCanvas *cProfile = new TCanvas("cProfile","cProfile",700,700);
			TProfile *hPDEE = hDraw->ProfileX();
			//hPDEE->SetMarkerColor(2);
                        hPDEE->Draw("same");
                        hPDEE->Fit("pol1");

		}
};

void slewEffect(){
	//Be10
	//int runStart = 298;
	//int runStop = 330;
	//Be12
	//int runStart = 334;
	//int runStop = 365;
	//Be14
	//int runStart = 366;
	//int runStop = 456;
	//TString fileName = Form("correctSlewEffect%d_%d.root",runStart,runStop);

	int runNumber = 310;
	//int runNumber = 320;
	//int runNumber = 340;
	//int runNumber = 360;
	TString fileName = Form("correctSlewEffect%d.root",runNumber);


	TFile *outputFile = new TFile(fileName,"RECREATE");
	
	SlewCorrection *sc = new SlewCorrection();
	//sc->loadRuns(runStart,runStop);
	sc->loadRun(runNumber);
	sc->setVar("F3TCal[0]","F3QRaw[0]", "hF3Slew0");
	//sc->setRange(500,0,1500,500,540,580);
	sc->setRange(350,250,600,500,540,580);//320
	//sc->setRange(250,250,500,500,540,580);//360
	sc->setGate("Trig_DSB");
	sc->drawBeforeCorrection();
	sc->profileX();
}
