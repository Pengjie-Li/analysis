#include "DCTrack.h"
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
		void setWirePosition(vector<vector<int> > &trackWire,vector<vector<double> > &trackXY,vector<vector<double> > &trackDL,vector<double>  &trackZ,int layerId, int wireId,double dl){
			trackWire[layerId].push_back(wireId);
			trackXY[layerId].push_back(getWireXYPosition(layerId,wireId));
			trackDL[layerId].push_back(dl);
			trackZ[layerId] = getWireZPosition(layerId);
		}
		int getLayerXYDirection(int layerId){
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
		vector<vector<int> > trackWire;
		vector<vector<double> > trackXY;
		vector<vector<double> > trackDL;//Drift Length
		vector<double> trackZ;
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
		DCTrack	*dcTrack[2];
		void init(){
			trackWire.clear();
			trackXY.clear();
			trackDL.clear();
			trackZ.clear();
			trackWire.resize(totalLayerNumber);
			trackXY.resize(totalLayerNumber);
			trackDL.resize(totalLayerNumber);
			trackZ.resize(totalLayerNumber);
			convertData = NULL;
			chiXY[0] = NAN;
			chiXY[1] = NAN;
			ndfXY[0] = NAN;
			ndfXY[1] = NAN;
			layerResidue.resize(totalLayerNumber,NAN);
			dcTrack[0]->init();
			dcTrack[1]->init();
		}
	public:
		int totalLayerNumber;
		TString dcName;
		DCTracking(){
			dcTrack[0] = new DCTrack();
			dcTrack[1] = new DCTrack();

		}
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
			tracking();
			//convertData->print();
			/**
			 * 1. (wire,layer)->wire Position in X,Z
			 * 2. seperate hits into X and Y Array,find numLayer and 
			 * 3. loop Hit Position, fit into Track, sort with Chi2
			 */
			//	for (int i = 0; i < getNHits(); ++i) {
		//		
		//	}
			
		}
		void setWirePosition(){
			for (int i = 0; i < getNHits(); ++i) {
				//cout<<"Hit "<<i<<":"<<getLayerId(i)<<":"<<getWireId(i)<<":"<<getDriftLength(i)<<endl;
				dcPositionPara->setWirePosition(trackWire,trackXY,trackDL,trackZ,getLayerId(i),getWireId(i),getDriftLength(i));

			}
		}
		void tracking(){
	
			for (int i = 0; i < totalLayerNumber; ++i) {
				dcTrack[getLayerXYDirection(i)]->loadData(trackWire[i],trackXY[i],trackDL[i],trackZ[i]);
			}

			dcTrack[0]->tracking();
			dcTrack[1]->tracking();
		}
		void print(){
			cout<<"Tracking Data :"<<endl;
			cout<<"Layer Wire XY DL Z"<<endl;
			cout<<setiosflags(ios::left);
			for (int i = 0; i < trackXY.size(); ++i) {
				for (int j = 0; j < trackXY[i].size(); ++j) {
					cout<<setw(4)<<i<<setw(4)<<trackWire[i][j]<<setw(8)<<trackXY[i][j]<<setw(12)<<trackDL[i][j]<<setw(8)<<trackZ[i]<<endl;	
				}
			}
			cout<<"X Track Direction:"<<endl;
			dcTrack[0]->print();
			cout<<"Y Track Direction:"<<endl;
			dcTrack[1]->print();
			
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
		int getLayerXYDirection(int i){
			return dcPositionPara->getLayerXYDirection(i);
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
