#include "DCRaw.h"
#include "ReadFile.h"
#include "ShowProcess.h"
class CalibDC{
	private:
		ShowProcess *sp;	
		ReadFile *rf;
		int runStart;
		int runStop;
		TFile *outputFile;
		TString outputName;

		// Head Variables

		DCRaw *bdc1RawData;
		DCRaw *bdc2RawData;
		DCRaw *fdc0RawData;
		DCRaw *fdc2RawData;


		void getOutputName(){
			outputName = Form("rootfiles/run%d_%d_tdcCalib.root",runStart,runStop);
			cout<<"Output File Name:"<<outputName<<endl;
		}
		bool goodGate(){
			//return true;
			return rf->goodGate();
		}
		bool goodBdc1Gate(){
			return rf->goodBdc1Gate();
		}
		bool goodBdc2Gate(){
			return rf->goodBdc2Gate();
		}
		bool goodFdc0Gate(){
			return rf->goodFdc0Gate();
		}

		vector<double> * getBdc1Layer(){
			return rf->getBdc1Layer();
		}
		vector<double> * getBdc1Tdc(){
			return rf->getBdc1Tdc();
		}
		vector<double> * getBdc2Layer(){
			return rf->getBdc2Layer();
		}
		vector<double> * getBdc2Tdc(){
			return rf->getBdc2Tdc();
		}
		vector<double> * getFdc0Layer(){
			return rf->getFdc0Layer();
		}
		vector<double> * getFdc0Tdc(){
			return rf->getFdc0Tdc();
		}








	public:
		CalibDC(){
			sp = new ShowProcess();
			rf = new ReadFile();
			bdc1RawData = new BDC1Raw();
			bdc2RawData = new BDC2Raw();
			fdc0RawData = new FDC0Raw();
			fdc2RawData = new FDC2Raw();
		}
		~CalibDC(){}
		void loadChain(int rSt,int rSp){
			runStart = rSt;
			runStop  = rSp;
			rf->loadChain(runStart,runStop);

		}

		void setOutput(){
			getOutputName();
			outputFile = new TFile(outputName,"recreate");
		}
		void fillHistogram(){
			Long64_t nentries = getTotalEntries();
			//nentries = 100000;
			for (Long64_t i = 0; i < nentries; ++i) {
				sp->showAnalysisProgress((int)i);
				rf->getEntry(i);
				if(goodGate()){
					if(goodBdc1Gate()) bdc1RawData->fillTDC(getBdc1Layer(),getBdc1Tdc());
					if(goodBdc2Gate()) bdc2RawData->fillTDC(getBdc2Layer(),getBdc2Tdc());
					if(goodFdc0Gate()) fdc0RawData->fillTDC(getFdc0Layer(),getFdc0Tdc());
					//rf->print();
				}
			}
		}
		Long64_t getTotalEntries(){
			return rf->getTotalEntries();
		}
		
		void saveRootfile(){
			bdc1RawData->saveHistograms();
			bdc2RawData->saveHistograms();
			fdc0RawData->saveHistograms();
			fdc2RawData->saveHistograms();
		}
};
