class Particle{
	private:
	public:
		TString pName;
		double M;
		double T;
		double P;
		double E;
		double Theta;
		double Phi;
		double Beta;
		double Gamma;
		Particle(){
			init();
		}
		Particle(TString name){
			pName = name;
			init();
		}

		~Particle(){}
		void init(){
			M = NAN;
			T = NAN;
			P = NAN;
			E = NAN;
			Theta = 0;
			Phi = 0;
			Beta = NAN;
			Gamma = NAN; 	
		}
		void setName(TString name){
			pName = name;
		}
		void setP(double p){
			P = p;
		}
		void setM(double m){
			M = m;
		}
		void setE(double e){
			E = e;
		}
		void setT(double t){
			T = t;
		}
		void setTheta(double th){
			Theta = th*TMath::DegToRad();
		}
		void setPhi(double pi){
			Phi = pi;
		}
		void print(){
			cout<<"Particle "<<pName<<"\t"<<M<<"\t"<<E<<"\t"<<P<<"\t"<<Gamma<<"\t"<<Beta<<"\t"<<Theta*TMath::RadToDeg()<<"\t"<<Phi<<endl;
		}
		void setMT(double m,double t){
			M = m; T = t;
			E = M + T;
			P = sqrt(E*E - M*M);
			Gamma = E/M;
			Beta = P/E;
		}
		void setMP(double m,double p){
			M = m; P = p;
			E = sqrt(M*M + P*P);
			T = E - M;
			Gamma = E/M;
			Beta = P/E;
		}
		void setME(double m,double e){
			M = m; E = e;
			P = sqrt(E*E - M*M);
			T = E - M;
			Gamma = E/M;
			Beta = P/E;
		}

		void setEP(double e,double p){
			E = e; P = p;
			M = sqrt(E*E - P*P);
			T = E - M;
			Gamma = E/M;
			Beta = P/E;
		}
		void setLorentzVector(TLorentzVector x){
			P = x.P();
			M = x.M();
			E = x.E();
			T = x.T();
			Gamma = E/M;
			Beta = P/E;
		}
		void setBranch(TTree *tree){
			tree->Branch("M"+pName,&M,"M"+pName+"/D");
			tree->Branch("E"+pName,&E,"E"+pName+"/D");
			tree->Branch("P"+pName,&P,"P"+pName+"/D");
			tree->Branch("T"+pName,&T,"T"+pName+"/D");
			tree->Branch("Theta"+pName,&Theta,"Theta"+pName+"/D");
			tree->Branch("Phi"+pName,&Phi,"Phi"+pName+"/D");
		}
};
class Gate{
	private:
		ReadFile *rf;

		bool isBeam(){
			return (rf->getTof713()>0)&&(rf->getF13Q()>0);
		}
                bool isInsideTargetArea(double x,double y){
                        return (sqrt((x-2.0)*(x-2.0)+(y+1.1)*(y+1.1))<15);
                }
		bool isTarget(){
			return isInsideTargetArea(rf->getTargetX(),rf->getTargetY());
		}
		bool isProton(){
			return (rf->getTrigESPRI()>0);		
		}
		bool isAlpha(){
			return (rf->getTeleCsiE()>0)&&(rf->getTeleDssdE()>0);
		}
	public:
		Gate(ReadFile *rf):rf(rf){}
		~Gate(){}
		bool isGoodEvent(){
			return isBeam()&&isTarget()&&isProton()&&isAlpha();
			//return true;
		}
};
class Event{
	private:
		ReadFile *rf;
		Gate	*gate;

		Particle *a;
		Particle *b;
		Particle *r0;
		Particle *r1;
		Particle *r2;
		Particle *r3;

		void buildParticleA(){
		}

	public:
		Event(){}
		Event(ReadFile *rf):rf(rf){
			a	= new Particle("a");
			b	= new Particle("b");
			r0	= new Particle("CM");
			r1	= new Particle("1");
			r2	= new Particle("2");
			r3	= new Particle("3");
			gate	= new Gate(rf);
		}

		bool isSelectedEvent(){
			return gate->isGoodEvent();
		}
		void reconstruct(){
				buildParticleA();
		}
		~Event(){
			delete a;
			delete b;
			delete r0;
			delete r1;
			delete r2;
			delete r3;
		}
		void setBranch(TTree *tree){
			a ->setBranch(tree);
			b ->setBranch(tree);      
			r0->setBranch(tree);	
			r1->setBranch(tree);	
			r2->setBranch(tree);	
			r3->setBranch(tree);			
		}
};
