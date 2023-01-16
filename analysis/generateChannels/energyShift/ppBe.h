#include "header.h"
using namespace std;
#include "ReadFile.h"
#include "Event.h"
#include "EnergyShift.h"
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
		EnergyShift *es;
	public:

		PPBe(){}
		PPBe(int runNumber,int maxEventNumber);

		bool isFilesExist();
		void loadInputFiles();
		void createOutput();
		void setOutputBranch();
		void eventLoop();
		void saveOutput();
		void print();
		void addEnergyShift();

		~PPBe(){
			delete env;
			delete rf;
		}
};
