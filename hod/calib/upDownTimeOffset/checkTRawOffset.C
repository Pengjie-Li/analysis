class TRawOffset{
	private:
		TChain *tree;
		ofstream out;
		TString outputName;
	public:
		TRawOffset(){
			tree = new TChain("tree");
		}
		~TRawOffset(){}
		void loadChain(int runStart,int runStop){

			outputName = Form("upDownOffset%d_%d.txt",runStart,runStop);
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
		void checkBar(int barId){
			TString drawVar = Form("hodTRaw[0][%d]-hodTRaw[1][%d]>>hTRaw%d",barId,barId,barId);
			TString drawRange ;
			drawRange = "(2000,-1000,1000)";
			TString drawOption = drawVar + drawRange;
			TString gate =Form("hodTRaw[0][%d]>0&&hodTRaw[1][%d]>0",barId,barId);
			TString color = "colz";
			tree->Draw(drawOption,gate,color);
			TH1F *hTemp = (TH1F*)gDirectory->Get(Form("hTRaw%d",barId));
			hTemp->Write();
		}
		void checkAllBars(){
			TCanvas *cHodTRaw = new TCanvas("cHodTRaw","cHodTRaw",1200,900);
			cHodTRaw->Divide(8,5);
			for (int i = 0; i < 40; ++i) {
			//for (int i = 0; i < 3; ++i) {
				cHodTRaw->cd(i+1);
				checkBar(i);
				findOffset(i);
				cHodTRaw->Modified();
				cHodTRaw->Update();
			}
			//cHodTRaw->Write();
                        //cHodTRaw->Print("checkTRawOffset.pdf");
                        //cHodTRaw->Print("checkTRawOffset.svg");
                        //cHodTRaw->Print("checkTRawOffset.root");
		}
		void findOffset(int barId){
			TH1F *hTemp = (TH1F*)gDirectory->Get(Form("hTRaw%d",barId));
			double xpos = findPeak(hTemp);
			double fitPar[3] = {0};
			fitPeak(hTemp,xpos,fitPar);
			outputOffset(barId,fitPar);
		}
		double findPeak(TH1F *hDraw){
			TSpectrum *s = new TSpectrum(1,5);
			Int_t nfound = s->Search(hDraw,20,"nobackground new",0.3); 
			//cout<<nfound<<endl;
			Double_t *xpeaks = s->GetPositionX();
			delete s;
			return xpeaks[0];
		}
		void fitPeak(TH1F *hDraw,double xpos,double *fpar){

			Double_t par[3]={0};

			Int_t bin = hDraw->GetXaxis()->FindBin(xpos);
			Double_t ypos = hDraw->GetBinContent(bin);

			par[0] = ypos;
			par[1] = xpos;
			par[2] = 30;
			cout<<"par:"<<" yp="<<ypos<<" xp="<<xpos<<endl;

			printf("Now fitting: Be patient\n");


			double afr1=10;
			double abr1=10;
			double fr1=par[1]-afr1*par[2];
			double br1=par[1]+abr1*par[2];


			TF1 *peak1 = new TF1("peak1","gaus(0)",fr1,br1);
			peak1->SetParameters(&par[0]);
			peak1->SetParLimits(0, 10, 10000);
			peak1->SetParLimits(1, -1000, 1000);
			peak1->SetParLimits(2, 0.001, 50);
			//peak1->SetParameters(&par[0]);
			peak1->SetNpx(2000);
			hDraw->Fit(peak1,"QR");
			peak1->GetParameters(&fpar[0]);
			peak1->Draw("same");

			delete peak1;
		}
		void setOutput(){
			out.open(outputName,ios_base::app | ios_base::out);
			out.flags (ios::left);
		}
		void outputOffset(int barId,double *fpar){
			out<<setw(20)<<barId<<setw(20)<<fpar[0]<<setw(20)<<fpar[1]<<setw(20)<<fpar[2]<<endl;
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
	//int runStart = 366;
	//int runStop = 456;
	
	int runStart = 436;
	int runStop = 437;
	
	
	TString fileName = Form("checkTRawOffset%d_%d.root",runStart,runStop);
	TFile *outputFile = new TFile(fileName,"RECREATE");
	TRawOffset *to = new TRawOffset();
	to->loadRuns(runStart,runStop);
	to->setOutput();
	to->checkAllBars();
	//to->checkBar(23);
}
