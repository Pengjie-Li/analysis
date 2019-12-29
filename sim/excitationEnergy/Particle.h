class Particle{
	private:
	protected:
		int A;// Mass Number
		int Z;// Charge Number
		double m0;// Rest Mass u


		double T; //kinetic Energy MeV
		double m;// mass Energy MeV
		double p;// Momentum Energy MeV
		double E;// Total Energy MeV
		double theta;// angle refer to Beam

	public:
		Particle():A(-1),Z(-1),m0(-9999),T(-9999),p(-9999),m(-9999),E(-9999),theta(-9999){}
		~Particle(){}
		double getRestMassEnergy(){
			return m;
		}
		double getKineticEnergy(){
			return T;
		}
		double getTotalEnergy(){
			return E;
		}
		double getMassEnergy(){
			return sqrt(E*E-p*p); 
		}
		double getMomentum(){
			return p;
		}
		double getTheta(){
			return theta;
		}

		void setKineticEnergy(double input){
			T = input;
		}
		void setTheta(double input){
			theta = input;
		}
		void setMomentum(double input){
			p = input;
		}
		void setTotalEnergy(double input){
			E = input;
		}

		void setRestMassEnergy(){
			m = m0*AMU;
		}
		void setMomentum(){
			p = sqrt(T*T+2*T*m);
		}
		void setTotalEnergy(){
			E = T + m;
		}
		void print(){
			cout<<"MassEnergy = "<<"\t"<<m<<" Momentum Energy = "<<"\t"<<p<<" Total Energy = "<<E<<endl;
		}
};
class Proton:public Particle{
	private:
	public:
		Proton(){
			A = 1;
			Z = 1;
			m0 = 1.007276452;
		}
		~Proton(){}
};
class Beam:public Particle{
	private:
	public:
		Beam(){
			A = 14;
			Z = 4;
			m0 = 14.04069708;
			T = 150.113*m0;
			theta = 0;
		}
		~Beam(){}
};
class Residue:public Particle{
	private:
	public:
		Residue(){
			A = 14;
			Z = 4;
			m0 = 14.04069708;
		}
		~Residue(){}
};
