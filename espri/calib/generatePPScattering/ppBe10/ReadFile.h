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
		Int_t           dssdTRaw[4][32];
		Double_t        dssdQScm[4][32];
		Double_t        dssdQCal[4][32];
		Double_t        dssdTCal[4][32];
		Int_t           csiQRaw[7];
		Int_t           csiTRaw[7];
		Double_t        csiQPed[7];
		Double_t        csiQSync[7];
		Double_t        csiQCal[7];
		Double_t        csiTCal[7];
		Int_t           dssdNHit[4];
		Double_t        dssdSideQ[4];
		Int_t           dssdId[4];
		Int_t           csiNHit;
		Int_t           csiHitIdArray[7];
		Int_t           csiId;
		Int_t           dssdFid;
		Int_t           dssdBid;
		Double_t        teleDssdE;
		Double_t        teleCsiE;
		Double_t        teleEnergy;
		Double_t        teleAngle;

		Int_t           hodNHit;
		Int_t           hodID[40];
		Int_t           hodTRaw[2][40];
		Int_t           hodQRaw[2][40];
		Double_t        hodQPed[2][40];
		Double_t        hodTCal[2][40];
		Double_t        hodQCal[2][40];
		Double_t        hodBarTCal[40];
		Double_t        hodBarQCal[40];

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
		Int_t           rdcMult;
		Double_t        rdcX[2];
		Double_t        rdcY[2];
		Double_t        rdcA[2];
		Double_t        rdcB[2];
		Double_t        rdcChi2[2];
		Double_t        rdcDL[2][7];
		Double_t        rdcTch[2][7];
		Double_t        rdcRes[2][7];
		Double_t        naiQPed[4][7];
		Double_t        naiBarMQPed[2][7];
		Double_t        naiBarMQSync[2][7];
		Double_t        naiBarMQCal[2][7];
		Double_t        naiBarMSQCal[2][7];
		Double_t        naiBarQCal[2][7];
		Double_t        naiQ[2];
		Int_t           naiQId[2];
		Double_t        plasQCal[4];
		Double_t        plasQPed[4];
		Double_t        plasBarMQPed[4];
		Double_t        plasTCal[4];
		Double_t        plasMQ[2];
		Double_t        plasQ[2];
		Double_t        plasT[2];

		Double_t        espriFL;
		Double_t        espriAngle;
		Double_t        espriLocusAngle;
		Int_t           isEspriLR;
		Int_t           isEspriRdc;
		Int_t           isEspriPlas;
		Int_t           naiBarId;
		Int_t           naiNHit;
		Double_t        espriPlasE;
		Double_t        espriPlasT;
		Double_t        espriNaiE;
		Double_t        espriEnergy;




		TVector3* vBeam;
		TVector3* vBDC1;
		TVector3* vBDC2;
		TVector3* vTarget;
		TVector3* vSBT;
		TVector3* vESPRI;
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

			plasTdcRaw0	= 0;
			plasTdcRaw1	= 0;
			plasTdcRaw2	= 0;
			plasTdcRaw3	= 0;
			rdcTdc		= 0;
			rdcPlaneId	= 0;
			rdcWireId	= 0;
			rdcPlaneNHit	= 0;

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
			inputTree->SetBranchAddress("dssdQRaw",dssdQRaw);
			inputTree->SetBranchAddress("dssdTRaw",dssdTRaw);
			inputTree->SetBranchAddress("dssdQScm",dssdQScm);
			inputTree->SetBranchAddress("dssdQCal",dssdQCal);
			inputTree->SetBranchAddress("dssdTCal",dssdTCal);
			inputTree->SetBranchAddress("csiQRaw",csiQRaw);
			inputTree->SetBranchAddress("csiTRaw",csiTRaw);
			inputTree->SetBranchAddress("csiQPed",csiQPed);
			inputTree->SetBranchAddress("csiQSync",csiQSync);
			inputTree->SetBranchAddress("csiQCal",csiQCal);
			inputTree->SetBranchAddress("csiTCal",csiTCal);
			inputTree->SetBranchAddress("dssdNHit",dssdNHit);
			inputTree->SetBranchAddress("dssdSideQ",dssdSideQ);
			inputTree->SetBranchAddress("dssdId",dssdId);
			inputTree->SetBranchAddress("csiNHit",&csiNHit);
			inputTree->SetBranchAddress("csiHitIdArray",csiHitIdArray);
			inputTree->SetBranchAddress("csiId",&csiId);
			inputTree->SetBranchAddress("dssdFid",&dssdFid);
			inputTree->SetBranchAddress("dssdBid",&dssdBid);
			inputTree->SetBranchAddress("teleDssdE",&teleDssdE);
			inputTree->SetBranchAddress("teleCsiE",&teleCsiE);
			inputTree->SetBranchAddress("teleEnergy",&teleEnergy);
			inputTree->SetBranchAddress("teleAngle",&teleAngle);
			inputTree->SetBranchAddress("telePosition",&telePosition);
			inputTree->SetBranchAddress("hodNHit",&hodNHit);
			inputTree->SetBranchAddress("hodID",hodID);
			inputTree->SetBranchAddress("hodTRaw",hodTRaw);
			inputTree->SetBranchAddress("hodQRaw",hodQRaw);
			inputTree->SetBranchAddress("hodQPed",hodQPed);
			inputTree->SetBranchAddress("hodTCal",hodTCal);
			inputTree->SetBranchAddress("hodQCal",hodQCal);
			inputTree->SetBranchAddress("hodBarTCal",hodBarTCal);
			inputTree->SetBranchAddress("hodBarQCal",hodBarQCal);
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
			inputTree->SetBranchAddress("rdcMult",&rdcMult);
			inputTree->SetBranchAddress("rdcX",rdcX);
			inputTree->SetBranchAddress("rdcY",rdcY);
			inputTree->SetBranchAddress("rdcA",rdcA);
			inputTree->SetBranchAddress("rdcB",rdcB);
			inputTree->SetBranchAddress("rdcChi2",rdcChi2);
			inputTree->SetBranchAddress("rdcDL",rdcDL);
			inputTree->SetBranchAddress("rdcTch",rdcTch);
			inputTree->SetBranchAddress("rdcRes",rdcRes);
			inputTree->SetBranchAddress("naiQPed",naiQPed);
			inputTree->SetBranchAddress("naiBarMQPed",naiBarMQPed);
			inputTree->SetBranchAddress("naiBarMQSync",naiBarMQSync);
			inputTree->SetBranchAddress("naiBarMQCal",naiBarMQCal);
			inputTree->SetBranchAddress("naiBarMSQCal",naiBarMSQCal);
			inputTree->SetBranchAddress("naiBarQCal",naiBarQCal);
			inputTree->SetBranchAddress("naiQ",naiQ);
			inputTree->SetBranchAddress("naiQId",naiQId);
			inputTree->SetBranchAddress("plasQCal",plasQCal);
			inputTree->SetBranchAddress("plasQPed",plasQPed);
			inputTree->SetBranchAddress("plasBarMQPed",plasBarMQPed);
			inputTree->SetBranchAddress("plasTCal",plasTCal);
			inputTree->SetBranchAddress("plasMQ",plasMQ);
			inputTree->SetBranchAddress("plasQ",plasQ);
			inputTree->SetBranchAddress("plasT",plasT);
			inputTree->SetBranchAddress("vESPRI",&vESPRI);
			inputTree->SetBranchAddress("espriRdcPosition",&espriRdcPosition);
			inputTree->SetBranchAddress("espriPlasPosition",&espriPlasPosition);
			inputTree->SetBranchAddress("espriFL",&espriFL);
			inputTree->SetBranchAddress("espriAngle",&espriAngle);
			inputTree->SetBranchAddress("espriLocusAngle",&espriLocusAngle);
			inputTree->SetBranchAddress("isEspriLR",&isEspriLR);
			inputTree->SetBranchAddress("isEspriRdc",&isEspriRdc);
			inputTree->SetBranchAddress("isEspriPlas",&isEspriPlas);
			inputTree->SetBranchAddress("naiBarId",&naiBarId);
			inputTree->SetBranchAddress("naiNHit",&naiNHit);
			inputTree->SetBranchAddress("espriPlasE",&espriPlasE);
			inputTree->SetBranchAddress("espriPlasT",&espriPlasT);
			inputTree->SetBranchAddress("espriNaiE",&espriNaiE);
			inputTree->SetBranchAddress("espriEnergy",&espriEnergy);

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
                        tree->Branch("dssdTRaw",dssdTRaw,"dssdTRaw[4][32]/I");
                        tree->Branch("dssdQScm",dssdQScm,"dssdQScm[4][32]/D");
                        tree->Branch("dssdQCal",dssdQCal,"dssdQCal[4][32]/D");
                        tree->Branch("dssdTCal",dssdTCal,"dssdTCal[4][32]/D");

                        tree->Branch("csiQRaw",csiQRaw,"csiQRaw[7]/I");
                        tree->Branch("csiTRaw",csiTRaw,"csiTRaw[7]/I");
                        tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
                        tree->Branch("csiQSync",csiQSync,"csiQSync[7]/D");
                        tree->Branch("csiQCal",csiQCal,"csiQCal[7]/D");
                        tree->Branch("csiTCal",csiTCal,"csiTCal[7]/D");

			tree->Branch("dssdNHit",dssdNHit);
			tree->Branch("dssdSideQ",dssdSideQ);
			tree->Branch("dssdId",dssdId);
			tree->Branch("csiNHit",&csiNHit);
			tree->Branch("csiHitIdArray",csiHitIdArray);
			tree->Branch("csiId",&csiId);
			tree->Branch("dssdFid",&dssdFid);
			tree->Branch("dssdBid",&dssdBid);
			tree->Branch("teleDssdE",&teleDssdE);
			tree->Branch("teleCsiE",&teleCsiE);
			tree->Branch("teleEnergy",&teleEnergy);
			tree->Branch("teleAngle",&teleAngle);
			tree->Branch("telePosition",&telePosition);

                        tree->Branch("hodNHit",&hodNHit,"hodNHit/I");
                        tree->Branch("hodID",hodID,"hodID[40]/I");
                        tree->Branch("hodTRaw",hodTRaw,"hodTRaw[2][40]/I");
                        tree->Branch("hodQRaw",hodQRaw,"hodQRaw[2][40]/I");

                        tree->Branch("hodQPed",hodQPed,"hodQPed[2][40]/D");
                        tree->Branch("hodTCal",hodTCal,"hodTCal[2][40]/D");
                        tree->Branch("hodQCal",hodQCal,"hodQCal[2][40]/D");
                        tree->Branch("hodBarTCal",hodBarTCal,"hodBarTCal[40]/D");
                        tree->Branch("hodBarQCal",hodBarQCal,"hodBarQCal[40]/D");


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
                        tree->Branch("rdcMult",&rdcMult);
                        tree->Branch("rdcX",rdcX,"rdcX[2]/D");
                        tree->Branch("rdcY",rdcY,"rdcY[2]/D");
                        tree->Branch("rdcA",rdcA,"rdcA[2]/D");
                        tree->Branch("rdcB",rdcB,"rdcB[2]/D");
                        tree->Branch("rdcChi2",rdcChi2,"rdcChi2[2]/D");
                        tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
                        tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
                        tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");

                        tree->Branch("naiQPed", naiQPed, "naiQPed[4][7]/D");
                        tree->Branch("naiBarMQPed", naiBarMQPed, "naiBarMQPed[2][7]/D");
                        tree->Branch("naiBarMQSync", naiBarMQSync, "naiBarMQSync[2][7]/D");
                        tree->Branch("naiBarMQCal", naiBarMQCal, "naiBarMQCal[2][7]/D");
                        tree->Branch("naiBarMSQCal", naiBarMSQCal, "naiBarMSQCal[2][7]/D");
                        tree->Branch("naiBarQCal", naiBarQCal, "naiBarQCal[2][7]/D");
                        tree->Branch("naiQ", &naiQ, "naiQ[2]/D");
                        tree->Branch("naiQId", &naiQId, "naiQId[2]/I");

                        tree->Branch("plasQCal",plasQCal,"plasQCal[4]/D");
                        tree->Branch("plasQPed",plasQPed,"plasQPed[4]/D");
                        tree->Branch("plasBarMQPed",plasBarMQPed,"plasBarMQPed[4]/D");
                        tree->Branch("plasTCal",plasTCal,"plasTCal[4]/D");
                        tree->Branch("plasMQ",&plasMQ,"plasMQ[2]/D");
                        tree->Branch("plasQ",&plasQ,"plasQ[2]/D");
                        tree->Branch("plasT",&plasT,"plasT[2]/D");

			tree->Branch("vESPRI",&vESPRI);
			tree->Branch("espriRdcPosition",&espriRdcPosition);
			tree->Branch("espriPlasPosition",&espriPlasPosition);
			tree->Branch("espriFL",&espriFL);
			tree->Branch("espriAngle",&espriAngle);
			tree->Branch("espriLocusAngle",&espriLocusAngle);
			tree->Branch("isEspriLR",&isEspriLR);
			tree->Branch("isEspriRdc",&isEspriRdc);
			tree->Branch("isEspriPlas",&isEspriPlas);
			tree->Branch("naiBarId",&naiBarId);
			tree->Branch("naiNHit",&naiNHit);
			tree->Branch("espriPlasE",&espriPlasE);
			tree->Branch("espriPlasT",&espriPlasT);
			tree->Branch("espriNaiE",&espriNaiE);
			tree->Branch("espriEnergy",&espriEnergy);

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
		}
		double getEspriPlasE(){
			return espriPlasE;
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

};
