
class DSSDEnergyCalParameter{
	private:
		double kScmSlope[4][32];
		double bScmOffset[4][32];
		double ekScmSlope[4][32];
		double ebScmOffset[4][32];

		double kCalSlope[2];
		double bCalOffset[2];

	public:

		DSSDEnergyCalParameter(){
			loadSiliconCalibrationParameters(kScmSlope,bScmOffset,ekScmSlope,ebScmOffset);
			kCalSlope[0] = 7.17797775;
			bCalOffset[0] = -1524.240925;

			kCalSlope[1] = 7.685283145;
			bCalOffset[1] = -1646.273395;
		}
		void loadSiliconCalibrationParameters(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32]){
			ifstream in;
			TString par_name;

			par_name="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/Remove/DSSD_Fit_Whole.txt";

			in.open(par_name);
			//      if(!in.open(par_name))
			//      {
			//              cout<<"Error: parameter file didn't open"<<endl;
			//              cout<<par_name<<endl;
			//      }
			int side;
			int strip;
			double  k0;
			double  b0;
			double ek0;
			double eb0;
			while (1)
			{
				in >>side>>strip>>k0>>b0>>ek0>>eb0;
				//cout<<side<< "  "<<strip<<endl;
				if (!in.good()) break;


				k[side][strip]=k0;
				ek[side][strip]=ek0;

				b[side][strip]=b0;
				eb[side][strip]=eb0;

			}
		}
		double getSiliconScmSlope(int side, int id){
			return kScmSlope[side][id];
		}
		double getSiliconScmOffset(int side, int id){
			return bScmOffset[side][id];
		}
		double getSiliconCalSlope(int side){
			return kCalSlope[side/2];
		}
		double getSiliconCalOffset(int side){
			return bCalOffset[side/2];
		}


};

DSSDEnergyCalParameter *dssdCalibrationParameter = new DSSDEnergyCalParameter();

class DSSDEnergyCal{
	public:
		DSSDEnergyCal(){
		}
		double calibrate(int side,int id,double raw){
			// raw->SCM->cal
			//side = 0 LF, 1 LB, 2 RF, 3 RB
			double scm = getSiliconScmSlope(side,id)*raw + getSiliconScmOffset(side,id);
			double cal = getSiliconCalSlope(side)*scm + getSiliconCalOffset(side);

			// Some ADC Saturation events
			if(raw>4096){
				raw = -9999;
				scm = -9999;
				cal = -9999;
			}
			return cal;

		}
		double getSiliconScmSlope(int side, int id){
			return dssdCalibrationParameter->getSiliconScmSlope(side,id);
		}
		double getSiliconScmOffset(int side, int id){
			return dssdCalibrationParameter->getSiliconScmOffset(side,id);
		}

		double getSiliconCalSlope(int side){
			return dssdCalibrationParameter->getSiliconCalSlope(side);
		}

		double getSiliconCalOffset(int side){
			return dssdCalibrationParameter->getSiliconCalOffset(side);
		}
};

