class DCDetectorPara{
	private:
		double pitch;

		TString dcName;
		vector<int> dcDirection;
		vector<double> dcZPosition;
		vector<double> dcXYPosition;
		void loadLayer(){
			ifstream in;	
			TString fileName = env->GetValue(dcName+"Layer","txt/direction.txt");
			cout<<fileName<<endl;
			in.open(fileName);
			int isXY;
			int layerId;
			double zPos;
			double xPos;
			while(1){
				if(!in.good()) break;
				in>>layerId>>zPos>>isXY>>xPos;
				dcDirection.push_back(isXY);
				dcZPosition.push_back(zPos);
				dcXYPosition.push_back(xPos);
			}
			in.close();
		}
		void print(){

			cout<<dcName<<" Detector Layer:"<<endl;
			for (int i = 0; i < dcDirection.size(); ++i) {
				cout<<i<<":"<<dcZPosition[i]<<":"<<dcDirection[i]<<":"<<dcXYPosition[i]<<endl;
			}
		}
	public:
		DCDetectorPara(TString dc){
			dcName = dc;
			pitch = 5;//mm
			loadLayer();
			print();
		}
		~DCDetectorPara(){}
		int getLayerDirection(int layerId){
			return dcDirection[layerId];
		}
		double getWirePosition(int layerId,int wireId){
			return dcXYPosition[layerId]-wireId*pitch;
		}
		double getWireZPosition(int layerId){
			return dcZPosition[layerId];
		}
};

class TrackPattern{
	private:
		vector<DCHit> hitArray;
	public:
		TrackPattern(){}
		~TrackPattern(){}
		void addHit(DCHit hit){
			hitArray.push_back(hit);
		}
		void print(){
			for (int i = 0; i < hitArray.size(); ++i) {
				hitArray[i].print();	
			}
		}
	//	void tracking(){
	//		cout<<"come on Tracking"<<endl;
	//	}
};
class TrackHit{
	private:
		vector<DCLayerHit> hitArray;
		vector<TrackPattern> trackPattern;
		int nPattern;
		int nHitLayer;

		void calPattern(){
			for (int i = 0; i < hitArray.size(); ++i) {
				if(hitArray[i].size()>0){
					nPattern *= hitArray[i].size();
					nHitLayer++;
				}
			}
		}
		void generatePattern(){
			
			trackPattern.resize(nPattern);
			int np = 1;
			for (int i = 0;  i < hitArray.size(); ++i) {
				if(hitArray[i].size()>0){
					for (int j = 0; j < nPattern; j+=np) {
						for (int k = 0; k < np; ++k) {
							trackPattern[j+k].addHit(hitArray[i].getHit((j%(np*hitArray[i].size()))/np));
						}

					}
					np *= hitArray[i].size();
				}

			}
		}
//		void trackEachPattern(){
//			for (int i = 0; i < trackPattern.size(); ++i) {
//				trackPattern[i].tracking();
//			}
//		}



	public:
		TrackHit(){
		}
		~TrackHit(){}
		void init(){
			nPattern = 1;
			nHitLayer = 0;
			hitArray.clear();
			trackPattern.clear();
		}
		void loadData(DCLayerHit hit){
			hitArray.push_back(hit);
		}
		void tracking(){
			calPattern();
			generatePattern();
			//trackEachPattern();
		}
		void print(){
			cout<<"nPattern = "<< nPattern<<endl;
			for (int i = 0; i < hitArray.size(); ++i) {
					hitArray[i].print();
			}
			for (int i = 0; i < trackPattern.size(); ++i) {
				cout<<"Pattern Number:"<< i <<endl;
				trackPattern[i].print();	
			}
			
		}

		
};
class DCTracking{
	private:
		
		DCReadRaw *rawData;
		TrackHit *xTrackHit;
		TrackHit *yTrackHit;
		DCDetectorPara *dcDetectorPara;
		void init(){
			rawData = NULL;
			xTrackHit->init();
			yTrackHit->init();
		}
	public:
		TString dcName;
		int totalLayerNumber;
		DCTracking(){
			xTrackHit = new TrackHit();
			yTrackHit = new TrackHit();
		}
		~DCTracking(){}
		void loadDetector(){
			dcDetectorPara = new DCDetectorPara(dcName);
		}
		void calibrate(DCReadRaw *dc){
			init();
			rawData = dc;
			loadXYHitsIntoTrack();
			tracking();
		}
		void loadXYHitsIntoTrack(){
			for (int i = 0; i < totalLayerNumber; ++i) {
				if(getLayerDirection(i) == 0) xTrackHit->loadData(rawData->getHit(i));
				else yTrackHit->loadData(rawData->getHit(i));
			}
		}
		void tracking(){
			xTrackHit->tracking();
			yTrackHit->tracking();
		}
		void setBranch(TTree *tree){
		}
		void print(){
			cout<<"X Tracking Hit:"<<endl;
			xTrackHit->print();	
			cout<<"Y Tracking Hit:"<<endl;
			yTrackHit->print();	
		}
		int getNHits(){
			return rawData->getNHits();
		}
		int getLayerId(int i){
			return rawData->getLayerId(i);
		}
		int getWireId(int i){
			return rawData->getWireId(i);
		}
		int getTdc(int i){
			return rawData->getTdc(i);
		}
		int getLayerDirection(int layerId){
			return dcDetectorPara->getLayerDirection(layerId);
		}

};
class BDC1Tracking:public DCTracking{
	private:
	public:
		BDC1Tracking(){
			dcName = "bdc1";
			totalLayerNumber = 8;
			loadDetector();
		}
		~BDC1Tracking(){}
};
class BDC2Tracking:public DCTracking{
	private:
	public:
		BDC2Tracking(){
			dcName = "bdc2";
			totalLayerNumber = 8;
			loadDetector();
		}
		~BDC2Tracking(){}
};
class FDC0Tracking:public DCTracking{
	private:
	public:
		FDC0Tracking(){
			dcName = "fdc0";
			totalLayerNumber = 8;
			loadDetector();
		}
		~FDC0Tracking(){}
};
