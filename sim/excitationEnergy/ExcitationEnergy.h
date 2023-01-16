
class ExcitationEnergy{
	private:
		double exEnergy;
		Beam *A;
		Proton *b;
		Residue *B;
		void init(){
			exEnergy = -9999;
			A = NULL;
			b = NULL;
		}
		double getResidueMomentum(){
			double beamMomentum = A->getMomentum();
			double protonMomentum = b->getMomentum();
			double theta = b->getTheta();
			return sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(theta*TMath::DegToRad()));
		}
		double getResidueTotalEnergy(){
			return A->getKineticEnergy()+A->getRestMassEnergy()-b->getKineticEnergy();
		}
	public:
		ExcitationEnergy(){
			B = new Residue();	
		}
		~ExcitationEnergy(){
			B = NULL;
			delete B;
		}
		void load(Beam *p1,Proton *p2){
			init();
			A = p1;
			b = p2;
		}
		void setExEnergy(){
			B->setRestMassEnergy();
			B->setMomentum(getResidueMomentum());	
			B->setTotalEnergy(getResidueTotalEnergy());
			double massEx = B->getMassEnergy();
			double massGs = B->getRestMassEnergy();
			exEnergy = massEx - massGs;
		}
		double getExEnergy(){
			return exEnergy;
		}
		void print(){
			B->print();
			cout<<"ExEnergy = "<<exEnergy<<endl;
		}
};
