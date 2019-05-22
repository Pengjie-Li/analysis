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

			if(side == 0){
				cName = Form("dEELeftBar%d",barNo);
				hName = Form("hLeft%d",barNo);
				draw = Form("plasQL:naiQ[%d][%d]>>hLeft%d(1000,-100,3900,1000,0,4000)",side,barNo,barNo);
			}else{
				cName = Form("dEERightBar%d",barNo);
				hName = Form("hRight%d",barNo);
				draw = Form("plasQR:naiQ[%d][%d]>>hRight%d(1000,-100,3900,1000,0,4000)",side,barNo,barNo);
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

		ExtractDE(TChain *t,int s,int b){
			tree = t;
			side = s;
			barNo = b;

			fit = new TF1(fitName,"pol3",-10,1500);

			nameAll();
			drawBand();
			profileBand();
			//fitBand();
			outputTXT();
		}
		~ExtractDE(){
			delete fit;
			gROOT->ProcessLine(".x cut/delete.C");
		}
		void nameAll(){

			DrawDE::nameAll();
			gROOT->ProcessLine(Form(".x cut/side%dBarNo%d.C",side,barNo));
			cutName = Form("side%dBarNo%d",side,barNo);
			condition=cutName;
			fitName = Form("fitSide%dBar%d",side,barNo);
		}

		void drawBand(){
			cDEE = new TCanvas(cName,cName,1600,700);
			cDEE->Divide(2,1);
			cDEE->cd(1);

			tree->Draw(draw,condition,"colz");

			gROOT->ProcessLine(".x cut/draw.C");

		}
		void profileBand(){


			cDEE->cd(2);
			TH2D *hDEE = (TH2D *)gDirectory->Get(hName);
			TProfile *hPDEE = hDEE->ProfileX();
			hPDEE->Draw();
			hPDEE->Fit(fit,"R");

			cout<<fit->GetParameter(0)<<"\t"<<fit->GetX(1500,100,800)<<"\t"<<fit->GetParameter(1)<<"\t"<<fit->GetParameter(2)<<"\t"<<"\t"<<fit->GetParameter(3)<<endl;
			

			//hPDEE->SetLineColor(2);
			//hPDEE->Fit("pol3");
		}
		void outputTXT(){

			cDEE->Write();
			outputName=Form("PlasticMaximumDE.txt");
			ofstream fout(outputName,ios_base::app | ios_base::out);

			fout <<side<<"\t"<<barNo<<"\t"<<fit->GetParameter(0)<<"\t"<<fit->GetX(1500,100,800)<<"\t"<<fit->GetParameter(1)<<"\t"<<fit->GetParameter(2)<<"\t"<<"\t"<<fit->GetParameter(3)<<endl;
			fout.close();
		}
};

class PlasDE{
	private :
		TChain *tree;

		TFile *outputFile;
	public :
		PlasDE(){
			tree = new TChain("CalTreeESPRI");

			loadRunChain();

			//outputFile = new TFile("dEEPlot.root","recreate");
			outputFile = new TFile("dEEPlotWithCut.root","recreate");
			//test();
			//analysingAllBars();
			//drawDEE(tree,0,1);
			//profile(tree,0,1);
		}
		void test(){
			ExtractDE *extractDE = new ExtractDE(tree,0,1);
		}

		~PlasDE(){delete tree;}
		void loadRunChain(){

			//for(int i = 390;i<430;i++)
			//for(int i = 354;i<365;i++)
			//for(int i = 360;i<361;i++)
			for(int i = 360;i<455;i++)
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
					delete extractDE;
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
void drawDEEPlotWithCut(){
	PlasDE *plasGain = new PlasDE();
	plasGain->drawOneBarsWithCut(0,2);
	//plasGain->drawAllBarsWithCut();
	plasGain->write();
}
void drawDEEPlot(){
	PlasDE *plasGain = new PlasDE();
	plasGain->drawAllBars();
	plasGain->write();
}
void drawDEE(){
	drawDEEPlot();
	//drawDEEPlotWithCut();
}
