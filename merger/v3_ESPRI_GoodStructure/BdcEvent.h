class BdcEvent{
	private:

		Double_t BDC1_Z;
		Double_t BDC2_Z;
		Double_t Target_Z;
		Double_t SBT_Z;

		MergeBDC *mergeBDC;
		TVector3* vBeam;	
		TVector3* vBDC1;	
		TVector3* vBDC2;	
		TVector3* vTarget;	
		TVector3* vSBT;	
		Double_t  beamFL;


		void init(){

			/********* BDC ***************/
			beamFL = NAN;

			vBDC1->SetXYZ(NAN,NAN,NAN);
			vBDC2->SetXYZ(NAN,NAN,NAN);
			vTarget->SetXYZ(NAN,NAN,NAN);
			vSBT->SetXYZ(NAN,NAN,NAN);
			vBeam->SetXYZ(NAN,NAN,NAN);

		}
		Double_t getBDC1TargetRatio(){
			return (Target_Z-(*vBDC1).Z())/(*vBeam).Z();
		}
		Double_t getBDC1SBTRatio(){
			return (SBT_Z-(*vBDC1).Z())/(*vBeam).Z();
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
			BDC1_Z=-6666.11;
			BDC2_Z=-5666.67;
			Target_Z=-4222.34;
			SBT_Z =-7377.93;
		}
		~BdcEvent(){}
		void loadBDC(MergeBDC *calibData){
			mergeBDC = calibData;
		}
		void setBDCEvent(){

			init();

			vBDC1->SetXYZ(-getBDC1X(),getBDC1Y(),getBDC1Z());
			vBDC2->SetXYZ(-getBDC2X(),getBDC2Y(),getBDC2Z());

			(*vBeam)=(*vBDC2)-(*vBDC1);
			(*vBeam)=(*vBeam).Unit();
			(*vTarget) =(*vBDC1) + getBDC1TargetRatio()*(*vBeam);
			(*vSBT) =(*vBDC1) + getBDC1SBTRatio()*(*vBeam);
			beamFL =((*vTarget)-(*vSBT)).Mag();
		}
		void print(){

			cout<<"Beam Flight Length from SBT to Target:"<<beamFL<<endl;
			cout<<"Beam Vector::"<<endl;
			vBeam->Print();

			cout<<"BDC1&2 3D Position"<<endl;
			vBDC1->Print();
			vBDC2->Print();
			cout<<"Target Position::"<<endl;
			vTarget->Print();
		}

		void setOutputBranch(TTree *tree){

			vBeam = new TVector3;
			vTarget = new TVector3;
			vSBT = new TVector3;
			vBDC1 = new TVector3;
			vBDC2 = new TVector3;

			tree->Branch("beamFL",&beamFL);
			tree->Branch("vBeam","TVector3",&vBeam);
			tree->Branch("vBDC1","TVector3",&vBDC1);
			tree->Branch("vBDC2","TVector3",&vBDC2);
			tree->Branch("vTarget","TVector3",&vTarget);
			tree->Branch("vSBT","TVector3",&vSBT);
		}
		TVector3 * getTargetPosotion(){
			return vTarget;
		}
		TVector3 * getBeamVector(){
			return vBeam;
		}

};
