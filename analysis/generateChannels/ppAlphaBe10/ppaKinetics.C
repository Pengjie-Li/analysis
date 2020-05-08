int nEvt = 1500;	
double theta1Min = 60; double theta1Max = 75; // MeV
int eEvt = 1;	
int markerColor = 4;
double  exEnergy = 0;
//int markerColor = 3;
//double  exEnergy = 2;
double T1 = 27.357; double T2 = 564.296; // degree 
//double T1 = 48.916; double T2 = 542.765; // degree 
//double theta1 = 65; double theta2 = 7.672; // degree



class Particle{
		private:
				TString pName;
				double M;
				double T;
				double P;
				double E;
				double theta;
				double phi;
				double beta;
				double gamma;
		public:
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
class Kinetic3Body{
		private:
		public:
				Kinetic3Body(){}
				~Kinetic3Body(){}
};
class Kinetics{
		private:
				double SOL;
				double AMU;	
				Particle a;
				Particle b;
				Particle r0;
				Particle r1;
				Particle r2;
				Particle r3;
				

				Particle r23;// r2 and r3 as a whole in Lab
				Particle r2R23;// r2 in R23 system
				Particle rs2[2];
				Particle rs3[2];
				Particle rs3B[2];

				double cosPhi12;
				double cosTheta1To2; 
				double cosTheta2Prime; 
				double cosTheta3 ;
				double sinTheta23;
				double cosTheta23;
		public:
				Kinetics(){
						SOL= 299.792458;//mm/ns
						AMU= 931.49410242;//MeV/u	
						cosPhi12 = -1;
				}
				~Kinetics(){}
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
						r3.setME(5606.593+ exEnergy,r0.E-r1.E-r2.E);
						r3.print();
				}
				void setR23(){
						r23.setName("R23");
						r23.setEP(r0.E-r1.E,sqrt(pow(r0.P,2) + pow(r1.P,2) - 2*r0.P*r1.P*cos(r1.theta)));
						//r23.print();
						//cout<<sqrt(pow(r0.M,2) + pow(r1.M,2) - 2*r0.E*r1.E + 2*r0.P*r1.P*cos(r1.theta))<<endl; // M23
				}
				double lamda(double x,double y,double z){
						return x*x+y*y+z*z-2*x*y-2*y*z-2*z*x;
				}
				bool setR2R23(){
						r2R23.setName("r2R23");
						double M23 = r23.M; double M2 = r2.M; double M3 = r3.M;
						double E2R23 =(M23*M23 + M2*M2 - M3*M3)/(2*M23); 
						double P2R23 = sqrt(lamda(M23*M23,M2*M2,M3*M3))/(2*M23);
						if(lamda(M23*M23,M2*M2,M3*M3)<=0) return false;
						r2R23.setEP(E2R23 ,P2R23);
						//r2R23.print();
						return true;

				}
			
