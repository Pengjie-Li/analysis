#include <iostream>
#include <fstream>
#include <TString.h>
#include <TF1.h>
#include <TCanvas.h>
class DataBase{
	private:
		double dbDE[10];
		double dbE[10];
	public:
		DataBase(){
			
			dbDE[0] = 18.45;
			dbE[0] = 1.55;
			dbDE[1] = 15.3;
			dbE[1] = 5.7;
			dbDE[2]=13.73;
			dbE[2]=8.27;
			dbDE[3]=12.63;
			dbE[3]=10.37;
			dbDE[4]=11.78;
			dbE[4]=12.22;
			dbDE[5]=11.22;
			dbE[5]=13.45;
			dbDE[0]=8.89;
			dbE[0]=20.75;

		}
		~DataBase(){}
		double getE(double dE){
		//	if(dE<10) return 20.75;
		//	else return 13.45;
	//		if(dE<10) return 17.71;
	//		else return 11.15;
			if(dE<10) return 20.28;
			else return 12.77;
		
		
		
			//int i = find(dE);
			//return interpolate(i,dE);
		}
		int find(double dE){
			for (int i = 0; i < 10; ++i) {
				if(dbDE[i+1]<dE&&dbDE[i]>=dE) return i;
			}
		}
};
class BarGainCal{
	private:
		double thr;
		TF1 *fit;
		double dE;
		double E;
		double barGain;
	public:

	BarGainCal(){}
	~BarGainCal(){}
	void loadDE(double t){
		thr =t;
	}
	void loadDEERelation(double *par){
		fit =new TF1("dEE","pol3",0,2000);
		//cout<<par[0]<<endl;
		fit->SetParameters(par);
		fit->Draw();
		cout<<fit->GetX(thr,0,1500)<<endl;
	}
	void calibDE(double calPar){
		dE = calPar*thr;
		cout<<"dE="<<dE<<endl;
	}
	void getE(){
		DataBase *dEE = new DataBase();
		E = dEE->getE(dE);
		delete dEE;
	}
	double getSlope(){
		barGain = E/fit->GetX(thr,0,1500);
		return barGain;
		//cout<<barGain<<endl;
	}
};
class DEECal{
	private:
		TString inputFile;
		TString dECalFile;
		double par[14][4];
		double dECalPar[2];
		double barGain[2][7];
		TCanvas *cDraw;
	public:
		DEECal(int i){
			cDraw = new TCanvas("cDraw","cDraw",1400,900);
			cDraw->Divide(7,2);
			nameInput(i);
			load();
			dealAllBars();
		}
		~DEECal(){
		}
		void print(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<barGain[i][j]<<endl;
				}
			}

		}
		void nameInput(int i){
			switch(i){
				case 10:
					inputFile = "../dEE/txt/dEERelation_298_329.txt"; 
					dECalFile = "../plasGain/txt/plasGain_Be10.txt";
					break;
				case 12: 
					inputFile = "../dEE/txt/dEERelation_334_365.txt";
					dECalFile = "../plasGain/txt/plasGain_Be12.txt";
					break;
				case 14:
					inputFile = "../dEE/txt/dEERelation_366_430.txt";
					dECalFile = "../plasGain/txt/plasGain_Be14.txt";
					break;
				case 142:
					inputFile = "../dEE/txt/dEERelation_433_455.txt";
					dECalFile = "../plasGain/txt/plasGain_Be14.txt";
					break;
				default:
					cout<<"Could not locate dEERelation"<<endl;
					exit(0);
			}
		}
		void load(){
			loadDEERelation();
			loadDEPar();
		}
		void loadDEPar(){
			ifstream in1;
			in1.open(dECalFile);
			double gd;
			double gu;
			double sqrt_gd_gu;
			int side = 0;
			while(1){
				in1 >>gu>>gd>>sqrt_gd_gu;
				//cout<<gu<<":"<<gd<<":"<<sqrt_gd_gu<<endl;
				dECalPar[side] = sqrt_gd_gu;
				//cout<<"side:"<<side<<"dECal:"<<dECalPar[side]<<endl;
				side++;
				if(!in1.good()) break;
			}
			in1.close();
		}
		void loadDEERelation(){
			ifstream in;
			in.open(inputFile);
			cout<<inputFile<<endl;
			int side;
			int barNo;
			double p0;
			double p1;
			double p2;
			double p3;
			while(1){
				in >>side>>barNo>>p0>>p0>>p1>>p2>>p3;
				//cout<<side<<":"<<barNo<<":"<<par[0]<<":"<<par[0]<<":"<<par[1]<<":"<<par[2]<<":"<<par[3]<<endl;
				par[7*side+barNo][0] = p0;
				par[7*side+barNo][1] = p1;
				par[7*side+barNo][2] = p2;
				par[7*side+barNo][3] = p3;
				//cout<<" "<<side<<":"<<barNo<<":"<<par[7*side+barNo][0]<<endl;
				if(!in.good()) break;
			}
			in.close();

		}
		void dealAllBars(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {
					//cDraw->cd(i*7+j);
					BarGainCal *barGainCal =new BarGainCal();
					double dEPar = getDECalPar(i);
					barGainCal->loadDE(1500);
					barGainCal->loadDEERelation(par[i*7+j]);
					barGainCal->calibDE(dEPar);
					barGainCal->getE();
					barGain[i][j] = barGainCal->getSlope();
					
				}
			}
		}
		double getDECalPar(int side){
			return dECalPar[side];
		}

};
void calDEERelation(){
	// 10-Be 12-Be 14-Be 142-Be	
	DEECal *dEECal =new DEECal(10);
	dEECal->print();
}
