class ProtonPara{
	private:
		double ppPlasE;
		double ppWinE;
		double ppShtE;

		TGraph *plasEnergyToRange;
		TGraph *plasRangeToEnergy;

		TGraph *shtEnergyToRange;
		TGraph *shtRangeToEnergy;
		TGraph *winEloss;

		double plasThickness;
		double shtThickness;

		TGraph *naiToProton;

		double getSHTE(double angle,double energyOut){
			double realThickness = shtThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + shtEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = shtRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"SHT "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getPlasE(double angle,double energyOut){
			double realThickness = plasThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + plasEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = plasRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"Plas "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getWindowE(double energy){
			return winEloss->Eval(energy);
		}

	public:
		ProtonPara(){
			plasThickness = 4; //mm
			shtThickness = 1; //mm , assume reaction happened in the middle
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/naiEToProtonE/naiProtonRelation.root","READ");
                        naiToProton = (TGraph *)gDirectory->Get("naiProton");
                        fCalib->Close();	

			TFile *fEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/protonInMaterials.root","READ");
                        shtEnergyToRange = (TGraph *)gDirectory->Get("protonTargetER");
                        shtRangeToEnergy = (TGraph *)gDirectory->Get("protonTargetRE");
			plasEnergyToRange = (TGraph *)gDirectory->Get("protonPlasER");
                        plasRangeToEnergy = (TGraph *)gDirectory->Get("protonPlasRE");
                        fEloss->Close();	
			TFile *fWinEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/protonWindowEloss.root","READ");
			winEloss = (TGraph *)gDirectory->Get("windowEloss");
			fWinEloss->Close();
		}
		~ProtonPara(){}
		double getProtonEnergy_nai(double naiE){
			return naiToProton->Eval(naiE);
		}
		double getProtonEnergy(double naiE,double locusAngle,double angle){
			ppPlasE = getPlasE(locusAngle,naiE);
			ppWinE = getWindowE(naiE+ppPlasE);
			ppShtE = getSHTE(angle,naiE+ppPlasE+ppWinE);
		
			return naiE+ppPlasE+ppWinE+ppShtE;
		}
		void init(){
			ppPlasE = NAN;
			ppWinE = NAN;
			ppShtE = NAN;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("ppPlasE",&ppPlasE,"ppPlasE/D");
			tree->Branch("ppWinE",&ppWinE,"ppWinE/D");
			tree->Branch("ppShtE",&ppShtE,"ppShtE/D");
		}
		void print(){
			cout<<" shtE = "<<ppShtE<<" winE ="<<ppWinE<<" plasE = "<<ppPlasE<<endl;
		}

};
class ProtonEvent{
	private:
		double protonEnergy_nai;
		double protonEnergy;

		double protonEnergy_lm10_g0;
		double protonEnergy_lm5_g0;
		double protonEnergy_l5_g0;
		double protonEnergy_l10_g0;
		double protonEnergy_l0_g1;
		double protonEnergy_l0_g2;
		double protonEnergy_l0_g3;

		EspriEvent *espriEvent;
		ProtonPara *protonPara;

		void setProtonEnergy(){
			if(espriEvent->isNaiHit()){
				protonEnergy_nai = protonPara->getProtonEnergy_nai(espriEvent->getNaiEnergy());
				protonEnergy = protonPara->getProtonEnergy(espriEvent->getNaiEnergy(),espriEvent->getLocusAngle(),espriEvent->getAngle());
			}
		}
	public:
		ProtonEvent(){
			protonPara = new ProtonPara();
		}
		~ProtonEvent(){}
		bool isGoodEvent(){
			return espriEvent->isGoodEvent();
		}

		void init(){
			protonPara->init();
			espriEvent = NULL;
			protonEnergy_nai = NAN;
			protonEnergy = NAN;
		}
		void load(EspriEvent *ee){
			espriEvent = ee;
		}
		void setEvent(){
			if(isGoodEvent()){
				setProtonEnergy();
			}
		}
		void print(){
			protonPara->print();
			cout<<"Proton Energy = "<<protonEnergy<<" "<<protonEnergy_nai<<endl;
		}
		void setOutputBranch(TTree *tree){
			protonPara->setOutputBranch(tree);
			tree->Branch("protonEnergy_nai",&protonEnergy_nai,"protonEnergy_nai/D");
			tree->Branch("protonEnergy",&protonEnergy,"protonEnergy/D");
		}
};
