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

		double teleAngle_right_1;
		double teleAngle_right_2;
		double teleAngle_right_3;
		double teleAngle_right_4;
		double teleAngle_right_5;

		double teleAngle_left_1;
		double teleAngle_left_2;
		double teleAngle_left_3;
		double teleAngle_left_4;
		double teleAngle_left_5;
	
		double teleAngle_up_1;
		double teleAngle_up_2;
		double teleAngle_up_3;

		double teleAngle_down_1;
		double teleAngle_down_2;
		double teleAngle_down_3;


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
			targetCenter->SetXYZ(0,0,0);
		}
		~AlphaEvent(){
		}

		void init(){
			rf = NULL;
			vTele->SetXYZ(NAN,NAN,NAN);

			teleAngle_up_1 = NAN;
			teleAngle_up_2 = NAN;
			teleAngle_up_3 = NAN;

			teleAngle_down_1 = NAN;
			teleAngle_down_2 = NAN;
			teleAngle_down_3 = NAN;
	
			teleAngle_left_1 = NAN;
			teleAngle_left_2 = NAN;
			teleAngle_left_3 = NAN;
			teleAngle_left_4 = NAN;
			teleAngle_left_5 = NAN;
	
			teleAngle_right_1 = NAN;
			teleAngle_right_2 = NAN;
			teleAngle_right_3 = NAN;
			teleAngle_right_4 = NAN;
			teleAngle_right_5 = NAN;
		}
		void load(ReadFile *te){
			rf = te;
		}
		void setEvent(){
			telePosition = rf->getTelePosition();
			targetPosition = rf->getTargetPosition();
			vBeam = rf->getBeamDirection();

			//targetPosition->Print();
			//vBeam->Print();
			//telePosition->Print();
			shiftLR(0.1);
			teleAngle_right_1 = setAngle();
			shiftLR(0.1);
			teleAngle_right_2 = setAngle();
			shiftLR(0.1);
			teleAngle_right_3 = setAngle();
			shiftLR(0.1);
			teleAngle_right_4 = setAngle();
			shiftLR(0.1);
			teleAngle_right_5 = setAngle();
			//telePosition->Print();
	
			shiftLR(-0.5);

			shiftLR(-0.1);
			teleAngle_left_1 = setAngle();
			shiftLR(-0.1);
			//telePosition->Print();
			teleAngle_left_2 = setAngle();
			shiftLR(-0.1);
			teleAngle_left_3 = setAngle();
			shiftLR(-0.1);
			teleAngle_left_4 = setAngle();
			shiftLR(-0.1);
			teleAngle_left_5 = setAngle();
			//telePosition->Print();
		
			shiftLR(0.5);

			shiftUD(-0.1);
			teleAngle_up_1 = setAngle();
			shiftUD(-0.1);
			teleAngle_up_2 = setAngle();
			shiftUD(-0.1);
			teleAngle_up_3 = setAngle();
			//telePosition->Print();

			shiftUD(0.3);

			shiftUD(0.1);
			teleAngle_down_1 = setAngle();
			shiftUD(0.1);
			teleAngle_down_2 = setAngle();
			shiftUD(0.1);
			teleAngle_down_3 = setAngle();
			//telePosition->Print();
			shiftUD(-0.3);
	
		}
		void print(){
			//cout<<"Alpha Angle: "<<rf->getTeleAngle()<<"  "<<teleAngle_up<<"  "<<teleAngle_down<<"  "<<teleAngle_left<<"  "<<teleAngle_right<<endl;
		}
		void setOutputBranch(TTree *tree){

			tree->Branch("teleAngle_up_1",&teleAngle_up_1,"teleAngle_up_1/D");
			tree->Branch("teleAngle_up_2",&teleAngle_up_2,"teleAngle_up_2/D");
			tree->Branch("teleAngle_up_3",&teleAngle_up_3,"teleAngle_up_3/D");

			tree->Branch("teleAngle_down_1",&teleAngle_down_1,"teleAngle_down_1/D");
			tree->Branch("teleAngle_down_2",&teleAngle_down_2,"teleAngle_down_2/D");
			tree->Branch("teleAngle_down_3",&teleAngle_down_3,"teleAngle_down_3/D");

			tree->Branch("teleAngle_left_1",&teleAngle_left_1,"teleAngle_left_1/D");
			tree->Branch("teleAngle_left_2",&teleAngle_left_2,"teleAngle_left_2/D");
			tree->Branch("teleAngle_left_3",&teleAngle_left_3,"teleAngle_left_3/D");
			tree->Branch("teleAngle_left_4",&teleAngle_left_4,"teleAngle_left_4/D");
			tree->Branch("teleAngle_left_5",&teleAngle_left_5,"teleAngle_left_5/D");
	
			tree->Branch("teleAngle_right_1",&teleAngle_right_1,"teleAngle_right_1/D");
			tree->Branch("teleAngle_right_2",&teleAngle_right_2,"teleAngle_right_2/D");
			tree->Branch("teleAngle_right_3",&teleAngle_right_3,"teleAngle_right_3/D");
			tree->Branch("teleAngle_right_4",&teleAngle_right_4,"teleAngle_right_4/D");
			tree->Branch("teleAngle_right_5",&teleAngle_right_5,"teleAngle_right_5/D");
		}
};
