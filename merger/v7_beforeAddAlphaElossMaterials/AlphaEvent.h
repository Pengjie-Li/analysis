class AlphaCalibPara{
	private:

		TGraph *csiAlpha;
	public:
		AlphaCalibPara(){
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
                        csiAlpha = (TGraph *)gDirectory->Get("dEE_TotCsi");
                        fCalib->Close();	
		}
		~AlphaCalibPara(){}
		double getEnergy(double csiE){
			return csiAlpha->Eval(csiE);
		}
};
class AlphaEvent{
	private:
		double alphaEnergy;
		double alphaAngle;
		double alphaLocusAngle;
		TVector3 *vAlpha;

		TVector3 *targetPosition;
		TVector3 *vBeam;
		TVector3 *telePosition;

		TeleEvent *teleEvent;
		AlphaCalibPara *alphaPara;
		void setAlphaAngle(){
			telePosition = teleEvent->getTelePosition();
			(*vAlpha)	= (*telePosition)-(*targetPosition);
			(*vAlpha)	= (*vAlpha).Unit();
			alphaAngle      = (*vAlpha).Angle((*vBeam))*TMath::RadToDeg();
			TVector3 dssdPlaneNorm = teleEvent->getDssdPlaneNorm();
			alphaLocusAngle = (*vAlpha).Angle(dssdPlaneNorm)*TMath::RadToDeg();
		}
		void setAlphaEnergy(){
			alphaEnergy = alphaPara->getEnergy(teleEvent->getCsiEnergy());
		}
	public:
		AlphaEvent(){
			alphaPara = new AlphaCalibPara();
		}
		~AlphaEvent(){
			delete alphaPara;
		}

		bool isGoodEvent(){
			return teleEvent->isGoodEvent();
		}

		void init(){
			teleEvent = NULL;
			alphaEnergy = NAN;
			alphaAngle = NAN;
			alphaLocusAngle = NAN;
			vAlpha->SetXYZ(NAN,NAN,NAN);
		}
		void load(TeleEvent *te){
			teleEvent = te;
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void setEvent(){
			if(isGoodEvent()){
				setAlphaAngle();
				setAlphaEnergy();
			}
		}
		void print(){
			cout<<"Alpha Energy = "<<alphaEnergy<<" Alpha Angle = "<<alphaAngle<<" Locus Angle ="<<alphaLocusAngle<<endl;
		}
		void setOutputBranch(TTree *tree){
			vAlpha = new TVector3;
			tree->Branch("alphaEnergy",&alphaEnergy,"alphaEnergy/D");
			tree->Branch("alphaAngle",&alphaAngle,"alphaAngle/D");
			tree->Branch("alphaLocusAngle",&alphaLocusAngle,"alphaLocusAngle/D");
			tree->Branch("vAlpha","TVector3",&vAlpha);
		}
};
