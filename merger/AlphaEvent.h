class AlphaCalibPara{
	private:

		TGraph *csiAlpha;
	public:
		AlphaCalibPara(){
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
                        csiAlpha = (TGraph *)gDirectory->Get("dEE_TotCsi");
                        fCalib->Close();	
		}
		~AlphaCalibPara(){}
		double getEnergy(double csiE){
			return csiAlpha->Eval(csiE);
		}
};
class AlphaEvent{
	private:
		double alphaEnergy;

		TeleEvent *teleEvent;
		AlphaCalibPara *alphaPara;
		void setAlphaEnergy(){
			alphaEnergy = alphaPara->getEnergy(teleEvent->getCsiEnergy());
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
			teleEvent = NULL;
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
			cout<<"Alpha Energy = "<<alphaEnergy<<endl;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("alphaEnergy",&alphaEnergy,"alphaEnergy/D");
		}
};
