class PlasticHit{
	private:


	public:
		double QCal[2]; // = QRaw
		double TCal[2]; // Raw to Cal with constant slope
		double TCorr[2];// Slew; Position correction
		double T;
		double Q;

		TString detectorName;
		double slewPara[2];
		double positionPara[2];
		PlasticHit(){}
		~PlasticHit(){}
		void setBranch(TTree *tree){
			tree->Branch(detectorName+"TCorr",&TCorr,detectorName+"TCorr[2]/D");
			tree->Branch(detectorName+"T",&T,detectorName+"T/D");
			tree->Branch(detectorName+"Q",&Q,detectorName+"Q/D");
		}
		void init(){

			TCal[0] = NAN;
			TCal[1] = NAN;
			QCal[0] = NAN;
			QCal[1] = NAN;
	
			TCorr[0] = NAN;
			TCorr[1] = NAN;

			T = NAN;
			Q = NAN;
		}

		virtual void convert(double t0,double t1,double q0,double q1){
			init();
			TCal[0] = t0;
			TCal[1] = t1;
			QCal[0] = q0;
			QCal[1] = q1;

			setTime();
			setEnergy();

		}
		void print(){
			cout<<detectorName<<"TCorr[0] = "<<TCorr[0]<<" "<<detectorName<<"TCorr[1] = "<<TCorr[1]<<endl;
			cout<<detectorName<<"T = "<<T<<" "<<detectorName<<"Q = "<<Q<<endl;
		}
		double getT(){
			return T;
		}
		double getQ(){
			return Q;
		}
		void setT(double t){
			T = t;
		}
		void setQ(double q){
			Q = q;
		}
		void saveOneHitTime(){}
		void saveOneHitEnergy(){}
		void convertEnergy(){
			if(QCal[0]!= -9999 && QCal[1]!= -9999){
				Q = sqrt(QCal[0]*QCal[1]);
			}else{
				saveOneHitEnergy();
			}
		}
		virtual void setTime(){
			corrSlewEffect();
			if(TCal[0]!=-9999 && TCal[1]!=-9999){
				T = 0.5*(TCorr[0]+TCorr[1]);
			}
			corrPositionDependence();
		}
		virtual void setEnergy(){
			convertEnergy();
		}

		virtual void corrSlewEffect(){
			if(TCal[0]!=-9999) TCorr[0] = TCal[0] + slewPara[0]*QCal[0];
			if(TCal[1]!=-9999) TCorr[1] = TCal[1] + slewPara[1]*QCal[1];
		}
		virtual void corrPositionDependence(){
			if(TCal[0]!=-9999 && TCal[1]!=-9999){
				T = T+ 0.5*positionPara[1];
				T = T+ positionPara[0]*(TCorr[0] - (TCorr[1]+positionPara[1]));
				//cout<<positionPara[0]<<":"<<positionPara[1]<<endl;
				//cout<<TCorr[0]<<":"<<TCorr[1]+positionPara[1]<<endl;
			}else{
				saveOneHitTime();
			}
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
	//	void corrSlewEffect(){
	//		if(TCal[0]!=-9999&&QCal[0]!=-9999) TCorr[0] = TCal[0] + 0.0010*QCal[0]-10/sqrt(sqrt(QCal[0]));
	//		if(TCal[1]!=-9999&&QCal[1]!=-9999) TCorr[1] = TCal[1] + 0.0008*QCal[1]-10/sqrt(sqrt(QCal[1]));
	//	}
	//	void corrPositionDependence(){
	//	}

		~F7Hit(){}
};
class SBT1Hit:public PlasticHit{
	private:
	public:
		SBT1Hit(){
			detectorName = "SBT1";
			slewPara[0] = 0.0;
			slewPara[1] = 0.0;
			//positionPara[0] = 0.38;
			//positionPara[1] = 1.3;
	
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
		void convert(double t0,double t1,double q0,double q1){
			init();
			if(t1!= -9999) setT(t1);
			if(q1!= -9999) setQ(q1);
		}

		
};
class F13Hit:public PlasticHit{
	private:
		double sbtPara[2]; // Align SBT1 and SBT2, in order to make 1 Detector to represent F13T
		// TCal[0] = SBT1T;TCal[1] = SBT2T;
		// QCal[0] = SBT1Q;QCal[1] = SBT2Q;
	public:
		F13Hit(){
			detectorName = "F13";
			sbtPara[0] = 2.7;
			sbtPara[1] = 1.2;
	
		}
		~F13Hit(){}

		void setTime(){

			if(!isnan(TCal[0])) TCorr[0] = TCal[0] + 0; //	Align to SBT1 as reference
			if(!isnan(TCal[1])) TCorr[1] = TCal[1] + sbtPara[0]; // Align SBT1 and SBT2 make even 1 detector could represent F13	
			if(!isnan(TCorr[0]) && !isnan(TCorr[1])){
				T = 0.5*(TCorr[0]+TCorr[1]);
			}else{
				if(!isnan(TCorr[0])) T = TCorr[0];
				if(!isnan(TCorr[1])) T = TCorr[1];
			}
		}
		void setEnergy(){

			if(!isnan(QCal[1])) QCal[1] = QCal[1]*sbtPara[1]; // Align SBT1 and SBT2 make even 1 detector could represent 	
			if(!isnan(QCal[0]) && !isnan(QCal[1])){
				Q = 0.5*(QCal[0]+QCal[1]);
			}else{
				if(!isnan(QCal[0])) Q = QCal[0];
				if(!isnan(QCal[1])) Q = QCal[1];
			}

		}
		
};


class PLAConvert{
	private:
		PlasticHit *hitF3;
		PlasticHit *hitF7;
		PlasticHit *hitSBT1;
		PlasticHit *hitSBT2;
		PlasticHit *hitSBV;
		PlasticHit *hitF13; // take SBT1 and SBT2 as 2 PMT signal

		PLARead *rawData;

		double getF3TCal(int id){
			return rawData->getF3TCal(id);
		}
		double getF3QCal(int id){
			return rawData->getF3QCal(id);
		}
		double getF13TCal(int id){
			if(id == 0) return hitSBT1->getT(); 
			else return hitSBT2->getT(); 
		}
		double getF13QCal(int id){
			if(id == 0) return hitSBT1->getQ(); 
			else return hitSBT2->getQ(); 
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
			hitF13 = new F13Hit();
		}
		~PLAConvert(){}
		void setBranch(TTree *tree){
			hitF3->setBranch(tree);
			hitF7->setBranch(tree);
			hitSBT1->setBranch(tree);
			hitSBT2->setBranch(tree);
			hitSBV->setBranch(tree);
			hitF13->setBranch(tree);

		}
		void convert(PLARead *pla){
			rawData = pla;	
			hitF3->convert(getF3TCal(0),getF3TCal(1),getF3QCal(0),getF3QCal(1));
			hitF7->convert(getF7TCal(0),getF7TCal(1),getF7QCal(0),getF7QCal(1));
			hitSBT1->convert(getSBT1TCal(0),getSBT1TCal(1),getSBT1QCal(0),getSBT1QCal(1));
			hitSBT2->convert(getSBT2TCal(0),getSBT2TCal(1),getSBT2QCal(0),getSBT2QCal(1));
			hitSBV->convert(getSBVTCal(0),getSBVTCal(1),getSBVQCal(0),getSBVQCal(1));
			hitF13->convert(getF13TCal(0),getF13TCal(1),getF13QCal(0),getF13QCal(1));
		}
		void print(){
		}
		void printF13(){
			hitF13->print();
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
