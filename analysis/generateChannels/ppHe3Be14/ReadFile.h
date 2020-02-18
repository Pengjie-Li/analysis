class ReadFile{
	private:

		TFile *inputFile;
		TTree *inputTree;
		TEnv *env;
		int runNumber;
		TString inputName;

		//Declaration of leaves types
		Int_t           RunNumber;
		Long64_t       	EventNumber;
		Int_t           CoincidenceTrigger;
		Int_t           Trig_DSB;
		Int_t           Trig_BxESPRIxTEL;
		Int_t           Trig_BxESPRI;
		Int_t           Trig_BxTEL;
		Int_t           Trig_BxHODP;
		Int_t           Trig_BxHODF;
		Int_t           Trig_BxNEBULA;
		Int_t           F3TRaw[2];
		Int_t           F3QRaw[2];
		Double_t        F3TCal[2];
		Double_t        F3QCal[2];
		Double_t        F3T;
		Double_t        F3Q;
		Int_t           F7TRaw[2];
		Int_t           F7QRaw[2];
		Double_t        F7TCal[2];
		Double_t        F7QCal[2];
		Double_t        F7T;
		Double_t        F7Q;
		Int_t           SBT1TRaw[2];
		Int_t           SBT1QRaw[2];
		Double_t        SBT1TCal[2];
		Double_t        SBT1QCal[2];
		Double_t        SBT1T;
		Double_t        SBT1Q;
		Int_t           SBT2TRaw[2];
		Int_t           SBT2QRaw[2];
		Double_t        SBT2TCal[2];
		Double_t        SBT2QCal[2];
		Double_t        SBT2T;
		Double_t        SBT2Q;
		Double_t        F13T;
		Double_t        F13Q;
		Int_t           SBVTRaw[2];
		Int_t           SBVQRaw[2];
		Double_t        SBVTCal[2];
		Double_t        SBVQCal[2];
		Double_t        SBVT;
		Double_t        SBVQ;
		Double_t        TOF37;
		Double_t        Beta37;
		Double_t        Gamma37;
		Double_t        Ek37;
		Double_t        TOF713;
		Double_t        Beta713;
		Double_t        Gamma713;
		Double_t        Ek713;
		Int_t           BDC1_nhits;
		vector<double>  *BDC1_TDC;
		vector<double>  *BDC1_layerid;
		vector<double>  *BDC1_wireid;
		vector<int>     *BDC1_layer_hits;
		Int_t           BDC1_nlayerx;
		Int_t           BDC1_nlayery;
		vector<double>  *BDC1_Track_dl;
		vector<double>  *BDC1_Track_XY;
		vector<double>  *BDC1_Track_Z;
		vector<double>  *BDC1_Track_dXY;
		Double_t        BDC1_X;
		Double_t        BDC1_Y;
		Double_t        BDC1_ThetaX;
		Double_t        BDC1_ThetaY;
		Int_t           BDC2_nhits;
		vector<double>  *BDC2_TDC;
		vector<double>  *BDC2_layerid;
		vector<double>  *BDC2_wireid;
		vector<int>     *BDC2_layer_hits;
		Int_t           BDC2_nlayerx;
		Int_t           BDC2_nlayery;
		vector<double>  *BDC2_Track_dl;
		vector<double>  *BDC2_Track_XY;
		vector<double>  *BDC2_Track_Z;
		vector<double>  *BDC2_Track_dXY;
		Double_t        BDC2_X;
		Double_t        BDC2_Y;
		Double_t        BDC2_ThetaX;
		Double_t        BDC2_ThetaY;
		Double_t        beamFL;

		Int_t           FDC0_nhits;
		vector<double>  *FDC0_TDC;
		vector<double>  *FDC0_layerid;
		vector<double>  *FDC0_wireid;
		vector<int>     *FDC0_layer_hits;
		Int_t           FDC0_nlayerx;
		Int_t           FDC0_nlayery;
		vector<double>  *FDC0_Track_dl;
		vector<double>  *FDC0_Track_XY;
		vector<double>  *FDC0_Track_Z;
		vector<double>  *FDC0_Track_dXY;
		Double_t        FDC0_X;
		Double_t        FDC0_Y;
		Double_t        FDC0_ThetaX;
		Double_t        FDC0_ThetaY;
		Double_t        resAngle;

		Int_t           dssdQRaw[4][32];
		Int_t           dssdTRaw[2][32];
		Int_t           csiQRaw[7];
		Int_t           csiTRaw[7];
		Int_t           RefTime1;
		Int_t           RefTime2;
		Double_t        dssdQPed[4][32];
		Double_t        csiQPed[7];
		Int_t           dssdQHit;
		Int_t           dssdQHitSide[10];
		Int_t           dssdQHitStripId[10];
		Double_t        dssdQHitQPed[10];
		Int_t           dssdTHit;
		Int_t           dssdTHitSide[10];
		Int_t           dssdTHitStripId[10];
		Double_t        dssdTHitTCal[10];
		Int_t           dssdHit;
		Int_t           dssdHitSide[10];
		Int_t           dssdHitFid[10];
		Int_t           dssdHitBid[10];
		Double_t        dssdHitFQPed[10];
		Double_t        dssdHitBQPed[10];
		Double_t        dssdHitTCal[10];
		Int_t           csiQHit;
		Int_t           csiQHitId[7];
		Double_t        csiQHitQPed[7];
		Int_t           csiTHit;
		Int_t           csiTHitId[7];
		Double_t        csiTHitTCal[7];
		Int_t           csiHit;
		Int_t           csiHitId[7];
		Double_t        csiHitQPed[7];
		Double_t        csiHitTCal[7];
		Int_t           teleHit;
   Int_t           teleHitSide[10];
   Int_t           teleHitFid[10];
   Int_t           teleHitBid[10];
   Double_t        teleHitDssdFQPed[10];
   Double_t        teleHitDssdBQPed[10];
   Double_t        teleHitDssdTCal[10];
   Int_t           teleHitCid[10];
   Double_t        teleHitCsiQPed[10];
   Double_t        teleHitCsiTCal[10];
   Double_t        teleHitDssdFE[10];
   Double_t        teleHitDssdBE[10];
   Double_t        teleHitCsiE[10];
   Int_t           bestHit;
		Double_t        teleCsiE;
		Double_t        teleCsiE_sync;
		Double_t        teleDssdFE;
		Double_t        teleDssdBE;
   Double_t        teleDssdFE_old;
   Double_t        teleDssdBE_old;
   Double_t        teleDssdE;
   Double_t        teleDssdMaxE;
		Double_t        teleCsiT;
		Double_t        teleDssdT;
		Double_t        teleEnergy;
		Double_t        teleX;
		Double_t        teleY;
		Double_t        teleZ;

   Double_t        teleAngle;
   Double_t        teleLocusAngle;
		Int_t           hodNHit;
		Int_t           hodID[40];
		Int_t           hodTRaw[2][40];
		Int_t           hodQRaw[2][40];
		Double_t        hodQPed[2][40];
		Double_t        hodTCal[2][40];
		Double_t        hodQCal[2][40];
		Double_t        hodBarTCal[40];
		Double_t        hodBarQCal[40];


		Int_t           rdcHit;
		Int_t           rdcHitSide[2];
		Double_t        rdcHitX[2];
		Double_t        rdcHitY[2];
		Double_t        rdcHitChi2[2];
		Int_t           naiHit;
		Int_t           naiHitSide[7];
		Int_t           naiHitBarId[7];
		Double_t        naiHitQPed[7];
		Int_t           plasHit;
		Int_t           plasHitSide[2];
		Double_t        plasHitQPed[2];
		Double_t        plasTCal[4];
		Int_t           espriHit;
		Int_t           espriHitSide[1];
		Double_t        espriPlasE_Birks;
		Double_t        espriNaiE_Pol3;
		Double_t        espriPlasE;
		Double_t        espriPlasT;
		Double_t        espriNaiE;
		Double_t        espriDeeEnergy;

		Double_t        espriFL;
		Double_t        espriLocusAngle;
		Double_t        espriEnergy;
		Double_t        espriAngle;


		Double_t        protonEnergy;
		Double_t        protonEnergy_nai;

		Double_t        alphaEnergy;
		Double_t        alphaEnergy_old;

		Double_t        beamEnergy;
		Double_t        beamBeta;
		Double_t        tofSBTTarget;

		Double_t        ppPlasE;
		Double_t        ppWinE;
		Double_t        ppShtE;
		Double_t        apDssdE;
		Double_t        apDegraderE;
		Double_t        apWinE;

		TVector3* vBeam;
		TVector3* vTele;

		TVector3* vBDC1;
		TVector3* vBDC2;
		TVector3* vTarget;
		TVector3* vSBT;
		TVector3* vESPRI;
		TVector3* espriPosition;
		TVector3* espriRdcPosition;
		TVector3* espriPlasPosition;
		TVector3* vFDC0;
		TVector3* fdc0Position;
		TVector3* telePosition;



		TString getFileName(){
			TString inputPath = env->GetValue("inputPath","rootfiles");
			TString runPrefix = env->GetValue("runPrefix","run");
			TString runSuffix = env->GetValue("runSuffix",".root");	
			TString runString = Form("%04d",runNumber);
			return inputPath+runPrefix+runString+runSuffix;
		}
		void setReadBranch(){


			BDC1_TDC	= 0;
			BDC1_layerid	= 0;
			BDC1_wireid	= 0;
			BDC1_layer_hits	= 0;
			BDC1_Track_dl	= 0;
			BDC1_Track_XY	= 0;
			BDC1_Track_Z	= 0;
			BDC1_Track_dXY	= 0;

			BDC2_TDC	= 0;
			BDC2_layerid	= 0;
			BDC2_wireid	= 0;
			BDC2_layer_hits	= 0;
			BDC2_Track_dl	= 0;
			BDC2_Track_XY	= 0;
			BDC2_Track_Z	= 0;
			BDC2_Track_dXY	= 0;


			FDC0_TDC	= 0;
			FDC0_layerid	= 0;
			FDC0_wireid	= 0;
			FDC0_layer_hits	= 0;
			FDC0_Track_dl	= 0;
			FDC0_Track_XY	= 0;
			FDC0_Track_Z	= 0;
			FDC0_Track_dXY	= 0;



			// Set branch addresses.
			inputTree->SetBranchAddress("RunNumber",&RunNumber);
			inputTree->SetBranchAddress("EventNumber",&EventNumber);
			inputTree->SetBranchAddress("CoincidenceTrigger",&CoincidenceTrigger);
			inputTree->SetBranchAddress("Trig_DSB",&Trig_DSB);
			inputTree->SetBranchAddress("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			inputTree->SetBranchAddress("Trig_BxESPRI",&Trig_BxESPRI);
			inputTree->SetBranchAddress("Trig_BxTEL",&Trig_BxTEL);
			inputTree->SetBranchAddress("Trig_BxHODP",&Trig_BxHODP);
			inputTree->SetBranchAddress("Trig_BxHODF",&Trig_BxHODF);
			inputTree->SetBranchAddress("Trig_BxNEBULA",&Trig_BxNEBULA);
			inputTree->SetBranchAddress("F3TRaw",F3TRaw);
			inputTree->SetBranchAddress("F3QRaw",F3QRaw);
			inputTree->SetBranchAddress("F3TCal",F3TCal);
			inputTree->SetBranchAddress("F3QCal",F3QCal);
			inputTree->SetBranchAddress("F3T",&F3T);
			inputTree->SetBranchAddress("F3Q",&F3Q);
			inputTree->SetBranchAddress("F7TRaw",F7TRaw);
			inputTree->SetBranchAddress("F7QRaw",F7QRaw);
			inputTree->SetBranchAddress("F7TCal",F7TCal);
			inputTree->SetBranchAddress("F7QCal",F7QCal);
			inputTree->SetBranchAddress("F7T",&F7T);
			inputTree->SetBranchAddress("F7Q",&F7Q);
			inputTree->SetBranchAddress("SBT1TRaw",SBT1TRaw);
			inputTree->SetBranchAddress("SBT1QRaw",SBT1QRaw);
			inputTree->SetBranchAddress("SBT1TCal",SBT1TCal);
			inputTree->SetBranchAddress("SBT1QCal",SBT1QCal);
			inputTree->SetBranchAddress("SBT1T",&SBT1T);
			inputTree->SetBranchAddress("SBT1Q",&SBT1Q);
			inputTree->SetBranchAddress("SBT2TRaw",SBT2TRaw);
			inputTree->SetBranchAddress("SBT2QRaw",SBT2QRaw);
			inputTree->SetBranchAddress("SBT2TCal",SBT2TCal);
			inputTree->SetBranchAddress("SBT2QCal",SBT2QCal);
			inputTree->SetBranchAddress("SBT2T",&SBT2T);
			inputTree->SetBranchAddress("SBT2Q",&SBT2Q);
			inputTree->SetBranchAddress("F13T",&F13T);
			inputTree->SetBranchAddress("F13Q",&F13Q);
			inputTree->SetBranchAddress("SBVTRaw",SBVTRaw);
			inputTree->SetBranchAddress("SBVQRaw",SBVQRaw);
			inputTree->SetBranchAddress("SBVTCal",SBVTCal);
			inputTree->SetBranchAddress("SBVQCal",SBVQCal);
			inputTree->SetBranchAddress("SBVT",&SBVT);
			inputTree->SetBranchAddress("SBVQ",&SBVQ);
			inputTree->SetBranchAddress("TOF37",&TOF37);
			inputTree->SetBranchAddress("Beta37",&Beta37);
			inputTree->SetBranchAddress("Gamma37",&Gamma37);
			inputTree->SetBranchAddress("Ek37",&Ek37);
			inputTree->SetBranchAddress("TOF713",&TOF713);
			inputTree->SetBranchAddress("Beta713",&Beta713);
			inputTree->SetBranchAddress("Gamma713",&Gamma713);
			inputTree->SetBranchAddress("Ek713",&Ek713);
			inputTree->SetBranchAddress("BDC1_nhits",&BDC1_nhits);
			inputTree->SetBranchAddress("BDC1_TDC",&BDC1_TDC);
			inputTree->SetBranchAddress("BDC1_layerid",&BDC1_layerid);
			inputTree->SetBranchAddress("BDC1_wireid",&BDC1_wireid);
			inputTree->SetBranchAddress("BDC1_layer_hits",&BDC1_layer_hits);
			inputTree->SetBranchAddress("BDC1_nlayerx",&BDC1_nlayerx);
			inputTree->SetBranchAddress("BDC1_nlayery",&BDC1_nlayery);
			inputTree->SetBranchAddress("BDC1_Track_dl",&BDC1_Track_dl);
			inputTree->SetBranchAddress("BDC1_Track_XY",&BDC1_Track_XY);
			inputTree->SetBranchAddress("BDC1_Track_Z",&BDC1_Track_Z);
			inputTree->SetBranchAddress("BDC1_Track_dXY",&BDC1_Track_dXY);
			inputTree->SetBranchAddress("BDC1_X",&BDC1_X);
			inputTree->SetBranchAddress("BDC1_Y",&BDC1_Y);
			inputTree->SetBranchAddress("BDC1_ThetaX",&BDC1_ThetaX);
			inputTree->SetBranchAddress("BDC1_ThetaY",&BDC1_ThetaY);
			inputTree->SetBranchAddress("BDC2_nhits",&BDC2_nhits);
			inputTree->SetBranchAddress("BDC2_TDC",&BDC2_TDC);
			inputTree->SetBranchAddress("BDC2_layerid",&BDC2_layerid);
			inputTree->SetBranchAddress("BDC2_wireid",&BDC2_wireid);
			inputTree->SetBranchAddress("BDC2_layer_hits",&BDC2_layer_hits);
			inputTree->SetBranchAddress("BDC2_nlayerx",&BDC2_nlayerx);
			inputTree->SetBranchAddress("BDC2_nlayery",&BDC2_nlayery);
			inputTree->SetBranchAddress("BDC2_Track_dl",&BDC2_Track_dl);
			inputTree->SetBranchAddress("BDC2_Track_XY",&BDC2_Track_XY);
			inputTree->SetBranchAddress("BDC2_Track_Z",&BDC2_Track_Z);
			inputTree->SetBranchAddress("BDC2_Track_dXY",&BDC2_Track_dXY);
			inputTree->SetBranchAddress("BDC2_X",&BDC2_X);
			inputTree->SetBranchAddress("BDC2_Y",&BDC2_Y);
			inputTree->SetBranchAddress("BDC2_ThetaX",&BDC2_ThetaX);
			inputTree->SetBranchAddress("BDC2_ThetaY",&BDC2_ThetaY);
			inputTree->SetBranchAddress("beamFL",&beamFL);
			inputTree->SetBranchAddress("vBeam",&vBeam);
			inputTree->SetBranchAddress("vBDC1",&vBDC1);
			inputTree->SetBranchAddress("vBDC2",&vBDC2);
			inputTree->SetBranchAddress("vTarget",&vTarget);
			inputTree->SetBranchAddress("vSBT",&vSBT);
			inputTree->SetBranchAddress("FDC0_nhits",&FDC0_nhits);
			inputTree->SetBranchAddress("FDC0_TDC",&FDC0_TDC);
			inputTree->SetBranchAddress("FDC0_layerid",&FDC0_layerid);
			inputTree->SetBranchAddress("FDC0_wireid",&FDC0_wireid);
			inputTree->SetBranchAddress("FDC0_layer_hits",&FDC0_layer_hits);
			inputTree->SetBranchAddress("FDC0_nlayerx",&FDC0_nlayerx);
			inputTree->SetBranchAddress("FDC0_nlayery",&FDC0_nlayery);
			inputTree->SetBranchAddress("FDC0_Track_dl",&FDC0_Track_dl);
			inputTree->SetBranchAddress("FDC0_Track_XY",&FDC0_Track_XY);
			inputTree->SetBranchAddress("FDC0_Track_Z",&FDC0_Track_Z);
			inputTree->SetBranchAddress("FDC0_Track_dXY",&FDC0_Track_dXY);
			inputTree->SetBranchAddress("FDC0_X",&FDC0_X);
			inputTree->SetBranchAddress("FDC0_Y",&FDC0_Y);
			inputTree->SetBranchAddress("FDC0_ThetaX",&FDC0_ThetaX);
			inputTree->SetBranchAddress("FDC0_ThetaY",&FDC0_ThetaY);
			inputTree->SetBranchAddress("resAngle",&resAngle);
			inputTree->SetBranchAddress("fdc0Position",&fdc0Position);
			inputTree->SetBranchAddress("vFDC0",&vFDC0);

			inputTree->SetBranchAddress("hodNHit",&hodNHit);
			inputTree->SetBranchAddress("hodID",hodID);
			inputTree->SetBranchAddress("hodTRaw",hodTRaw);
			inputTree->SetBranchAddress("hodQRaw",hodQRaw);
			inputTree->SetBranchAddress("hodQPed",hodQPed);
			inputTree->SetBranchAddress("hodTCal",hodTCal);
			inputTree->SetBranchAddress("hodQCal",hodQCal);
			inputTree->SetBranchAddress("hodBarTCal",hodBarTCal);
			inputTree->SetBranchAddress("hodBarQCal",hodBarQCal);

			inputTree->SetBranchAddress("rdcHit",&rdcHit);
			inputTree->SetBranchAddress("rdcHitSide",rdcHitSide);
			inputTree->SetBranchAddress("rdcHitX",rdcHitX);
			inputTree->SetBranchAddress("rdcHitY",rdcHitY);
			inputTree->SetBranchAddress("rdcHitChi2",rdcHitChi2);
			inputTree->SetBranchAddress("naiHit",&naiHit);
			inputTree->SetBranchAddress("naiHitSide",naiHitSide);
			inputTree->SetBranchAddress("naiHitBarId",naiHitBarId);
			inputTree->SetBranchAddress("naiHitQPed",naiHitQPed);
			inputTree->SetBranchAddress("plasHit",&plasHit);
			inputTree->SetBranchAddress("plasHitSide",plasHitSide);
			inputTree->SetBranchAddress("plasHitQPed",plasHitQPed);
			inputTree->SetBranchAddress("plasTCal",plasTCal);
			inputTree->SetBranchAddress("espriHit",&espriHit);
			inputTree->SetBranchAddress("espriHitSide",espriHitSide);
			inputTree->SetBranchAddress("espriPlasE_Birks",&espriPlasE_Birks);
			inputTree->SetBranchAddress("espriNaiE_Pol3",&espriNaiE_Pol3);
			inputTree->SetBranchAddress("espriPlasE",&espriPlasE);
			inputTree->SetBranchAddress("espriPlasT",&espriPlasT);
			inputTree->SetBranchAddress("espriNaiE",&espriNaiE);
			inputTree->SetBranchAddress("espriDeeEnergy",&espriDeeEnergy);

			inputTree->SetBranchAddress("vESPRI",&vESPRI);
			inputTree->SetBranchAddress("espriRdcPosition",&espriRdcPosition);
			inputTree->SetBranchAddress("espriPlasPosition",&espriPlasPosition);

			inputTree->SetBranchAddress("espriFL",&espriFL);
			inputTree->SetBranchAddress("espriLocusAngle",&espriLocusAngle);
			inputTree->SetBranchAddress("espriEnergy",&espriEnergy);
			inputTree->SetBranchAddress("espriAngle",&espriAngle);

			inputTree->SetBranchAddress("espriPosition",&espriPosition);

			inputTree->SetBranchAddress("protonEnergy",&protonEnergy);

			inputTree->SetBranchAddress("dssdQRaw",dssdQRaw);
			inputTree->SetBranchAddress("dssdTRaw",dssdTRaw);
			inputTree->SetBranchAddress("csiQRaw",csiQRaw);
			inputTree->SetBranchAddress("csiQPed",csiQPed);
			inputTree->SetBranchAddress("RefTime1",&RefTime1);
			inputTree->SetBranchAddress("RefTime2",&RefTime2);
			inputTree->SetBranchAddress("dssdQPed",dssdQPed);
			inputTree->SetBranchAddress("csiQPed",csiQPed);
			inputTree->SetBranchAddress("dssdQHit",&dssdQHit);
			inputTree->SetBranchAddress("dssdQHitSide",dssdQHitSide);
			inputTree->SetBranchAddress("dssdQHitStripId",dssdQHitStripId);
			inputTree->SetBranchAddress("dssdQHitQPed",dssdQHitQPed);
			inputTree->SetBranchAddress("dssdTHit",&dssdTHit);
			inputTree->SetBranchAddress("dssdTHitSide",dssdTHitSide);
			inputTree->SetBranchAddress("dssdTHitStripId",dssdTHitStripId);
			inputTree->SetBranchAddress("dssdTHitTCal",dssdTHitTCal);
			inputTree->SetBranchAddress("dssdHit",&dssdHit);
			inputTree->SetBranchAddress("dssdHitSide",dssdHitSide);
			inputTree->SetBranchAddress("dssdHitFid",dssdHitFid);
			inputTree->SetBranchAddress("dssdHitBid",dssdHitBid);
			inputTree->SetBranchAddress("dssdHitFQPed",dssdHitFQPed);
			inputTree->SetBranchAddress("dssdHitBQPed",dssdHitBQPed);
			inputTree->SetBranchAddress("dssdHitTCal",dssdHitTCal);
			inputTree->SetBranchAddress("csiQHit",&csiQHit);
			inputTree->SetBranchAddress("csiQHitId",csiQHitId);
			inputTree->SetBranchAddress("csiQHitQPed",csiQHitQPed);
			inputTree->SetBranchAddress("csiTHit",&csiTHit);
			inputTree->SetBranchAddress("csiTHitId",csiTHitId);
			inputTree->SetBranchAddress("csiTHitTCal",csiTHitTCal);
			inputTree->SetBranchAddress("csiHit",&csiHit);
			inputTree->SetBranchAddress("csiHitId",csiHitId);
			inputTree->SetBranchAddress("csiHitQPed",csiHitQPed);
			inputTree->SetBranchAddress("csiHitTCal",csiHitTCal);
			inputTree->SetBranchAddress("teleHit",&teleHit);
			inputTree->SetBranchAddress("teleHitSide",teleHitSide);
			inputTree->SetBranchAddress("teleHitFid",teleHitFid);
			inputTree->SetBranchAddress("teleHitBid",teleHitBid);
			inputTree->SetBranchAddress("teleHitDssdFQPed",teleHitDssdFQPed);
			inputTree->SetBranchAddress("teleHitDssdBQPed",teleHitDssdBQPed);
			inputTree->SetBranchAddress("teleHitDssdTCal",teleHitDssdTCal);
			inputTree->SetBranchAddress("teleHitCid",teleHitCid);
			inputTree->SetBranchAddress("teleHitCsiQPed",teleHitCsiQPed);
			inputTree->SetBranchAddress("teleHitCsiTCal",teleHitCsiTCal);
			inputTree->SetBranchAddress("teleHitDssdFE",teleHitDssdFE);
			inputTree->SetBranchAddress("teleHitDssdBE",teleHitDssdBE);
			inputTree->SetBranchAddress("teleHitCsiE",teleHitCsiE);
			inputTree->SetBranchAddress("bestHit",&bestHit);

			inputTree->SetBranchAddress("teleCsiE",&teleCsiE);
			inputTree->SetBranchAddress("teleCsiE_sync",&teleCsiE_sync);
			inputTree->SetBranchAddress("teleDssdFE",&teleDssdFE);
			inputTree->SetBranchAddress("teleDssdBE",&teleDssdBE);
			inputTree->SetBranchAddress("teleDssdFE_old",&teleDssdFE_old);
			inputTree->SetBranchAddress("teleDssdBE_old",&teleDssdBE_old);
			inputTree->SetBranchAddress("teleDssdE",&teleDssdE);
			inputTree->SetBranchAddress("teleDssdMaxE",&teleDssdMaxE);
			inputTree->SetBranchAddress("teleCsiT",&teleCsiT);
			inputTree->SetBranchAddress("teleDssdT",&teleDssdT);
			inputTree->SetBranchAddress("teleEnergy",&teleEnergy);
			inputTree->SetBranchAddress("teleAngle",&teleAngle);
			inputTree->SetBranchAddress("teleLocusAngle",&teleLocusAngle);


			inputTree->SetBranchAddress("protonEnergy",&protonEnergy);
			inputTree->SetBranchAddress("beamEnergy",&beamEnergy);
			inputTree->SetBranchAddress("beamBeta",&beamBeta);

			inputTree->SetBranchAddress("alphaEnergy",&alphaEnergy);
			inputTree->SetBranchAddress("vTele",&vTele);


			inputTree->SetBranchAddress("ppPlasE",&ppPlasE);
			inputTree->SetBranchAddress("ppWinE",&ppWinE);
			inputTree->SetBranchAddress("ppShtE",&ppShtE);
			inputTree->SetBranchAddress("apWinE",&apWinE);
			inputTree->SetBranchAddress("apDssdE",&apDssdE);
			inputTree->SetBranchAddress("apDegraderE",&apDegraderE);
		}

	public:
		ReadFile(){}
		ReadFile(int runNumber):runNumber(runNumber){
			env = new TEnv("configPPBe.prm");
		}
		~ReadFile(){
			delete env;
		}
		bool isFilesExist(){
			inputName = getFileName();
			cout<<inputName<<endl;

			bool isFile = gSystem->AccessPathName(inputName);
			if(!isFile){
				cout<<" Confirmed::"<<getFileName()<<endl;
				return true;
			}else{
				return false;
			}
		}
		void loadInputFiles(){
			inputFile = new TFile(inputName,"READ");
			inputTree = (TTree *)inputFile->Get("tree");
			//inputTree->Print();
			setReadBranch();
		}

		void setBranch(TTree *tree){

			// Set branch addresses.
			tree->Branch("RunNumber",&RunNumber);
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("CoincidenceTrigger",&CoincidenceTrigger);
			tree->Branch("Trig_DSB",&Trig_DSB);
			tree->Branch("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			tree->Branch("Trig_BxESPRI",&Trig_BxESPRI);
			tree->Branch("Trig_BxTEL",&Trig_BxTEL);
			tree->Branch("Trig_BxHODP",&Trig_BxHODP);
			tree->Branch("Trig_BxHODF",&Trig_BxHODF);
			tree->Branch("Trig_BxNEBULA",&Trig_BxNEBULA);
			tree->Branch("F3TRaw",F3TRaw);
			tree->Branch("F3QRaw",F3QRaw);
			tree->Branch("F3TCal",F3TCal);
			tree->Branch("F3QCal",F3QCal);
			tree->Branch("F3T",&F3T);
			tree->Branch("F3Q",&F3Q);
			tree->Branch("F7TRaw",F7TRaw);
			tree->Branch("F7QRaw",F7QRaw);
			tree->Branch("F7TCal",F7TCal);
			tree->Branch("F7QCal",F7QCal);
			tree->Branch("F7T",&F7T);
			tree->Branch("F7Q",&F7Q);
			tree->Branch("SBT1TRaw",SBT1TRaw);
			tree->Branch("SBT1QRaw",SBT1QRaw);
			tree->Branch("SBT1TCal",SBT1TCal);
			tree->Branch("SBT1QCal",SBT1QCal);
			tree->Branch("SBT1T",&SBT1T);
			tree->Branch("SBT1Q",&SBT1Q);
			tree->Branch("SBT2TRaw",SBT2TRaw);
			tree->Branch("SBT2QRaw",SBT2QRaw);
			tree->Branch("SBT2TCal",SBT2TCal);
			tree->Branch("SBT2QCal",SBT2QCal);
			tree->Branch("SBT2T",&SBT2T);
			tree->Branch("SBT2Q",&SBT2Q);
			tree->Branch("F13T",&F13T);
			tree->Branch("F13Q",&F13Q);
			tree->Branch("SBVTRaw",SBVTRaw);
			tree->Branch("SBVQRaw",SBVQRaw);
			tree->Branch("SBVTCal",SBVTCal);
			tree->Branch("SBVQCal",SBVQCal);
			tree->Branch("SBVT",&SBVT);
			tree->Branch("SBVQ",&SBVQ);
			tree->Branch("TOF37",&TOF37);
			tree->Branch("Beta37",&Beta37);
			tree->Branch("Gamma37",&Gamma37);
			tree->Branch("Ek37",&Ek37);
			tree->Branch("TOF713",&TOF713);
			tree->Branch("Beta713",&Beta713);
			tree->Branch("Gamma713",&Gamma713);
			tree->Branch("Ek713",&Ek713);
			tree->Branch("BDC1_nhits",&BDC1_nhits);
			tree->Branch("BDC1_TDC",&BDC1_TDC);
			tree->Branch("BDC1_layerid",&BDC1_layerid);
			tree->Branch("BDC1_wireid",&BDC1_wireid);
			tree->Branch("BDC1_layer_hits",&BDC1_layer_hits);
			tree->Branch("BDC1_nlayerx",&BDC1_nlayerx);
			tree->Branch("BDC1_nlayery",&BDC1_nlayery);
			tree->Branch("BDC1_Track_dl",&BDC1_Track_dl);
			tree->Branch("BDC1_Track_XY",&BDC1_Track_XY);
			tree->Branch("BDC1_Track_Z",&BDC1_Track_Z);
			tree->Branch("BDC1_Track_dXY",&BDC1_Track_dXY);
			tree->Branch("BDC1_X",&BDC1_X);
			tree->Branch("BDC1_Y",&BDC1_Y);
			tree->Branch("BDC1_ThetaX",&BDC1_ThetaX);
			tree->Branch("BDC1_ThetaY",&BDC1_ThetaY);
			tree->Branch("BDC2_nhits",&BDC2_nhits);
			tree->Branch("BDC2_TDC",&BDC2_TDC);
			tree->Branch("BDC2_layerid",&BDC2_layerid);
			tree->Branch("BDC2_wireid",&BDC2_wireid);
			tree->Branch("BDC2_layer_hits",&BDC2_layer_hits);
			tree->Branch("BDC2_nlayerx",&BDC2_nlayerx);
			tree->Branch("BDC2_nlayery",&BDC2_nlayery);
			tree->Branch("BDC2_Track_dl",&BDC2_Track_dl);
			tree->Branch("BDC2_Track_XY",&BDC2_Track_XY);
			tree->Branch("BDC2_Track_Z",&BDC2_Track_Z);
			tree->Branch("BDC2_Track_dXY",&BDC2_Track_dXY);
			tree->Branch("BDC2_X",&BDC2_X);
			tree->Branch("BDC2_Y",&BDC2_Y);
			tree->Branch("BDC2_ThetaX",&BDC2_ThetaX);
			tree->Branch("BDC2_ThetaY",&BDC2_ThetaY);
			tree->Branch("beamFL",&beamFL);
			tree->Branch("vBeam",&vBeam);
			tree->Branch("vBDC1",&vBDC1);
			tree->Branch("vBDC2",&vBDC2);
			tree->Branch("vTarget",&vTarget);
			tree->Branch("vSBT",&vSBT);
			tree->Branch("FDC0_nhits",&FDC0_nhits);
			tree->Branch("FDC0_TDC",&FDC0_TDC);
			tree->Branch("FDC0_layerid",&FDC0_layerid);
			tree->Branch("FDC0_wireid",&FDC0_wireid);
			tree->Branch("FDC0_layer_hits",&FDC0_layer_hits);
			tree->Branch("FDC0_nlayerx",&FDC0_nlayerx);
			tree->Branch("FDC0_nlayery",&FDC0_nlayery);
			tree->Branch("FDC0_Track_dl",&FDC0_Track_dl);
			tree->Branch("FDC0_Track_XY",&FDC0_Track_XY);
			tree->Branch("FDC0_Track_Z",&FDC0_Track_Z);
			tree->Branch("FDC0_Track_dXY",&FDC0_Track_dXY);
			tree->Branch("FDC0_X",&FDC0_X);
			tree->Branch("FDC0_Y",&FDC0_Y);
			tree->Branch("FDC0_ThetaX",&FDC0_ThetaX);
			tree->Branch("FDC0_ThetaY",&FDC0_ThetaY);
			tree->Branch("resAngle",&resAngle);
			tree->Branch("fdc0Position",&fdc0Position);
			tree->Branch("vFDC0",&vFDC0);

			tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
                        tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[2][32]/I");

                        tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
                        tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
                        tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");


                        tree->Branch("hodNHit",&hodNHit,"hodNHit/I");
                        tree->Branch("hodID",hodID,"hodID[40]/I");
                        tree->Branch("hodTRaw",hodTRaw,"hodTRaw[2][40]/I");
                        tree->Branch("hodQRaw",hodQRaw,"hodQRaw[2][40]/I");

                        tree->Branch("hodQPed",hodQPed,"hodQPed[2][40]/D");
                        tree->Branch("hodTCal",hodTCal,"hodTCal[2][40]/D");
                        tree->Branch("hodQCal",hodQCal,"hodQCal[2][40]/D");
                        tree->Branch("hodBarTCal",hodBarTCal,"hodBarTCal[40]/D");
                        tree->Branch("hodBarQCal",hodBarQCal,"hodBarQCal[40]/D");

			tree->Branch("rdcHit",&rdcHit,"rdcHit/I");
			tree->Branch("rdcHitSide",rdcHitSide,"rdcHitSide[rdcHit]/I");
			tree->Branch("rdcHitX",rdcHitX,"rdcHitX[rdcHit]/D");
			tree->Branch("rdcHitY",rdcHitY,"rdcHitY[rdcHit]/D");
			tree->Branch("rdcHitChi2",rdcHitChi2,"rdcHitChi2[rdcHit]/D");

			tree->Branch("naiHit",&naiHit,"naiHit/I");
			tree->Branch("naiHitSide",naiHitSide,"naiHitSide[naiHit]/I");
			tree->Branch("naiHitBarId",naiHitBarId,"naiHitBarId[naiHit]/I");
			tree->Branch("naiHitQPed",naiHitQPed,"naiHitQPed[naiHit]/D");

			tree->Branch("plasHit",&plasHit,"plasHit/I");
			tree->Branch("plasHitSide",plasHitSide,"plasHitSide[plasHit]/I");
			tree->Branch("plasHitQPed",plasHitQPed,"plasHitQPed[plasHit]/D");
			tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");

			tree->Branch("espriHit",&espriHit,"espriHit/I");
			tree->Branch("espriHitSide",espriHitSide,"espriHitSide[espriHit]/I");

			tree->Branch("espriPlasE_Birks",&espriPlasE_Birks);
			tree->Branch("espriNaiE_Pol3",&espriNaiE_Pol3);
			tree->Branch("espriPlasE",&espriPlasE);
			tree->Branch("espriPlasT",&espriPlasT);
			tree->Branch("espriNaiE",&espriNaiE);
			tree->Branch("espriDeeEnergy",&espriDeeEnergy);

			tree->Branch("vESPRI",&vESPRI);
			tree->Branch("espriRdcPosition",&espriRdcPosition);
			tree->Branch("espriPlasPosition",&espriPlasPosition);

			tree->Branch("espriFL",&espriFL);
			tree->Branch("espriLocusAngle",&espriLocusAngle);
			tree->Branch("espriEnergy",&espriEnergy);
			tree->Branch("espriAngle",&espriAngle);

			tree->Branch("espriPosition",&espriPosition);

			tree->Branch("dssdHit",&dssdHit,"dssdHit/I");
			tree->Branch("csiHit",&csiHit,"csiHit/I");
			tree->Branch("csiHitId",csiHitId,"csiHitId[csiHit]/I");
			tree->Branch("csiHitQPed",csiHitQPed,"csiHitQPed[csiHit]/D");
			tree->Branch("csiHitTCal",csiHitTCal,"csiHitTCal[csiHit]/D");
	
			tree->Branch("teleHit",&teleHit,"teleHit/I");
			tree->Branch("teleHitSide",teleHitSide,"teleHitSide[teleHit]/I");
			tree->Branch("teleHitFid",teleHitFid,"teleHitFid[teleHit]/I");
			tree->Branch("teleHitBid",teleHitBid,"teleHitBid[teleHit]/I");
			tree->Branch("teleHitDssdFQPed",teleHitDssdFQPed,"teleHitDssdFQPed[teleHit]/I");
			tree->Branch("teleHitDssdBQPed",teleHitDssdBQPed,"teleHitDssdBQPed[teleHit]/I");
			tree->Branch("teleHitDssdTCal",teleHitDssdTCal,"teleHitDssdTCal[teleHit]/I");
			tree->Branch("teleHitCid",teleHitCid,"teleHitCid[teleHit]/I");
			tree->Branch("teleHitCsiQPed",teleHitCsiQPed,"teleHitCsiQPed[teleHit]/I");
			tree->Branch("teleHitCsiTCal",teleHitCsiTCal,"teleHitCsiTCal[teleHit]/I");
	

                        tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
                        tree->Branch("teleCsiE_sync",&teleCsiE_sync,"teleCsiE_sync/D");
                        tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE/D");
                        tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE/D");
			tree->Branch("teleDssdFE_old",&teleDssdFE_old,"teleDssdFE_old/D");
                        tree->Branch("teleDssdBE_old",&teleDssdBE_old,"teleDssdBE_old/D");
                        tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
                        tree->Branch("teleDssdMaxE",&teleDssdMaxE,"teleDssdMaxE/D");
         
                        tree->Branch("teleCsiT",&teleCsiT,"teleCsiT/D");
                        tree->Branch("teleDssdT",&teleDssdT,"teleDssdT/D");
                        tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
                        tree->Branch("teleAngle",&teleAngle,"teleAngle/D");
                        tree->Branch("teleLocusAngle",&teleLocusAngle,"teleLocusAngle/D");
                        tree->Branch("telePosition","TVector3",&telePosition);

			tree->Branch("protonEnergy",&protonEnergy);
			tree->Branch("beamEnergy",&beamEnergy);
			tree->Branch("beamBeta",&beamBeta);


                        tree->Branch("ppPlasE",&ppPlasE,"ppPlasE/D");
                        tree->Branch("ppWinE",&ppWinE,"ppWinE/D");
                        tree->Branch("ppShtE",&ppShtE,"ppShtE/D");
                        tree->Branch("apWinE",&apWinE,"apWinE/D");
                        tree->Branch("apDssdE",&apDssdE,"apDssdE/D");
                        tree->Branch("apDegraderE",&apDegraderE,"apDegraderE/D");

                        tree->Branch("alphaEnergy",&alphaEnergy,"alphaEnergy/D");
                        tree->Branch("vTele","TVector3",&vTele);




		}
		Long64_t getEntries(){
			return inputTree->GetEntries();
		}
		void getEntry(Long64_t ientry){
			inputTree->GetEntry(ientry);
		}
		double getTof713(){
			return TOF713;
		}
		double getF13Q(){
			return F13Q;
		}
		double getEspriNaiE(){
			return espriNaiE;
			//return espriNaiE_Pol3;
		}
		double getEspriPlasE(){
			return espriPlasE;
		}
		double getNaiQ(){
			return espriNaiE;
		}
		double getPlasQ(){
			//return plasHitQPed[0];
			return espriPlasE;
		}
		double getNaiQ_Pol3(){
			return espriNaiE_Pol3;
		}
		double getPlasQ_Birks(){
			//return plasHitQPed[0];
			return espriPlasE_Birks;
		}
		double getTeleCsiE(){
			return teleCsiE;
		}
		double getCsiEnergy(){
			return teleCsiE;
		}
	
		double getLocusAngle(){
			return teleLocusAngle;
		}
		double getTeleDssdE(){
			return teleDssdFE; 
		}
		double getTargetX(){
			return vTarget->X();
		}
		double getTargetY(){
			return vTarget->Y();
		}
		double getResAngle(){
			return resAngle;
		}
		double getEspriAngle(){
			return espriAngle;
		}
		double getHodBarTRaw(int id){
			return 0.5*(hodTRaw[0][id]+hodTRaw[1][id]);
		}
		double getHodBarQRaw(int id){
			return hodBarQCal[id];
		}
		bool isPALR(){
			if((espriHit==1&&espriHitSide[0]==0&&teleHit==1&&teleHitSide[0]==1)||(espriHit==1&&espriHitSide[0]==1&&teleHit==1&&teleHitSide[0]==0)) return true;
			else return false;
		}

};
