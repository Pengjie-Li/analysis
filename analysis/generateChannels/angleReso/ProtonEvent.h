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
		double protonEnergy_sig3;
		double protonAngle_sig3;


		ReadFile *rf;
		ProtonPara *protonPara;

		void setProtonEnergy(){
			if(rf->isNaiHit()){
				protonAngle_sig3 = rf->getEspriAngle() + gRandom->Gaus(0,0.3);
				protonEnergy_sig3 = protonPara->getProtonEnergy(rf->getNaiEnergy(),rf->getEspriLocusAngle(),protonAngle_sig3);
			}
		}
	public:
		ProtonEvent(){
			protonPara = new ProtonPara();
		}
		~ProtonEvent(){}

		void init(){
			protonPara->init();
			rf = NULL;
			protonEnergy_sig3 = NAN;
			protonAngle_sig3 = NAN;
		}
		void load(ReadFile *ee){
			rf = ee;
		}
		void setEvent(){
				setProtonEnergy();
		}
		void print(){
			protonPara->print();
			cout<<"Proton Energy = "<<protonEnergy_sig3<<" "<<protonAngle_sig3<<endl;
		}
		void setOutputBranch(TTree *tree){
			protonPara->setOutputBranch(tree);
			tree->Branch("protonEnergy_sig3",&protonEnergy_sig3,"protonEnergy_sig3/D");
			tree->Branch("protonAngle_sig3",&protonAngle_sig3,"protonAngle_sig3/D");
		}
};
