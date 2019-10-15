class PlasticHit{
	private:
		
		double TCal[2];
		double QCal[2];

		double TSlew[2];
		double T;
		double Q;
		void init(){

			TCal[0] = NAN;
			TCal[1] = NAN;
			QCal[0] = NAN;
			QCal[1] = NAN;
	
			TSlew[0] = NAN;
			TSlew[1] = NAN;

			T = NAN;
			Q = NAN;
		}
		void saveOneHitTime(){}
		void saveOneHitEnergy(){}
		void setTime(){
				T = 0.5*(TSlew[0]+TSlew[1]);
		}
		void convertEnergy(double q0,double q1){
			if(q0!= -9999 && q1!= -9999){
				Q = sqrt(q0*q1);
			}else{
				saveOneHitEnergy();
			}
		}
		void corrSlewEffect(){
			if(TCal[0]!=-9999) TSlew[0] = TCal[0] + slewPara[0]*QCal[0];
			if(TCal[1]!=-9999) TSlew[1] = TCal[1] + slewPara[1]*QCal[1];
		}
		void corrPositionDependence(){
			if(TCal[0]!=-9999 && TCal[1]!=-9999){
				setTime();
				T = T+ 0.5*positionPara[1];
				T = T+ positionPara[0]*(TSlew[0] - (TSlew[1]+positionPara[1]));
				//cout<<positionPara[0]<<":"<<positionPara[1]<<endl;
				//cout<<TSlew[0]<<":"<<TSlew[1]+positionPara[1]<<endl;
			}else{
				saveOneHitTime();
			}
		}

	public:
		TString detectorName;
		double slewPara[2];
		double positionPara[2];
		PlasticHit(){}
		~PlasticHit(){}
		void setBranch(TTree *tree){
			tree->Branch(detectorName+"T",&T,detectorName+"T/D");
			tree->Branch(detectorName+"Q",&Q,detectorName+"Q/D");
		}
		void convert(double t0,double t1,double q0,double q1){
			init();
			TCal[0] = t0;
			TCal[1] = t1;
			QCal[0] = q0;
			QCal[1] = q1;

			corrSlewEffect();
			corrPositionDependence();

			convertEnergy(q0,q1);
		}
		void print(){
			cout<<detectorName<<"TSlew[0] = "<<TSlew[0]<<" "<<detectorName<<"TSlew[1] = "<<TSlew[1]<<endl;
			cout<<detectorName<<"T = "<<T<<" "<<detectorName<<"Q = "<<Q<<endl;
		}

};
class F3Hit:public PlasticHit{
	private:
	public:
		F3Hit(){
			detectorName = "F3";
			slewPara[0] = 0.0015;
			slewPara[1] = 0.0014;
			positionPara[0] = 0;
			positionPara[1] = 0;
		}
		~F3Hit(){}
};
class F7Hit:public PlasticHit{
	private:
	public:
		F7Hit(){
			detectorName = "F7";
			slewPara[0] = 0.00092;
			slewPara[1] = 0.00107;
	
			positionPara[0] = 0;
			positionPara[1] = 0;
		}
		~F7Hit(){}
};
class SBT1Hit:public PlasticHit{
	private:
	public:
		SBT1Hit(){
			detectorName = "SBT1";
			slewPara[0] = 0.0;
			slewPara[1] = 0.0;
			positionPara[0] = 0.39;
			positionPara[1] = 1.24;
	
		}
		~SBT1Hit(){}
};
class SBT2Hit:public PlasticHit{
	private:
	public:
		SBT2Hit(){
			detectorName = "SBT2";
			slewPara[0] = 0.0;
			slewPara[1] = 0.0;
			positionPara[0] = 0.40;
			positionPara[1] = -2.8;
	
		}
		~SBT2Hit(){}
};
class SBVHit:public PlasticHit{
	private:
	public:
		SBVHit(){
			detectorName = "SBV";
			slewPara[0] = 0.0;
			slewPara[1] = 0.0;
			positionPara[0] = 0.0;
			positionPara[1] = 0.0;
	
		}
		~SBVHit(){}
};

class PLAConvert{
	private:
		PlasticHit *hitF3;
		PlasticHit *hitF7;
		PlasticHit *hitSBT1;
		PlasticHit *hitSBT2;
		PlasticHit *hitSBV;

		PLARead *rawData;


		void finalizeF13(){
		//	if(SBT1T!=NAN && SBT2T!= NAN){
		//		F13T = 0.5*(SBT1T+SBT2T);
		//	}else{
		//		if(SBT1T!= NAN) F13T = SBT1T;
		//		if(SBT2T!= NAN) F13T = SBT2T;
		//	}
		//	if(SBT1Q!=NAN && SBT2Q!= NAN){
		//		F13Q = 0.5*(SBT1Q+SBT2Q);
		//	}else{
		//		if(SBT1Q!= NAN) F13Q = SBT1Q;
		//		if(SBT2Q!= NAN) F13Q = SBT2Q;
		//	}

		}

		double getF3TCal(int id){
			return rawData->getF3TCal(id);
		}
		double getF3QCal(int id){
			return rawData->getF3QCal(id);
		}
		double getF7TCal(int id){
			return rawData->getF7TCal(id);
		}
		double getF7QCal(int id){
			return rawData->getF7QCal(id);
		}
		double getSBT1TCal(int id){
			return rawData->getSBT1TCal(id);
		}
		double getSBT1QCal(int id){
			return rawData->getSBT1QCal(id);
		}
		double getSBT2TCal(int id){
			return rawData->getSBT2TCal(id);
		}
		double getSBT2QCal(int id){
			return rawData->getSBT2QCal(id);
		}
		double getSBVTCal(int id){
			return rawData->getSBVTCal(id);
		}
		double getSBVQCal(int id){
			return rawData->getSBVQCal(id);
		}

	
	public:
		PLAConvert(){
			hitF3 = new F3Hit();
			hitF7 = new F7Hit();
			hitSBT1 = new SBT1Hit();
			hitSBT2 = new SBT2Hit();
			hitSBV = new SBVHit();
		}
		~PLAConvert(){}
		void setBranch(TTree *tree){
			hitF3->setBranch(tree);
			hitF7->setBranch(tree);
			hitSBT1->setBranch(tree);
			hitSBT2->setBranch(tree);
			hitSBV->setBranch(tree);
		}
		void convert(PLARead *pla){
			rawData = pla;	
			hitF3->convert(getF3TCal(0),getF3TCal(1),getF3QCal(0),getF3QCal(1));
			hitF7->convert(getF7TCal(0),getF7TCal(1),getF7QCal(0),getF7QCal(1));
			hitSBT1->convert(getSBT1TCal(0),getSBT1TCal(1),getSBT1QCal(0),getSBT1QCal(1));
			hitSBT2->convert(getSBT2TCal(0),getSBT2TCal(1),getSBT2QCal(0),getSBT2QCal(1));
			hitSBV->convert(getSBVTCal(0),getSBVTCal(1),getSBVQCal(0),getSBVQCal(1));
		}
		void print(){
		}
		void printF3(){
			hitF3->print();
		}
		void printF7(){
			hitF7->print();
		}
		void printSBT1(){
			hitSBT1->print();
		}
		void printSBT2(){
			hitSBT2->print();
		}
		void printSBV(){
			hitSBV->print();
		}

};
