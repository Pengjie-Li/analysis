class DssdPed{
	private:
		int runNumber;
		TChain *tree;
		double fitPara[7][3];
		TH1F *hTemp[7];

		TString draw;
		TString gate;
	public:
		DssdPed(){
			tree = new TChain("tree");
		}
		~DssdPed(){}
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
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 32; ++j) {
					cout<<"generating "<<i<<" "<<j<<endl;
					drawHist(i,j);
				}
			}
		}
		void save(){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 32; ++j) {

					TH1F *hTemp = (TH1F*)gDirectory->Get(Form("hDssd%d_%d",i,j));
					hTemp->Write();
				}
			}
		}
	
		void fitHist(){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 32; ++j) {
					//cout<<"Fitting :"<<i<<"	"<<j<<endl;
					fitHist(i,j);	
				}
			}
		}
		void outputText(){
			TString outputName = Form("./txt/dssdPedestal%d.txt",runNumber);
			ofstream fout(outputName,ios_base::out);
			for (int i = 0; i < 7; ++i) {
			fout<<i<<"\t"<<fitPara[i][1]<<"\t"<<fitPara[i][2]<<endl;
			}
			fout.close();
		}
		void fitHist(int i,int j){
			TH1F *hTemp = (TH1F*)gDirectory->Get(Form("hDssd%d_%d",i,j));
			int xBin = hTemp->GetMaximumBin();	

			TF1 *fitFunction;
			fitFunction = new TF1("fitFunction","gaus",0,200);
			fitFunction->SetNpx(1000);
			fitFunction->SetParameter(1,(double)xBin);
			fitFunction->SetParameter(2,0.5);
			hTemp->Fit(fitFunction,"Q","R",xBin-30,xBin+30);
			double par[3];
			fitFunction->GetParameters(par);
			cout<<i<<"	"<<j<<"	"<<par[1]<<"	"<<par[2]<<endl;
		}
		void drawHist(int i,int j){
			draw = Form("dssdQRaw[%d][%d]>>hDssd%d_%d(300,0,300)",i,j,i,j);
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

//int runNumber = 310;
int runNumber = 320;
//int runNumber = 597;
//int runNumber = 596;
void generatePedestal(){
	gStyle->SetOptStat(0);

	TString fileName = Form("./output/dssdPedestal%d.root",runNumber);

	TFile *outputFile = new TFile(fileName,"RECREATE");


	DssdPed *dssdPed = new DssdPed();
	dssdPed->loadRun(runNumber);
	dssdPed->loadGate("Trig_DSB");
	dssdPed->drawHist();
	dssdPed->save();

}
void fitPedestal(){
	gStyle->SetOptStat(0);

	TString fileName = Form("./output/dssdPedestal%d.root",runNumber);
	TFile *outputFile = new TFile(fileName,"READ");

	DssdPed *dssdPed = new DssdPed();
	dssdPed->fitHist();
	//dssdPed->outputText();


}
void dssdPedestal(){

	generatePedestal();
	//fitPedestal();
}
