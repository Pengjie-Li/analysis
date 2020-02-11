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
			int nBin = 400;
			int xMin = 0;
			int xMax = 150;
			int yMin = 0;
			int yMax = 40;

			cName = Form("dEESide%dBar%d",side,barNo);
			hName = Form("hSide%dBar%d",side,barNo);
			draw = Form("plasQ[%d]:naiBarQCal[%d][%d]>>hSide%dBar%d(%d,%d,%d,%d,%d,%d)",side,side,barNo,side,barNo,nBin,xMin,xMax,nBin,yMin,yMax);
			condition="";
		}
		void drawBand(){
			cDEE = new TCanvas(cName,cName,800,700);
			tree->Draw(draw,condition,"colz");
		}
};
class DrawAll:public DrawDE{
	private:
	public:
		DrawAll(TChain *t,int s){
			tree = t;
			side = s;

			nameAll();
			drawBand();
		}
		void nameAll(){
			int nBin = 400;
			int xMin = 0;
			int xMax = 150;
			int yMin = 0;
			int yMax = 40;

			cName = Form("dEESide%d",side);
			hName = Form("hSide%d",side);
			draw = Form("plasQ[%d]:naiQ[%d]>>hSide%d(%d,%d,%d,%d,%d,%d)",side,side,side,nBin,xMin,xMax,nBin,yMin,yMax);
			if(side ==0 ){
				gROOT->ProcessLine(".x cut/leftPlastic.C");
				condition="leftPlastic";
			}else {
				gROOT->ProcessLine(".x cut/rightPlastic.C");
				condition="rightPlastic";
			}
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
		void draw(){

			for(int side = 0;side<2;side++){
				DrawAll *drawAll =new DrawAll(tree,side);
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

class FitDEERelation{
	private:
		TFile *inputFile;
		
	public:
		FitDEERelation(TString fileName){
			inputFile = new TFile(fileName,"READ");
		}
		void checkDraw(){
			TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
			cPad->Divide(7,2);
			TH2F* hDEE[2][7];
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					cPad->cd(7*side+barNo+1);
					TString hName = Form("hSide%dBar%d",side,barNo);
					hDEE[side][barNo] = (TH2F *)gDirectory->Get(hName);
					hDEE[side][barNo]->Draw();
				}
			}
		}
		~FitDEERelation(){}
};
void fitDEEPlot(){
	TString inputName = "dEEPlot298_330.root";
	FitDEERelation *fitDee = new FitDEERelation(inputName);
	fitDee->checkDraw();
}
void fitDEE(){
	fitDEEPlot();
}
