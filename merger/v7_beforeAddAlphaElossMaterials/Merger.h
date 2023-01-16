#include "header.h"

extern TEnv *calib;
extern TEnv *env;

#include "Convert.h"
#include "MergeMAIN.h"
#include "MergePLA.h"
#include "MergeBDC.h"
#include "MergeFDC0.h"
#include "MergeTELE.h"
#include "MergeHOD.h"
#include "MergeESPRI.h"

#include "PlaEvent.h"
#include "EspriEvent.h"
#include "Fdc0Event.h"
#include "BdcEvent.h"
#include "TeleEvent.h"
#include "BeamEvent.h"
#include "ProtonEvent.h"
#include "AlphaEvent.h"


class Merger{
	private: 
		const static bool kMAIN = true;
		const static bool kPLA = true;
		const static bool kBDC = true;
		const static bool kFDC0 = true;
		const static bool kTELE = true;
		const static bool kHOD = true;
		const static bool kESPRI = true;
	public :

		Int_t Trig_DSB;
		Int_t Trig_BxESPRIxTEL;
		Int_t Trig_BxESPRI;
		Int_t Trig_BxTEL;
		Int_t Trig_BxHODP;
		Int_t Trig_BxHODF;
		Int_t Trig_BxNEBULA;

		TVector3* vESPRI;	
		TVector3* vDSSD;	
		TVector3* vProton;




		TEnv *env;
		int runNumber;
		int maxEventNumber;
		TTree *inputTree;

		TFile *outputFile;
		TTree *tree;
		Long64_t nentries;

		MergeMAIN *mergeMAIN;
		MergePLA *mergePLA;
		MergeBDC *mergeBDC;
		MergeFDC0 *mergeFDC0;
		MergeTELE *mergeTELE;
		MergeHOD  *mergeHOD;
		MergeESPRI  *mergeESPRI;

		Merger(int runNumber,int maxEventNumber);

		void print();
		void eventLoop();
		void getEntry(Long64_t ientry);

		void analysingMAIN();
		void initAnalysedMAIN();
		Int_t getCoincidenceTrigger();
		void setMAINOutputBranch();

		void analysingPLA();
		PlaEvent *plaEvent;
		void initAnalysedPLA();
		void printPLA();
		void setPLAOutputBranch();
	
		BdcEvent *bdcEvent;
		void analysingBDC();
		void printBDC();
		void setBDCOutputBranch();

		Fdc0Event *fdc0Event;
		void analysingFDC0();
		void printFDC0();
		void setFDC0OutputBranch();

		void analysingTELE();
		TeleEvent *teleEvent;
		void setTELEOutputBranch();
		void printTELE();


		void analysingHOD();
		void setHODOutputBranch();

		void analysingESPRI();
		EspriEvent *espriEvent;
		void printESPRI();
		void setESPRIOutputBranch();


		BeamEvent 	*beamEvent;
		void printBeam();
		void setBeamEvent();
		void setBeamOutputBranch();

		ProtonEvent 	*protonEvent;
		void printProton();
		void setProtonEvent();
		void setProtonOutputBranch();

		AlphaEvent 	*alphaEvent;
		void printAlpha();
		void setAlphaEvent();
		void setAlphaOutputBranch();


		void createOutput();
		void setOutputBranch();
		void saveOutput();
		void setBranch();
		void loadInputFiles();

		void checkTotalEventNumber();
		void printTotalEventNumber();
		bool isFilesExist();
};
