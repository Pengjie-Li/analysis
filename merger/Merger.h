#include "header.h"
#include "Convert.h"
#include "MergeMAIN.h"
#include "MergePLA.h"
#include "MergeBDC.h"
#include "MergeFDC0.h"
#include "MergeTELE.h"
#include "MergeHOD.h"
#include "MergeESPRI.h"


#include "EspriEvent.h"
#include "TeleEvent.h"

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

		Double_t TOF713;
		Double_t Beta713;
		Double_t Gamma713;
		Double_t Ek713;

		Double_t TOF37;
		Double_t Beta37;
		Double_t Gamma37;
		Double_t Ek37;


		TVector3* vBeam;	
		TVector3* vBDC1;	
		TVector3* vBDC2;	
		TVector3* vTarget;	
		TVector3* vSBT;	
		TVector3* vESPRI;	
		TVector3* vDSSD;	
		TVector3* vProton;

		Double_t	Target_X ;
		Double_t	Target_Y ;
		Double_t	Target_ThetaX ;
		Double_t	Target_ThetaY ;
		Double_t 	flightLengthBeamTarget;
		Double_t 	flightLengthTargetESPRI;

		

		// Silicon Parameters

		Int_t	multiplicity[4];	

		
		Double_t CsILL_CAL ;
		Double_t CsILRT_CAL;
		Double_t CsILRB_CAL;

		Double_t CsIRLT_CAL;
		Double_t CsIRLB_CAL;
		Double_t CsIRRT_CAL;
		Double_t CsIRRB_CAL;


		double espriNaiEnergy;
		double espriPlasTime;
		double espriPlasDeltaE;
		double protonTheta;



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

		Merger(int runNumber);

		void eventLoop();
		void getEntry(Long64_t ientry);

		void analysingMAIN();
		void initAnalysedMAIN();
		Int_t getCoincidenceTrigger();

		void analysingPLA();
		void initAnalysedPLA();
		Double_t getF3Time();
		Double_t getF7Time();
		Double_t getF13Time();

		void analysingBDC();
		void initAnalysedBDC();
		Double_t getBDC1TargetRatio();
		Double_t getBDC1SBTRatio();
		Double_t getBDC1X();
		Double_t getBDC1Y();
		Double_t getBDC1Z();
		Double_t getBDC2X();
		Double_t getBDC2Y();
		Double_t getBDC2Z();


		void analysingFDC0();
		void analysingTELE();
		TeleEvent *teleEvent;
		void  getMultiplicity();
		Int_t getMultiplicity(int side);
		void printMultiplicity();


		void analysingHOD();

		void analysingESPRI();
		EspriEvent *espriEvent;
		void initAnalysedESPRI();
		void setESPRIEvent();
		TVector3 getESPRIPosition();
		double getESPRINaiEnergy();
		double getESPRIPlasTime();
		double getESPRIPlasDeltaE();
		void setProtonAngle();


		void createOutput();
		void setOutputBranch();
		void setMAINOutputBranch();
		void setPLAOutputBranch();
		void setBDCOutputBranch();
		void setFDC0OutputBranch();
		void setTELEOutputBranch();
		void setHODOutputBranch();
		void setESPRIOutputBranch();
		void saveOutput();

		void addFriend();
		void setBranch();
		void loadInputFiles();

		void checkTotalEventNumber();
		void printTotalEventNumber();
		bool isFilesExist();
};
