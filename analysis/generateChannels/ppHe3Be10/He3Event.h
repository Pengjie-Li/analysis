class He3CalibPara{
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

		TGraph *csiHe3;

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
		He3CalibPara(){
			dssdThickness = 1.522;//mm
			degraderThickness = 25;//mm
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/he3DEE/dEECurve.root","READ");
                        csiHe3 = (TGraph *)gDirectory->Get("dEE_TotCsi");
                        fCalib->Close();	
			TFile *fEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/he3InMaterials.root","READ");
                        dssdEnergyToRange = (TGraph *)gDirectory->Get("he3DssdER");
                        dssdRangeToEnergy = (TGraph *)gDirectory->Get("he3DssdRE");
			degraderEnergyToRange = (TGraph *)gDirectory->Get("he3DegraderER");
                        degraderRangeToEnergy = (TGraph *)gDirectory->Get("he3DegraderRE");
                        fEloss->Close();	
			TFile *fWinEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/he3WindowEloss.root","READ");
			winEloss = (TGraph *)gDirectory->Get("windowEloss");
			fWinEloss->Close();
		}
		~He3CalibPara(){}
		double getEnergy_old(double csiE){
			return csiHe3->Eval(csiE);
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
class He3Event{
	private:
		double he3Energy_old;
		double he3Energy;

		TeleEvent *teleEvent;
		He3CalibPara *he3Para;
		void setHe3Energy(){
			he3Energy_old = he3Para->getEnergy_old(teleEvent->getCsiEnergy());
			he3Energy = he3Para->getEnergy(teleEvent->getCsiEnergy(),teleEvent->getLocusAngle());
			//he3Energy = he3Para->getEnergy(teleEvent->getCsiEnergy(),0);
		}
	public:
		He3Event(){
			he3Para = new He3CalibPara();
		}
		~He3Event(){
			delete he3Para;
		}

		bool isGoodEvent(){
			return teleEvent->isGoodEvent();
		}

		void init(){
			he3Para->init();
			teleEvent = NULL;
			he3Energy_old = NAN;
			he3Energy = NAN;
		}
		void load(TeleEvent *te){
			teleEvent = te;
		}
		void setEvent(){
			if(isGoodEvent()){
				setHe3Energy();
			}
		}
		void print(){
			he3Para->print();
			cout<<"He3 Energy = "<<he3Energy<<" "<<he3Energy_old<<endl;
		}
		void setOutputBranch(TTree *tree){
			he3Para->setOutputBranch(tree);
			tree->Branch("he3Energy_old",&he3Energy_old,"he3Energy_old/D");
			tree->Branch("he3Energy",&he3Energy,"he3Energy/D");
		}
};
