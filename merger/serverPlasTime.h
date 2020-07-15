class PlasTimePara{
		private:
				TString inputName;
				double offset[4];
				double rdcSlope[4];
				double rdcOffset[4];
				double magSlope[4];
				double magOffset[4];
		public:
				PlasTimePara(TString input){
					inputName = input;
					init();
					load();
					print();
				}
				~PlasTimePara(){}
				void init(){
					for (int i = 0; i < 4; ++i) {
							offset[i]	 = NAN;
							rdcSlope[i]	 = NAN;
							rdcOffset[i] = NAN;
							magSlope[i]	 = NAN;
							magOffset[i] = NAN;
					}
				}
				void load(){
						ifstream inputFile;
                        //TString inputName = "txt/plasParameters.txt";
                        inputFile.open(inputName);
						cout<<inputName<<endl;
						int side;
						int ud;
						double a,b,c,d,e;

                        while(1){
                                inputFile>>side>>ud>>a>>b>>c>>d>>e;
                                if(!inputFile.good()) break;
								offset[2*side+ud] 	 = a;
								rdcSlope[2*side+ud]	 = b;
								rdcOffset[2*side+ud]  = c;
								magSlope[2*side+ud]	 = d;
								magOffset[2*side+ud]  = e;
                        }
			
				}
				void print(){
						cout<<"Plas Time Para:"<<endl;
						for (int i = 0; i < 4; ++i) {
								cout<<offset[i]<<"\t"<<rdcSlope[i]<<"\t"<<rdcOffset[i]<<"\t"<<magSlope[i]<<"\t"<<magOffset[i]<<"\t"<<endl;
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

				double getMagOffset(int side,int ud){
					return magOffset[2*side+ud];
				}
				double getMagSlope(int side,int ud){
					return magSlope[2*side+ud];
				}
};		
class PlasTime{
		private:
				PlasTimePara *calibTimePara[2];
				PlasTimePara *plasPara;
				double espriPlasT;
			
				int side;
				int ud;
				double upTime;
				double downTime;
		public:
				PlasTime(){
					calibTimePara[0] = new PlasTimePara("txt/plasParameters.txt_Low");
					calibTimePara[1] = new PlasTimePara("txt/plasParameters.txt_High");
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
						//Be10
						//if(side == 0) espriPlasT += -0.103;
						//else espriPlasT += -0.002;
						//Be12
						//if(side == 0) espriPlasT += -0.062;
						//else espriPlasT += -0.052;
						//Be14
						//if(side == 0) espriPlasT += -0.012;
						//else espriPlasT += -0.062;
	
						if(upTime == -9999&& downTime == -9999) return false;
						else{
								if(upTime != -9999&& downTime != -9999){
										//cout<<side<<" "<<upTime<<" "<<downTime<<endl;
								}
								if(downTime!=-9999){
										ud = 1;
										espriPlasT = downTime + plasPara->getOffset(side,ud);
								}
								if(upTime!=-9999){
										ud = 0;
										espriPlasT = upTime + plasPara->getOffset(side,ud);
								}
								//cout<<plasPara->getOffset(side)<<" "<<downTime<<" "<<espriPlasT<<endl;
								//cout<<espriPlasT<<endl;
								return true;
						}
				}
				void setEnergyPara(int side, int qPed){
								if((side==0&&qPed>=2000)||(side==1&&qPed>=1500)) plasPara = calibTimePara[0]; // Low
								if((side==0&&qPed<2000)||(side==1&&qPed<1500)) plasPara = calibTimePara[1]; // High 
				}
				void positionCorr(double posY){
						espriPlasT += (plasPara->getRdcSlope(side,ud)*posY + plasPara->getRdcOffset(side,ud));
						//cout<<espriPlasT<<endl;
				}
				void slewCorr(double mag){
						espriPlasT += (plasPara->getMagSlope(side,ud)*mag + plasPara->getMagOffset(side,ud));
						//espriPlasT += plasPara->getMag2A(side)*(1./sqrt(mag) +plasPara->getMag2B(side))*(1./sqrt(mag) +plasPara->getMag2B(side)) + plasPara->getMag2C(side);
						//cout<<plasPara->getMagSlope(side)<<" "<< plasPara->getMagOffset(side)<<" "<<espriPlasT<<endl;
				}
				void tofBeamCorr(double tofBeam){
						//cout<<plasPara->getBeamOffset(side) <<" "<< tofBeam<<endl;
						espriPlasT += (- tofBeam);
						//cout<<tofBeam<<" "<<espriPlasT<<endl;
				}
				void print(){
						cout<<"espriPlasT = "<<espriPlasT<<" ns"<<endl;

				}
				double getPlasT(){
					return espriPlasT;
				}
};