				void calTheta2Prime(){
						cosTheta2Prime = (r0.P*cos(r2.theta) - r1.P*cosTheta1To2)/r23.P;
						//cout<<"Theta23: "<<sinTheta23<<" "<<cosTheta23<<endl;
						//cout<<"cosTheta1To2 =  "<<cosTheta1To2<<endl;
						//cout<<"cosTheta2Prime =  "<<cosTheta2Prime<<endl;
				}
				void calTheta23(){
						sinTheta23 = r1.P*sin(r1.theta)/r23.P;
						cosTheta23 = (r0.P-r1.P*cos(r1.theta))/r23.P;
						//cout<<"Theta23: "<<sinTheta23<<" "<<cosTheta23<<endl;
				}
				void calTheta1To2(){
						cosTheta1To2 = cos(r1.theta)*cos(r2.theta) + sin(r1.theta)*sin(r2.theta)*cosPhi12;
				}
				double getTheta2Prime(){
						return (r23.gamma*r2.E-r2R23.E)/(r23.gamma*r23.beta*r2.P);
				}
				bool calTheta2(){
						double A = 1;// 
						double B = -2*sinTheta23*cosTheta2Prime;
						double C = cosTheta2Prime*cosTheta2Prime - cosTheta23*cosTheta23;

						if((B*B-4*A*C)<=0) return false;
							
						double S0 = (-B + sqrt(B*B-4*A*C))/(2*A);
						double S1 = (-B - sqrt(B*B-4*A*C))/(2*A);

						//cout<<"Solution : "<<S0<<" "<<S1<<endl;
	
						double SS0 = (cosTheta2Prime - S0*sinTheta23)/cosTheta23;
						double SS1 = (cosTheta2Prime - S1*sinTheta23)/cosTheta23;

						//cout<<"Solution : "<<SS0<<" "<<SS1<<endl;
						rs2[0].setName("r2S0");
						rs2[1].setName("r2S1");
						rs2[0].setMP(r2.M,r2.P);
						rs2[1].setMP(r2.M,r2.P);
						rs2[0].setTheta(acos(SS0)*TMath::RadToDeg());
						rs2[1].setTheta(acos(SS1)*TMath::RadToDeg());
						//rs2[0].print();
						//rs2[1].print();
						return true;
	
				}
				bool calP2(){

						double gamma23 = r23.gamma; double beta23 = r23.beta;
						double E2_R23 = r2R23.E;
						double M2 = r2.M;
						double A = gamma23*gamma23*(1-beta23*beta23*cosTheta2Prime*cosTheta2Prime);
						double B = -2*E2_R23*gamma23*beta23*cosTheta2Prime;
						double C = gamma23*gamma23*M2*M2 - E2_R23*E2_R23;
						double P2S0,P2S1;
						//P2 = (-B + sqrt(B*B-4*A*C))/(2*A);
						if((B*B-4*A*C)<=0) return false;
						P2S0 = (-B + sqrt(B*B-4*A*C))/(2*A);
						P2S1 = (-B - sqrt(B*B-4*A*C))/(2*A);
						
						rs2[0].setName("r2S0");
						rs2[1].setName("r2S1");
						rs2[0].setMP(M2,P2S0);
						rs2[1].setMP(M2,P2S1);
						//rs2[0].print();
						//rs2[1].print();
						return true;
				}
				bool setParticle2(){
						setR23();
						if(!setR2R23()) return false;
						calTheta2Prime();
						if(!calP2()) return false;
						return true;
				}
				double getP3Prime(int i){
					//cout<<a.beta<<" "<<rs3[i].beta<<" "<<rs3B[i].beta<<rs3B[i].P<<endl;
					//if(a.beta<=rs3[i].beta*cosTheta3) return rs3B[i].P;
					//else return -rs3B[i].P;
					//if(i==0)return rs3B[i].P;
					//else return -rs3B[i].P;
					return rs3B[i].P;
				}
				double getTheta2(int i){
					return rs2[i].theta*TMath::RadToDeg();
					//return rs2[1].T;
				}
				void setTheta1(double theta1){
						r1.setTheta(theta1);
				}
				bool setTheta2(){
						setR23();
						if(!setR2R23()) return false;
						cosTheta2Prime = getTheta2Prime();
						calTheta23();
						if(!calTheta2()) return false;
						return true;
				}
				void setParticle3(){

						for (int i = 0; i < 2; ++i) {

								cosTheta1To2 = cos(r1.theta)*cos(rs2[i].theta) + sin(r1.theta)*sin(rs2[i].theta)*cosPhi12;
								rs3[i].setName(Form("r3S%d",i));
								rs3[i].setEP(r0.E-r1.E-rs2[i].E,sqrt( pow(r0.P,2) + pow(r1.P,2) +  pow(rs2[i].P,2) - 2*r0.P*r1.P*cos(r1.theta) - 2*r0.P*rs2[i].P*cos(rs2[i].theta) + 2*r1.P*rs2[i].P*cosTheta1To2));
								//rs3[i].print();

								cosTheta3 = (r0.P-r1.P*cos(r1.theta)-rs2[i].P*cos(rs2[i].theta))/rs3[i].P;
								rs3B[i].setName(Form("r3S%dB",i));
								//rs3B[i].setME(r3.M,(a.E*r3.E-a.P*r3.P*cosTheta3)/a.M);
								rs3B[i].setME(rs3[i].M,(a.E*rs3[i].E-a.P*rs3[i].P*cosTheta3)/a.M);
								//rs3B[i].print();
						}

				}
				void print(){
						r1.print();
						r23.print();
						r2R23.print();
						for (int i = 0; i < 2; ++i) {
								rs2[i].print();
								rs3[i].print();
								rs3B[i].print();
						}
				}

};
void generateKinetics(double *theta1Array,double *theta2Array,double *p3PrimeArray){

		double ma = 10.0113404; double ta = 150;
		double mb = 1.007276466621;double tb = 0;
		double m1 = mb; 
		double m2 = 4.001506105;//He4
		double m3 = 6.017788744;//He6

		//double t1Min = 7.5; double t1Max = 28.0; // MeV
		Kinetics *kin = new Kinetics();
		kin->setParticleA(ma,ta);
		kin->setParticleB(mb,tb);
		kin->setCM();
		kin->setParticle1(m1,T1);
		kin->setParticle2(m2,T2);
		kin->setParticle3(m3);

		int j = 0;	
		for (int i = 0; i < nEvt; ++i) {
				//cout<<"EventNumber : "<<i<<endl;
				double theta1 = theta1Min + (theta1Max-theta1Min)/nEvt*i;
				kin->setTheta1(theta1);
				if(kin->setTheta2()){
						kin->setParticle3();
						theta1Array[j] = theta1;
						theta2Array[j] = kin->getTheta2(0);
						p3PrimeArray[j] = kin->getP3Prime(0);

						//theta2Array[2*j+1] = kin->getTheta2(1);
						//theta1Array[2*j+1] = theta1;
						//p3PrimeArray[2*j+1] = kin->getP3Prime(1);
						//cout<<theta1Array[2*j]<<" "<<theta1Array[2*j+1]<<endl;
						//cout<<theta2Array[2*j]<<" "<<theta2Array[2*j+1]<<endl;
						//cout<<p3PrimeArray[2*j]<<" "<<p3PrimeArray[2*j+1]<<endl;
						j++;
						//kin->print();
				}
		}
		eEvt = j;
		cout<<"Effective Points = "<<eEvt<<endl;
}
void drawT1P3(double *x,double *y){
		TGraph *gr = new TGraph(eEvt,x,y);
		gr->SetTitle("Theta1 vs P3'");
		gr->SetName("Theta1P3Prime");
		gr->GetXaxis()->SetTitle("Theta1(Deg)");
		gr->GetYaxis()->SetTitle("P3'(MeV)");
		gr->SetLineColor(4);
		gr->SetMarkerColor(markerColor);
		gr->SetMarkerSize(2);
		gr->SetMarkerStyle(1);
		gr->SetLineWidth(3);
		gr->SetLineStyle(2);
		gr->Draw("AP");
		gr->Write();
}
void drawT1T2(double *x,double *y){
		TGraph *gr = new TGraph(eEvt,x,y);
		gr->SetTitle("Theta1 vs Theta2");
		gr->SetName("Theta1Theta2");
		gr->GetXaxis()->SetTitle("Theta1(Deg)");
		gr->GetYaxis()->SetTitle("Theta2(Deg)");
		gr->SetLineColor(4);
		gr->SetMarkerColor(markerColor);
		gr->SetMarkerSize(2);
		gr->SetMarkerStyle(1);
		gr->SetLineWidth(3);
		gr->SetLineStyle(2);
		gr->Draw("AP");
		gr->Write();
}

void ppaKinetics(){
		TString fileName = "output.root";
		TFile *outputFile = new TFile(fileName,"RECREATE");

		double theta1Array[10000];
		double theta2Array[10000];
		double p3PrimeArray[10000];
		generateKinetics(theta1Array,theta2Array,p3PrimeArray);
		TCanvas *cPad = new TCanvas("cPad","cPad",1400,600);
		cPad->Divide(2,1);
		cPad->cd(1);
		drawT1T2(theta1Array,theta2Array);
		cPad->cd(2);
		drawT1P3(theta1Array,p3PrimeArray);
		//drawT1P3(p3PrimeArray,theta1Array);
}

