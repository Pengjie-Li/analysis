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
		double alphaEnergy_old;
		double alphaEnergy;

		TeleEvent *teleEvent;
		AlphaCalibPara *alphaPara;
		void setAlphaEnergy(){
			alphaEnergy_old = alphaPara->getEnergy_old(teleEvent->getCsiEnergy());
			alphaEnergy = alphaPara->getEnergy(teleEvent->getCsiEnergy(),teleEvent->getLocusAngle());
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
