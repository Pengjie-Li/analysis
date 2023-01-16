#include "header.h"
using namespace std;
#include "ReadFile.h"
#include "Event.h"
#include "He3Event.h"
class PPBe{
	private:
		TEnv *env;
		ReadFile *rf;
		Event *event;
		int runNumber;
		int maxEventNumber;
		TFile *outputFile;
		TTree *tree;
		Long64_t nentries;

		He3Event *he3Event;
	public:

		PPBe(){}
		PPBe(int runNumber,int maxEventNumber);

		bool isFilesExist();
		void loadInputFiles();
		void createOutput();
		void setOutputBranch();

		void eventLoop();
		void setHe3Event();

	
		void saveOutput();
		void print();

		~PPBe(){
			delete env;
			delete rf;
		}
};
