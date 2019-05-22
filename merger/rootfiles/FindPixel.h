
class DSSDPosition{
	public:
		double leftXPosition[32][32];
		double rightXPosition[32][32];

		double leftYPosition[32][32];
		double rightYPosition[32][32];

		double leftZPosition[32][32];
		double rightZPosition[32][32];

		DSSDPosition(){
			loadDSSDPosition(0,leftXPosition,leftYPosition,leftZPosition);
			loadDSSDPosition(1,rightXPosition,rightYPosition,rightZPosition);
		}

                void loadDSSDPosition(int isLR,double xPosition[32][32],double yPosition[32][32],double zPosition[32][32]){
                        ifstream in;
                        TString inputName;

			if(isLR = 0) inputName="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/tele/scattering_angle/OnePixelGenerateAllPixelPosition/LeftDSSDPixelPosition.txt";
			else inputName = "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/tele/scattering_angle/OnePixelGenerateAllPixelPosition/RightDSSDPixelPosition.txt";

			in.open(inputName);

			int fid;
			int bid;
			double  x0;
			double  y0;
			double  z0;
			while (1)
			{
				in >>fid>>bid>>x0>>y0>>z0;
				//cout<<side<< "  "<<strip<<endl;
				if (!in.good()) break;
				xPosition[fid][bid] = x0;
				yPosition[fid][bid] = y0;
				zPosition[fid][bid] = z0;
			}
		}



		TVector3 getPositionVector(int isLR, int fid, int bid){
			TVector3 result;
			if(isLR = 0) result.SetXYZ(leftXPosition[fid][bid],leftYPosition[fid][bid],leftZPosition[fid][bid]);
			else result.SetXYZ(rightXPosition[fid][bid],rightYPosition[fid][bid],rightZPosition[fid][bid]);
			return result;
		}
};
DSSDPosition *dssdPosition = new DSSDPosition();
class FindPixel{
	private:
		const static double threshold = 500;
	public:
		int isLR;
		int fid;
		int bid;
	double dssdEnergyFront;
	double dssdEnergyBack;

	int lfid;
	int lbid;
	int rfid;
	int rbid;

	double lfenergy;
	double lbenergy;
	double rfenergy;
	double rbenergy;

	FindPixel(double dssdEnergyCal[4][32]){
		findMaximum(dssdEnergyCal[0],lfid,lfenergy);
		findMaximum(dssdEnergyCal[1],lbid,lbenergy);

		findMaximum(dssdEnergyCal[2],rfid,rfenergy);
		findMaximum(dssdEnergyCal[3],rbid,rbenergy);
		
		if((lfenergy+lbenergy)/2 > (rfenergy+rbenergy)/2){
			isLR = 0;
			fid = lfid;
			bid = lbid;
			dssdEnergyFront = lfenergy;
			dssdEnergyBack  = lbenergy;
		}else{
			isLR = 1;
			fid = rfid;
			bid = rbid;
			dssdEnergyFront = rfenergy;
			dssdEnergyBack  = rbenergy;

		}
	}

	void findMaximum(double *array,int &id,double &maxEnergy){
		id = -1;
		maxEnergy = threshold;
		for(int i = 0;i<32;i++){
			if(array[i]>maxEnergy){
				id = i;
				maxEnergy =array[i];
				//cout<<id<<" "<<maxEnergy<<endl;
			}
		}
	}
	TVector3 getVectorDSSD(){
		TVector3 v1(-1,-1,-1);
		if(fid>-1&&bid>-1) v1 = dssdPosition->getPositionVector(isLR,fid,bid);
		return v1;
	}
	int getFrontId(){
		return fid;
	}
	int getBackId(){
		return bid;
	}
	double getDSSDEnergyFront(){
		return dssdEnergyFront;
	}
	double getDSSDEnergyBack(){
		return dssdEnergyBack;
	}

	
};
