#include "ESPRIRdcHit.h"
#include "ESPRINaiHit.h"
#include "ESPRIPlasHit.h"
class ESPRIDetHit{
	private:
		int runNumber;
		ESPRIRdcHit *rdcHit;
		ESPRINaiHit *naiHit;
		ESPRIPlasHit *plasHit;
	public:

		ESPRIDetHit(){
			cout<<"Create: rdcHit:naiHit:plasHit"<<endl;
			rdcHit	 = new ESPRIRdcHit();
			naiHit	 = new ESPRINaiHit();
			plasHit	 = new ESPRIPlasHit();
		}
		~ESPRIDetHit(){
			delete rdcHit;
			delete naiHit;
			delete plasHit;
		}

		void init(){
			rdcHit->init();
			naiHit->init();
			plasHit->init();
		}
		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void sortHit(ESPRIReadRaw *espriRaw){
			//rdcHit->sortHit(espriRaw->getTdcRaw());

			naiHit->sortHit(espriRaw->getNaiRaw());

			plasHit->sortHit(espriRaw->getPlasRaw());
		}
		void readAndSortReconstructedData(TClonesArray *rdcArray){
			rdcHit->readReconstructedData(rdcArray);
		}
		void setBranch(TTree *tree){
			rdcHit->setBranch(tree);
			naiHit->setBranch(tree); 
			plasHit->setBranch(tree);
		}
		void printRdc(){
			//if(rdcHit->getNHit()>1&&plasHit->getNHit()>1) rdcHit->print();
			rdcHit->print();
		}
	
		void printPlas(){
			//if(rdcHit->getNHit()>1&&plasHit->getNHit()>1) plasHit->print();
			plasHit->print();
		}
		void printNai(){
			//if(rdcHit->getNHit()>1&&plasHit->getNHit()>1) naiHit->print();
			naiHit->print();
		}
		int getRdcHit(){
			return rdcHit->getNHit();
		}
		int getRdcSide(int hitId){
			return rdcHit->getSide(hitId);
		}
		double getRdcX(int side){
			return rdcHit->getRdcX(side);
		}
		double getRdcY(int side){
			return rdcHit->getRdcY(side);
		}
		int getPlasHit(){
			return plasHit->getNHit();
		}
		int getPlasSide(int hitId){
			return plasHit->getSide(hitId);
		}
		double getPlasQPed(int side){
			return plasHit->getBarQPed(side);
		}
		int getNaiHit(){
			return naiHit->getHit();
		}
		int getNaiSide(int hitId){
			return naiHit->getSide(hitId);
		}
		double getNaiQPed(int side,int &barId){
			return naiHit->getNaiQPed(side,barId);
		}


};
