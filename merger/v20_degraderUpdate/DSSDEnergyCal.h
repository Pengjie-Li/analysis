class DSSDEnergyCalPara{
	private:
		double kScmSlope[4][32];
		double bScmOffset[4][32];
		double ekScmSlope[4][32];
		double ebScmOffset[4][32];

		double kCalSlope[2];
		double bCalOffset[2];

		void loadSiliconCalibrationParas(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32]){
			ifstream in;
			TString inputName;

			inputName = env->GetValue("dssdScmPara","DSSD_Fit_Whole.txt");
			cout<<inputName<<endl;
			in.open(inputName);

			int side;
			int strip;
			double  k0;
			double  b0;
			double ek0;
			double eb0;
			while (1)
			{
				in >>side>>strip>>k0>>b0>>ek0>>eb0;
				cout<<side<<"\t"<<strip<<"\t"<<k0<<"\t"<<b0<<endl;
				if (!in.good()) break;

				k[side][strip]=k0;
				ek[side][strip]=ek0;

				b[side][strip]=b0;
				eb[side][strip]=eb0;

			}
		}


	public:

		DSSDEnergyCalPara(){
			loadSiliconCalibrationParas(kScmSlope,bScmOffset,ekScmSlope,ebScmOffset);

			kCalSlope[0] =  0.00645438;
			bCalOffset[0] = -0.621313;

			kCalSlope[1] = 0.00683802;
			bCalOffset[1] = -0.612683;
	
			//kCalSlope[0] = 7.17797775;
			//bCalOffset[0] = -1524.240925;

			//kCalSlope[1] = 7.685283145;
			//bCalOffset[1] = -1646.273395;
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


class DSSDEnergyCal{
	private:
		TELEReadRaw *rawData;
		DSSDEnergyCalPara *dssdCalibrationPara;
		double dssdQScm[4][32];	
		double dssdQCal[4][32];	
		void init(){
			for(int i = 0; i<4;i++){
				for(int j = 0; j<32;j++){
					dssdQScm[i][j] = NAN;
					dssdQCal[i][j] = NAN;
				}
			}
		}
		void selfCalibration(){
			// raw->SCM->cal
			//side = 0 LF, 1 LB, 2 RF, 3 RB
			
			for(int side = 0;side<4;side++)
				for(int id=0;id<32;id++){
					dssdQScm[side][id] = getSiliconScmSlope(side,id)*getSiliconRaw(side,id) + getSiliconScmOffset(side,id);
					dssdQCal[side][id] = getSiliconCalSlope(side)*dssdQScm[side][id] + getSiliconCalOffset(side);

					// Some ADC Saturation events
					if(getSiliconRaw(side,id)>4096){
						dssdQScm[side][id] = NAN;
						dssdQCal[side][id] = NAN;
					}

				}
		}

	public:
		DSSDEnergyCal(){
			dssdCalibrationPara = new DSSDEnergyCalPara();
		}

		~DSSDEnergyCal(){
			delete dssdCalibrationPara;
		}

		void setBranch(TTree *tree){
			tree->Branch("dssdQScm",dssdQScm,"dssdQScm[4][32]/D");
			tree->Branch("dssdQCal",dssdQCal,"dssdQCal[4][32]/D");
		}
		void calibrate(TELEReadRaw *raw){
			rawData = raw;
			selfCalibration();
		}
		double getSiliconScmSlope(int side, int id){
			return dssdCalibrationPara->getSiliconScmSlope(side,id);
		}
		double getSiliconScmOffset(int side, int id){
			return dssdCalibrationPara->getSiliconScmOffset(side,id);
		}

		double getSiliconCalSlope(int side){
			return dssdCalibrationPara->getSiliconCalSlope(side);
		}

		double getSiliconCalOffset(int side){
			return dssdCalibrationPara->getSiliconCalOffset(side);
		}
		double getSiliconRaw(int side,int id){
			return rawData->getDssdQRaw(side,id);
		}


};

