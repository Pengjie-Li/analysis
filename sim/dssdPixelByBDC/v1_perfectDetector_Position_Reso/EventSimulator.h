class EventSimulator{
	public : 
		int nEvent;

		TFile *outputFile;
		TTree *tree;
		// SetBranch variables
		Double_t BDC1_X;
		Double_t BDC1_Y;

		Double_t BDC2_X;
		Double_t BDC2_Y;

		Double_t vBDC1_X;
		Double_t vBDC1_Y;

		Double_t vBDC2_X;
		Double_t vBDC2_Y;


		Double_t DSSD_X;
		Double_t DSSD_Y;


		Double_t vDSSD_X;
		Double_t vDSSD_Y;

		Int_t DSSD_Fid;
		Int_t DSSD_Bid;

		EventSimulator(){
		}
		EventSimulator(int nevt){
			nEvent=nevt;
			createFile();
			setBranch();
			lanchSimulatorLoop();
			saveFile();
		}
		void lanchSimulatorLoop(){
			for(int i=0;i<nEvent;i++){
				r.SetSeed(i);
				EventBuilder *eb=new EventBuilder();
				if(nEvent<100) eb->printEvent();
				BDC1Detector *BDC1 = eb->getBDC1Detector();
				BDC2Detector *BDC2 = eb->getBDC2Detector();
				DSSDDetector *DSSD = eb->getDSSDDetector();
				DSSDDetector *buildedDSSD = eb->getBuildedDSSDDetector();

				setBDC1Position(BDC1);
				setBDC2Position(BDC2);
				setDSSD(DSSD);
				setBuildedDSSD(buildedDSSD);

				tree->Fill();
				delete eb;
				if(i%10000 ==0) cout<<i<<endl;

			}

		}
		void setBDC1Position(BDC1Detector *BDC1){
			BDC1_X=BDC1->getX();
			BDC1_Y=BDC1->getY();
			vBDC1_X = BDC1->getVirtualX();
			vBDC1_Y = BDC1->getVirtualY();
		}
		void setBDC2Position(BDC2Detector *BDC2){
			BDC2_X=BDC2->getX();
			BDC2_Y=BDC2->getY();
			vBDC2_X = BDC2->getVirtualX();
			vBDC2_Y = BDC2->getVirtualY();
		}

		void setDSSD(DSSDDetector *DSSD){
			vDSSD_X=DSSD->getVirtualX();
			vDSSD_Y=DSSD->getVirtualY();
			DSSD_Fid = DSSD->getFrontStripId();
			DSSD_Bid = DSSD->getBackStripId();
		}
		void setBuildedDSSD(DSSDDetector *buildedDSSD){
			DSSD_X=buildedDSSD->getVirtualX();
			DSSD_Y=buildedDSSD->getVirtualY();
		}



		void createFile(){
			TEnv *env = new TEnv("configDetector.prm");	
			double BDC1Reso = env->GetValue("xBDC1Sigma",-1.);
			double BDC2Reso = env->GetValue("xBDC2Sigma",-1.);
			//cout<<BDC1Reso<<" "<<BDC2Reso<<endl;
			outputFile=new TFile(Form("./rootfiles/DSSDPixelByBDC%4.2f_%4.2f.root",BDC1Reso,BDC2Reso),"recreate");
			tree=new TTree("tree","tree");
			delete env;
			env = NULL;
		}
		void setBranch(){


			tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");

			tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");

			tree->Branch("vBDC1_X",&vBDC1_X,"vBDC1_X/D");
			tree->Branch("vBDC1_Y",&vBDC1_Y,"vBDC1_Y/D");

			tree->Branch("vBDC2_X",&vBDC2_X,"vBDC2_X/D");
			tree->Branch("vBDC2_Y",&vBDC2_Y,"vBDC2_Y/D");

			tree->Branch("DSSD_X",&DSSD_X,"DSSD_X/D");
			tree->Branch("DSSD_Y",&DSSD_Y,"DSSD_Y/D");

			tree->Branch("vDSSD_X",&vDSSD_X,"vDSSD_X/D");
			tree->Branch("vDSSD_Y",&vDSSD_Y,"vDSSD_Y/D");

			tree->Branch("DSSD_Fid",&DSSD_Fid,"DSSD_Fid/I");
			tree->Branch("DSSD_Bid",&DSSD_Bid,"DSSD_Bid/I");

		}

		void saveFile(){
			tree->Write();
		//	outputFile->Write();
			outputFile->Close();
		}


};
