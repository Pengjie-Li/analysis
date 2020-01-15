class FitTGraph{
	private:
		TFile *inputFile;
		TGraph *gr;
		int refId;
		int side;
		int stripId;
		TF1 *fitFunction;


	public:
		FitTGraph(){
			fitFunction = new TF1("fitFunction","pol1",0,4000);
			fitFunction->SetParameter(0,0);
			fitFunction->SetParameter(1,1);
		}
		void addFile(TString fileName){
			inputFile = new TFile(fileName,"READ");
		}
		void setMarkerStyle(int color,double size,int style){
			gr->SetMarkerColor(color);
			gr->SetMarkerSize(size);
			gr->SetMarkerStyle(style);
		}
		void getTGraph(int s, int ref,int b){
			side = s; stripId = b;
			refId = ref;
			gr = (TGraph*)gDirectory->Get(Form("Side%d_Ref%d_strip%d",side,refId,stripId));
		}
		void draw(){
			gr->Draw("Ap");
		}
		void fit(){
			gr->Fit(fitFunction);
		}
		void output(){
                        TString outputName = "./txt/dssdScmParaRaw.txt";
                        ofstream fout(outputName,ios_base::app | ios_base::out);
			fout<<side<<"\t"<<stripId<<"\t"<<refId<<"\t"<<fitFunction->GetParameter(0)<<"\t"<<fitFunction->GetParameter(1)<<endl;
			fout.close();

		}
		void close(){
			inputFile->Close();
		}
		void write(){
			gr->Write();
			fitFunction->Write();
		}

		~FitTGraph(){
			delete tree;
		}
};

void fitStrip(int side,int refId,int stripId){

	FitTGraph *ce = new FitTGraph();
	ce->addFile("../graph/rootfiles/run0700_graph.root");
	ce->getTGraph(side,refId,stripId);
	ce->setMarkerStyle(1,3,3);
	ce->close();

	TString fileName = "fitPad.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");

	TCanvas *cPad = new TCanvas("cPad","cPad",1400,1000);
	ce->draw();
	ce->fit();
	ce->output();
	ce->write();	
	outputFile->Close();
}

void fitTGraph(){
	//int side = 3;	
	//int stripId = 6;	
	//int refId = 15;	
	//fitStrip(side,refId,stripId);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j <32; ++j) {
			fitStrip(i,15,j);
		}
	}
}
