class DrawDE{
	private:
	public:
		int side;
		int barNo;
		TChain *tree;

		TCanvas *cDEE;
		TString cName;
		TString hName;
		TString draw;
		TString condition;

		DrawDE(){}
		~DrawDE(){
			delete cDEE;
		}
		DrawDE(TChain *t,int s,int b){
			tree = t;
			side = s;
			barNo = b;

			nameAll();
			drawBand();
		}
		void nameAll(){
			int nBin = 410;
			int min = 0;
			int max = 4100;

			if(side == 0){
				cName = Form("dEELeftBar%d",barNo);
				hName = Form("hLeft%d",barNo);
				draw = Form("plasQL:naiQ[%d][%d]>>hLeft%d(%d,%d,%d,%d,%d,%d)",side,barNo,barNo,nBin,min,max,nBin,min,max);
			}else{
				cName = Form("dEERightBar%d",barNo);
				hName = Form("hRight%d",barNo);
				draw = Form("plasQR:naiQ[%d][%d]>>hRight%d(%d,%d,%d,%d,%d,%d)",side,barNo,barNo,nBin,min,max,nBin,min,max);
			}

			condition="";
		}
		void drawBand(){
			cDEE = new TCanvas(cName,cName,800,700);
			tree->Draw(draw,condition,"colz");
		}
};
class ExtractDE:public DrawDE{
	private:
	public:

		TString outputName;
		TString cutName;
		TString fitName;
		TF1 *fit;
		TH2D *hDEE;

		ExtractDE(TChain *t,int s,int b){
			tree = t;
			side = s;
			barNo = b;

			fit = new TF1(fitName,"pol3",-10,1500);

			nameAll();
			drawBand();
			profileBand();
			outputTXT();
		}
		~ExtractDE(){
			delete fit;
			//gROOT->ProcessLine(".x cut/delete.C");
		}
		void nameAll(){

			DrawDE::nameAll();
			gROOT->ProcessLine(Form(".x cut/Be14_2/side%dBarNo%d.C",side,barNo));
			cutName = Form("side%dBarNo%d",side,barNo);
			condition=cutName;
			fitName = Form("fitSide%dBar%d",side,barNo);
		}

		void drawBand(){
			cDEE = new TCanvas(cName,cName,1600,700);
			cDEE->Divide(2,1);
			cDEE->cd(1);

			//tree->Print();
			tree->Draw(draw,condition,"colz");
			//gROOT->ProcessLine(".x cut/draw.C");

		}
		void profileBand(){


			cDEE->cd(2);
			hDEE = (TH2D *)gDirectory->Get(hName);
			TProfile *hPDEE = hDEE->ProfileX();
			hPDEE->Draw();
			hPDEE->Fit(fit,"R");

			cout<<fit->GetParameter(0)<<"\t"<<fit->GetX(1500,100,800)<<"\t"<<fit->GetParameter(1)<<"\t"<<fit->GetParameter(2)<<"\t"<<"\t"<<fit->GetParameter(3)<<endl;
			

			//hPDEE->SetLineColor(2);
			//hPDEE->Fit("pol3");
		}
		void outputTXT(){

			cDEE->Write();
			outputName=Form("dEERelation.txt");
			ofstream fout(outputName,ios_base::app | ios_base::out);

			fout <<side<<"\t"<<barNo<<"\t"<<fit->GetParameter(0)<<"\t"<<fit->GetParameter(0)<<"\t"<<fit->GetParameter(1)<<"\t"<<fit->GetParameter(2)<<"\t"<<"\t"<<fit->GetParameter(3)<<endl;
			fout.close();
		}
};

class PlasDE{
	private :

	public :
		TChain *tree;
		TFile *outputFile;
		TString outputName;
		TString outputPrefix;
		TString outputSuffix;

		void init(){
			tree = new TChain("CalTreeESPRI");
			outputPrefix = "dEEPlot";
		}
		PlasDE(){
		}
		void createOutputFile(){
			outputName = outputPrefix + outputSuffix;
			cout<<outputName<<endl;
			outputFile = new TFile(outputName,"recreate");
		}
		void loadRun(int run){
			init();
			loadRunChain(run);
			outputSuffix = Form("%d.root",run);
		}
		void loadRun(int runStart,int runStop){
			init();
			loadRunChain(runStart,runStop);
			outputSuffix = Form("%d_%d.root",runStart,runStop);
			cout<<outputPrefix<<":"<<outputSuffix<<endl;
		}
		void test(){
			ExtractDE *extractDE = new ExtractDE(tree,0,1);
		}

		~PlasDE(){delete tree;}
		void loadRunChain(){
			//cout<<"g1"<<endl;
			loadRunChain(360,361);
		}
		void loadRunChain(int run){
			//cout<<"g2"<<endl;
			loadRunChain(run,run+1);
		}
		void loadRunChain(int runStart,int runStop){

			//cout<<"g3"<<endl;
			for(int i = runStart;i<runStop;i++)
			{
				tree->Add(Form("../convert/rootfiles/run0%d_ESPRI.root",i));
			}

			tree->Print();
		}
		void analysingAllBars(){
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					ExtractDE *extractDE = new ExtractDE(tree,side,barNo);

				}
			}
		}
		void drawAllBars(){
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					DrawDE *drawDE = new DrawDE(tree,side,barNo);

				}
			}
		}
		void drawAllBarsWithCut(){
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					ExtractDE *extractDE = new ExtractDE(tree,side,barNo);
					//delete extractDE;
				}
			}
		}
		void drawOneBarsWithCut(int side,int barNo){
			ExtractDE *extractDE = new ExtractDE(tree,side,barNo);

		}



		void write(){
			outputFile->Write();
		}

};
class PlasDECut : public PlasDE {
	private:
	public:
		PlasDECut(){
			//子类默认调用父类的默认构造函数
		}
		void init(){
			tree = new TChain("CalTreeESPRI");
			outputPrefix = "dEEPlotCut";
		}
};
void drawDEEPlotWithCut(){
	PlasDECut *plasGain = new PlasDECut();
	//plasGain->loadRun(334,365);
	plasGain->loadRun(433,455);
	plasGain->createOutputFile();
	plasGain->drawOneBarsWithCut(1,3);
	//plasGain->drawAllBarsWithCut();
	plasGain->write();
}
void drawDEEPlot(){
	//PlasDE *plasGain = new PlasDE(361,365);
	PlasDE *plasGain = new PlasDE();
	//plasGain->loadRun(334,365);
	plasGain->loadRun(334,335);
	plasGain->createOutputFile();
	plasGain->drawAllBars();
	plasGain->write();
}
void drawDEE(){
	//drawDEEPlot();
	drawDEEPlotWithCut();
}
