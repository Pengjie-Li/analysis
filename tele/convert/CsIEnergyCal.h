class CsIEnergyCalParameter{
	private:
	public:
		double kCsISlope[7];
		double kCsIOffset[7];

		CsIEnergyCalParameter(){
			double CsISlope[7] = {0.357925,0.40584 ,0.350254,0.350748,0.464291,0.306815,0.353228};
			double CsIOffset[7]= {-139.651,-137.378,-105.061,-108.566,-150.243,-101.453,-117.866};
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
CsIEnergyCalParameter *csiEnergyCalParameter = new CsIEnergyCalParameter();
class CsIEnergyCal{
	private:

		double csiEnergyCal[7];
		void init(){
			for(int k = 0;k<7;k++){
				csiEnergyCal[k] = NAN;
			}

		}


	public:
		double calibrate(int id,double raw){
				return getCsISlope(id)*raw+getCsIOffset(id);
		}
		double getCsISlope(int id){
			return csiEnergyCalParameter->getCsISlope(id);
		}
		double getCsIOffset(int id){
			return csiEnergyCalParameter->getCsIOffset(id);
		}
};

