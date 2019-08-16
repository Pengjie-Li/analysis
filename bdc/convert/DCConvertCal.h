class DCConvertCalPara{
	private:
		TGraph *gCalib[20];
		TFile *fCalib;
	public:
		DCConvertCalPara(TString detectorName,int totalLayerNumber){
			TString inputName = env->GetValue(detectorName+"ConvertPara","calib.root");
			cout<<inputName<<endl;
			cout<<detectorName<<"Parameters"<<endl;
			//fCalib = new TFile(inputName,"READ");
			for (int i = 0; i < totalLayerNumber; ++i) {
					
				
			}
			
		}
		~DCConvertCalPara(){}
		double calDriftLength(int layerId,int wireId,int tdc){
			return -10;
		}
};
class DCConvertCal{
	private:
		DCReadRaw *rawData;
		DCConvertCalPara *convertPara;
		vector<double> driftLength;
		void init(){
			rawData = NULL;
			driftLength.clear();
		}

	public:
		int totalLayerNumber;
		TString dcName;

		DCConvertCal(){}
		~DCConvertCal(){}
		void loadParameters(){
			convertPara = new DCConvertCalPara(dcName);
		}

		void setBranch(TTree *tree){
			tree->Branch(dcName + "DriftLength"   ,&driftLength);
		}
		void calibrate(DCReadRaw *dcReadRaw){
			init();
			rawData = dcReadRaw;
			for (int i = 0; i < getNHits(); ++i) {
				double dl = calDriftLength( getLayerId(i),getWireId(i),getTdc(i));
				driftLength.push_back(dl);
			}
			//dcReadRaw->print();
		}
		int getNHits(){
			rawData->getNHits();
		}
		int getLayerId(int i){
			rawData->getLayerId(i);
		}
		int getWireId(int i){
			rawData->getWireId(i);
		}
		int getTdc(int i){
			rawData->getTdc(i);
		}
		double calDriftLength(int layerId,int wireId,int tdc){
			return convertPara->calDriftLength(layerId,wireId,tdc);
		}




};
class BDC1ConvertCal:public DCConvertCal{
	private:
	public:
		BDC1ConvertCal(){
			dcName = "bdc1";
			totalLayerNumber = 8;
			loadParameters();
		}
		~BDC1ConvertCal(){}
};
class BDC2ConvertCal:public DCConvertCal{
	private:
	public:
		BDC2ConvertCal(){
			dcName = "bdc2";
			totalLayerNumber = 8;
			loadParameters();
		}
		~BDC2ConvertCal(){}
};
class FDC0ConvertCal:public DCConvertCal{
	private:
	public:
		FDC0ConvertCal(){
			dcName = "fdc0";
			totalLayerNumber = 8;
			loadParameters();
		}
		~FDC0ConvertCal(){}
};
