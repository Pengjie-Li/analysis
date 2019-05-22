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


		Double_t Target_X;
		Double_t Target_Y;


		Double_t vTarget_X;
		Double_t vTarget_Y;


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
				r.SetSeed(0);
				EventBuilder *eb=new EventBuilder();
				if(nEvent<100) eb->printEvent();
				BDC1Detector *BDC1 = eb->getBDC1Detector();
				BDC2Detector *BDC2 = eb->getBDC2Detector();
				MaterialDetector *Target = eb->getTargetDetector();
				MaterialDetector *buildedTarget = eb->getBuildedTargetDetector();

				setBDC1Position(BDC1);
				setBDC2Position(BDC2);
				setTarget(Target);
				setBuildedTarget(buildedTarget);

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

		void setTarget(MaterialDetector *Target){
			vTarget_X=Target->getVirtualX();
			vTarget_Y=Target->getVirtualY();
		}
		void setBuildedTarget(MaterialDetector *buildedTarget){
			Target_X=buildedTarget->getVirtualX();
			Target_Y=buildedTarget->getVirtualY();
		}



		void createFile(){
			TEnv *env = new TEnv("configDetector.prm");	
			bool isBDC1AddPositionResolution = env ->GetValue("isBDC1Add",false);
			bool isBDC1AddAngularStraggling = env ->GetValue("isBDC1AddAng",false);

			double xBDC1Sigma = -1;
			if(isBDC1AddPositionResolution) xBDC1Sigma = env->GetValue("xBDC1Sigma",-1.);

			double angBDC1Sigma = -1;
			if(isBDC1AddAngularStraggling) angBDC1Sigma = env->GetValue("angBDC1Sigma",0.);

			bool isBDC2AddPositionResolution = env ->GetValue("isBDC2Add",false);
			bool isBDC2AddAngularStraggling = env ->GetValue("isBDC2AddAng",false);

			double xBDC2Sigma = -1;
			if(isBDC2AddPositionResolution) xBDC2Sigma = env->GetValue("xBDC2Sigma",-1.);

			double angBDC2Sigma = -1;
			if(isBDC2AddAngularStraggling) angBDC2Sigma = env->GetValue("angBDC2Sigma",0.);
	
			bool isDegrederAddAng = env->GetValue("isDegrederAddAng",false);
	
			//cout<<BDC1Reso<<" "<<BDC2Reso<<endl;
			//outputFile=new TFile(Form("./rootfiles/DSSDPixelByBDC%4.2f_%4.2f_%4.2f_%4.2f.root",xBDC1Sigma,xBDC2Sigma,angBDC1Sigma,angBDC2Sigma),"recreate");
			if(isDegrederAddAng) outputFile=new TFile(Form("./rootfiles/tDSSDPixelByBDC%4.2f_%4.2f_%4.2f_%4.2f_AddDegrader.root",xBDC1Sigma,xBDC2Sigma,angBDC1Sigma,angBDC2Sigma),"recreate");
			else outputFile=new TFile(Form("./rootfiles/tDSSDPixelByBDC%4.2f_%4.2f_%4.2f_%4.2f.root",xBDC1Sigma,xBDC2Sigma,angBDC1Sigma,angBDC2Sigma),"recreate");
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

			tree->Branch("Target_X",&Target_X,"Target_X/D");
			tree->Branch("Target_Y",&Target_Y,"Target_Y/D");

			tree->Branch("vTarget_X",&vTarget_X,"vTarget_X/D");
			tree->Branch("vTarget_Y",&vTarget_Y,"vTarget_Y/D");


		}

		void saveFile(){
			tree->Write();
		//	outputFile->Write();
			outputFile->Close();
		}


};
