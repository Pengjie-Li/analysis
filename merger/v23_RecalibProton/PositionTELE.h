class PositionTELE{
	public:
		double leftXPosition[32][32];
		double rightXPosition[32][32];

		double leftYPosition[32][32];
		double rightYPosition[32][32];

		double leftZPosition[32][32];
		double rightZPosition[32][32];

		TVector3 leftNorm;
		TVector3 rightNorm;

                TVector3 *teleLXAxis;
                TVector3 *teleLYAxis;
                TVector3 *teleRXAxis;
                TVector3 *teleRYAxis;

		PositionTELE(){
			env = new TEnv("./config/configMerger.prm");
			loadLeftPosition();
			loadRightPosition();

                        //teleLXAxis=new TVector3();teleLXAxis->SetXYZ(0.989134,0.000000,0.147020);
                        //teleLYAxis=new TVector3();teleLYAxis->SetXYZ(0.000588,0.999992,-0.003957);
                        //teleRXAxis=new TVector3();teleRXAxis->SetXYZ(0.988069,0.000000,-0.154011);
                        //teleRYAxis=new TVector3();teleRYAxis->SetXYZ(0.000308,0.999998,0.001976);

			//leftNorm.SetXYZ(-0.147,0.004,0.989);
			leftNorm.SetXYZ(-0.143447,0.00,0.989658);
			leftNorm.Unit();
			//rightNorm.SetXYZ(0.154,-0.002,0.988);
			rightNorm.SetXYZ(0.16109,0.0,0.986940);
			rightNorm.Unit();
			//print();
		}

		void loadLeftPosition(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("dssdLeftPosition","./txt/dssdLeftPosition.txt");
			in.open(inputName);
			cout<<inputName<<endl;

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
				leftXPosition[fid][bid] = x0;
				leftYPosition[fid][bid] = y0;
				leftZPosition[fid][bid] = z0;
			}
		}
		void loadRightPosition(){
			ifstream in;
			TString inputName;
			inputName = env->GetValue("dssdRightPosition","./txt/dssdRightPosition.txt");
			in.open(inputName);
			cout<<inputName<<endl;

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
				rightXPosition[fid][bid] = x0;
				rightYPosition[fid][bid] = y0;
				rightZPosition[fid][bid] = z0;
			}
		}

		void print(){
			cout<<"DSSD Pixel Position"<<endl;
			cout<<"Left DSSD:"<<endl;
			for (int i = 0; i < 32; ++i) {
				for (int j = 0; j < 32; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<leftXPosition[i][j]<<"\t"<<leftYPosition[i][j]<<"\t"<<leftZPosition[i][j]<<endl;
				}

			}
			cout<<"Right DSSD:"<<endl;
			for (int i = 0; i < 32; ++i) {
				for (int j = 0; j < 32; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<rightXPosition[i][j]<<"\t"<<rightYPosition[i][j]<<"\t"<<rightZPosition[i][j]<<endl;
				}

			}

		}
		TVector3 getPosition(int isLR, int fid, int bid){
			TVector3 telePosition;
			if(isLR == 0) telePosition.SetXYZ(leftXPosition[fid][bid],leftYPosition[fid][bid],leftZPosition[fid][bid]);
			else telePosition.SetXYZ(rightXPosition[fid][bid],rightYPosition[fid][bid],rightZPosition[fid][bid]);

                        //if(isLR==0) telePosition = telePosition + 0.9*(*teleLXAxis);
                        //else telePosition = telePosition + 2.4*(*teleRXAxis);
 
			return telePosition;
		}
		TVector3 getDssdPlaneNorm(int isLR){
			if(isLR == 0) return leftNorm;
			else return rightNorm;
		}
};
