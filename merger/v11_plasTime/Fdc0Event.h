class Fdc0Event{
	private:
		MergeFDC0 *mergeFDC0;
		TVector3 *targetPosition;
		TVector3 *vBeam;
		TVector3 *fdc0Position;
		TVector3 *vFDC0;
		double fdc0Angle;
		double fdc0Phi;
		PhiFunction *phiFunction;
		void init(){
			fdc0Angle = NAN;
			fdc0Phi = NAN;
			fdc0Position->SetXYZ(NAN,NAN,NAN);
			vFDC0->SetXYZ(NAN,NAN,NAN);
		}
		double getFDC0X(){
			return mergeFDC0->getFDC0X();
		}
		double getFDC0Y(){
			return mergeFDC0->getFDC0Y();
		}
		double getFDC0Z(){
			// From PGS
			//return -3384.81;
			return 837.530;
		}

	public:
		Fdc0Event(){
			phiFunction = new PhiFunction();
		}
		~Fdc0Event(){}
		void setFDC0Event(){
			init();
			fdc0Position->SetXYZ(getFDC0X()+0.55,getFDC0Y()+0.76,getFDC0Z());
			
			(*vFDC0) = (*fdc0Position) - (*targetPosition);
			(*vFDC0) = (*vFDC0).Unit();

			fdc0Angle = (*vFDC0).Angle((*vBeam))*TMath::RadToDeg();
			fdc0Phi = phiFunction->getPhi((*vBeam),(*vFDC0));
			
		}
		void loadFDC0(MergeFDC0 *calibData){
			mergeFDC0 = calibData;
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void setOutputBranch(TTree *tree){
			fdc0Position = new TVector3();
			vFDC0 = new TVector3();
			tree->Branch("fdc0Angle",&fdc0Angle,"fdc0Angle/D");
			tree->Branch("fdc0Phi",&fdc0Phi,"fdc0Phi/D");
			tree->Branch("fdc0Position","TVector3",&fdc0Position);
			tree->Branch("vFDC0","TVector3",&vFDC0);
		}
		void print(){
			cout<<"FDC0 Event::"<<endl;
			cout<<"FDC0 Angle = "<<fdc0Angle<<endl;
			cout<<"FDC0 Phi = "<<fdc0Phi<<endl;
			cout<<"FDC0 Position::"<<endl;
			fdc0Position->Print();
			cout<<"FDC0 Vector::"<<endl;
			vFDC0->Print();
		}
};
