class EventBuilder{
	private:
	public:

		TEnv *env;
		bool isAddResolution;
		BeamGenerator *beam ;
		BDC1Detector  *BDC1 ;
		BDC2Detector  *BDC2 ;
		MaterialDetector *degrader;
		MaterialDetector *dumpExitWindow;
		MaterialDetector *sbvWrapping;
		MaterialDetector *shtEntrance;
		MaterialDetector *shtExit;
		DSSDDetector  *DSSD;
		DSSDDetector  *buildedDSSD;
		BeamGenerator *buildedBeam;

		EventBuilder(){
			env = new TEnv("configDetector.prm");
			beam =new BeamGenerator();
			BDC1 =new BDC1Detector(beam);
			BDC2 =new BDC2Detector(beam);

			dumpExitWindow	 = new MaterialDetector(beam, 4525.34);
			sbvWrapping	 = new MaterialDetector(beam, 4417.34);
			shtEntrance	 = new MaterialDetector(beam, 4347.34);
			shtExit		 = new MaterialDetector(beam, 4097.34);
			degrader	 = new MaterialDetector(beam,3920);

			addAngularStraggling();

			DSSD =new DSSDDetector(beam);
			reconstruct();
			//printEvent();

		}
		void addAngularStraggling(){
			if(env->GetValue("isDumpExitWindowAddAng",false))	dumpExitWindow->addAngularStraggling(beam,0.35524);
			if(env->GetValue("isSBVWrappingAddAng",false))		sbvWrapping->addAngularStraggling(beam,0.28053);
			if(env->GetValue("isSHTEntranceAddAng",false))		shtEntrance->addAngularStraggling(beam,0.27514);
			if(env->GetValue("isSHTExitAddAng",false))		shtExit->addAngularStraggling(beam,0.27514);
			if(env->GetValue("isDegraderAddAng",false))		degrader->addAngularStraggling(beam,10);
		}
		~EventBuilder(){
			clearMemory();
			pointerNull();
		}
		void reconstruct(){
			TVector3 direct;
			direct.SetXYZ(BDC2->getX()-BDC1->getX(),BDC2->getY()-BDC1->getY(),BDC2->getZ()-BDC1->getZ());
			direct = direct.Unit();
			buildedBeam =new BeamGenerator();
			buildedBeam->setPointX(BDC1->getX());
			buildedBeam->setPointY(BDC1->getY());
			buildedBeam->setPointZ(BDC1->getZ());
			buildedBeam->setDirect(direct);
			
			buildedDSSD =new DSSDDetector(buildedBeam);
		}
		void pointerNull(){
			env = NULL;
			beam = NULL;
			BDC1 = NULL;
			BDC2 = NULL;
			dumpExitWindow	 =  NULL;
			sbvWrapping	 =  NULL;
			shtEntrance	 =  NULL;
			shtExit		 =  NULL;
			degrader = NULL;
			DSSD = NULL;
			buildedBeam = NULL;
			buildedDSSD = NULL;
	
		}
		void clearMemory(){
			delete env;
			delete beam;
			delete BDC1;
			delete BDC2;
			delete dumpExitWindow	;
			delete sbvWrapping	;
			delete shtEntrance	;
			delete shtExit		;
			delete degrader;
			delete DSSD;
			delete buildedBeam;
			delete buildedDSSD;
		}

		void printEvent(){

			cout<<"#########################"<<endl;
			cout<<"Beam:"<<endl;
			beam->printPoint();
			beam->printDirect();
			cout<<"BDC1:"<<endl;
			BDC1->printPosition();
			cout<<"BDC2:"<<endl;
			BDC2->printPosition();
			cout<<"dumpExitWindow:"<<endl;
			dumpExitWindow->printPosition();
			cout<<"sbvWrapping:"<<endl;
			sbvWrapping->printPosition();
			cout<<"shtEntrance:"<<endl;
			shtEntrance->printPosition();
			cout<<"shtExit:"<<endl;
			shtExit->printPosition();
			cout<<"Degrader:"<<endl;
			degrader->printPosition();
			cout<<"DSSD:"<<endl;
			DSSD->printDSSD();
			cout<<"Builded DSSD:"<<endl;
			buildedDSSD->printDSSD();
	
		}
		BDC1Detector * getBDC1Detector(){
			return BDC1;
		}
		BDC2Detector * getBDC2Detector(){
			return BDC2;
		}
		DSSDDetector * getDSSDDetector(){
			return DSSD;
		}
		DSSDDetector * getBuildedDSSDDetector(){
			return buildedDSSD;
		}

};
