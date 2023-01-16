#include "header.h"
using namespace std;
#include "ReadFile.h"
#include "Event.h"
class PPBe{
	private:
		TEnv *env;
		ReadFile *rf;
		Event *event;
		int runStart;
		int runStop;
		int maxEventNumber;
		TFile *outputFile;
		TTree *tree;
		Long64_t nentries;
	public:

	
		PPBe(){}

		void loadChain(int rSt,int rSp);
		bool isFilesExist();
		void loadInputFiles();
		void createOutput();
		void setOutputBranch();
		void eventLoop();
		void saveOutput();
		void print();

		~PPBe(){
			delete env;
			delete rf;
		}
};
