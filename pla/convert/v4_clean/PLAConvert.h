class PlasticHit{
	private:


	public:
		double QCal[2]; // = QRaw
		double TCal[2]; // Raw to Cal with constant slope
		double T;
		double Q;

		TString detectorName;
		PlasticHit(){}
		~PlasticHit(){}
		void setBranch(TTree *tree){
			tree->Branch(detectorName+"T",&T,detectorName+"T/D");
			tree->Branch(detectorName+"Q",&Q,detectorName+"Q/D");
		}
		void init(){

			TCal[0] = NAN;
			TCal[1] = NAN;
			QCal[0] = NAN;
			QCal[1] = NAN;
	
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
			if(TCal[0]!=-9999 && TCal[1]!=-9999){
				T = 0.5*(TCal[0]+TCal[1]);
			}
		}
		virtual void setEnergy(){
			convertEnergy();
		}


};
class F3Hit:public PlasticHit{
	private:
	public:
		F3Hit(){
			detectorName = "F3";
		}
		~F3Hit(){}
};
class F7Hit:public PlasticHit{
	private:
	public:
		F7Hit(){
			detectorName = "F7";
		}

		~F7Hit(){}
};
class SBT1Hit:public PlasticHit{
	private:
	public:
		SBT1Hit(){
			detectorName = "SBT1";
		}
		~SBT1Hit(){}
};
class SBT2Hit:public PlasticHit{
	private:
	public:
		SBT2Hit(){
			detectorName = "SBT2";
		}
		~SBT2Hit(){}
};
class SBVHit:public PlasticHit{
	private:
	public:
		SBVHit(){
			detectorName = "SBV";
		}
		~SBVHit(){}
		void convert(double t0,double t1,double q0,double q1){
			init();
			if(t1!= -9999) setT(t1);
			if(q1!= -9999) setQ(q1);
		}

		
};
class PLAConvert{
	private:
		PlasticHit *hitF3;
		PlasticHit *hitF7;
		PlasticHit *hitSBT1;
		PlasticHit *hitSBT2;
		PlasticHit *hitSBV;

		PLARead *rawData;

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
