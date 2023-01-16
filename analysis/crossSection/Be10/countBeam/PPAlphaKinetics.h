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
				Particle(){
					phi = 0;
					theta = 0;
				}
				~Particle(){}
				void init(){

					M = NAN;
					T = NAN;
					P = NAN;
					E = NAN;
					theta = 0;
					phi = 0;
					beta = NAN;
					gamma = NAN; 	
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
				void setBranch(TTree *tree){
					tree->Branch("M"+pName,&M,"M"+pName+"/D");
					tree->Branch("E"+pName,&E,"E"+pName+"/D");
					tree->Branch("P"+pName,&P,"P"+pName+"/D");
					tree->Branch("T"+pName,&T,"T"+pName+"/D");
					tree->Branch("theta"+pName,&theta,"theta"+pName+"/D");
					tree->Branch("phi"+pName,&phi,"phi"+pName+"/D");
					//tree->Branch("M"+pName,&M,"M"+pName+"/D");
				}
};
class PPAlphaKinetics{
		private:
				TEnv *env;
				double SOL;
				double AMU;	
				Particle a;
				Particle b;
				Particle r0;
				Particle r1;
				Particle r2;
				Particle r3;
				Particle r3B;
				double P3Prime;
				double exEnergy;

				double ma;
				double mb;
				double m1;
				double m2;
				double m3;
				ReadFile *rf;
		public:
				PPAlphaKinetics(ReadFile *rf):rf(rf){
					env = new TEnv("configPPBe.prm");
						SOL= 299.792458;//mm/ns
						AMU= 931.49410242;//MeV/u	

						a.setName("a");
						b.setName("b");
						r0.setName("CM");
						r1.setName("1");
						r2.setName("2");
						r3.setName("3");

						ma = env->GetValue("ma",9.0);
						mb = env->GetValue("mb",1.0);
						m1 = env->GetValue("m1",1.0);
						m2 = env->GetValue("m2",4.0);
						m3 = env->GetValue("m3",6.0);
				}

				~PPAlphaKinetics(){}
				void setBranch(TTree *tree){
					a.setBranch(tree);
					b.setBranch(tree);
					r1.setBranch(tree);
					r2.setBranch(tree);
					r3.setBranch(tree);
					tree->Branch("P3Prime", &P3Prime, "P3Prime/D");
					tree->Branch("exEnergy", &exEnergy, "exEnergy/D");
				}
				void init(){
					a.init();
					b.init();
					r1.init();
					r2.init();
					r3.init();
					r3B.init();
					P3Prime = NAN;
					exEnergy = NAN;
				}
				void calculate(){
					init();
					setParticleA();
					setParticleB();
					setCM();
					setParticle1();
					setParticle2();
					setParticle3();
					setParticle3BeamSystem();
					setP3Prime();
					setExEnergy();
				}
				void setParticleA(){
						a.setMT(ma*AMU,rf->getBeamEnergy()*ma);
						//a.setMT(9327.6075,rf->getBeamEnergy()*10);
						//a.print();
				}
				void setParticleB(){
						double tb = 0;
						b.setMT(mb*AMU,tb*mb);
						//b.print();
				}
				void setCM(){
						TLorentzVector cm = a.getLorentzVector() + b.getLorentzVector();		
						r0.setLorentzVector(cm);
						//r0.print();
				}
				void setParticle1(){
						//r1.setMT(,t1);
						r1.setMT(m1*AMU,rf->getProtonEnergy());
						r1.setTheta(rf->getEspriAngle());
						//r1.print();
				}
				void setParticle2(){
						r2.setMT(m2*AMU,rf->getAlphaEnergy());	
						r2.setTheta(rf->getTeleAngle());
						//r2.print();
				}
				void setParticle3(){
						//r3.setM();

					double theta3 = rf->getFdc0Angle();
					//cout<<rf->getEspriPhi() - rf->getTelePhi()<<endl;
					double cosPhi12 = cos((rf->getEspriPhi()-rf->getTelePhi())*TMath::DegToRad());
					//double cosPhi12 = -1;
					double cosTheta1To2 = cos(r1.theta)*cos(r2.theta) + sin(r1.theta)*sin(r2.theta)*cosPhi12;

					//r3.setEP(r0.E-r1.E-r2.E,);
					r3.setEP(r0.E-r1.E-r2.E,sqrt( pow(r0.P,2) + pow(r1.P,2) +  pow(r2.P,2) - 2*r0.P*r1.P*cos(r1.theta) - 2*r0.P*r2.P*cos(r2.theta) + 2*r1.P*r2.P*cosTheta1To2));
					//r3.setME(m3*AMU,r0.E-r1.E-r2.E);
					double cosTheta3 = (r0.P-r1.P*cos(r1.theta)-r2.P*cos(r2.theta))/r3.P;
					r3.setTheta(acos(cosTheta3)*TMath::RadToDeg());
					//r3.setTheta(theta3);
					//cout<<cosPhi12<<" "<<cosTheta1To2<<endl;
					//cout<<theta3<<" "<<r3.theta*TMath::RadToDeg()<<" "<<cosTheta3<<endl;
					r3.print();
				}
				void setParticle3BeamSystem(){
					r3B.setName("r3B");
					double cosTheta3 = cos(r3.theta);
					double sinTheta3 = sin(r3.theta);
					//cout<<cosTheta3<<endl;
					//r3B.setME(r3.M,(a.E*r3.E-a.P*r3.P*cosTheta3)/a.M);
					//r3B.setMP(r3.M,(a.E*r3.P-a.P*r3.E*cosTheta3)/a.M);
					//r3B.setEP((a.E*r3.E-a.P*r3.P*cosTheta3)/a.M,(a.E*r3.P-a.P*r3.E*cosTheta3)/a.M);
					double gamma = a.E/a.M; double beta = a.P/a.E;
					double EStar =(gamma*r3.E- gamma*beta*r3.P*cosTheta3);
					double PzStar = (-gamma*beta*r3.E + gamma*r3.P*cosTheta3);
					double PpenStar = r3.P*sinTheta3;
					double PStar = sqrt(PpenStar*PpenStar + PzStar*PzStar);
					//a.print();
					//cout<<gamma<<" "<<beta<<endl;
					r3B.setME(r3.M,EStar);
					//cout<<PStar<<" "<<PzStar<<" "<<PpenStar<<endl;	
					//r3B.setEP(EStar,PStar);
					//r3B.setME(r3.M,(a.E*r3.E-a.P*r3.P)/a.M);
					//r3B.print();
				}
				void setExEnergy(){
					exEnergy = r3.M - m3*AMU;
				}
				void setP3Prime(){
					if(a.beta<=r3.beta*cos(r3.theta)) P3Prime = r3B.P;
					else P3Prime = -r3B.P;
				}
				void print(){
					a.print();
					b.print();
					r1.print();
					r2.print();
					r3.print();
					r3B.print();
					cout<<"P3Prime = "<<P3Prime<<endl;
					cout<<"exEnergy = "<<exEnergy<<endl;
				}
};
