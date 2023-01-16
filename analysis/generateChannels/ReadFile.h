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
		Double_t        fdc0Angle;

                Int_t           dssdQRaw[4][32];
                Int_t           dssdTRaw[2][32];
                Double_t        dssdQPed[4][32];
                Int_t           RefTime1;
                Int_t           RefTime2;
                Int_t           csiQRaw[7];
                Int_t           csiTRaw[7];
                Double_t        csiQPed[7];
                Int_t           dssdTHit;
                Int_t           dssdTHitSide[64];
                Int_t           dssdTHitStripId[64];
                Double_t        dssdTHitTCal[64];
                Int_t           csiTHit;
                Int_t           csiTHitId[7];
                Double_t        csiTHitTCal[7];

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

		Int_t		teleSide;
		int             teleCsiId;
		int             teleDssdFid;
		int             teleDssdBid;
		double          teleCsiQPed;
		double          teleDssdFQPed;
		double          teleDssdBQPed;
		Double_t        teleCsiE;
		Double_t        teleDssdFE;
		Double_t        teleDssdBE;
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

		int 		hodQHit;
		int 		hodQHitId[40];
		double 		hodQHitQSyn[40];

		int 		hodTHit;
		int 		hodTHitId[40];
		double 		hodTHitTSyn[40];

		int 		hodHit;
		int 		hodHitId[40];
		double 		hodHitQ[40];
		double 		hodHitT[40];

		vector<int>     *plasTdcRaw0;
		vector<int>     *plasTdcRaw1;
		vector<int>     *plasTdcRaw2;
		vector<int>     *plasTdcRaw3;
		vector<int>     *rdcTdc;
		vector<int>     *rdcPlaneId;
		vector<int>     *rdcWireId;
		vector<int>     *rdcPlaneNHit;
		Int_t           naiQRaw[4][7];
		Int_t           plasQRaw[4];
		Int_t           plasTRaw[4];
		Int_t           plasTimeRef;
		Double_t        rdcX[2];
		Double_t        rdcY[2];
		Double_t        rdcA[2];
		Double_t        rdcB[2];
		Double_t        rdcChi2[2];
		Double_t        rdcDL[2][7];
		Double_t        rdcTch[2][7];
		Double_t        rdcRes[2][7];
		Double_t        naiQPed[4][7];
		Double_t        plasQPed[4];
		Int_t           rdcHit;
		Int_t           rdcHitSide[10];
		Int_t           naiHit;
		Int_t           naiHitSide[10];
		Int_t           naiHitBarId[10];
		Int_t           plasHit;
		Int_t           plasHitSide[10];
		Int_t           plasTHit;
		Int_t           plasQHit;
		Int_t           espriHit;
		Int_t           espriSide;
		Double_t        espriRdcX;
		Double_t        espriRdcY;
		Double_t        espriPlasQPed;
		Int_t           espriNaiBarId;
		Double_t        espriNaiQPed;
		Double_t        espriPlasT;
		Double_t        espriPlasE_Birks;
		Double_t        espriPlasE;
		Double_t        espriNaiE;

		Double_t        espriFL;
		Double_t        espriLocusAngle;
		Double_t        espriAngle;
		Double_t        espriPhi;
		Double_t        ppDegraderE;
		Double_t        ppPlasE;
		Double_t        ppWinE;
		Double_t        ppShtE;
		Double_t        degraderThickness;
		Double_t        protonEnergy;



		Double_t        beamEnergy;
		Double_t        beamBeta;
		Double_t        tofSBTTarget;
		Double_t        alphaEnergy;
		Double_t        alphaEnergy_old;
		Double_t        apDssdE;
		Double_t        apDegraderE;
		Double_t        apWinE;

		TVector3* vBeam;
		TVector3* vTele;

		TVector3* bdc1Position;
		TVector3* bdc2Position;
		TVector3* targetPosition;
		TVector3* sbtPosition;
		TVector3* vESPRI;
		TVector3* espriPosition;
		TVector3* espriRdcPosition;
		TVector3* espriPlasPosition;
		TVector3* vFDC0;
		TVector3* fdc0Position;
		TVector3* telePosition;

		Double_t telePhi;
		Double_t fdc0Phi;


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


			plasTdcRaw0 = 0;
			plasTdcRaw1 = 0;
			plasTdcRaw2 = 0;
			plasTdcRaw3 = 0;
			rdcTdc	= 0;
			rdcPlaneId = 0;
			rdcWireId = 0;
			rdcPlaneNHit = 0;


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
			inputTree->SetBranchAddress("bdc1Position",&bdc1Position);
			inputTree->SetBranchAddress("bdc2Position",&bdc2Position);
			inputTree->SetBranchAddress("targetPosition",&targetPosition);
			inputTree->SetBranchAddress("telePosition",&telePosition);
			inputTree->SetBranchAddress("sbtPosition",&sbtPosition);
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
			inputTree->SetBranchAddress("fdc0Angle",&fdc0Angle);
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

                        inputTree->SetBranchAddress("hodQHit",&hodQHit);
                        inputTree->SetBranchAddress("hodQHitId",hodQHitId);
                        inputTree->SetBranchAddress("hodQHitQSyn",hodQHitQSyn);
                        inputTree->SetBranchAddress("hodTHit",&hodTHit);
                        inputTree->SetBranchAddress("hodTHitId",hodTHitId);
                        inputTree->SetBranchAddress("hodTHitTSyn",hodTHitTSyn);
                        inputTree->SetBranchAddress("hodHit",&hodHit);
                        inputTree->SetBranchAddress("hodHitId",hodHitId);
                        inputTree->SetBranchAddress("hodHitT",hodHitT);
                        inputTree->SetBranchAddress("hodHitQ",hodHitQ);

			inputTree->SetBranchAddress("plasTdcRaw0",&plasTdcRaw0);
			inputTree->SetBranchAddress("plasTdcRaw1",&plasTdcRaw1);
			inputTree->SetBranchAddress("plasTdcRaw2",&plasTdcRaw2);
			inputTree->SetBranchAddress("plasTdcRaw3",&plasTdcRaw3);
			inputTree->SetBranchAddress("rdcTdc",&rdcTdc);
			inputTree->SetBranchAddress("rdcPlaneId",&rdcPlaneId);
			inputTree->SetBranchAddress("rdcWireId",&rdcWireId);
			inputTree->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
			inputTree->SetBranchAddress("naiQRaw",naiQRaw);
			inputTree->SetBranchAddress("plasQRaw",plasQRaw);
			inputTree->SetBranchAddress("plasTRaw",plasTRaw);
			inputTree->SetBranchAddress("plasTimeRef",&plasTimeRef);
			inputTree->SetBranchAddress("rdcHit",&rdcHit);
			inputTree->SetBranchAddress("rdcHitSide",rdcHitSide);
			inputTree->SetBranchAddress("rdcX",rdcX);
			inputTree->SetBranchAddress("rdcY",rdcY);
			inputTree->SetBranchAddress("rdcA",rdcA);
			inputTree->SetBranchAddress("rdcB",rdcB);
			inputTree->SetBranchAddress("rdcChi2",rdcChi2);
			inputTree->SetBranchAddress("rdcDL",rdcDL);
			inputTree->SetBranchAddress("rdcTch",rdcTch);
			inputTree->SetBranchAddress("rdcRes",rdcRes);

			inputTree->SetBranchAddress("naiHit",&naiHit);
			inputTree->SetBranchAddress("naiHitSide",naiHitSide);
			inputTree->SetBranchAddress("naiHitBarId",naiHitBarId);
			inputTree->SetBranchAddress("naiQPed",naiQPed);
			inputTree->SetBranchAddress("plasHit",&plasHit);
			inputTree->SetBranchAddress("plasHitSide",plasHitSide);
			inputTree->SetBranchAddress("plasTHit",&plasTHit);
			inputTree->SetBranchAddress("plasQHit",&plasQHit);
			inputTree->SetBranchAddress("plasQPed",plasQPed);
			inputTree->SetBranchAddress("espriHit",&espriHit);
			inputTree->SetBranchAddress("espriSide",&espriSide);
			inputTree->SetBranchAddress("espriRdcX",&espriRdcX);
			inputTree->SetBranchAddress("espriRdcY",&espriRdcY);
			inputTree->SetBranchAddress("espriPlasQPed",&espriPlasQPed);
			inputTree->SetBranchAddress("espriNaiQPed",&espriNaiQPed);
			inputTree->SetBranchAddress("espriNaiBarId",&espriNaiBarId);


			inputTree->SetBranchAddress("espriPlasE_Birks",&espriPlasE_Birks);
			inputTree->SetBranchAddress("espriPlasE",&espriPlasE);
			inputTree->SetBranchAddress("espriPlasT",&espriPlasT);
			inputTree->SetBranchAddress("espriNaiE",&espriNaiE);

			inputTree->SetBranchAddress("vESPRI",&vESPRI);
			inputTree->SetBranchAddress("espriRdcPosition",&espriRdcPosition);
			inputTree->SetBranchAddress("espriPlasPosition",&espriPlasPosition);
			inputTree->SetBranchAddress("espriFL",&espriFL);
			inputTree->SetBranchAddress("espriLocusAngle",&espriLocusAngle);
			inputTree->SetBranchAddress("espriAngle",&espriAngle);
			inputTree->SetBranchAddress("espriPosition",&espriPosition);
			inputTree->SetBranchAddress("protonEnergy",&protonEnergy);

			inputTree->SetBranchAddress("dssdQRaw",dssdQRaw);
                        inputTree->SetBranchAddress("dssdTRaw",dssdTRaw);
                        inputTree->SetBranchAddress("dssdQPed",dssdQPed);
                        inputTree->SetBranchAddress("RefTime1",&RefTime1);
                        inputTree->SetBranchAddress("RefTime2",&RefTime2);
                        inputTree->SetBranchAddress("csiQRaw",csiQRaw);
                        inputTree->SetBranchAddress("csiTRaw",csiTRaw);
                        inputTree->SetBranchAddress("csiQPed",csiQPed);
                        inputTree->SetBranchAddress("dssdTHit",&dssdTHit);
                        inputTree->SetBranchAddress("dssdTHitSide",dssdTHitSide);
                        inputTree->SetBranchAddress("dssdTHitStripId",dssdTHitStripId);
                        inputTree->SetBranchAddress("dssdTHitTCal",dssdTHitTCal);
                        inputTree->SetBranchAddress("csiTHit",&csiTHit);
                        inputTree->SetBranchAddress("csiTHitId",csiTHitId);
                        inputTree->SetBranchAddress("csiTHitTCal",csiTHitTCal);
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

			inputTree->SetBranchAddress("teleSide",&teleSide);
			inputTree->SetBranchAddress("teleCsiId",&teleCsiId);
			inputTree->SetBranchAddress("teleDssdFid",&teleDssdFid);
			inputTree->SetBranchAddress("teleDssdBid",&teleDssdBid);
			inputTree->SetBranchAddress("teleCsiQPed",&teleCsiQPed);
			inputTree->SetBranchAddress("teleDssdFQPed",&teleDssdFQPed);
			inputTree->SetBranchAddress("teleDssdBQPed",&teleDssdBQPed);
			inputTree->SetBranchAddress("teleCsiE",&teleCsiE);
			inputTree->SetBranchAddress("teleDssdFE",&teleDssdFE);
			inputTree->SetBranchAddress("teleDssdBE",&teleDssdBE);
			inputTree->SetBranchAddress("teleDssdE",&teleDssdE);
			inputTree->SetBranchAddress("teleDssdMaxE",&teleDssdMaxE);
			inputTree->SetBranchAddress("teleCsiT",&teleCsiT);
			inputTree->SetBranchAddress("teleDssdT",&teleDssdT);
			inputTree->SetBranchAddress("teleEnergy",&teleEnergy);
			inputTree->SetBranchAddress("teleAngle",&teleAngle);
			inputTree->SetBranchAddress("teleLocusAngle",&teleLocusAngle);

			inputTree->SetBranchAddress("telePhi",&telePhi);
			inputTree->SetBranchAddress("fdc0Phi",&fdc0Phi);
			inputTree->SetBranchAddress("espriPhi",&espriPhi);

			inputTree->SetBranchAddress("protonEnergy",&protonEnergy);
			inputTree->SetBranchAddress("beamEnergy",&beamEnergy);
			inputTree->SetBranchAddress("beamBeta",&beamBeta);
			inputTree->SetBranchAddress("tofSBTTarget",&tofSBTTarget);

			inputTree->SetBranchAddress("alphaEnergy",&alphaEnergy);
			inputTree->SetBranchAddress("vTele",&vTele);


			inputTree->SetBranchAddress("degraderThickness",&degraderThickness);
			inputTree->SetBranchAddress("ppDegraderE",&ppDegraderE);
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

		void setGeneralBranch(TTree *tree){
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

		}
		void setDetectorBranch(TTree *tree){
			// Plas  
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

			tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
			tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[2][32]/I");

			tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
			tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");

			tree->Branch("plasTdcRaw0",&plasTdcRaw0);
			tree->Branch("plasTdcRaw1",&plasTdcRaw1);
			tree->Branch("plasTdcRaw2",&plasTdcRaw2);
			tree->Branch("plasTdcRaw3",&plasTdcRaw3);
			tree->Branch("rdcTdc",&rdcTdc);
			tree->Branch("rdcPlaneId",&rdcPlaneId);
			tree->Branch("rdcWireId",&rdcWireId);
			tree->Branch("rdcPlaneNHit",&rdcPlaneNHit);
			tree->Branch("naiQRaw",naiQRaw,"naiQRaw[4][7]/I");
			tree->Branch("plasQRaw",plasQRaw,"plasQRaw[4]/I");
			tree->Branch("plasTRaw",plasTRaw,"plasTRaw[4]/I");
			tree->Branch("plasTimeRef",&plasTimeRef);
			tree->Branch("rdcX",rdcX,"rdcX[2]/D");
			tree->Branch("rdcY",rdcY,"rdcY[2]/D");
			tree->Branch("rdcA",rdcA,"rdcA[2]/D");
			tree->Branch("rdcB",rdcB,"rdcB[2]/D");
			tree->Branch("rdcChi2",rdcChi2,"rdcChi2[2]/D");
			tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
			tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
			tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");

			tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
			tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");

			tree->Branch("rdcHit",&rdcHit,"rdcHit/I");
			tree->Branch("rdcHitSide",rdcHitSide,"rdcHitSide[rdcHit]/I");

			tree->Branch("naiHit",&naiHit,"naiHit/I");
			tree->Branch("naiHitSide",naiHitSide,"naiHitSide[naiHit]/I");
			tree->Branch("naiHitBarId",naiHitBarId,"naiHitBarId[naiHit]/I");
			tree->Branch("plasHit",&plasHit,"plasHit/I");
			tree->Branch("plasHitSide",plasHitSide,"plasHitSide[plasHit]/I");
			tree->Branch("plasTHit",&plasTHit,"plasTHit/I");
			tree->Branch("plasQHit",&plasQHit,"plasQHit/I");
			tree->Branch("espriHit",&espriHit,"espriHit/I");
			tree->Branch("espriSide",&espriSide,"espriSide/I");
			tree->Branch("espriRdcX",&espriRdcX,"espriRdcX/D");
			tree->Branch("espriRdcY",&espriRdcY,"espriRdcY/D");
			tree->Branch("espriPlasQPed",&espriPlasQPed,"espriPlasQPed/D");
			tree->Branch("espriNaiBarId",&espriNaiBarId,"espriNaiBarId/I");
			tree->Branch("espriNaiQPed",&espriNaiQPed,"espriNaiQPed/D");

			tree->Branch("ppDegraderE",&ppDegraderE,"ppDegraderE/D");
			tree->Branch("degraderThickness",&degraderThickness,"degraderThickness/D");
			tree->Branch("ppPlasE",&ppPlasE,"ppPlasE/D");
			tree->Branch("ppWinE",&ppWinE,"ppWinE/D");
			tree->Branch("ppShtE",&ppShtE,"ppShtE/D");


			tree->Branch("apWinE",&apWinE,"apWinE/D");
			tree->Branch("apDssdE",&apDssdE,"apDssdE/D");
			tree->Branch("apDegraderE",&apDegraderE,"apDegraderE/D");


			tree->Branch("hodQRaw",hodQRaw,"hodQRaw[2][40]/I");
			tree->Branch("hodQPed",hodQPed,"hodQPed[2][40]/D");
			tree->Branch("hodTCal",hodTCal,"hodTCal[2][40]/D");
			tree->Branch("hodQCal",hodQCal,"hodQCal[2][40]/D");
			tree->Branch("hodBarTCal",hodBarTCal,"hodBarTCal[40]/D");

		}
		void setBranch(TTree *tree){

			setGeneralBranch(tree);
			setDetectorBranch(tree);
			tree->Branch("TOF37",&TOF37);
			tree->Branch("Beta37",&Beta37);
			tree->Branch("Gamma37",&Gamma37);
			tree->Branch("Ek37",&Ek37);
			tree->Branch("TOF713",&TOF713);
			tree->Branch("Beta713",&Beta713);
			tree->Branch("Gamma713",&Gamma713);
			tree->Branch("Ek713",&Ek713);
			tree->Branch("beamFL",&beamFL);
			tree->Branch("vBeam",&vBeam);
			tree->Branch("bdc1Position",&bdc1Position);
			tree->Branch("bdc2Position",&bdc2Position);
			tree->Branch("targetPosition",&targetPosition);
			tree->Branch("sbtPosition",&sbtPosition);
			tree->Branch("fdc0Angle",&fdc0Angle);
			tree->Branch("fdc0Position",&fdc0Position);
			tree->Branch("vFDC0",&vFDC0);


			tree->Branch("hodNHit",&hodNHit,"hodNHit/I");
			tree->Branch("hodID",hodID,"hodID[40]/I");
			tree->Branch("hodTRaw",hodTRaw,"hodTRaw[2][40]/I");
			tree->Branch("hodBarQCal",hodBarQCal,"hodBarQCal[40]/D");
			tree->Branch("hodQHit",&hodQHit,"hodQHit/I");
                        tree->Branch("hodQHitId",hodQHitId,"hodQHitId[hodQHit]/I");
                        tree->Branch("hodQHitQSyn",hodQHitQSyn,"hodQHitQSyn[hodQHit]/D");
                        tree->Branch("hodTHit",&hodTHit,"hodTHit/I");
                        tree->Branch("hodTHitId",hodTHitId,"hodTHitId[hodTHit]/I");
                        tree->Branch("hodTHitTSyn",hodTHitTSyn,"hodTHitTSyn[hodTHit]/D");
                        tree->Branch("hodHit",&hodHit,"hodHit/I");
                        tree->Branch("hodHitId",hodHitId,"hodHitId[hodHit]/I");
                        tree->Branch("hodHitT",hodHitT,"hodHitT[hodHit]/D");
                        tree->Branch("hodHitQ",hodHitQ,"hodHitQ[hodHit]/D");


			tree->Branch("espriPlasE",&espriPlasE);
			tree->Branch("espriPlasT",&espriPlasT);
			tree->Branch("espriNaiE",&espriNaiE);
			tree->Branch("vESPRI",&vESPRI);
			tree->Branch("espriRdcPosition",&espriRdcPosition);
			tree->Branch("espriPlasPosition",&espriPlasPosition);
			tree->Branch("espriFL",&espriFL);
			tree->Branch("espriLocusAngle",&espriLocusAngle);
			tree->Branch("espriAngle",&espriAngle);
			tree->Branch("espriPosition",&espriPosition);

                        tree->Branch("dssdQRaw",dssdQRaw,"dssdQRaw[4][32]/I");
                        tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[2][32]/I");
                        tree->Branch("dssdQPed",dssdQPed,"dssdQPed[4][32]/D");
                        tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
                        tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
                        tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
                        tree->Branch("RefTime1",&RefTime1);
                        tree->Branch("RefTime2",&RefTime2);
			tree->Branch("dssdTHit",&dssdTHit,"dssdTHit/I");
                        tree->Branch("dssdTHitSide",dssdTHitSide,"dssdTHitSide[dssdTHit]/I");
                        tree->Branch("dssdTHitStripId",dssdTHitStripId,"dssdTHitStripId[dssdTHit]/I");
                        tree->Branch("dssdTHitTCal",dssdTHitTCal,"dssdTHitTCal[dssdTHit]/D");
                        tree->Branch("csiTHit",&csiTHit,"csiTHit/I");
                        tree->Branch("csiTHitId",csiTHitId,"csiTHitId[csiTHit]/I");
                        tree->Branch("csiTHitTCal",csiTHitTCal,"csiTHitTCal[csiTHit]/D");

			tree->Branch("teleHit",&teleHit,"teleHit/I");
                        tree->Branch("teleHitSide",&teleHitSide,"teleHitSide[teleHit]/I");
                        tree->Branch("teleHitFid",&teleHitFid,"teleHitFid[teleHit]/I");
                        tree->Branch("teleHitBid",&teleHitBid,"teleHitBid[teleHit]/I");
                        tree->Branch("teleHitDssdFQPed",&teleHitDssdFQPed,"teleHitDssdFQPed[teleHit]/D");
                        tree->Branch("teleHitDssdBQPed",&teleHitDssdBQPed,"teleHitDssdBQPed[teleHit]/D");
                        tree->Branch("teleHitDssdTCal",&teleHitDssdTCal,"teleHitDssdTCal[teleHit]/D");
                        tree->Branch("teleHitCid",&teleHitCid,"teleHitCid[teleHit]/I");
                        tree->Branch("teleHitCsiQPed",&teleHitCsiQPed,"teleHitCsiQPed[teleHit]/D");
                        tree->Branch("teleHitCsiTCal",&teleHitCsiTCal,"teleHitCsiTCal[teleHit]/D");
                        tree->Branch("teleHitDssdFE",&teleHitDssdFE,"teleHitDssdFE[teleHit]/D");
                        tree->Branch("teleHitDssdBE",&teleHitDssdBE,"teleHitDssdBE[teleHit]/D");
                        tree->Branch("teleHitCsiE",&teleHitCsiE,"teleHitCsiE[teleHit]/D");
                        tree->Branch("bestHit",&bestHit,"bestHit/I");

			tree->Branch("teleSide",&teleSide,"teleSide/I");
			tree->Branch("teleCsiId",&teleCsiId,"teleCsiId/I");
                        tree->Branch("teleDssdFid",&teleDssdFid,"teleDssdFid/I");
                        tree->Branch("teleDssdBid",&teleDssdBid,"teleDssdBid/I");
                        tree->Branch("teleCsiQPed",&teleCsiQPed,"teleCsiQPed/D");
                        tree->Branch("teleDssdFQPed",&teleDssdFQPed,"teleDssdFQPed/D");
                        tree->Branch("teleDssdBQPed",&teleDssdBQPed,"teleDssdBQPed/D");
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
			tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE/D");
			tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE/D");
			tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
			tree->Branch("teleDssdMaxE",&teleDssdMaxE,"teleDssdMaxE/D");
			tree->Branch("teleCsiT",&teleCsiT,"teleCsiT/D");
			tree->Branch("teleDssdT",&teleDssdT,"teleDssdT/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("teleAngle",&teleAngle,"teleAngle/D");
			tree->Branch("teleLocusAngle",&teleLocusAngle,"teleLocusAngle/D");
			tree->Branch("telePosition","TVector3",&telePosition);

			tree->Branch("telePhi",&telePhi,"telePhi/D");
			tree->Branch("espriPhi",&espriPhi,"espriPhi/D");
			tree->Branch("fdc0Phi",&fdc0Phi,"fdc0Phi/D");

			tree->Branch("protonEnergy",&protonEnergy);
			tree->Branch("beamEnergy",&beamEnergy);
			tree->Branch("beamBeta",&beamBeta);
			tree->Branch("tofSBTTarget",&tofSBTTarget);


			tree->Branch("alphaEnergy",&alphaEnergy,"alphaEnergy/D");
			tree->Branch("vTele","TVector3",&vTele);


		}
		double getProtonEnergy(){
			return protonEnergy;
		}
		double getAlphaEnergy(){
			return alphaEnergy;
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
		double getF13T(){
			return F13T;
		}
		double getF13Q(){
			return F13Q;
		}
		int getTrigESPRI(){
			return Trig_BxESPRI;
		}
		double getEspriNaiE(){
			return espriNaiE;
		}
		double getEspriToF(){
			return espriPlasT;
		}
		bool isEspriRDCHit(){
			return (espriAngle>0);
		}
		bool isEspriPlasTime(){
			return (espriPlasT>0)||(plasTRaw[0]!=-9999)||(plasTRaw[2]!=-9999);
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
		double getPlasQ_Birks(){
			//return plasHitQPed[0];
			return espriPlasE_Birks;
		}
		double getTeleCsiE(){
			return teleCsiE;
		}
		double getTeleDssdE(){
			return teleDssdFE; 
		}
		TVector3 * getTelePosition(){
			return telePosition;
		}
		TVector3 * getEspriPosition(){
			return espriPosition;
		}
		TVector3 * getFdc0Position(){
			return fdc0Position;
		}

		TVector3 * getBeamDirection(){
			return vBeam;
		}
		double getBeamEnergy(){
			return beamEnergy;
		}
		TVector3 * getTargetPosition(){
			return targetPosition;
		}

		double getTargetX(){
			return targetPosition->X();
		}
		double getTargetY(){
			return targetPosition->Y();
		}
		double getResAngle(){
			return fdc0Angle;
		}
		double getFdc0Angle(){
			return fdc0Angle;
		}
		double getFdc0Phi(){
			return fdc0Phi;
		}
		double getEspriLocusAngle(){
			return espriLocusAngle;
		}
		double getEspriPhi(){
			return espriPhi;
		}
		double getEspriAngle(){
			return espriAngle;
		}
		bool getTrigTele(){
			return (Trig_BxESPRIxTEL>0)||(Trig_BxTEL>0);
		}

		int getTeleHit(){
			return teleHit;
		}
		//int getTeleSide(){
		//	return teleHitSide[0];
		//}
		//double  getTeleDssdFQPed(){
		//	return teleHitDssdFQPed[0];
		//}
		//double getTeleDssdBQPed(){
		//	return teleHitDssdBQPed[0];
		//}
		//int getTeleDssdFid(){
		//	return teleHitFid[0];
		//}
		//int getTeleDssdBid(){
		//	return teleHitBid[0];
		//}

		double getTeleAngle(){
			return teleAngle;
		}
		double getTelePhi(){
			return telePhi;
		}
		double getHodBarTRaw(int id){
			return 0.5*(hodTRaw[0][id]+hodTRaw[1][id]);
		}
		double getHodBarQRaw(int id){
			return hodBarQCal[id];
		}
		int getEspriSide(){
			return espriSide;
		}
		double getNaiQPed(){
			return espriNaiQPed;
		}
		int getNaiId(){
			return espriNaiBarId;
		}
		double getRdcX(){
			return espriRdcX;
		}
		double getRdcY(){
			return espriRdcY;
		}

		bool isPALR(){
			if((espriHit==1&&espriSide==0&&teleHit==1&&teleHitSide[0]==1)||(espriHit==1&&espriSide==1&&teleHit==1&&teleHitSide[0]==0)) return true;
			else return false;
		}
		int getTrigDSB(){
			return Trig_DSB;
		}
		int getRunNumber(){
			return RunNumber;
		}
		double getHodBarQCal(int i){
			return hodBarQCal[i];
		}
		int getHodQHit(){
			return hodQHit;
			//int hQHit = 0;
			//for (int i = 0; i < 39; ++i) {
			//	if(hodBarQCal[i]>50&&hodBarQCal[i+1]>50) { hQHit+=2; }	
			//}
			////cout<<hQHit<<endl;
			//return hQHit;
		}
		int getHodTHit(){
			return hodTHit;
			//int hTHit = 0;
			//for (int i = 0; i < 39; ++i) {
			//	if(hodBarTCal[i]>0&&hodBarTCal[i+1]>0) {hTHit+=2;}
			//}
			////cout<<hTHit<<endl;
			//return hTHit;
		}
		int getHodHit(){
			return hodHit;
		}
		int getHodHitId(int i){
			return hodHitId[i];
		}

};
