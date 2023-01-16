class EventBuilder{
	private:

		Proton *b;	
		Beam *A;	
		ExcitationEnergy *ex;	

		void generateBeam(){
			A->setRestMassEnergy();
			A->setMomentum();
			A->setTotalEnergy();
		}
		void generateProton(){
			b->setRestMassEnergy();
			double Tb = pg->getKinecticEnergy();
			double theta = pg->getAngle();
			b->setKineticEnergy(Tb);
			b->setMomentum();
			b->setTotalEnergy();
			b->setTheta(theta);
		}

	public:

		EventBuilder(){
			A = new Beam();
			b = new Proton();
			ex = new ExcitationEnergy();

			generate();
		}
		~EventBuilder(){
			clearMemory();
			pointerNull();
		}
		void generate(){
			generateBeam();	
			generateProton();
			ex->load(A,b);
			ex->setExEnergy();
		}
		void pointerNull(){
			A = NULL;
			b = NULL;
			ex = NULL;

		}
		void clearMemory(){
			delete A;
			delete b;
			delete ex;
		}

		void printEvent(){

			cout<<"######## Generator #################"<<endl;
			cout<<"Beam"<<endl;
			A->print();
			cout<<"Proton"<<endl;
			b->print();
			cout<<"Residue"<<endl;
			ex->print();

		}
		double getExEnergy(){
			return ex->getExEnergy();
		}
};
