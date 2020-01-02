#include "ESPRIRdcCal.h"
#include "ESPRINaiCal.h"
#include "ESPRIPlasCal.h"
class ESPRIConvertCal{
	private:
		int runNumber;
		ESPRIRdcCal *rdcCal;
		ESPRINaiCal *naiCal;
		ESPRIPlasCal *plasCal;
	public:

		ESPRIConvertCal(){
			cout<<"Create: rdcCal:naiCal:plasCal"<<endl;
			rdcCal	 = new ESPRIRdcCal();
			naiCal	 = new ESPRINaiCal();
			plasCal	 = new ESPRIPlasCal();
		}
		~ESPRIConvertCal(){
			delete rdcCal;
			delete naiCal;
			delete plasCal;
		}

		void updateRunNumber(int run){
			runNumber = -1;
			runNumber = run;
		}
		void convertCal(ESPRIReadRaw *espriRaw){
			rdcCal->convertCal(espriRaw->getTdcRaw());

			naiCal->updateRunNumber(runNumber);
			naiCal->convertCal(espriRaw->getNaiRaw());

			plasCal->updateRunNumber(runNumber);
			plasCal->convertCal(espriRaw->getPlasRaw());
		}
		void readReconstructedData(TClonesArray *rdcArray){
			rdcCal->readReconstructedData(rdcArray);
		}
		void keepRdcSide(int side){
			rdcCal->keepRdcSide(side);
		}
		void keepPlasSide(int side){
			plasCal->keepPlasSide(side);
		}
		void swapPlasSide(){
			plasCal->swapPlasSide();
		}
		void setBranch(TTree *tree){
			rdcCal->setBranch(tree);
			naiCal->setBranch(tree); 
			plasCal->setBranch(tree);
		}
		void printRdc(){
			//if(rdcCal->getNHit()>1&&plasCal->getNHit()>1) rdcCal->print();
			rdcCal->print();
		}
	
		void printPlas(){
			//if(rdcCal->getNHit()>1&&plasCal->getNHit()>1) plasCal->print();
			plasCal->print();
		}
		void printNai(){
			//if(rdcCal->getNHit()>1&&plasCal->getNHit()>1) naiCal->print();
			naiCal->print();
		}
		int getRdcHit(){
			return rdcCal->getNHit();
		}
		int getRdcSide(int hitId){
			return rdcCal->getSide(hitId);
		}

		int getPlasHit(){
			return plasCal->getNHit();
		}

		int getPlasSide(int hitId){
			return plasCal->getSide(hitId);
		}


};
