
class EventSimulator{
	public : 
		int nEvent;

		TFile *outputFile;
		TTree *tree;
		// SetBranch variables

		double exEnergy;

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

			r.SetSeed(0);
			for(int i=0;i<nEvent;i++){
				pg->generateEvent();
				EventBuilder *eb=new EventBuilder();
				if(nEvent<100){
					pg->print();
					eb->printEvent();
				}

				exEnergy = eb->getExEnergy();

				tree->Fill();
				delete eb;
				if(i%10000 ==0) cout<<i<<endl;

			}

		}


		void createFile(){
			TEnv *env = new TEnv("configDetector.prm");	

			double sigmaProtonEnergy = env->GetValue("sigmaProtonEnergy",0.);
			double sigmaProtonAngle = env->GetValue("sigmaProtonAngle",0.);

			//outputFile=new TFile(Form("./rootfiles/tDSSDPixelByBDC%4.2f_%4.2f_%4.2f_%4.2f.root",xBDC1Sigma,xBDC2Sigma,angBDC1Sigma,angBDC2Sigma),"recreate");
			outputFile=new TFile(Form("./rootfiles/exPPBe14_%4.3f_%4.3f.root",sigmaProtonEnergy,sigmaProtonAngle),"recreate");
			tree=new TTree("tree","tree");
			delete env;
			env = NULL;
		}
		void setBranch(){
			tree->Branch("exEnergy",&exEnergy,"exEnergy/D");
			pg->setBranch(tree);
		}

		void saveFile(){
			tree->Write();
		//	outputFile->Write();
			outputFile->Close();
		}


};
