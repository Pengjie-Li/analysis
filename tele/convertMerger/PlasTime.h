class PlasTimePara{
	private:
		double offset[4];
		double rdcSlope[4];
		double rdcOffset[4];
		vector<vector<double> > magMin;
		vector<vector<double> > magMax;
		vector<vector<double> > magOffset;
		vector<vector<double> > magSlope;
	public:
		PlasTimePara(){
			init();
			load();
			print();
		}
		~PlasTimePara(){}
		void init(){
			magMin.clear();
			magMax.clear();
			magSlope.clear();
			magOffset.clear();
			magMin.resize(4);
			magMax.resize(4);
			magSlope.resize(4);
			magOffset.resize(4);
			for (int i = 0; i < 4; ++i) {
				offset[i]	 = NAN;
				rdcSlope[i]	 = NAN;
				rdcOffset[i] = NAN;
			}
		}
		void load(){
			loadRdcParameters();
			loadSlewParameters();
		}
		void loadRdcParameters(){
			ifstream inputFile;
			TString inputName = "txt/plasRdcParameters.txt";
			inputFile.open(inputName);
			cout<<inputName<<endl;
			int ch;
			double boff,slp,off;

			while(1){
				inputFile>>ch>>boff>>slp>>off;
				if(!inputFile.good()) break;
				offset[ch] 	 	= boff;
				rdcSlope[ch]	= slp;
				rdcOffset[ch]	= off;
			}

		}
		void loadSlewParameters(){
			ifstream inputFile;
			TString inputName = "txt/plasSlewParameters.txt";
			inputFile.open(inputName);
			cout<<inputName<<endl;
			int ch;
			double min,max,slp,off;

			while(1){
				inputFile>>ch>>min>>max>>slp>>off;
				if(!inputFile.good()) break;
				magMin[ch].push_back(min);
				magMax[ch].push_back(max);
				magSlope[ch].push_back(slp);
				magOffset[ch].push_back(off);
			}
		}
		void print(){
			cout<<"Plas Time Para:"<<endl;
			for (int i = 0; i < 4; ++i) {
				cout<<offset[i]<<"\t"<<rdcSlope[i]<<"\t"<<rdcOffset[i]<<"\t"<<magSlope[i][0]<<"\t"<<magOffset[i][0]<<"\t"<<endl;
			}
		}
		double getOffset(int side,int ud){
			return offset[2*side+ud];
		}
		double getRdcOffset(int side, int ud){
			return rdcOffset[2*side+ud];
		}
		double getRdcSlope(int side,int ud){
			return rdcSlope[2*side+ud];
		}

		double getMagOffset(int side,int ud,double mag){
			int ch = 2*side+ud;
			for (int i = 0; i < magOffset[ch].size(); ++i) {
				if(magMin[ch][i]<=mag&&mag<=magMax[ch][i])	return magOffset[ch][i];
			}
			return 0;
		}
		double getMagSlope(int side,int ud,double mag){
			int ch = 2*side+ud;
			for (int i = 0; i < magOffset[ch].size(); ++i) {
				if(magMin[ch][i]<=mag&&mag<=magMax[ch][i])	return magSlope[ch][i];
			}
			return 0;
		}
};
class PlasTime{
	private:
		PlasTimePara *plasPara;
		double espriPlasT;

		int side;
		int ud;
		double upTime;
		double downTime;
	public:
		PlasTime(){
			plasPara = new PlasTimePara();
		}
		~PlasTime(){}

		void init(){
			espriPlasT = NAN;
		}
		void setBranch(TTree *tree){
			tree->Branch("espriPlasT",&espriPlasT,"espriPlasT/D");
		}
		bool read(int s,double uT,double dT){
			side = s;
			upTime = uT;
			downTime = dT;

			if(upTime == -9999&& downTime == -9999) return false;
			else{
				if(upTime != -9999&& downTime != -9999){
					//cout<<side<<" "<<upTime<<" "<<downTime<<endl;
					if(downTime>upTime){
						ud = 1;
						espriPlasT = downTime + plasPara->getOffset(side,ud);
					}else{
						ud = 0;
						espriPlasT = upTime + plasPara->getOffset(side,ud);
					}

				}
				if(upTime!=-9999&&downTime==-9999){
					ud = 0;
					espriPlasT = upTime + plasPara->getOffset(side,ud);
				}

				if(downTime!=-9999&&upTime==-9999){
					ud = 1;
					espriPlasT = downTime + plasPara->getOffset(side,ud);
				}
				//cout<<plasPara->getOffset(side,ud)<<" "<<upTime<<" "<<downTime<<" "<<espriPlasT<<endl;
				//cout<<espriPlasT<<endl;
				return true;
			}
		}
		void positionCorr(double posY){
			espriPlasT += (plasPara->getRdcSlope(side,ud)*posY + plasPara->getRdcOffset(side,ud));
			//cout<<espriPlasT<<endl;
		}
		void slewCorr(double mag){
			if(mag>0) espriPlasT += (plasPara->getMagSlope(side,ud,mag)*mag + plasPara->getMagOffset(side,ud,mag));
			//cout<<plasPara->getMagSlope(side,ud)<<" "<< plasPara->getMagOffset(side,ud)<<" "<<espriPlasT<<endl;
		}
		void tofBeamCorr(double tofBeam){
			//cout<<plasPara->getBeamOffset(side) <<" "<< tofBeam<<endl;
			espriPlasT += (- tofBeam);
			//cout<<tofBeam<<" "<<espriPlasT<<endl;
		}
		void addOffset(double offset){
			espriPlasT += offset;
		}
		void print(){
			cout<<"espriPlasT = "<<espriPlasT<<" ns"<<endl;

		}
		double getPlasT(){
			return espriPlasT;
		}
};
