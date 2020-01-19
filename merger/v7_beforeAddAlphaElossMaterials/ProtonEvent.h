class ProtonPara{
	private:
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
			double rangeIn = realThickness + shtEnergyToRange->Eval(energyOut);
			double energyIn = shtRangeToEnergy->Eval(rangeIn);
			//cout<<"SHT "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getPlasE(double angle,double energyOut){
			double realThickness = plasThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + plasEnergyToRange->Eval(energyOut);
			double energyIn = plasRangeToEnergy->Eval(rangeIn);
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
			TFile *fWinEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/windowEloss.root","READ");
			winEloss = (TGraph *)gDirectory->Get("windowEloss");
			fWinEloss->Close();
		}
		~ProtonPara(){}
		double getProtonEnergy_nai(double naiE){
			return naiToProton->Eval(naiE);
		}
		double getProtonEnergy(double naiE,double locusAngle,double angle){
			double plasE = getPlasE(locusAngle,naiE);
			double winE = getWindowE(naiE+plasE);
			double shtE = getSHTE(angle,naiE+plasE+winE);
		
			//cout<<"locusAngle = "<<locusAngle<<" angle="<<angle<<" shtE = "<<shtE<<" winE ="<<winE<<" plasE = "<<plasE<<" naiE = "<<naiE<<endl;
			return naiE+plasE+winE+shtE;
		}

};
class ProtonEvent{
	private:
		double protonEnergy_nai;
		double protonEnergy;
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
			cout<<"Proton Energy = "<<protonEnergy<<" "<<protonEnergy_nai<<endl;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("protonEnergy_nai",&protonEnergy_nai,"protonEnergy_nai/D");
			tree->Branch("protonEnergy",&protonEnergy,"protonEnergy/D");
		}
};
