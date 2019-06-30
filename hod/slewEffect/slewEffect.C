class DrawSlewEffect{
	private:
	public:
		int runStart;
		int runStop;
		TChain *tree;

		TString draw;
		TString gate;
		TString color;

		TFile *outputFile;
		DrawSlewEffect(int start,int stop):runStart(start),runStop(stop){
			gate = "";
			execute();
		}
		DrawSlewEffect(int start,int stop,TString gate):runStart(start),runStop(stop),gate(gate){
			execute();
		}

		void execute(){
			TString outputName = Form("run%d_%dSlewEffect.root",runStart,runStop);
			tree = new TChain("CalTreeHOD");
			loadRunChain(runStart,runStop);
			outputFile = new TFile(outputName,"recreate");
			drawSlewEffect();
			saveIntoRoot();
		}


		void loadRunChain(int runStart,int runStop){

			//cout<<"g3"<<endl;
			for(int i = runStart;i<runStop;i++)
			{
				tree->Add(Form("../convert/rootfiles/run0%d_HOD.root",i));
			}

			tree->Print();
		}
		void drawSlewEffect(){
			int xBin = 500;
			int yBin = 500;
			int xMin = 17500;
			int xMax = 20000;
			int yMin = 0;
			int yMax = 4000;
			draw = "hodTRaw[0][10]:hodQCal[0][10]>>hSlew0_10(1000,0,4000,1000,17500,20000)";
			color = "colz";
			tree->Draw(draw,gate,color);
		}
		void saveIntoRoot(){
			TH2F *h2D = (TH2F *)gDirectory->Get("hSlew0_10")->Clone("h2D");
			h2D->Write();
			outputFile->Close();
		}

};


void slewEffect(){
	//drawSlewEffect();
	//fitSlewEffect();
	//correctSlewEffect();
	//combineFiles();
}
void drawSlewEffect(){
	//int runStart = 334;
	//int runStop = 365;

	//int runStart = 360;
	//int runStop = 371;
	//
	int runStart = 366;
	int runStop = 450;

	DrawSlewEffect *draw = new DrawSlewEffect(runStart,runStop);
}
class FitSlewEffect{
	private:
	public:
	TFile *inputFile;
	FitSlewEffect(TString inputName){
		inputFile = new TFile(inputName,"READ");
		TH2F *h = (TH2F *)inputFile->Get("h2D");
		h->Draw("[CUTG]");
		TProfile *hPf =h->ProfileX("hPf",700,1000,"[cutg]");
		hPf->Draw("same");
	}
};
void fitSlewEffect(){
	TString inputName = "run366_450SlewEffect.root";	
	TString cutName = "Be14Cut1.C";
	TString lineCut = ".x " + cutName;
	gROOT->ProcessLine(lineCut);
	FitSlewEffect *fit = new FitSlewEffect(inputName);
}
void combineFiles(){
	TString inputName3 = "run366_450SlewEffect.root";	
	TString inputName2 = "run334_365SlewEffect.root";	
	TString inputName1 = "run298_330SlewEffect.root";	

	TFile *f1 = new TFile(inputName1,"READ");
	TH2F *h1 = (TH2F *)f1->Get("h2D")->Clone("h1");
	TFile *f2 = new TFile(inputName2,"READ");
	TH2F *h2 = (TH2F *)f1->Get("h2D")->Clone("h2");
	TFile *f3 = new TFile(inputName3,"READ");
	TH2F *h3 = (TH2F *)f1->Get("h2D")->Clone("h3");

	TList *list = new TList();
	list->Add(h1);
	list->Add(h2);
	list->Add(h3);
	TH2F *hAll = (TH2F *)h1->Clone("hAll");
	hAll->Reset();
	hAll->Merge(list);
	hAll->Draw();
}
