class BdcEvent{
	private:

		Double_t BDC1_Z;
		Double_t BDC2_Z;
		Double_t Target_Z;
		Double_t SBT_Z;

		MergeBDC *mergeBDC;
		TVector3* vBeam;	
		TVector3* bdc1Position;	
		TVector3* bdc2Position;	
		TVector3* targetPosition;	
		TVector3* sbtPosition;	
		Double_t  beamFL;


		void init(){

			/********* BDC ***************/
			beamFL = NAN;

			bdc1Position->SetXYZ(NAN,NAN,NAN);
			bdc2Position->SetXYZ(NAN,NAN,NAN);
			targetPosition->SetXYZ(NAN,NAN,NAN);
			sbtPosition->SetXYZ(NAN,NAN,NAN);
			vBeam->SetXYZ(NAN,NAN,NAN);

		}
		Double_t getBDC1TargetRatio(){
			return (Target_Z-(*bdc1Position).Z())/(*vBeam).Z();
		}
		Double_t getBDC1SBTRatio(){
			return (SBT_Z-(*bdc1Position).Z())/(*vBeam).Z();
		}
		Double_t getBDC1X(){
			return mergeBDC->getBDC1X();
		}
		Double_t getBDC1Y(){
			return mergeBDC->getBDC1Y();
		}
		Double_t getBDC1Z(){
			return BDC1_Z;
		}
		Double_t getBDC2X(){
			return mergeBDC->getBDC2X();
		}
		Double_t getBDC2Y(){
			return mergeBDC->getBDC2Y();
		}
		Double_t getBDC2Z(){
			return BDC2_Z; 
		}


	public:
		BdcEvent(){

			//BDC1_Z	=-6666.11;
			//BDC2_Z 	=-5666.67;
			//Target_Z=-4222.34;
			//SBT_Z	=-7377.93;

			BDC1_Z	=-2443.77;
			BDC2_Z 	=-1444.22;
			Target_Z=0;
			SBT_Z	=-3155.59;

		}
		~BdcEvent(){}
		void loadBDC(MergeBDC *calibData){
			mergeBDC = calibData;
		}
		void setBDCEvent(){

			init();

			bdc1Position->SetXYZ(-getBDC1X(),getBDC1Y(),getBDC1Z());
			bdc2Position->SetXYZ(-getBDC2X(),getBDC2Y(),getBDC2Z());

			(*vBeam)=(*bdc2Position)-(*bdc1Position);
			(*vBeam)=(*vBeam).Unit();
			(*targetPosition) =(*bdc1Position) + getBDC1TargetRatio()*(*vBeam);
			(*sbtPosition) =(*bdc1Position) + getBDC1SBTRatio()*(*vBeam);
			beamFL =((*targetPosition)-(*sbtPosition)).Mag();
		}
		void print(){

			cout<<"Beam Flight Length from SBT to Target:"<<beamFL<<endl;
			cout<<"Beam Vector::"<<endl;
			vBeam->Print();

			cout<<"BDC1&2 3D Position"<<endl;
			bdc1Position->Print();
			bdc2Position->Print();
			cout<<"Target Position::"<<endl;
			targetPosition->Print();
		}

		void setOutputBranch(TTree *tree){

			vBeam = new TVector3;
			targetPosition = new TVector3;
			sbtPosition = new TVector3;
			bdc1Position = new TVector3;
			bdc2Position = new TVector3;

			tree->Branch("beamFL",&beamFL);
			tree->Branch("vBeam","TVector3",&vBeam);
			tree->Branch("bdc1Position","TVector3",&bdc1Position);
			tree->Branch("bdc2Position","TVector3",&bdc2Position);
			tree->Branch("targetPosition","TVector3",&targetPosition);
			tree->Branch("sbtPosition","TVector3",&sbtPosition);
		}
		TVector3 * getTargetPosotion(){
			return targetPosition;
		}
		TVector3 * getBeamVector(){
			return vBeam;
		}
		double getBeamFL(){
			return beamFL;
		}

};
