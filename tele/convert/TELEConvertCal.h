#include "DSSDEnergyCal.h"
#include "CsIEnergyCal.h"
class DSSDTimeCal{

		double dssdTimeCal[4][32];	
	public:
		void init(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdTimeCal[i][j] = NAN;
				}
			}

		}


		void calibrate(TELEReadRaw *rawData){
		}
		void setBranch(TTree *tree){
			tree->Branch("dssdTimeCal",dssdTimeCal,"dssdTimeCal[4][32]/D");
		}

};

class CsITimeCal{

		double csiTimeCal[7];
	public:
		void init(){
			for(int k = 0;k<7;k++){
				csiTimeCal[k] = NAN;
			}

		}


		void calibrate(TELEReadRaw *rawData){
		}

		void setBranch(TTree *tree){
			tree->Branch("csiTimeCal",csiTimeCal,"csiTimeCal[7]/D");
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
		void calibration(){
			for(int side = 0;side<4;side++)
				for(int id=0;id<32;id++){

					dssdEnergyCal[side][id] = dssdEnergy->calibrate(side,id,getSiliconRawADC(side,id));
					//					dssdTime->calibrate(teleReadRaw);
				}

			for(int k = 0;k<7;k++){
				csiEnergyCal[k] = csiEnergy->calibrate(k,getCsIRawADC(k));
			}
			//csiTime->calibrate(teleReadRaw);
		}
		double getSiliconRawADC(int side, int id){
			return teleReadRaw->getDssdQRaw(side,id);
		}
		double getCsIRawADC(int id){
			return teleReadRaw->getCsIQRaw(id);
		}

		~TELEConvertCal(){
			delete dssdEnergy;
			delete dssdTime;
			delete csiEnergy;
			delete csiTime;
		}



};
