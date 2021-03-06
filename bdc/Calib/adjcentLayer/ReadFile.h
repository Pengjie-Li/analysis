class ReadFile{
	private:
		TChain *tree;
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
		vector<double>  BDC1_Track_dl;
		vector<double>  BDC1_Track_XY;
		vector<double>  BDC1_Track_Z;
		vector<double>  BDC1_Track_dXY;
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
		vector<double>  BDC2_Track_dl;
		vector<double>  BDC2_Track_XY;
		vector<double>  BDC2_Track_Z;
		vector<double>  BDC2_Track_dXY;
		Double_t        BDC2_X;
		Double_t        BDC2_Y;
		Double_t        BDC2_ThetaX;
		Double_t        BDC2_ThetaY;
		Double_t        flightLengthBeamTarget;
		Double_t        Target_X;
		Double_t        Target_Y;
		Double_t        Target_ThetaX;
		Double_t        Target_ThetaY;
		Int_t           FDC0_nhits;
		vector<double>  *FDC0_TDC;
		vector<double>  *FDC0_layerid;
		vector<double>  *FDC0_wireid;
		vector<int>     *FDC0_layer_hits;
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
		Int_t           hodNHit;
		Int_t           hodID[40];
		Int_t           hodTRaw[2][40];
		Int_t           hodQRaw[2][40];
		Double_t        hodQPed[2][40];
		Double_t        hodTCal[2][40];
		Double_t        hodQCal[2][40];
		Double_t        hodBarTCal[40];
		Double_t        hodBarQCal[40];
		Int_t           isLR;
		Int_t           isESPRIL;
		Int_t           isESPRIR;
		vector<int>     rdcTDC;
		vector<int>     rdcPlaneID;
		vector<int>     rdcWireID;
		vector<int>     rdcPlaneNHit;
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
		Double_t        naiQCal[4][7];
		Double_t        naiQPed[4][7];
		Double_t        naiBarQCal[2][7];
		Double_t        naiQ[2];
		Int_t           naiQId[2];
		Double_t        plasQCal[4];
		Double_t        plasQPed[4];
		Double_t        plasTCal[4];
		Double_t        plasQ[2];
		Double_t        plasT[2];
		Double_t        espriNaiEnergy;
		Double_t        espriPlasTime;
		Double_t        espriPlasDeltaE;
		Double_t        protonTheta;
		Double_t        flightLengthTargetESPRI;

		void initVector(){
			BDC1_TDC	= 0;
			BDC1_layerid	= 0;
			BDC1_wireid	= 0;
			BDC1_layer_hits	= 0;

		}
		void setBranch(){
			initVector();
			// Set branch addresses.
			tree->SetBranchAddress("RunNumber",&RunNumber);
			tree->SetBranchAddress("EventNumber",&EventNumber);
			tree->SetBranchAddress("CoincidenceTrigger",&CoincidenceTrigger);
			tree->SetBranchAddress("Trig_DSB",&Trig_DSB);
			tree->SetBranchAddress("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			tree->SetBranchAddress("Trig_BxESPRI",&Trig_BxESPRI);
			tree->SetBranchAddress("Trig_BxTEL",&Trig_BxTEL);
			tree->SetBranchAddress("Trig_BxHODP",&Trig_BxHODP);
			tree->SetBranchAddress("Trig_BxHODF",&Trig_BxHODF);
			tree->SetBranchAddress("Trig_BxNEBULA",&Trig_BxNEBULA);
			tree->SetBranchAddress("F3TRaw",F3TRaw);
			tree->SetBranchAddress("F3QRaw",F3QRaw);
			tree->SetBranchAddress("F3TCal",F3TCal);
			tree->SetBranchAddress("F3QCal",F3QCal);
			tree->SetBranchAddress("F3T",&F3T);
			tree->SetBranchAddress("F3Q",&F3Q);
			tree->SetBranchAddress("F7TRaw",F7TRaw);
			tree->SetBranchAddress("F7QRaw",F7QRaw);
			tree->SetBranchAddress("F7TCal",F7TCal);
			tree->SetBranchAddress("F7QCal",F7QCal);
			tree->SetBranchAddress("F7T",&F7T);
			tree->SetBranchAddress("F7Q",&F7Q);
			tree->SetBranchAddress("SBT1TRaw",SBT1TRaw);
			tree->SetBranchAddress("SBT1QRaw",SBT1QRaw);
			tree->SetBranchAddress("SBT1TCal",SBT1TCal);
			tree->SetBranchAddress("SBT1QCal",SBT1QCal);
			tree->SetBranchAddress("SBT1T",&SBT1T);
			tree->SetBranchAddress("SBT1Q",&SBT1Q);
			tree->SetBranchAddress("SBT2TRaw",SBT2TRaw);
			tree->SetBranchAddress("SBT2QRaw",SBT2QRaw);
			tree->SetBranchAddress("SBT2TCal",SBT2TCal);
			tree->SetBranchAddress("SBT2QCal",SBT2QCal);
			tree->SetBranchAddress("SBT2T",&SBT2T);
			tree->SetBranchAddress("SBT2Q",&SBT2Q);
			tree->SetBranchAddress("F13T",&F13T);
			tree->SetBranchAddress("F13Q",&F13Q);
			tree->SetBranchAddress("SBVTRaw",SBVTRaw);
			tree->SetBranchAddress("SBVQRaw",SBVQRaw);
			tree->SetBranchAddress("SBVTCal",SBVTCal);
			tree->SetBranchAddress("SBVQCal",SBVQCal);
			tree->SetBranchAddress("SBVT",&SBVT);
			tree->SetBranchAddress("SBVQ",&SBVQ);
			tree->SetBranchAddress("TOF37",&TOF37);
			tree->SetBranchAddress("Beta37",&Beta37);
			tree->SetBranchAddress("Gamma37",&Gamma37);
			tree->SetBranchAddress("Ek37",&Ek37);
			tree->SetBranchAddress("TOF713",&TOF713);
			tree->SetBranchAddress("Beta713",&Beta713);
			tree->SetBranchAddress("Gamma713",&Gamma713);
			tree->SetBranchAddress("Ek713",&Ek713);
			tree->SetBranchAddress("BDC1_nhits",&BDC1_nhits);
			tree->SetBranchAddress("BDC1_TDC",&BDC1_TDC);
			tree->SetBranchAddress("BDC1_layerid",&BDC1_layerid);
			tree->SetBranchAddress("BDC1_wireid",&BDC1_wireid);
			tree->SetBranchAddress("BDC1_layer_hits",&BDC1_layer_hits);
			tree->SetBranchAddress("BDC1_nlayerx",&BDC1_nlayerx);
			tree->SetBranchAddress("BDC1_nlayery",&BDC1_nlayery);
			tree->SetBranchAddress("BDC1_Track_dl",&BDC1_Track_dl);
			tree->SetBranchAddress("BDC1_Track_XY",&BDC1_Track_XY);
			tree->SetBranchAddress("BDC1_Track_Z",&BDC1_Track_Z);
			tree->SetBranchAddress("BDC1_Track_dXY",&BDC1_Track_dXY);
			tree->SetBranchAddress("BDC1_X",&BDC1_X);
			tree->SetBranchAddress("BDC1_Y",&BDC1_Y);
			tree->SetBranchAddress("BDC1_ThetaX",&BDC1_ThetaX);
			tree->SetBranchAddress("BDC1_ThetaY",&BDC1_ThetaY);
			tree->SetBranchAddress("BDC2_nhits",&BDC2_nhits);
			tree->SetBranchAddress("BDC2_TDC",&BDC2_TDC);
			tree->SetBranchAddress("BDC2_layerid",&BDC2_layerid);
			tree->SetBranchAddress("BDC2_wireid",&BDC2_wireid);
			tree->SetBranchAddress("BDC2_layer_hits",&BDC2_layer_hits);
			tree->SetBranchAddress("BDC2_nlayerx",&BDC2_nlayerx);
			tree->SetBranchAddress("BDC2_nlayery",&BDC2_nlayery);
			tree->SetBranchAddress("BDC2_Track_dl",&BDC2_Track_dl);
			tree->SetBranchAddress("BDC2_Track_XY",&BDC2_Track_XY);
			tree->SetBranchAddress("BDC2_Track_Z",&BDC2_Track_Z);
			tree->SetBranchAddress("BDC2_Track_dXY",&BDC2_Track_dXY);
			tree->SetBranchAddress("BDC2_X",&BDC2_X);
			tree->SetBranchAddress("BDC2_Y",&BDC2_Y);
			tree->SetBranchAddress("BDC2_ThetaX",&BDC2_ThetaX);
			tree->SetBranchAddress("BDC2_ThetaY",&BDC2_ThetaY);
			tree->SetBranchAddress("flightLengthBeamTarget",&flightLengthBeamTarget);
			tree->SetBranchAddress("Target_X",&Target_X);
			tree->SetBranchAddress("Target_Y",&Target_Y);
			tree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
			tree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);
			tree->SetBranchAddress("FDC0_nhits",&FDC0_nhits);
			tree->SetBranchAddress("FDC0_TDC",&FDC0_TDC);
			tree->SetBranchAddress("FDC0_layerid",&FDC0_layerid);
			tree->SetBranchAddress("FDC0_wireid",&FDC0_wireid);
			tree->SetBranchAddress("FDC0_layer_hits",&FDC0_layer_hits);
			tree->SetBranchAddress("FDC0_nlayerx",&FDC0_nlayerx);
			tree->SetBranchAddress("FDC0_nlayery",&FDC0_nlayery);
			tree->SetBranchAddress("FDC0_Track_dl",&FDC0_Track_dl);
			tree->SetBranchAddress("FDC0_Track_XY",&FDC0_Track_XY);
			tree->SetBranchAddress("FDC0_Track_Z",&FDC0_Track_Z);
			tree->SetBranchAddress("FDC0_Track_dXY",&FDC0_Track_dXY);
			tree->SetBranchAddress("FDC0_X",&FDC0_X);
			tree->SetBranchAddress("FDC0_Y",&FDC0_Y);
			tree->SetBranchAddress("FDC0_ThetaX",&FDC0_ThetaX);
			tree->SetBranchAddress("FDC0_ThetaY",&FDC0_ThetaY);
			tree->SetBranchAddress("dssdEnergyRaw",dssdEnergyRaw);
			tree->SetBranchAddress("dssdTimeRaw",dssdTimeRaw);
			tree->SetBranchAddress("dssdEnergyCal",dssdEnergyCal);
			tree->SetBranchAddress("dssdTimeCal",dssdTimeCal);
			tree->SetBranchAddress("csiEnergyRaw",csiEnergyRaw);
			tree->SetBranchAddress("csiTimeRaw",csiTimeRaw);
			tree->SetBranchAddress("csiEnergyCal",csiEnergyCal);
			tree->SetBranchAddress("csiTimeCal",csiTimeCal);
			tree->SetBranchAddress("multiplicity",multiplicity);
			tree->SetBranchAddress("hodNHit",&hodNHit);
			tree->SetBranchAddress("hodID",hodID);
			tree->SetBranchAddress("hodTRaw",hodTRaw);
			tree->SetBranchAddress("hodQRaw",hodQRaw);
			tree->SetBranchAddress("hodQPed",hodQPed);
			tree->SetBranchAddress("hodTCal",hodTCal);
			tree->SetBranchAddress("hodQCal",hodQCal);
			tree->SetBranchAddress("hodBarTCal",hodBarTCal);
			tree->SetBranchAddress("hodBarQCal",hodBarQCal);
			tree->SetBranchAddress("isLR",&isLR);
			tree->SetBranchAddress("isESPRIL",&isESPRIL);
			tree->SetBranchAddress("isESPRIR",&isESPRIR);
			tree->SetBranchAddress("rdcTDC",&rdcTDC);
			tree->SetBranchAddress("rdcPlaneID",&rdcPlaneID);
			tree->SetBranchAddress("rdcWireID",&rdcWireID);
			tree->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
			tree->SetBranchAddress("naiQRaw",naiQRaw);
			tree->SetBranchAddress("plasQRaw",plasQRaw);
			tree->SetBranchAddress("plasTRaw",plasTRaw);
			tree->SetBranchAddress("plasTimeRef",&plasTimeRef);
			tree->SetBranchAddress("rdcMult",&rdcMult);
			tree->SetBranchAddress("rdcX",rdcX);
			tree->SetBranchAddress("rdcY",rdcY);
			tree->SetBranchAddress("rdcA",rdcA);
			tree->SetBranchAddress("rdcB",rdcB);
			tree->SetBranchAddress("rdcChi2",rdcChi2);
			tree->SetBranchAddress("rdcDL",rdcDL);
			tree->SetBranchAddress("rdcTch",rdcTch);
			tree->SetBranchAddress("rdcRes",rdcRes);
			tree->SetBranchAddress("naiQCal",naiQCal);
			tree->SetBranchAddress("naiQPed",naiQPed);
			tree->SetBranchAddress("naiBarQCal",naiBarQCal);
			tree->SetBranchAddress("naiQ",naiQ);
			tree->SetBranchAddress("naiQId",naiQId);
			tree->SetBranchAddress("plasQCal",plasQCal);
			tree->SetBranchAddress("plasQPed",plasQPed);
			tree->SetBranchAddress("plasTCal",plasTCal);
			tree->SetBranchAddress("plasQ",plasQ);
			tree->SetBranchAddress("plasT",plasT);
			tree->SetBranchAddress("espriNaiEnergy",&espriNaiEnergy);
			tree->SetBranchAddress("espriPlasTime",&espriPlasTime);
			tree->SetBranchAddress("espriPlasDeltaE",&espriPlasDeltaE);
			tree->SetBranchAddress("protonTheta",&protonTheta);
			tree->SetBranchAddress("flightLengthTargetESPRI",&flightLengthTargetESPRI);
		}


	public:
		ReadFile(){

			tree = new TChain("tree");
		}
		~ReadFile(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i <= runStop; ++i) {

				//tree->Add(Form("mergerRootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("mergerRootfiles/run0%d_analysed.root",i));
			}
			//tree->Print();
			setBranch();

		}
		Long64_t getTotalEntries(){
			return tree->GetEntries();
		}
		void getEntry(Long64_t i){
			tree->GetEntry(i);
		}
		vector<double> * getBdc1Layer(){
			return BDC1_layerid;
		}
		vector<double> * getBdc1Tdc(){
			return BDC1_TDC;
		}
		vector<double> * getBdc2Layer(){
			return BDC2_layerid;
		}
		vector<double> * getBdc2Tdc(){
			return BDC2_TDC;
		}
		vector<double> * getFdc0Layer(){
			return FDC0_layerid;
		}
		vector<double> * getFdc0Tdc(){
			return FDC0_TDC;
		}

		void print(){
			printBDC1();
			printBDC2();
			printFDC0();
		//	printFDC2();
		}
		void printBDC1(){
			cout<<"BDC1"<<" total Hits:"<<BDC1_nhits<<endl;
			for (int i = 0; i < (int)BDC1_TDC->size(); ++i) {
				cout<< (*BDC1_layerid)[i]<<":"<<(*BDC1_wireid)[i]<<":"<<(*BDC1_TDC)[i]<<endl;
			}

		}
		void printBDC2(){
			cout<<"BDC2"<<" total Hits:"<<BDC2_nhits<<endl;
			for (int i = 0; i < (int)BDC2_TDC->size(); ++i) {
				cout<< (*BDC2_layerid)[i]<<":"<<(*BDC2_wireid)[i]<<":"<<(*BDC2_TDC)[i]<<endl;
			}

		}
		void printFDC0(){
			cout<<"FDC0"<<" total Hits:"<<FDC0_nhits<<endl;
			for (int i = 0; i < (int)FDC0_TDC->size(); ++i) {
				cout<< (*FDC0_layerid)[i]<<":"<<(*FDC0_wireid)[i]<<":"<<(*FDC0_TDC)[i]<<endl;
			}

		}

		bool goodGate(){
			//cout<<"Trig_DSB= "<<Trig_DSB<<endl;
			if(Trig_DSB) return true;
			else return false;
		}
		bool layerHitNoMoreThan2(vector<int> *layer_hits){
			for (int i = 0; i < (*layer_hits).size(); ++i) {
				if((*layer_hits)[i]>2) return false;
			}
			return true;
		}
		bool oneLayerOneHit(vector<int> *layer_hits){
			for (int i = 0; i < (*layer_hits).size(); ++i) {
				if((*layer_hits)[i]!=1) return false;
			}
			return true;
		}

		bool goodBdc1Gate(){
			//if(layerHitNoMoreThan2(BDC1_layer_hits)) cout<<"BDC1 true"<<endl;
			//if(layerHitNoMoreThan2(BDC1_layer_hits)) return true;
			if(oneLayerOneHit(BDC1_layer_hits)) return true;
			return false;
		}
		bool goodBdc2Gate(){

			//if(layerHitNoMoreThan2(BDC2_layer_hits)) cout<<"BDC2 true"<<endl;
			//if(layerHitNoMoreThan2(BDC2_layer_hits)) return true;
			if(oneLayerOneHit(BDC2_layer_hits)) return true;
			return false;
		}
		bool goodFdc0Gate(){
			//if(layerHitNoMoreThan2(FDC0_layer_hits)) cout<<"FDC 0 true"<<endl;
			//if(layerHitNoMoreThan2(FDC0_layer_hits)) return true;
			if(oneLayerOneHit(FDC0_layer_hits)) return true;
			return false;
		}

};
