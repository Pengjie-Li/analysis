class DCPositionPara{
	private:
		double pitch;

		TString dcName;
		vector<int> dcDirection;
		vector<double> dcZPosition;
		vector<double> dcXYPosition;
		void loadLayer(){
			ifstream in;	
			TString fileName = env->GetValue(dcName+"Layer","txt/direction.txt");
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
		DCPositionPara(TString dc){
			dcName = dc;
			pitch = 5;//mm
			loadLayer();
			print();
		}
		~DCPositionPara(){}
		void setWirePosition(vector<vector<double> > &trackXY,vector<vector<double> > &trackZ,int layerId, int wireId){
			int isXY = getWireXYDirection(layerId);
			trackXY[isXY].push_back(getWireXYPosition(layerId,wireId));
			trackZ[isXY].push_back(getWireZPosition(layerId));
		}
		int getWireXYDirection(int layerId){
			return dcDirection[layerId];
		}
		double getWireXYPosition(int layerId,int wireId){
			return dcXYPosition[layerId]-wireId*pitch;
		}
		double getWireZPosition(int layerId){
			return dcZPosition[layerId];
		}
};
class DCTracking{
	private:
		vector<vector<double> > trackXY;
		vector<vector<double> > trackZ;
		double chiXY[2];
		double ndfXY[2];
		vector<double> layerResidue;


		// Analysis Result
		double X;
		double Y;
		double thetaX;
		double thetaY;

		DCPositionPara *dcPositionPara;
		DCConvertCal *convertData;
		void init(){
			trackXY.resize(2);
			trackZ.resize(2);
			convertData = NULL;
			trackXY[0].clear();
			trackXY[1].clear();
			trackZ[0].clear();
			trackZ[1].clear();
			chiXY[0] = NAN;
			chiXY[1] = NAN;
			ndfXY[0] = NAN;
			ndfXY[1] = NAN;
			layerResidue.resize(totalLayerNumber,NAN);
		}
	public:
		int totalLayerNumber;
		TString dcName;
		DCTracking(){}
		~DCTracking(){}

		void loadPositionPara(){
			dcPositionPara = new DCPositionPara(dcName);	
		}
		void setBranch(TTree *tree){

			
			
			tree->Branch(dcName+"TrackXY",&trackXY);
	
			// How good fitness
			tree->Branch(dcName+"ChiXY",&chiXY,"chiXY[2]/D");
			tree->Branch(dcName+"NdfXY",&ndfXY,"ndfXY[2]/D");

			tree->Branch(dcName+"X",&X);
			tree->Branch(dcName+"Y",&Y);
			tree->Branch(dcName+"ThetaX",&thetaX);
			tree->Branch(dcName+"ThetaY",&thetaY);

			tree->Branch(dcName+"LayerResidue",&layerResidue);

		}
		void findBestTrack(DCConvertCal *dcConvertCal){
			init();
			convertData = dcConvertCal;
			setWirePosition();
			//convertData->print();
			/**
			 * 1. (wire,layer)->wire Position in X,Z
			 * 2. generate 2^layer possible Hit Position in X,Z
			 * 3. loop Hit Position, fit into Track, sort with Chi2
			 */
			//	for (int i = 0; i < getNHits(); ++i) {
		//		
		//	}
			
		}
		void setWirePosition(){
			for (int i = 0; i < getNHits(); ++i) {
				dcPositionPara->setWirePosition(trackXY,trackZ,getLayerId(i),getWireId(i));
			}
		}
		void print(){
			cout<<"Tracking Data"<<endl;
			for (int i = 0; i < trackXY.size(); ++i) {
				for (int j = 0; j < trackXY[i].size(); ++j) {
					cout<<i<<":"<<j<<":"<<trackXY[i][j]<<":"<<trackZ[i][j]<<endl;	
				}
			}
		}
		int getNHits(){
			return convertData->getNHits();
		}
		int getLayerId(int i){
			return convertData->getLayerId(i);
		}
		int getWireId(int i){
			return convertData->getWireId(i);
		}
		int getTdc(int i){
			return convertData->getTdc(i);
		}
		double getDriftLength(int i){
			return convertData->getDriftLength(i);
		}



};
class BDC1Tracking:public DCTracking{
	private:
	public:
		BDC1Tracking(){
			dcName = "bdc1";
			totalLayerNumber = 8;
			loadPositionPara();
		}
		~BDC1Tracking(){}
};
class BDC2Tracking:public DCTracking{
	private:
	public:
		BDC2Tracking(){
			dcName = "bdc2";
			totalLayerNumber = 8;
			loadPositionPara();
		}
		~BDC2Tracking(){}
};
class FDC0Tracking:public DCTracking{
	private:
	public:
		FDC0Tracking(){
			dcName = "fdc0";
			totalLayerNumber = 8;
			loadPositionPara();
		}
		~FDC0Tracking(){}
};
