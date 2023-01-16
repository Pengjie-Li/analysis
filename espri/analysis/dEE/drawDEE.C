class PlasDE{
	private :

	public :
		TChain *tree;
		TFile *outputFile;
		TString outputName;
		TString outputPrefix;
		TString outputSuffix;
		TString gate;

		void init(){
			tree = new TChain("tree");
			outputPrefix = "dEEPlot";
		}
		PlasDE(){
			gate = "";
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
		void loadGate(TString g){
			gate = g;
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
				tree->Add(Form("../../../merger/rootfiles/run0%d_analysed.root",i));
			}

			tree->Print();
		}
		void draw(int side,int barNo){
			if(side == -1&&barNo == -1) drawAllBars();
			drawOneBar(side,barNo);
		}
		void drawAllBars(){
			for(int side = 0;side<2;side++){
				for(int barNo = 0;barNo<7;barNo++){
					drawOneBar(side,barNo);

				}
			}
		}
		void drawOneBar(int side, int barNo){

			int nBin = 400;
			int xMin = 0;
			int xMax = 150;
			int yMin = 0;
			int yMax = 40;

			TString cName = Form("dEESide%dBar%d",side,barNo);
			TString hName = Form("hSide%dBar%d",side,barNo);
			TString draw = Form("plasQ[%d]:naiBarQCal[%d][%d]>>hSide%dBar%d(%d,%d,%d,%d,%d,%d)",side,side,barNo,side,barNo,nBin,xMin,xMax,nBin,yMin,yMax);

			TCanvas *cDEE = new TCanvas(cName,cName,800,700);
			tree->Draw(draw,gate,"colz");
		}

		void write(){
			outputFile->Write();
		}

};

void drawDEEPlot(int runStart = 360, int runStop = 361, int side = -1, int barNo = -1, TString gate = ""){
	//PlasDE *plasGain = new PlasDE(361,365);
	PlasDE *plasGain = new PlasDE();
	plasGain->loadRun(runStart,runStop);
	//plasGain->loadRun(360);
	plasGain->createOutputFile();
	plasGain->loadGate(gate);
	plasGain->draw(side,barNo);
	plasGain->write();
}
void drawDEE(){
	int runStart = 430;
	int runStop = 440;
	
	int side = 0;
	int barNo = 1;

	TString targetArea = "sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
	TString trigDSB = "Trig_DSB";
	TString trigBxESPRI = "Trig_BxESPRI";
	gROOT->ProcessLine(".x ../../../merger/rootfiles/cutHodBe14.C");
	TString hodBe14 = "HodBe14"; 
	TString gate = trigBxESPRI + "&&" + targetArea;

	drawDEEPlot(runStart,runStop,side,barNo,gate);
	//drawDEEPlot(runStart,runStop,,,gate); // Draw all bar
	//drawDEEPlotWithCut();
}
