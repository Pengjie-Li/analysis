#include <TLorentzVector.h>
class Particle{
		private:
		public:
				TString pName;
				double M;
				double T;
				double P;
				double E;
				double theta;
				double phi;
				double beta;
				double gamma;
				Particle(){}
				~Particle(){}
				void setName(TString name){
						pName = name;
						phi = 0;
						theta = 0;
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
					theta = th*TMath::DegToRad();
				}
				void setPhi(double pi){
					phi = pi;
				}
				void print(){
						cout<<"Particle "<<pName<<"\t"<<M<<"\t"<<E<<"\t"<<P<<"\t"<<gamma<<"\t"<<beta<<"\t"<<theta*TMath::RadToDeg()<<endl;
				}
				TLorentzVector getLorentzVector(){
						TLorentzVector x(0,0,P,E);
						return x;
				}
				void setMT(double m,double t){
					M = m; T = t;
					E = M + T;
					P = sqrt(E*E - M*M);
					gamma = E/M;
					beta = P/E;
				}
				void setMP(double m,double p){
					M = m; P = p;
					E = sqrt(M*M + P*P);
					T = E - M;
					gamma = E/M;
					beta = P/E;
				}
				void setME(double m,double e){
					M = m; E = e;
					P = sqrt(E*E - M*M);
					T = E - M;
					gamma = E/M;
					beta = P/E;
				}
	
				void setEP(double e,double p){
					E = e; P = p;
					M = sqrt(E*E - P*P);
					T = E - M;
					gamma = E/M;
					beta = P/E;
				}
				void setLorentzVector(TLorentzVector x){
						P = x.P();
						M = x.M();
						E = x.E();
						T = x.T();
						gamma = E/M;
						beta = P/E;
				}
};
class PPAlphaKinetics{
		private:
				double SOL;
				double AMU;	
				Particle a;
				Particle b;
				Particle r0;
				Particle r1;
				Particle r2;
				Particle r3;
				
				ReadFile *rf;
		public:
				PPAlphaKinetics(ReadFile *rf):rf(rf){
						SOL= 299.792458;//mm/ns
						AMU= 931.49410242;//MeV/u	
				}
				~PPAlphaKinetics(){}
				void setBranch(TTree *tree){
				}

				void calculate(){
				}
				void setParticleA(double ma,double ta){
						a.setName("a");
						//a.setMT(ma*AMU,ta*ma);
						a.setMT(9327.6075,ta*ma);
						a.print();
				}
				void setParticleB(double mb,double tb){
						b.setName("b");
						//b.setMT(mb*AMU,tb*mb);
						b.setMT(938.783,tb*mb);
						b.print();
				}
				void setCM(){
						r0.setName("CM");
						TLorentzVector cm = a.getLorentzVector() + b.getLorentzVector();		
						r0.setLorentzVector(cm);
						r0.print();
				}
				void setParticle1(double m1,double t1){
						r1.setName("1");
						//r1.setMT(m1*AMU,t1);
						r1.setMT(938.783,t1);
						r1.print();
				}
				void setParticle2(double m2,double T2){
						r2.setName("2");
						//r2.setM(m2*AMU);	
						r2.setMT(3728.4,T2);	
						r2.print();
				}
				void setParticle3(double m3){
						r3.setName("3");
						//r3.setM(m3*AMU);
						r3.setME(5606.593,r0.E-r1.E-r2.E);
						r3.print();
				}
};
