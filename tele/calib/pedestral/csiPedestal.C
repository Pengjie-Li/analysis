class CsiPed{
	private:
		int runNumber;
		TChain *tree;
		TF1 *fitFunction;
		double fitPara[7][3];
		TH1F *hTemp[7];

		TString draw;
		TString gate;
	public:
		CsiPed(){
			tree = new TChain("tree");
			fitFunction = new TF1("fit","gaus",0,200);
			fitFunction->SetNpx(1000);
		}
		~CsiPed(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i < runStop; ++i) {
				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root",i));
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
		void drawHist(){
			for (int i = 0; i < 7; ++i) {
				drawHist(i);
			}
			drawTCanvas();
		}
		void fitHist(){
			for (int i = 0; i < 7; ++i) {
				fitHist(i);	
			}
		}
		void outputTxt(){
			TString outputName = Form("./txt/Pedestal%d.txt",runNumber);
			ofstream fout(outputName,ios_base::out);
			for (int i = 0; i < 7; ++i) {
			fout<<i<<"\t"<<fitPara[i][1]<<"\t"<<fitPara[i][2]<<endl;
			}
			fout.close();
		}
		void fitHist(int i){
			int xBin = hTemp[i]->GetMaximumBin();	
			fitFunction->SetParameter(1,(double)xBin);
			fitFunction->SetParameter(2,0.5);
			hTemp[i]->Fit(fitFunction,"Q");
			fitFunction->GetParameters(fitPara[i]);
			cout<<fitPara[i][1]<<":"<<fitPara[i][2]<<endl;
			hTemp[i]->Write();
		}
		void drawHist(int i){
			draw = Form("csiEnergyRaw[%d]>>hCsI%d(200,0,200)",i,i);
			tree->Draw(draw,gate);
		}
		void drawTCanvas(){
			TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
			for (int i = 0; i < 7; ++i) {
				hTemp[i] = (TH1F*)gDirectory->Get(Form("hCsI%d",i));
			//	hTemp[i]->SetLineStyle(1);
				hTemp[i]->SetLineColor(i+1);
				//hTemp[i]->Scale(1./hTemp[i]->GetMaximum());
				//hTemp[i]->Scale(10);
				hTemp[i]->GetYaxis()->SetRangeUser(0,5E5);
				hTemp[i]->GetXaxis()->SetRangeUser(60,120);
				if(i>0) hTemp[i]->Draw("same");
				else hTemp[i]->Draw();
				
			}

			drawLegend();
			cPad->Write();
		}
		void drawLegend(){
			TLegend *legends=new TLegend(0.7,0.2,0.9,0.6); // the numbers determine the position of the box    
			// setting for legend
			legends->SetFillColor(0);
			legends->SetHeader("CsI Energy");
			legends->SetTextFont(72);
			legends->SetTextSize(0.04);
			TString nameCsi[7] = {"RLT","RRT","RLB","RRB","LL","LRT","LRB"};
			for (int i = 0; i < 7; ++i) {
				legends->AddEntry(hTemp[i], nameCsi[i],"l");
			}
			legends->Draw();
		}

};
void csiPedestal(){

	gStyle->SetOptStat(0);
	int runNumber = 380;

	TString fileName = Form("./output/csiPedestal%d.root",runNumber);

	TFile *outputFile = new TFile(fileName,"RECREATE");


	CsiPed *csiPed = new CsiPed();
	csiPed->loadRun(runNumber);
	csiPed->loadGate("Trig_DSB");
	csiPed->drawHist();
	csiPed->fitHist();
	csiPed->outputTxt();
}
