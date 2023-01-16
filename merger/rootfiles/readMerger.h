#include "header.h"
#include "TVector3.h"
#include "TFile.h"
#include "TTree.h"
#include "FindPixel.h"
class ReadMerger{

	public :


		int runNumber;
		FindPixel *findPixel;
		//Declaration of leaves types
		Int_t           RunNumber;
		Long64_t        EventNumber;
		Int_t           CoincidenceTrigger;
		Int_t           Trig_DSB;
		Int_t           Trig_BxESPRIxTEL;
		Int_t           Trig_BxESPRI;
		Int_t           Trig_BxTEL;
		Int_t           Trig_BxHODP;
		Int_t           Trig_BxHODF;
		Int_t           Trig_BxNEBULA;
		Double_t        F3_LTRaw;
		Double_t        F3_RTRaw;
		Double_t        F3_LTSlew;
		Double_t        F3_RTSlew;
		Double_t        F3_LQRaw;
		Double_t        F3_RQRaw;
		Double_t        F7_LTRaw;
		Double_t        F7_RTRaw;
		Double_t        F7_LTSlew;
		Double_t        F7_RTSlew;
		Double_t        F7_LQRaw;
		Double_t        F7_RQRaw;
		Double_t        SBT1_LTRaw;
		Double_t        SBT1_RTRaw;
		Double_t        SBT1_LTSlew;
		Double_t        SBT1_RTSlew;
		Double_t        SBT1_LQRaw;
		Double_t        SBT1_RQRaw;
		Double_t        SBT2_LTRaw;
		Double_t        SBT2_RTRaw;
		Double_t        SBT2_LTSlew;
		Double_t        SBT2_RTSlew;
		Double_t        SBT2_LQRaw;
		Double_t        SBT2_RQRaw;
		Double_t        SBV_RQRaw;
		Double_t        SBV_RTRaw;
		Double_t        SBV_RTSlew;
		Double_t        F3_Charge;
		Double_t        F3_Time;
		Double_t        F7_Charge;
		Double_t        F7_Time;
		Double_t        F13_Charge;
		Double_t        F13_Time;
		Double_t        SBV_Charge;
		Double_t        SBV_Time;
		Double_t        SBT1_Charge;
		Double_t        SBT1_Time;
		Double_t        SBT2_Charge;
		Double_t        SBT2_Time;
		Double_t        TOF37;
		Double_t        Beta37;
		Double_t        Gamma37;
		Double_t        Ek37;
		Double_t        TOF713;
		Double_t        Beta713;
		Double_t        Gamma713;
		Double_t        Ek713;
		Int_t           BDC1_nhits;
		vector<double>  BDC1_TDC;
		vector<double>  BDC1_layerid;
		vector<double>  BDC1_wireid;
		vector<int>     BDC1_layer_hits;
		Int_t           BDC1_nlayerx;
		Int_t           BDC1_nlayery;
		vector<double>  BDC1_Track_dl;
		vector<double>  BDC1_Track_XY;
		vector<double>  BDC1_Track_Z;
		vector<double>  BDC1_Track_dXY;
		Double_t        BDC1_X;
		Double_t        BDC1_Y;
		Double_t        BDC1_ThetaX;
		Double_t        BDC1_ThetaY;
		Int_t           BDC2_nhits;
		vector<double>  BDC2_TDC;
		vector<double>  BDC2_layerid;
		vector<double>  BDC2_wireid;
		vector<int>     BDC2_layer_hits;
		Int_t           BDC2_nlayerx;
		Int_t           BDC2_nlayery;
		vector<double>  BDC2_Track_dl;
		vector<double>  BDC2_Track_XY;
		vector<double>  BDC2_Track_Z;
		vector<double>  BDC2_Track_dXY;
		Double_t        BDC2_X;
		Double_t        BDC2_Y;
		Double_t        BDC2_ThetaX;
		Double_t        BDC2_ThetaY;
		Double_t        Target_X;
		Double_t        Target_Y;
		Double_t        Target_ThetaX;
		Double_t        Target_ThetaY;

		Int_t           FDC0_nhits;
		vector<double>  FDC0_TDC;
		vector<double>  FDC0_layerid;
		vector<double>  FDC0_wireid;
		vector<int>     FDC0_layer_hits;
		Int_t           FDC0_nlayerx;
		Int_t           FDC0_nlayery;
		vector<double>  FDC0_Track_dl;
		vector<double>  FDC0_Track_XY;
		vector<double>  FDC0_Track_Z;
		vector<double>  FDC0_Track_dXY;
		Double_t        FDC0_X;
		Double_t        FDC0_Y;
		Double_t        FDC0_ThetaX;
		Double_t        FDC0_ThetaY;
		Int_t           dssdEnergyRaw[4][32];
		Int_t           dssdTimeRaw[4][32];
		Double_t        dssdEnergyCal[4][32];
		Double_t        dssdTimeCal[4][32];
		Int_t           csiEnergyRaw[7];
		Int_t           csiTimeRaw[7];
		Double_t        csiEnergyCal[7];
		Double_t        csiTimeCal[7];
		Int_t           multiplicity[4];
		TVector3        *vBeam;
		TVector3        *vBDC1;
		TVector3        *vBDC2;
		TVector3        *vTarget;
		

