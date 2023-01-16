class ProtonGenerator{
	private:

		TEnv *env;
		double sigmaProtonEnergy;
		double sigmaProtonAngle;

		double detT; // from detecotr  with resolution
		double detTheta;// from detecotr  with resolution
		double theta; // real Event angle
		double T;// real kinetic Energy

		TGraph *protonEA;// Energy angle relation
		double getProtonEnergy(double angle){
			return protonEA->Eval(angle);
		}
	public:
		ProtonGenerator(){
			env = new TEnv("configDetector.prm");

			sigmaProtonEnergy = env->GetValue("sigmaProtonEnergy",0.);
			sigmaProtonAngle = env->GetValue("sigmaProtonAngle",0.);
			TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
                        protonEA = (TGraph *)gDirectory->Get("tot");
		}
		~ProtonGenerator(){
			delete env;
		}
		void generateEvent(){
			theta = r.Uniform(62,70);
			detTheta = r.Gaus(theta,sigmaProtonAngle);
			T = getProtonEnergy(theta);
			detT = r.Gaus(T,sigmaProtonEnergy*T);	
		}
		double getKinecticEnergy(){
			return detT;
		}
		double getAngle(){
			return detTheta;
		}
		void print(){
			cout<<"Proton Angle = "<<theta<<":"<<detTheta<<" Proton Energy = "<<T<<":"<<detT<<endl;
		}
		void setBranch(TTree *tree){
			tree->Branch("detTheta",&detTheta,"detTheta/D");
			tree->Branch("detT",&detT,"detT/D");
		}

		
};
