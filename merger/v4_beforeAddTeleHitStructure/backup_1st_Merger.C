#include "header.h"
TEnv *env = new TEnv("configMerger.prm");
#include "Convert.h"
#include "MergePLA.h"

class Merger{
	private: const static bool kPLA = true;
	public :
		int runNumber;
		TTree *inputTree;

		TFile *outputFile;
		TTree *tree;
		Long64_t nentries;

		MergePLA *mergePla;
		Merger(int runNumber):runNumber(runNumber){
			inputTree = new TTree("tree","tree");
			if(kPLA) mergePla =new MergePLA(runNumber);
		}
		void eventLoop(){
			nentries = 5000;
			cout << "NUMBER OF EVENTS = " << nentries << endl;
		}
		void createOutput(){

			outputFile = new TFile(Form("./rootfiles/run%04d_analysed.root",runNumber), "recreate"); 
			tree = new TTree("tree","Analysed Tree:raw,cal,analysed");
			setOutputBranch();
		}
		void setOutputBranch(){
		}
		void addFriend(){
			if(kPLA){
				 inputTree->AddFriend(mergePla->inputTree);
				 //mergePla->inputTree->Print();
				}
		}

		void setBranch(){
			if(kPLA) mergePla->setBranch();
		}
		void loadInputFiles(){
			if(kPLA) mergePla->loadInputFiles();
		}
		void checkTotalEventNumber(){
			printTotalEventNumber();
		}
		void printTotalEventNumber(){
			if(kPLA) mergePla->printTotalEventNumber();
		}

		bool isFilesExist(){
			return mergePla->isFileExists();
			//return mergePla->isFileExists()&&isFileExists("BDC")&&isFileExists("FDC")&&isFileExists("TELE");
		}

};