		TFile *inputFile;
		TTree *tree;
		ReadMerger(int rn){
			runNumber = rn;
			loadInputFile();
			setBranch();
		}
		void loadInputFile(){
			inputFile = new TFile(Form("run0%d_analysed.root",runNumber));
			tree= (TTree*)inputFile->Get("tree");
		}
		void setBranch(){

			vBeam = 0;
			vBDC1 = 0;
			vBDC2 = 0;
			vTarget = 0;



			// Set branch addresses.
			tree->SetBranchAddress("RunNumber",&RunNumber);
			tree->SetBranchAddress("EventNumber",&EventNumber);
			tree->SetBranchAddress("Trig_DSB",&Trig_DSB);
			tree->SetBranchAddress("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			tree->SetBranchAddress("Trig_BxESPRI",&Trig_BxESPRI);
			tree->SetBranchAddress("Trig_BxTEL",&Trig_BxTEL);
			tree->SetBranchAddress("Trig_BxHODP",&Trig_BxHODP);
			tree->SetBranchAddress("Trig_BxHODF",&Trig_BxHODF);
			tree->SetBranchAddress("Trig_BxNEBULA",&Trig_BxNEBULA);
			tree->SetBranchAddress("BDC1_X",&BDC1_X);
			tree->SetBranchAddress("BDC1_Y",&BDC1_Y);
			tree->SetBranchAddress("BDC2_X",&BDC2_X);
			tree->SetBranchAddress("BDC2_Y",&BDC2_Y);
			tree->SetBranchAddress("Target_X",&Target_X);
			tree->SetBranchAddress("Target_Y",&Target_Y);
			tree->SetBranchAddress("vBeam",&vBeam);
			tree->SetBranchAddress("vBDC1",&vBDC1);
			tree->SetBranchAddress("vBDC2",&vBDC2);
			tree->SetBranchAddress("vTarget",&vTarget);
			tree->SetBranchAddress("dssdEnergyCal",dssdEnergyCal);
			tree->SetBranchAddress("csiEnergyCal",&csiEnergyCal);
			tree->SetBranchAddress("multiplicity",multiplicity);
		}
		void setOutputBranch(TTree *outputTree){
			outputTree->Branch("Trig_DSB",&Trig_DSB);
			outputTree->Branch("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			outputTree->Branch("Trig_BxESPRI",&Trig_BxESPRI);
			outputTree->Branch("Trig_BxTEL",&Trig_BxTEL);
			outputTree->Branch("Trig_BxHODP",&Trig_BxHODP);
			outputTree->Branch("Trig_BxHODF",&Trig_BxHODF);
			outputTree->Branch("Trig_BxNEBULA",&Trig_BxNEBULA);

		}
		Long64_t getEntries(){

			return tree->GetEntries();
		}
		void getEntry(Long64_t ientry){
			tree->GetEntry(ientry);
		}
		void print(){
			tree->Print();
		}
		TVector3 getVectorBDC1(){
			return (*vBDC1);
		}
		TVector3 getVectorBDC2(){
			return (*vBDC2);
		}
		TVector3 getVectorTarget(){
			return (*vTarget);
		}
		TVector3 getVectorBeam(){
			return (*vBeam);
		}

		TVector3 getVectorDSSD(){
			analysingDSSD();
			return findPixel->getVectorDSSD();
		}

		void analysingDSSD(){
			findPixel =new FindPixel(dssdEnergyCal);

			int fid = findPixel->getFrontId();
			int bid = findPixel->getBackId();
			double dssdEnergyFront = findPixel->getDSSDEnergyFront();
			double dssdEnergyBack = findPixel->getDSSDEnergyBack();
			//cout<<fid<<" "<<bid<<" "<<dssdEnergyFront<<" "<<dssdEnergyBack<<endl;
		}
		double getCsIEnergy(){
			double CsIEnergy = 0;
			for(int i = 0;i<7;i++){
				if (csiEnergyCal[i]>CsIEnergy) CsIEnergy = csiEnergyCal[i];
				//cout<<csiEnergyCal[i]<<endl;
			}
			return CsIEnergy;
		}


};
