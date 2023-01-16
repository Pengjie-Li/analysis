class He3CalibPara{
	private:

		double he3DssdE;
		double he3DegraderE;
		double he3WinE;

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
		double getEnergy(double csiE,double locusAngle){
			
			 he3DssdE = getDssdE(locusAngle,csiE);
			 he3DegraderE = getDegraderE(locusAngle,csiE+he3DssdE);
			 he3WinE = getWindowE(he3DegraderE+he3DssdE+csiE);
			return he3WinE+he3DegraderE+he3DssdE+csiE;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("he3DssdE",&he3DssdE,"he3DssdE/D");
			tree->Branch("he3DegraderE",&he3DegraderE,"he3DegraderE/D");
			tree->Branch("he3WinE",&he3WinE,"he3WinE/D");
		}
		void init(){
			he3DssdE = NAN;
			he3DegraderE = NAN;
			he3WinE = NAN;
		}
		void print(){

			cout<<" he3WinE ="<<he3WinE<<" he3DegraderE ="<<he3DegraderE<<" he3DssdE ="<<he3DssdE<<endl;
		}
};
class He3Event{
	private:
		double he3Energy;

		ReadFile *rf;
		He3CalibPara *he3Para;
		void setHe3Energy(){
			he3Energy = he3Para->getEnergy(rf->getCsiEnergy(),rf->getLocusAngle());
			//he3Energy = he3Para->getEnergy(rf->getCsiEnergy(),0);
		}
	public:
		He3Event(){
			he3Para = new He3CalibPara();
		}
		~He3Event(){
			delete he3Para;
		}

		bool isGoodEvent(){
			//return rf->isGoodEvent();
			return true;
		}

		void init(){
			he3Para->init();
			rf = NULL;
			he3Energy = NAN;
		}
		void load(ReadFile *te){
			rf = te;
		}
		void setEvent(){
			if(isGoodEvent()){
				setHe3Energy();
			}
		}
		void print(){
			he3Para->print();
			cout<<"He3 Energy = "<<he3Energy<<" "<<endl;
		}
		void setOutputBranch(TTree *tree){
			he3Para->setOutputBranch(tree);
			tree->Branch("he3Energy",&he3Energy,"he3Energy/D");
		}
};
