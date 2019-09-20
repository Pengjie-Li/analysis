class SlewCorrection{
	private:
		TChain *tree;
		TString timeVar;
		TString energyVar;
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
		void setVar(TString t,TString q){
			timeVar = t;
			energyVar = q;
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
	int runStart = 366;
	int runStop = 456;
	TString fileName = Form("correctSlewEffect%d_%d.root",runStart,runStop);

	//int runNumber = 436;
	//TString fileName = Form("checkPidBars%d.root",runNumber);


	TFile *outputFile = new TFile(fileName,"RECREATE");
	
	SlewCorrection *sc = new SlewCorrection();
	sc->loadRuns(runStart,runStop);
	sc->setVar("F3TCal[0]","F3QRaw[0]");
	sc->drawBeforeCorrection();
}
