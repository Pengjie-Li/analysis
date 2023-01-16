#include "DssdCal.h"
#include "CsiCal.h"


class TELEConvertCal{
	private:
	public:
		TELEReadRaw *teleReadRaw;	

		DssdCal *dssdCal;
		CsiCal *csiCal;
		
	
		TELEConvertCal(){
			dssdCal = new DssdCal();
			csiCal = new CsiCal();
		}

		void setBranch(TTree *tree){
			dssdCal->setBranch(tree);	
			csiCal->setBranch(tree);	
		}
		void init(){
			teleReadRaw = NULL;
			dssdCal->init();
			csiCal->init();
		}

		void calibration(TELEReadRaw *rawData){
			teleReadRaw = rawData;
			// dssd Must have hit, then csi have Hit, then Tele has Hit
			dssdCal->calibration(rawData);
			csiCal->calibration(rawData);
			
		}
		void print(){
			dssdCal->print();
			csiCal->print();
		}

		~TELEConvertCal(){
			delete dssdCal;
			delete csiCal;
		}

};
