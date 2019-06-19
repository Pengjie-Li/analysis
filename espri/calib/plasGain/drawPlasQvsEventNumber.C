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
		DrawDE(TChain *t,int s){
			tree = t;
			side = s;

			nameAll();
			drawBand();
		}
		void nameAll(){

			int nBinx = 1000;
			int nBiny = 1000;
			int xMax = 1400E6;
			int xMin = 850E6;
			int yMax = 4100;
			int yMin = 100;
			
			if(side == 0){
				cName = Form("Plas Q vs Event Number Left");
				hName = Form("hLeft");
				draw = Form("plasQL:(EventNumber+RunNumber*3E6)>>hLeft(%d,%d,%d,%d,%d,%d)",nBinx,xMin,xMax,nBiny,yMin,yMax);
			}else{
				cName = Form("Plas Q vs Event Number Right");
				hName = Form("hRight");
				draw = Form("plasQR:(EventNumber+RunNumber*3E6)>>hRight(%d,%d,%d,%d,%d,%d)",nBinx,xMin,xMax,nBiny,yMin,yMax);
			}

			condition="";
		}
		void drawBand(){
			cDEE = new TCanvas(cName,cName,800,700);
			gPad->SetLogz();
			tree->Draw(draw,condition,"colz");
		}
};
class ESPRIChain{
	private :
		TChain *tree;

		TFile *outputFile;
	public :
		ESPRIChain(){
			tree = new TChain("CalTreeESPRI");

			loadRunChain();

			//outputFile = new TFile("dEEPlot.root","recreate");
			outputFile = new TFile("dEEPlotWithCut.root","recreate");
			//test();
			//analysingAllBars();
			//drawDEE(tree,0,1);
			//profile(tree,0,1);
		}
		~ESPRIChain(){delete tree;}
		void loadRunChain(){

			//for(int i = 390;i<430;i++)
			//for(int i = 354;i<365;i++)
			//for(int i = 360;i<361;i++)
			for(int i = 298;i<455;i++)
			{
				tree->Add(Form("../convert/rootfiles/run0%d_ESPRI.root",i));
			}
			tree->Print();
		}
		void drawPlasQvsEventNumber(){
			for(int side = 0;side<2;side++){
				DrawDE *drawDE = new DrawDE(tree,side);

			}
		}
		void write(){
			outputFile->Write();
		}

};
void drawPlasQvsEventNumber(){
	ESPRIChain *espriChain = new ESPRIChain();
	espriChain->drawPlasQvsEventNumber();
	espriChain->write();
}
