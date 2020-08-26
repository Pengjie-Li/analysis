class BeamEvent{
	private:
		double beamBetaOffset;
		double beamEnergyOffset;

		PlaEvent *plaEvent;
		BdcEvent *bdcEvent;

		double beamEnergy;

		double beamBeta;
		double tofSBTTarget;

		double getBeamFL(){
			return bdcEvent->getBeamFL();
		}
		double getF713Beta(){
			return plaEvent->getF713Beta();
		}
		double getF713Ek(){
			return plaEvent->getF713Ek();
		}

	public:
		BeamEvent(){
			beamBetaOffset = calib->GetValue("beamBetaOffset",0.);
			beamEnergyOffset = calib->GetValue("beamEnergyOffset",0.);
		}
		~BeamEvent(){}

		void init(){
			plaEvent = NULL;
			bdcEvent = NULL;
			beamEnergy = NAN;
			tofSBTTarget = NAN;
			beamBeta = NAN;
		}
		void load(PlaEvent *pla,BdcEvent *bdc){
			plaEvent = pla;
			bdcEvent = bdc;	
		}
		void setEvent(){

			double SOL = 299.792458;//mm/ns
			beamBeta = getF713Beta() + beamBetaOffset/SOL;
			tofSBTTarget = getBeamFL()/(beamBeta*SOL);
			beamEnergy = getF713Ek() + beamEnergyOffset;
			//cout<<beamEnergy<<" "<<beamBeta<<getBeamFL()<<endl;

		}
		void setOutputBranch(TTree *tree){
			tree->Branch("beamEnergy",&beamEnergy);
			tree->Branch("beamBeta",&beamBeta);
			tree->Branch("tofSBTTarget",&tofSBTTarget);
		}

		void print(){
			cout<<"Beam info"<<endl;
			cout<<"Beam Energy before Target : "<<beamEnergy<<endl;
			cout<<"Beam Tof SBT Target : "<<tofSBTTarget<<endl;
			cout<<"beamFL= "<<getBeamFL()<<endl;
		}
		double getBeamToF(){
			return tofSBTTarget;
		}
};

