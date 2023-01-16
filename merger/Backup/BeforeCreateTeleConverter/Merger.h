#include "header.h"
#include "Convert.h"
#include "MergeMAIN.h"
#include "MergePLA.h"
#include "MergeBDC.h"
#include "MergeFDC0.h"
#include "MergeTELE.h"
#include "MergeHOD.h"

class Merger{
	private: 
		const static bool kMAIN = true;
		const static bool kPLA = true;
		const static bool kBDC = true;
		const static bool kFDC0 = true;
		const static bool kTELE = true;
		const static bool kHOD = true;
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

		Double_t	Target_X ;
		Double_t	Target_Y ;
		Double_t	Target_ThetaX ;
		Double_t	Target_ThetaY ;


		// Silicon Parameters
		double siliconHitThreshold;

		Double_t kScmSlope[4][32];
		Double_t bScmOffset[4][32];
		Double_t ekScmSlope[4][32];
		Double_t ebScmOffset[4][32];

		Double_t kCalSlope[2];
		Double_t bCalOffset[2];

	
		Double_t SiLF_ADC[32];
		Double_t SiLB_ADC[32];
		Double_t SiRF_ADC[32];
		Double_t SiRB_ADC[32];

		Double_t SiLF_SCM[32];
		Double_t SiLB_SCM[32];
		Double_t SiRF_SCM[32];
		Double_t SiRB_SCM[32];

		Double_t SiLF_CAL[32];
		Double_t SiLB_CAL[32];
		Double_t SiRF_CAL[32];
		Double_t SiRB_CAL[32];

		Int_t	multiplicityLF;	
		Int_t	multiplicityLB;	
		Int_t	multiplicityRF;	
		Int_t	multiplicityRB;	

		
		Double_t CsILL_CAL ;
		Double_t CsILRT_CAL;
		Double_t CsILRB_CAL;

		Double_t CsIRLT_CAL;
		Double_t CsIRLB_CAL;
		Double_t CsIRRT_CAL;
		Double_t CsIRRB_CAL;



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

		Merger(int runNumber);

		void eventLoop();
		void initAnalysedOutput();
		void analysingMAIN();
		Int_t getCoincidenceTrigger();

		void analysingPLA();
		Double_t getF3Time();
		Double_t getF7Time();
		Double_t getF13Time();

		void analysingBDC();
		Double_t getBDC1TargetRatio();
		Double_t getBDC1X();
		Double_t getBDC1Y();
		Double_t getBDC1Z();
		Double_t getBDC2X();
		Double_t getBDC2Y();
		Double_t getBDC2Z();


		void analysingFDC0();
		void analysingTELE();
		void calibrateSilicon();
		void  getMultiplicity();
		Int_t getMultiplicity(double *array);
		void printMultiplicity();
		void calibrateSiliconStrip();
		void calibrateSiliconStrip(int side,int id);
		double getSiliconRawADC(int side,int id);
		double getSiliconScmSlope(int side,int id);
		double getSiliconScmOffset(int side,int id);
		double getSiliconCalSlope(int side);
		double getSiliconCalOffset(int side);
		void setCalibratedSiliconStrip(int side,int id,double raw,double scm,double cal);
		void printSilicon();

		void calibrateCsI();
		Double_t getCsILLRawADC();
		Double_t getCsILRTRawADC();
		Double_t getCsILRBRawADC();
		Double_t getCsIRLTRawADC();
		Double_t getCsIRLBRawADC();
		Double_t getCsIRRTRawADC();
		Double_t getCsIRRBRawADC();	
		void printCsI();

		void analysingHOD();

		void createOutput();
		void setOutputBranch();
		void setMAINOutputBranch();
		void setPLAOutputBranch();
		void setBDCOutputBranch();
		void setFDC0OutputBranch();
		void setTELEOutputBranch();
		void setHODOutputBranch();
		void saveOutput();

		void addFriend();
		void setBranch();
		void loadInputFiles();
		void loadSiliconCalibrationParameters();
		void loadSiliconCalibrationParameters(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32]);

		void checkTotalEventNumber();
		void printTotalEventNumber();
		bool isFilesExist();
};


