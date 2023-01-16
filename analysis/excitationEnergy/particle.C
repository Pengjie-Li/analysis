
double AMU = 931.49410242;
//double speedOfLight = 299792458;
double speedOfLight = 1;
class Particle{
	private:
		// Energy in MeV
		int A;
		int Z;
		double mass;// in u unit
		double momentum;
		double kE;// kinematic Energy

		double totE;// totE = mE + kE;
		double momE;
		double massE;
	public:
		Particle(){}
		Particle(double m,double k){// rest mass in u, kinematic Energy per u
			mass = m;
			kE = k*mass;
			massE = mass*AMU;
			momE = sqrt(kE*kE+2*kE*massE);
			totE = massE + kE;
			momentum = momE/speedOfLight;
		}
		~Particle(){}
		double getMassEnergy(){
			return massE;
		}
		double getMomentumEnergy{
			return momE;
		}
		double getTotalEnergy(){
			return totE;
		}
		void print(){
			cout<<"mass = "<<mass<<" u "<<" mass Energy = "<<massE<<endl;;
			cout<<"momentum = "<<momentum<<" MeV/c "<<" Momentum Energy = "<<momE<<endl;;
			cout<<"kinematic Energy = "<<kE <<" total Energy = "<<totE<<endl;
		}
};


void particle(){
	//Particle *Be10 = new Particle(10.0113, 150);
	Particle *Be10 = new Particle(10.0113,1498.0119/10.0113);
	Be10->print();
}
