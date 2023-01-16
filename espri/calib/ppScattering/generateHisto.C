
class GenerateHisto{
	private:
		TFile *inputFile;
		TFile *outputFile;
		TTree *tree;
		TCanvas *cPlas;
		TCanvas *cNai;
		void loadCut(){
			//gROOT->ProcessLine(".x rootfiles/cutPPETBe10.C");
			//gROOT->ProcessLine(".x rootfiles/cutLeftPlas.C");
			//gROOT->ProcessLine(".x rootfiles/cutRightPlas.C");
		}
		void loadCut(TString line){
			gROOT->ProcessLine(line);
		}
	public:
		GenerateHisto(){
			loadCut();
		}
		~GenerateHisto(){}
		void openInputFile(TString inputName){
			inputFile = new TFile(inputName,"READ");
			tree = (TTree*)gDirectory->Get("tree");
			//tree->Print();
		}
	

		void generatePlas(){
			cPlas = new TCanvas("cPlas","cPlas",1200,800);
			cPlas->Divide(2,1);
			TString cutPlas;
			for (int i = 0; i < 2; ++i) {
				cPlas->cd(i+1);
				if(i==0) cutPlas = "LeftPlas";
				else cutPlas = "RightPlas";
				//cutPlas = "1>0";
				tree->Draw(Form("sqrt(plasQPed[%d]*plasQPed[%d]):protonTheta>>hPed%d(100,60,73,100,200,4000)",2*i,2*i+1,i),"ppET&&"+cutPlas,"colz");
				gPad->Modified();
				gPad->Update();

			}
		}


		void generateNai(){
			cNai = new TCanvas("cNai","cNai",1200,800);
			cNai->Divide(4,4);
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {

					cNai->cd(i*8+j+1);
					tree->Draw(Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d]):protonTheta>>hPed%d_%d(100,40,80,100,200,4000)",2*i,j,2*i+1,j,i,j),"ppET","colz");
					gPad->Modified();
					gPad->Update();

				}
			}

		}
		void createRootFile(TString fileName){
			outputFile = new TFile(fileName,"recreate");		
		}
		void saveToRootFile(){
			outputFile->Write();
			outputFile->Close();
		}
};
void generateHisto(){
	int runNumber = 340;
	GenerateHisto *gh = new GenerateHisto();
	gh->loadCut(".x rootfiles/cutPPETBe12.C");
	gh->loadCut(".x rootfiles/cutLeftPlasBe12.C");
	gh->loadCut(".x rootfiles/cutRightPlasBe12.C");
	//gh->loadCut(".x rootfiles/cutPPETBe10.C");
	gh->openInputFile(Form("rootfiles/run0%d_analysed.root",runNumber));
	//gh->createRootFile("calibHisto.root");
	gh->createRootFile("calibHistoBe12.root");
	gh->generatePlas();
	gh->generateNai();
	gh->saveToRootFile();
}
