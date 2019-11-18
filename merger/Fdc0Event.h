class Fdc0Event{
	private:
		MergeFDC0 *mergeFDC0;
		TVector3 *vTarget;
		TVector3 *vBeam;
		TVector3 *vFDC0;
		TVector3 *vResidue;
		double resAngle;
		void init(){
			resAngle = NAN;
			vFDC0->SetXYZ(NAN,NAN,NAN);
			vResidue->SetXYZ(NAN,NAN,NAN);
		}
		double getFDC0X(){
			return mergeFDC0->getFDC0X();
		}
		double getFDC0Y(){
			return mergeFDC0->getFDC0Y();
		}
		double getFDC0Z(){
			// From PGS
			return 3384.81;
		}

	public:
		Fdc0Event(){}
		~Fdc0Event(){}
		void setFDC0Event(){
			init();
			vFDC0->SetXYZ(getFDC0X(),getFDC0Y(),getFDC0Z());
			
			(*vResidue) = (*vFDC0) - (*vTarget);
			(*vResidue) = (*vResidue).Unit();

			resAngle = (*vResidue).Angle((*vBeam))*TMath::RadToDeg();
			
		}
		void loadFDC0(MergeFDC0 *calibData){
			mergeFDC0 = calibData;
		}
		void loadTargetPosition(TVector3 *target){
			vTarget = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void setOutputBranch(TTree *tree){
			vFDC0 = new TVector3();
			vResidue = new TVector3();
			tree->Branch("resAngle",&resAngle,"resAngle/D");
			tree->Branch("vFDC0","TVector3",&vFDC0);
			tree->Branch("vResidue","TVector3",&vResidue);
		}
		void print(){
			cout<<"FDC0 Event::"<<endl;
			cout<<"Residue Angle = "<<resAngle<<endl;
			vFDC0->Print();
			vResidue->Print();
		}
};
