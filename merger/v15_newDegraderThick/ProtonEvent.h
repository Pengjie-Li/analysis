#include "DegraderPosition.h"
class ProtonPara{
	private:
		double ppPlasE;
		double ppDegraderE;
		double ppWinE;
		double ppShtE;

		TGraph *plasEnergyToRange;
		TGraph *plasRangeToEnergy;

		TGraph *degraderEnergyToRange;
		TGraph *degraderRangeToEnergy;

		TGraph *shtEnergyToRange;
		TGraph *shtRangeToEnergy;
		TGraph *winEloss;
		TGraph *wedgeThick;

		double degraderThickness;
		double plasThickness;
		double shtThickness;


		double getSHTE(double angle,double energyOut){
			double realThickness = shtThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + shtEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = shtRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"SHT "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getPlasE(double angle,double energyOut){
			double realThickness = plasThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + plasEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = plasRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"Plas "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getWindowE(double energy){
			return winEloss->Eval(energy);
		}
		double getDegraderE(double angle,double energyOut,double xPos){
			double realThickness = getDegraderThickness(xPos)/cos(angle*TMath::DegToRad()); 
			degraderThickness = realThickness;
			//realThickness = 0.9*realThickness;
			//double realThickness = getDegraderThickness(xPos); 
			if(realThickness == 0) return 0;
			double rangeIn = realThickness + degraderEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = degraderRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"Degrader "<<xPos<<" "<<realThickness<<" "<<energyIn<<" "<<energyOut<<endl;
			return (energyIn-energyOut);
		}

		double getDegraderThickness(double xPos){
			return wedgeThick->Eval(xPos + 227.5);
		}

	public:
		ProtonPara(){
			plasThickness = 4; //mm
			shtThickness = 1; //mm , assume reaction happened in the middle

			TString eloosName = "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/protonInMaterials.root";
			TFile *fEloss = new TFile(eloosName,"READ");
			shtEnergyToRange = (TGraph *)gDirectory->Get("protonTargetER");
			shtRangeToEnergy = (TGraph *)gDirectory->Get("protonTargetRE");
			plasEnergyToRange = (TGraph *)gDirectory->Get("protonPlasER");
			plasRangeToEnergy = (TGraph *)gDirectory->Get("protonPlasRE");
			degraderEnergyToRange = (TGraph *)gDirectory->Get("protonDegraderER");
			degraderRangeToEnergy = (TGraph *)gDirectory->Get("protonDegraderRE");
			fEloss->Close();	

			TString winEloosName = "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/protonWindowEloss.root";
			TFile *fWinEloss = new TFile(winEloosName,"READ");
			winEloss = (TGraph *)gDirectory->Get("windowEloss");
			fWinEloss->Close();

			TString wedgeFileName = "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/espri/calib/wedge/wedgeThickness.root";
			TFile *fWedgeThick = new TFile(wedgeFileName,"READ");
			wedgeThick = (TGraph *)gDirectory->Get("th2");
			fWedgeThick->Close();

		}
		~ProtonPara(){}
		double getProtonEnergy(double naiE,double locusAngle,double angle,double xPos){
			ppPlasE = getPlasE(locusAngle,naiE);
			ppDegraderE = getDegraderE(locusAngle,naiE+ppPlasE,xPos);
			ppWinE = getWindowE(naiE+ppPlasE+ppDegraderE);
			ppShtE = getSHTE(angle,naiE+ppPlasE+ppDegraderE+ppWinE);
		
			return naiE+ppPlasE+ppDegraderE+ppWinE+ppShtE;
		}
		void init(){
			ppPlasE = -9999;
			ppDegraderE = -9999;
			ppWinE = -9999;
			ppShtE = -9999;
			degraderThickness = NAN;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("ppDegraderE",&ppDegraderE,"ppDegraderE/D");
			tree->Branch("ppPlasE",&ppPlasE,"ppPlasE/D");
			tree->Branch("ppWinE",&ppWinE,"ppWinE/D");
			tree->Branch("ppShtE",&ppShtE,"ppShtE/D");
			tree->Branch("degraderThickness",&degraderThickness,"degraderThickness/D");
		}
		void print(){
			cout<<" shtE = "<<ppShtE<<" winE ="<<ppWinE<<" plasE = "<<ppPlasE<<" degraderE = "<<ppDegraderE<<endl;
		}

};

class ProtonEvent{
	private:
		double protonEnergy;


		EspriEvent *espriEvent;
		ProtonPara *protonPara;
		DegraderPosition *degraderPosition;

		void setProtonEnergy(){
			if(espriEvent->isNaiHit()){
				double xPos = degraderPosition->getPosition(espriEvent->getEspriSide(),espriEvent->getRdcPosition(),espriEvent->getTargetPosition()); 
				if(espriEvent->getEspriSide() == 1) {
				}
				else{ 
						xPos = -xPos;
				}
				protonEnergy = protonPara->getProtonEnergy(espriEvent->getNaiEnergy(),espriEvent->getLocusAngle(),espriEvent->getAngle(),xPos);
			}
		}
	public:
		ProtonEvent(){
			protonPara = new ProtonPara();
			degraderPosition = new DegraderPosition();
		}
		~ProtonEvent(){
			delete protonPara;
			delete degraderPosition;
		}
		bool isGoodEvent(){
			return espriEvent->isGoodEvent();
		}

		void init(){
			protonPara->init();
			espriEvent = NULL;
			protonEnergy = NAN;
		}
		void load(EspriEvent *ee){
			espriEvent = ee;
		}
		void setEvent(){
			if(isGoodEvent()){
				setProtonEnergy();
			}
		}
		void print(){
			protonPara->print();
			cout<<"Proton Energy = "<<protonEnergy<<" "<<endl;
		}
		void setOutputBranch(TTree *tree){
			protonPara->setOutputBranch(tree);
			tree->Branch("protonEnergy",&protonEnergy,"protonEnergy/D");
		}
};
