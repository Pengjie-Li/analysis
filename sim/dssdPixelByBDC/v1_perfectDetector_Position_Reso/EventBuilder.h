class EventBuilder{
	private:
	public:
		bool isAddResolution;
		BeamGenerator *beam ;
		BDC1Detector  *BDC1 ;
		BDC2Detector  *BDC2 ;
		DSSDDetector  *DSSD;
		DSSDDetector  *buildedDSSD;
		BeamGenerator *buildedBeam;

		EventBuilder(){
			beam =new BeamGenerator();
			BDC1 =new BDC1Detector(beam);
			BDC2 =new BDC2Detector(beam);
			DSSD =new DSSDDetector(beam);
			reconstruct();
			//printEvent();

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
			beam = NULL;
			BDC1 = NULL;
			BDC2 = NULL;
			DSSD = NULL;
			buildedBeam = NULL;
			buildedDSSD = NULL;
	
		}
		void clearMemory(){
			delete beam;
			delete BDC1;
			delete BDC2;
			delete DSSD;
			delete buildedBeam;
			delete buildedDSSD;
		}

		void printEvent(){

			cout<<"Beam:"<<endl;
			beam->printPoint();
			beam->printDirect();
			cout<<"BDC1:"<<endl;
			BDC1->printPosition();
			cout<<"BDC2:"<<endl;
			BDC2->printPosition();
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
