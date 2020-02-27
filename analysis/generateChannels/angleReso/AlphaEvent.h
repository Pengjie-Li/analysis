class AlphaCalibPara{
	private:

		double apDssdE;
		double apDegraderE;
		double apWinE;

		TGraph *degraderEnergyToRange;
		TGraph *degraderRangeToEnergy;

		TGraph *dssdEnergyToRange;
		TGraph *dssdRangeToEnergy;
		TGraph *winEloss;


		double dssdThickness;
		double degraderThickness;

		TGraph *csiAlpha;

		double getDssdE(double angle,double energyOut){
			double realThickness = dssdThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + dssdEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = dssdRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"DSSD "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getDegraderE(double angle,double energyOut){
			double realThickness = degraderThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + degraderEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = degraderRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"Degrader "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getWindowE(double energy){
			//cout<<"in "<<energy<<" winE"<<winEloss->Eval(energy,0,"S")<<endl;
			return winEloss->Eval(energy);
		}

	public:
		AlphaCalibPara(){
			dssdThickness = 1.522;//mm
			degraderThickness = 25;//mm
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
                        csiAlpha = (TGraph *)gDirectory->Get("dEE_TotCsi");
                        fCalib->Close();	
			TFile *fEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/alphaInMaterials.root","READ");
                        dssdEnergyToRange = (TGraph *)gDirectory->Get("alphaDssdER");
                        dssdRangeToEnergy = (TGraph *)gDirectory->Get("alphaDssdRE");
			degraderEnergyToRange = (TGraph *)gDirectory->Get("alphaDegraderER");
                        degraderRangeToEnergy = (TGraph *)gDirectory->Get("alphaDegraderRE");
                        fEloss->Close();	
			TFile *fWinEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/alphaWindowEloss.root","READ");
			winEloss = (TGraph *)gDirectory->Get("windowEloss");
			fWinEloss->Close();
		}
		~AlphaCalibPara(){}
		double getEnergy_old(double csiE){
			return csiAlpha->Eval(csiE);
		}
		double getEnergy(double csiE,double locusAngle){
			
			 apDssdE = getDssdE(locusAngle,csiE);
			 apDegraderE = getDegraderE(locusAngle,csiE+apDssdE);
			 apWinE = getWindowE(apDegraderE+apDssdE+csiE);
			return apWinE+apDegraderE+apDssdE+csiE;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("apDssdE",&apDssdE,"apDssdE/D");
			tree->Branch("apDegraderE",&apDegraderE,"apDegraderE/D");
			tree->Branch("apWinE",&apWinE,"apWinE/D");
		}
		void init(){
			apDssdE = NAN;
			apDegraderE = NAN;
			apWinE = NAN;
		}
		void print(){

			cout<<" apWinE ="<<apWinE<<" apDegraderE ="<<apDegraderE<<" apDssdE ="<<apDssdE<<endl;
		}
};
class AlphaEvent{
	private:

		ReadFile *rf;
		TVector3 *telePosition;
		TVector3 *targetPosition;
		TVector3 *vTele;
		TVector3 *vBeam;

		TVector3 *targetCenter;
		double teleAngle_up;
		double teleAngle_down;
		double teleAngle_left;
		double teleAngle_right;

		void shiftLR(double angle){
			(*telePosition) = (*telePosition) - (*targetCenter);
			(*telePosition).RotateY(angle*TMath::DegToRad());
			(*telePosition) = (*telePosition) + (*targetCenter);
		}
        
		void shiftUD(double angle){
			(*telePosition) = (*telePosition) - (*targetCenter);
			(*telePosition).RotateX(angle*TMath::DegToRad());
			(*telePosition) = (*telePosition) + (*targetCenter);
		}
                double setAngle(){
                        (*vTele)        = (*telePosition)-(*targetPosition);
                        (*vTele)        = (*vTele).Unit();
                        return (*vTele).Angle((*vBeam))*TMath::RadToDeg();
                }
	public:
		AlphaEvent(){
			vTele = new TVector3;
			targetCenter = new TVector3;
			targetCenter->SetXYZ(0,0,-4222.45);
		}
		~AlphaEvent(){
		}

		void init(){
			rf = NULL;
			vTele->SetXYZ(NAN,NAN,NAN);
			teleAngle_up = NAN;
			teleAngle_down = NAN;
			teleAngle_left = NAN;
			teleAngle_right = NAN;
		}
		void load(ReadFile *te){
			rf = te;
		}
		void setEvent(){
			telePosition = rf->getTelePosition();
			targetPosition = rf->getTargetPosition();
			vBeam = rf->getBeamDirection();

			shiftUD(0.5);
			teleAngle_down= setAngle();
			shiftUD(-1);
			teleAngle_up = setAngle();
			shiftUD(0.5);
			shiftLR(0.5);
			teleAngle_right = setAngle();
			shiftLR(-1);
			teleAngle_left = setAngle();
			shiftLR(0.5);
		}
		void print(){
			cout<<"Alpha Angle: "<<rf->getTeleAngle()<<"  "<<teleAngle_up<<"  "<<teleAngle_down<<"  "<<teleAngle_left<<"  "<<teleAngle_right<<endl;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("teleAngle_up",&teleAngle_up,"teleAngle_up/D");
			tree->Branch("teleAngle_down",&teleAngle_down,"teleAngle_down/D");
			tree->Branch("teleAngle_left",&teleAngle_left,"teleAngle_left/D");
			tree->Branch("teleAngle_right",&teleAngle_right,"teleAngle_right/D");
		}
};
