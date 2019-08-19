class DCTracking{
	private:
		vector<double> trackX;
		vector<double> trackY;
		double chiX;
		double chiY;
		double ndfX;
		double ndfY;
		vector<double> layerResidue;


		// Analysis Result
		double X;
		double Y;
		double thetaX;
		double thetaY;

		DCConvertCal *convertData;
		void init(){
			convertData = NULL;
			trackX.clear();
			trackY.clear();
			chiX = NAN;
			chiY = NAN;
			ndfX = NAN;
			ndfY = NAN;
			layerResidue.resize(totalLayerNumber,NAN);
		}
	public:
		int totalLayerNumber;
		TString dcName;
		DCTracking(){}
		~DCTracking(){}

		void setBranch(TTree *tree){

			
			
			tree->Branch(dcName+"TrackX",&trackX);
			tree->Branch(dcName+"TrackY",&trackY);
	
			// How good fitness
			tree->Branch(dcName+"ChiX",&chiX);
			tree->Branch(dcName+"ChiY",&chiY);
			tree->Branch(dcName+"NdfX",&ndfX);
			tree->Branch(dcName+"NdfY",&ndfY);

			tree->Branch(dcName+"X",&X);
			tree->Branch(dcName+"Y",&Y);
			tree->Branch(dcName+"ThetaX",&thetaX);
			tree->Branch(dcName+"ThetaY",&thetaY);

			tree->Branch(dcName+"LayerResidue",&layerResidue);

		}
		void findBestTrack(DCConvertCal *dcConvertCal){
			init();
			convertData = dcConvertCal;
			convertData->print();
			/**
			 * 1. (wire,layer)->wire Position in X,Z
			 * 2. generate 2^layer possible Hit Position in X,Z
			 * 3. loop Hit Position, fit into Track, sort with Chi2
			 */
			//	for (int i = 0; i < getNHits(); ++i) {
		//		
		//	}
			
		}
};
class BDC1Tracking:public DCTracking{
	private:
	public:
		BDC1Tracking(){
			dcName = "bdc1";
			totalLayerNumber = 8;

		}
		~BDC1Tracking(){}
};
class BDC2Tracking:public DCTracking{
	private:
	public:
		BDC2Tracking(){
			dcName = "bdc2";
			totalLayerNumber = 8;
		}
		~BDC2Tracking(){}
};
class FDC0Tracking:public DCTracking{
	private:
	public:
		FDC0Tracking(){
			dcName = "fdc0";
			totalLayerNumber = 8;
		}
		~FDC0Tracking(){}
};
