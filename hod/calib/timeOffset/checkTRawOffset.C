class TRawOffset{
	private:
		TChain *tree;
		TF1 *f;
	public:
		TRawOffset(){
			tree = new TChain("tree");
			f = new TF1("f","x",0,35000);
		}
		~TRawOffset(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i < runStop; ++i) {
				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}
		}
		void loadRuns(int run){
			loadChain(run,run+1);
		}
		void loadRuns(int runStart,int runStop){
			loadChain(runStart,runStop+1);
		}
		void drawFunction(){
			f->Draw("same");
		}
		void checkBar(int barId){
			TString drawVar = Form("hodTRaw[0][%d]:hodTRaw[1][%d]>>hTRaw%d",barId,barId,barId);
			TString drawRange ;
			if(barId>=0&&barId<=23) drawRange = "(4000,0,35000,4000,0,35000)";
			else if(barId>=24&&barId<=39) drawRange = "(4000,0,5000,4000,0,5000)";
			TString drawOption = drawVar + drawRange;
			TString gate ="";
			TString color = "colz";
			tree->Draw(drawOption,gate,color);
			TH1F *hTemp = (TH1F*)gDirectory->Get(Form("hTRaw%d",barId));
			hTemp->Write();
			drawFunction();
		}
		void checkAllBars(){
			TCanvas *cHodTRaw = new TCanvas("cHodTRaw","cHodTRaw",1200,900);
			cHodTRaw->Divide(8,5);
			for (int i = 0; i < 40; ++i) {
				cHodTRaw->cd(i+1);
				checkBar(i);	
				cHodTRaw->Modified();
				cHodTRaw->Update();
			}
			//cHodTRaw->Write();
                        //cHodTRaw->Print("checkTRawOffset.pdf");
                        //cHodTRaw->Print("checkTRawOffset.svg");
                        //cHodTRaw->Print("checkTRawOffset.root");
		}

		

};
void checkTRawOffset(){
	//Be10
	//int runStart = 298;
	//int runStop = 330;
	//Be12
	//int runStart = 334;
	//int runStop = 365;
	//Be14
	int runStart = 366;
	int runStop = 456;
	
	
	TString fileName = Form("checkTRawOffset%d_%d.root",runStart,runStop);
	TFile *outputFile = new TFile(fileName,"RECREATE");
	TRawOffset *to = new TRawOffset();
	to->loadRuns(runStart,runStop);
	to->checkAllBars();
	//to->checkBar(23);
}
