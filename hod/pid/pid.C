class PID{
	private:
		TChain *tree;
	public:
		PID(){
			tree = new TChain("tree");
		}
		~PID(){}
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
		void checkBarPid(int barId){
			TString drawVar = Form("hodBarQCal[%d]:0.5*(hodTRaw[0][%d]+hodTRaw[1][%d])>>hHod%d",barId,barId,barId,barId);
			TString drawRange;
			if(barId<24) drawRange = "(1000,17000,20000,1000,0,4000)";
			else drawRange = "(1000,1200,2200,1000,0,4000)";
			TString draw = drawVar+drawRange;

			TString gate1 = "Trig_BxESPRI";
			TString gate2 = Form("hodBarQCal[%d]>0&&hodTRaw[0][%d]!=-1&&hodTRaw[1][%d]!=-1",barId,barId,barId);
			cout<<"gate1: "<<gate1<<endl;
			cout<<"gate2: "<<gate2<<endl;
			TString gate = gate1+"&&"+gate2;

			TString color = "colz";

			tree->Draw(draw,gate,color);
			TH1F *hTemp = (TH1F*)gDirectory->Get(Form("hHod%d",barId));
			hTemp->Write();
		}
		void checkAllBarsPid(){
                        TCanvas *cHodPid = new TCanvas("cHodPid","cHodPid",1200,900);
                        cHodPid->Divide(8,5);
                        for (int i = 0; i < 40; ++i) {
                                cHodPid->cd(i+1);
                                checkBarPid(i);
                                cHodPid->Modified();
                                cHodPid->Update();
                        }
		}

};
void pid(){
	//Be10
	//int runStart = 298;
	//int runStop = 330;
	//Be12
	//int runStart = 334;
	//int runStop = 365;
	//Be14
	int runStart = 366;
	int runStop = 456;
	TString fileName = Form("checkPidBars%d_%d.root",runStart,runStop);

	//int runNumber = 436;
	//TString fileName = Form("checkPidBars%d.root",runNumber);


	TFile *outputFile = new TFile(fileName,"RECREATE");
	PID *p = new PID();
	//p->loadRun(runNumber);
	p->loadRuns(runStart,runStop);
	p->checkAllBarsPid();
	//p->checkBarPid(23);
}
