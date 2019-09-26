class PositionTELE{
	public:
		double leftXPosition[32][32];
		double rightXPosition[32][32];

		double leftYPosition[32][32];
		double rightYPosition[32][32];

		double leftZPosition[32][32];
		double rightZPosition[32][32];

		PositionTELE(){
			loadPositionTELE(0,leftXPosition,leftYPosition,leftZPosition);
			loadPositionTELE(1,rightXPosition,rightYPosition,rightZPosition);
		}

		void loadPositionTELE(int isLR,double xPosition[32][32],double yPosition[32][32],double zPosition[32][32]){
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



		TVector3 getTELEPosition(int isLR, int fid, int bid){
			TVector3 result;
			if(isLR = 0) result.SetXYZ(leftXPosition[fid][bid],leftYPosition[fid][bid],leftZPosition[fid][bid]);
			else result.SetXYZ(rightXPosition[fid][bid],rightYPosition[fid][bid],rightZPosition[fid][bid]);
			return result;
		}
};
