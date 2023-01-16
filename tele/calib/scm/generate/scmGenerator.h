#include "header.h"
using namespace std;
#include "ReadFile.h"
#include "Event.h"
class ScmGenerator{
	private:
		TEnv *env;
		ReadFile *rf;
		Event *event;
		int runNumber;
		int maxEventNumber;
		TFile *outputFile;
		TTree *tree;
		Long64_t nentries;
	public:

		ScmGenerator(){}
		ScmGenerator(int runNumber,int maxEventNumber);

		bool isFilesExist();
		void loadInputFiles();
		void createOutput();
		void setOutputBranch();
		void eventLoop();
		void saveOutput();
		void print();

		~ScmGenerator(){
			delete env;
			delete rf;
		}
};
