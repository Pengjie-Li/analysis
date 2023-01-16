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
		MaterialDetector  *Target;
		MaterialDetector  *buildedTarget;
		BeamGenerator *buildedBeam;

		EventBuilder(){
			env = new TEnv("configDetector.prm");
			beam =new BeamGenerator();

			//TVector3 beam0 = beam->getBeamVector();
			//beam->printDirect();
			BDC1 =new BDC1Detector(beam);
			//beam->printDirect();
			BDC2 =new BDC2Detector(beam);
			//TVector3 beam1 = beam->getBeamVector();
			//beam->printDirect();

			dumpExitWindow	 = new MaterialDetector(4525.34);
			sbvWrapping	 = new MaterialDetector(4417.34);
			shtEntrance	 = new MaterialDetector(4347.34);
			shtExit		 = new MaterialDetector(4097.34);
			degrader	 = new MaterialDetector(3920);

			addAngularStraggling();

			Target =new MaterialDetector(beam,4222.34);
			reconstruct();
			//printEvent();

		}
		void addAngularStraggling(){
			if(env->GetValue("isDumpExitWindowAddAng",false))	dumpExitWindow->addAngularStraggling(beam,0.21064);

			//beam->printDirect();
			if(env->GetValue("isSBVWrappingAddAng",false))		sbvWrapping->addAngularStraggling(beam,0.166339);
			if(env->GetValue("isSHTEntranceAddAng",false))		shtEntrance->addAngularStraggling(beam,0.16314);
			if(env->GetValue("isSHTExitAddAng",false))		shtExit->addAngularStraggling(beam,0.16314);
			if(env->GetValue("isDegraderAddAng",false))		degrader->addAngularStraggling(beam,6.04);
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
			
			buildedTarget =new MaterialDetector(buildedBeam,4222.34);
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
			Target = NULL;
			buildedBeam = NULL;
			buildedTarget = NULL;
	
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
			delete Target;
			delete buildedBeam;
			delete buildedTarget;
		}

		void printEvent(){

			cout<<"########After Construction#################"<<endl;
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
			cout<<"Target:"<<endl;
			Target->printPosition();
			cout<<"Builded Target:"<<endl;
			buildedTarget->printPosition();
	
		}
		BDC1Detector * getBDC1Detector(){
			return BDC1;
		}
		BDC2Detector * getBDC2Detector(){
			return BDC2;
		}
		MaterialDetector * getTargetDetector(){
			return Target;
		}
		MaterialDetector * getBuildedTargetDetector(){
			return buildedTarget;
		}

};
