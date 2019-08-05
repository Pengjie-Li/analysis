class DrawDE{
	private:
	public:
		int side;
		int barNo;
		TChain *tree;


		TString cName;
		TString hName;
		TString drawName;
		TString drawVar;
		TString drawRange;

		TString gate;
		TString targetArea;

		int nBin; 
		int xMin; 
		int xMax; 
		int yMin; 
		int yMax; 


		DrawDE(){}
		~DrawDE(){
		}
		DrawDE(TChain *t,int s,int b){
			tree = t;
			side = s;
			barNo = b;
		}
		DrawDE(TChain *t){
			tree = t;
			gate="1>0";
		}
		void loadTargetCut(){
			targetArea = "sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
			gate = gate+"&&"+targetArea;
		}
		void draw(){
			drawName = drawVar+hName+drawRange;
			cout<<"drawOption = "<<drawName<<endl;
			tree->Draw(drawName,gate,"colz");
		}
		void setHistoName(TString name){
			hName = name;
		}
		void setDrawVar(TString var1,TString var2){
			drawVar = var1 +":"+var2+">>";
		}
		void setRange(int par1,int par2,int par3,int par4,int par5){
			nBin = par1;
			xMin = par2;
			xMax = par3;
			yMin = par4;
			yMax = par5;
			drawRange = Form("(%d,%d,%d,%d,%d,%d)",nBin,xMin,xMax,nBin,yMin,yMax);

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
			tree = new TChain("tree");
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
			//ExtractDE *extractDE = new ExtractDE(tree,0,1);
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
				tree->Add(Form("./rootfiles/run0%d_analysed.root_1",i));
			}

			tree->Print();
		}
		void draw(){
			TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
			cPad->Divide(2,1);
			DrawDE *drawDE = new DrawDE(tree);
			drawDE->loadTargetCut();
			drawDE->setRange(500,0,200,0,4000);

			cPad->cd(1);
			drawDE->setHistoName("hLeft");
			drawDE->setDrawVar("sqrt(plasQPed[0]*plasQPed[1])","naiQ[0]");
			drawDE->draw();
			cPad->cd(2);
			drawDE->setHistoName("hRight");
			drawDE->setDrawVar("sqrt(plasQPed[2]*plasQPed[3])","naiQ[1]");
			drawDE->draw();

		}
		void drawAllBars(){
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					//DrawDE *drawDE = new DrawDE(tree,side,barNo);

				}
			}
		}
		void drawAllBarsWithCut(){
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					//ExtractDE *extractDE = new ExtractDE(tree,side,barNo);
					//delete extractDE;
				}
			}
		}


		void write(){
			outputFile->Write();
		}

};
void drawDEEPlot(){
	PlasDE *plasGain = new PlasDE();
	//plasGain->loadRun(300,325);
	plasGain->loadRun(310);
	plasGain->createOutputFile();
	//plasGain->loadCut();
	plasGain->draw();
	//plasGain->drawAllBars();
	//plasGain->drawOneBarsWithCut(1,3);
	plasGain->write();
}
void drawDEE(){
	drawDEEPlot();
	//drawDEEPlotWithCut();
}
