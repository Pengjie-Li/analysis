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

		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void sortHit(ESPRIReadRaw *espriRaw){
			rdcHit->convertHit(espriRaw->getTdcRaw());

			naiHit->updateRunNumber(runNumber);
			naiHit->convertHit(espriRaw->getNaiRaw());

			plasHit->updateRunNumber(runNumber);
			plasHit->convertHit(espriRaw->getPlasRaw());
		}
		//void readReconstructedData11(TClonesArray *rdcArray){
		//	rdcHit->readReconstructedData(rdcArray);
		//}
		void keepRdcSide(int side){
			rdcHit->keepRdcSide(side);
		}
		void keepPlasSide(int side){
			plasHit->keepPlasSide(side);
		}
		void keepNaiSide(int side){
			naiHit->keepNaiSide(side);
		}
		void swapNaiSide(){
			naiHit->swapNaiSide();
		}
		void swapPlasSide(){
			plasHit->swapPlasSide();
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

		int getPlasHit(){
			return plasHit->getNHit();
		}

		int getPlasSide(int hitId){
			return plasHit->getSide(hitId);
		}
		int getNaiHit(){
			return naiHit->getHit();
		}
		int getNaiSide(int hitId){
			return naiHit->getSide(hitId);
		}


};
