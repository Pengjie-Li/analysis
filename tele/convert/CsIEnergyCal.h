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

		CsIEnergyCalPara *csiEnergyCalPara;
		double csiEnergyCal[7];

		void init(){
			for(int k = 0;k<7;k++){
				csiEnergyCal[k] = NAN;
			}

		}
		double calibrate(int id,double raw){
				return getCsISlope(id)*raw+getCsIOffset(id);
		}
		double getCsISlope(int id){
			return csiEnergyCalPara->getCsISlope(id);
		}
		double getCsIOffset(int id){
			return csiEnergyCalPara->getCsIOffset(id);
		}
	public:
		CsIEnergyCal(){

			csiEnergyCalPara = new CsIEnergyCalPara();
		}

		~CsIEnergyCal(){
			delete csiEnergyCalPara;
		}
		void calibrate(TELEReadRaw *rawData){
			for(int k = 0;k<7;k++){
				csiEnergyCal[k] = calibrate(k,rawData->getCsIQRaw(k));
			}
		}
	
		void setBranch(TTree *tree){

			tree->Branch("csiEnergyCal",csiEnergyCal,"csiEnergyCal[7]/D");
		}
};

