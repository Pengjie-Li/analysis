class EspriPlasTime{
	private:
		double offset[2];
		double rdcSlope[2];
		double rdcOffset[2];
		double magSlope[2];
		double magOffset[2];
		double mag2A[2];
		double mag2B[2];
		double mag2C[2];
		double beamOffset[2];
		
	public:
		EspriPlasTime(){
			init();
			load();
			print();
		}
		~EspriPlasTime(){}
		void init(){
			for (int i = 0; i < 2; ++i) {
				offset[i]	 = NAN;
				rdcSlope[i]	 = NAN;
				rdcOffset[i] = NAN;
				magSlope[i]	 = NAN;
				magOffset[i] = NAN;
				mag2A[i] = NAN;
				mag2B[i] = NAN;
				mag2C[i] = NAN;
				beamOffset[i] = NAN;
				
			}
		}
		void load(){
			ifstream inputFile;
			//TString inputName = "txt/plasParameters.txt";
			TString inputName = calib->GetValue("plasTimePara","txt/plasParameters.txt");
			inputFile.open(inputName);
			int side;
			double a,b,c,d,e,f,g,h,i;

			while(1){
				inputFile>>side>>a>>b>>c>>d>>e>>f>>g>>h>>i;
				if(!inputFile.good()) break;
				offset[side] 	 = a;
				rdcSlope[side]	 = b;
				rdcOffset[side]  = c;
				magSlope[side]	 = d;
				magOffset[side]  = e;
				mag2A[side]  = f;
				mag2B[side]  = g;
				mag2C[side]  = h;
				beamOffset[side] = i;
			}

		}
		void print(){
			cout<<"Plas Time Para:"<<endl;
			for (int i = 0; i < 2; ++i) {
				cout<<offset[i]<<"\t"<<rdcSlope[i]<<"\t"<<rdcOffset[i]<<"\t"<<magSlope[i]<<"\t"<<magOffset[i]<<"\t"<<beamOffset[i]<<endl;
			}
		}

		double getOffset(int side){
			return offset[side];
		}
		double getRdcOffset(int side){
			return rdcOffset[side];
		}
		double getRdcSlope(int side){
			return rdcSlope[side];
		}

		double getMagOffset(int side){
			return magOffset[side];
		}
		double getMagSlope(int side){
			return magSlope[side];
		}
		double getMag2A(int side){
			return mag2A[side];
		}
		double getMag2B(int side){
			return mag2B[side];
		}
		double getMag2C(int side){
			return mag2C[side];
		}
		double getBeamOffset(int side){
			return beamOffset[side];
		}
};		
class PlasTime{
	private:
		EspriPlasTime *plasPara;
		double espriPlasT;
		double offsetBeam[2];

		int side;
		double upTime;
		double downTime;
	public:
		PlasTime(){
			plasPara = new EspriPlasTime();
			offsetBeam[0] = calib->GetValue("offsetLeft",0.);
			offsetBeam[1] = calib->GetValue("offsetRight",0.);
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
			espriPlasT = downTime + plasPara->getOffset(side);
			espriPlasT += offsetBeam[side];
			if(upTime == -9999&& downTime == -9999) return false;
			else{
				if(upTime != -9999&& downTime != -9999){
					cout<<side<<" "<<upTime<<" "<<downTime<<endl;
				}
				return true;
			}
		}

		void positionCorr(double posY){
			espriPlasT += (plasPara->getRdcSlope(side)*posY + plasPara->getRdcOffset(side));
		}
		void slewCorr(double mag){
			espriPlasT += (plasPara->getMagSlope(side)/sqrt(mag)+ plasPara->getMagOffset(side));
			espriPlasT += plasPara->getMag2A(side)*(1./sqrt(mag) +plasPara->getMag2B(side))*(1./sqrt(mag) +plasPara->getMag2B(side)) + plasPara->getMag2C(side);
		}
		void tofBeamCorr(double tofBeam){
			//cout<<plasPara->getBeamOffset(side) <<" "<< tofBeam<<endl;
			espriPlasT += plasPara->getBeamOffset(side) - tofBeam;
		}
		void print(){
                        cout<<"espriPlasT = "<<espriPlasT<<" ns"<<endl;

                }	
};
