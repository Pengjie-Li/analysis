class AlphaCalibPara{
	private:

		double apDssdE;
		double apDegraderE;
		double apWinE;
		double apShtE;

		TGraph *degraderEnergyToRange;
		TGraph *degraderRangeToEnergy;

		TGraph *dssdEnergyToRange;
		TGraph *dssdRangeToEnergy;
		TGraph *shtEnergyToRange;
		TGraph *shtRangeToEnergy;
	
		TGraph *winEloss;


		double shtThickness;
		double dssdThickness;
		double degraderThickness;

		TGraph *csiAlpha;

		double getShtE(double angle,double energyOut){
			double realThickness = shtThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + shtEnergyToRange->Eval(energyOut);
			double energyIn = shtRangeToEnergy->Eval(rangeIn);
			//cout<<"Sht "<<realThickness<<" "<<energyIn<<" "<<energyOut<<" "<<energyIn-energyOut<<endl;
			return (energyIn-energyOut);
		}

		double getDssdE(double angle,double energyOut){
			double realThickness = dssdThickness/cos(angle*TMath::DegToRad()); 
			//double rangeIn = realThickness + dssdEnergyToRange->Eval(energyOut);
			//double energyIn = dssdRangeToEnergy->Eval(rangeIn);
			double rangeIn = realThickness + dssdEnergyToRange->Eval(energyOut,0,"S");
                        double energyIn = dssdRangeToEnergy->Eval(rangeIn,0,"S");

			//cout<<"DSSD "<<realThickness<<" "<<energyIn<<energyOut<<" "<<energyIn-energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getDegraderE(double angle,double energyOut){
			double realThickness = degraderThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + degraderEnergyToRange->Eval(energyOut);
			double energyIn = degraderRangeToEnergy->Eval(rangeIn);
			//cout<<"Degrader "<<realThickness<<" "<<energyIn<<energyOut<<" "<<energyIn-energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getWindowE(double energy){
			//cout<<"in "<<energy<<" winE"<<winEloss->Eval(energy)<<endl;
			return winEloss->Eval(energy);
		}

	public:
		AlphaCalibPara(){
			
			shtThickness = 1.0;//mm
			dssdThickness = 1.522;//mm
			degraderThickness = 25;//mm
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
                        csiAlpha = (TGraph *)gDirectory->Get("dEE_TotCsi");
                        fCalib->Close();	
			TFile *fEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/alphaInMaterials.root","READ");
			shtEnergyToRange = (TGraph *)gDirectory->Get("alphaShtER");
                        shtRangeToEnergy = (TGraph *)gDirectory->Get("alphaShtRE");
			
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
		double getEnergy(double csiE,double locusAngle,double theta){
			
			 apDssdE = getDssdE(locusAngle,csiE);
			 apDegraderE = getDegraderE(locusAngle,csiE+apDssdE);
			 apWinE = getWindowE(apDegraderE+apDssdE+csiE);
			 apShtE = getShtE(theta, apWinE+apDegraderE+apDssdE+csiE);
			return apShtE+apWinE+apDegraderE+apDssdE+csiE;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("apDssdE",&apDssdE,"apDssdE/D");
			tree->Branch("apDegraderE",&apDegraderE,"apDegraderE/D");
			tree->Branch("apWinE",&apWinE,"apWinE/D");
			tree->Branch("apShtE",&apShtE,"apShtE/D");
		}
		void init(){
			apDssdE = NAN;
			apDegraderE = NAN;
			apWinE = NAN;
			apShtE = NAN;
		}
		void print(){
			cout<<" apWinE ="<<apWinE<<" apDegraderE ="<<apDegraderE<<" apDssdE ="<<apDssdE<<endl;
		}
};
class AlphaEvent{
	private:
		double alphaEnergy_old;
		double alphaEnergy;

		TeleEvent *teleEvent;
		AlphaCalibPara *alphaPara;
		void setAlphaEnergy(){
			alphaEnergy_old = alphaPara->getEnergy_old(teleEvent->getCsiEnergy());
			alphaEnergy = alphaPara->getEnergy(teleEvent->getCsiEnergy(),teleEvent->getLocusAngle(), teleEvent->getAngle());
			//alphaEnergy = alphaPara->getEnergy(499.45, 0 , 60);
			//alphaEnergy = alphaPara->getEnergy(317.74, 0 , 60);
			//alphaEnergy = alphaPara->getEnergy(teleEvent->getCsiEnergy(),0);
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
			alphaPara->init();
			teleEvent = NULL;
			alphaEnergy_old = NAN;
			alphaEnergy = NAN;
		}
		void load(TeleEvent *te){
			teleEvent = te;
		}
		void setEvent(){
			if(isGoodEvent()){
				setAlphaEnergy();
			}
		}
		void print(){
			alphaPara->print();
			cout<<"Alpha Energy = "<<alphaEnergy<<" "<<alphaEnergy_old<<endl;
		}
		void setOutputBranch(TTree *tree){
			alphaPara->setOutputBranch(tree);
			tree->Branch("alphaEnergy_old",&alphaEnergy_old,"alphaEnergy_old/D");
			tree->Branch("alphaEnergy",&alphaEnergy,"alphaEnergy/D");
		}
};
