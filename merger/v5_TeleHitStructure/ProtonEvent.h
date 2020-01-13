class ProtonPara{
	private:
		TGraph *naiToProton;
	public:
		ProtonPara(){
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/naiEToProtonE/naiProtonRelation.root","READ");
                        naiToProton = (TGraph *)gDirectory->Get("naiProton");
                        fCalib->Close();	
		}
		~ProtonPara(){}
		double getProtonEnergy(double naiE){
			return naiToProton->Eval(naiE);
		}
};
class ProtonEvent{
	private:
		double protonEnergy;
		EspriEvent *espriEvent;
		ProtonPara *protonPara;

		void setProtonEnergy(){
			if(espriEvent->isNaiHit()){
				protonEnergy = protonPara->getProtonEnergy(espriEvent->getNaiEnergy());
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
			cout<<"Proton Energy = "<<protonEnergy<<endl;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("protonEnergy",&protonEnergy,"protonEnergy/D");
		}
};
