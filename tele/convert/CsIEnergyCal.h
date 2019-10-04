class CsIEnergyCalPara{
	private:
	public:
		double kCsISlope[7];
		double kCsIOffset[7];

		CsIEnergyCalPara(){
			/********************************
			 * CsI: 0 = RLT; 1 = RRT; 2 = RLB; 3 = RRB; 4 = LL; 5 =LRT; 6 = LRB;
			 ********************************/

			double CsISlope[7] = {0.350748,0.306815,0.464291,0.353228,0.357925,0.40584 ,0.350254};
			double CsIOffset[7]= {-108.566,-101.453,-150.243,-117.866,-139.651,-137.378,-105.061};
	
			//double CsISlope[7] = {0.357925,0.40584 ,0.350254,0.350748,0.464291,0.306815,0.353228};
			//double CsIOffset[7]= {-139.651,-137.378,-105.061,-108.566,-150.243,-101.453,-117.866};
			for(int i = 0;i<7;i++){
				kCsISlope[i] = CsISlope[i];
				kCsIOffset[i] = CsIOffset[i];
			}
		}
		double getCsISlope(int id){
			return kCsISlope[id];
		}
		double getCsIOffset(int id){
			return kCsIOffset[id];
		}
		
};
class CsIEnergyCal{
	private:

		TELEReadRaw *rawData;
		CsIEnergyCalPara *csiEnergyCalPara;
		double csiEnergyCal[7];
		double csiQPed[7];
		double csiQSync[7];

		void init(){
			for(int k = 0;k<7;k++){
				csiQPed[k] = NAN;
				csiQSync[k] = NAN;
				csiEnergyCal[k] = NAN;
			}

		}
		double getCsIQRaw(int id){
			return rawData->getCsIQRaw(k);
		}
		double getCsIPedestal(int id){
			return csiEnergyCalPara->getCsIPedestal(k);
		}
		double getCsISyncA(int id){
			return csiEnergyCalPara->getCsISyncA(k);
		}
		double getCsISyncB(int id){
			return csiEnergyCalPara->getCsISyncB(k);
		}
		double getCsICalibA(int id){
			return csiEnergyCalPara->getCsICalibA(k);
		}
		double getCsICalibB(int id){
			return csiEnergyCalPara->getCsICalibB(k);
		}
	
	
	public:
		CsIEnergyCal(){

			csiEnergyCalPara = new CsIEnergyCalPara();
		}

		~CsIEnergyCal(){
			delete csiEnergyCalPara;
		}
		void calibrate(TELEReadRaw *raw){
			rawData = raw;
			for(int k = 0;k<7;k++){
				csiQPed[k] = getCsIQRaw(k) - getCsICalibA;
				csiQSync[k] = getCsISyncA(k)*csiQPed[k]/(1+getCsISyncB(k)*csiQPed[k]);
				csiEnergyCal[k] = getCsICalibA(k)*csiQSync[k]/(1+getCsICalibB(k)*csiQSync[k]);
			}
		}
	
		void setBranch(TTree *tree){

			tree->Branch("csiQPed",csiQPed,"csiQPed[7]/D");
			tree->Branch("csiQSync",csiQSync,"csiQSync[7]/D");
			tree->Branch("csiEnergyCal",csiEnergyCal,"csiEnergyCal[7]/D");
		}
};

