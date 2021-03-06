#include "header.h"
using namespace std;
#include "ReadFile.h"
#include "Event.h"
#include "AlphaEvent.h"
#include "EspriEvent.h"
#include "ProtonEvent.h"
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

		AlphaEvent *alphaEvent;
		ProtonEvent *protonEvent;
		EspriEvent *espriEvent;
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
		void setAlphaEvent();
		void setProtonEvent();
		void setEspriEvent();

		~PPBe(){
			delete env;
			delete rf;
		}
};
