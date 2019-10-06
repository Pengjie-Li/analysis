#include "DSSDEnergyCal.h"
#include "CsIEnergyCal.h"
class DSSDTimeCal{

		double dssdTCal[4][32];	
	public:
		void init(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdTCal[i][j] = NAN;
				}
			}

		}


		void calibrate(TELEReadRaw *rawData){
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdTCal",dssdTCal,"dssdTCal[4][32]/D");
		}

};

class CsITimeCal{

		double csiTCal[7];
	public:
		void init(){
			for(int k = 0;k<7;k++){
				csiTCal[k] = NAN;
			}

		}


		void calibrate(TELEReadRaw *rawData){
		}

		void setBranch(TTree *tree){
			tree->Branch("csiTCal",csiTCal,"csiTCal[7]/D");
		}


};


class TELEConvertCal{
	private:
	public:
		TELEReadRaw *teleReadRaw;	

		DSSDEnergyCal	*dssdEnergy;
		DSSDTimeCal	*dssdTime;
		CsIEnergyCal	*csiEnergy;
		CsITimeCal 	*csiTime;


		TELEConvertCal(){
			dssdEnergy = new DSSDEnergyCal();
			dssdTime   = new DSSDTimeCal();
			csiEnergy  = new CsIEnergyCal();
			csiTime    = new CsITimeCal();
		}

		void setBranch(TTree *tree){
			dssdEnergy->setBranch(tree);
			dssdTime->setBranch(tree);
			csiEnergy->setBranch(tree);
			csiTime->setBranch(tree);
			
		}

		void calibration(TELEReadRaw *rawData){
			teleReadRaw = NULL;
			teleReadRaw = rawData;
			dssdEnergy->calibrate(rawData);
			csiEnergy->calibrate(rawData);
			dssdTime->calibrate(rawData);
			csiTime->calibrate(rawData);

		}

		~TELEConvertCal(){
			delete dssdEnergy;
			delete dssdTime;
			delete csiEnergy;
			delete csiTime;
		}



};
