class DCConvertCalPara{
	private:
		TString detectorName;
		int totalLayerNumber;
		TGraph *gCalib[20];
		TFile *fCalib;

		void openCalibrationFile(){
			TString inputName = env->GetValue(detectorName+"ConvertPara","calib.root");
			TString inputPath = env->GetValue("convertPath",".");
			cout<<"Loading "<<detectorName<<" Parameters from "<< inputPath<<inputName<<endl;
			fCalib = new TFile(inputPath+inputName,"READ");
		}
		void loadTGraphCurve(){
			for (int i = 0; i < totalLayerNumber; ++i) {

				gCalib[i] = (TGraph *)fCalib->Get(detectorName+Form("tdc%d",i));
			}
		}

	public:
		DCConvertCalPara(TString detName,int totalNumber){
			detectorName = detName;
			totalLayerNumber = totalNumber;

			openCalibrationFile();
			loadTGraphCurve();
		}
		~DCConvertCalPara(){}
		double calDriftLength(int layerId,int wireId,int tdc){
			return gCalib[layerId]->Eval(tdc);
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

		double calDriftLength(int layerId,int wireId,int tdc){
			return convertPara->calDriftLength(layerId,wireId,tdc);
		}



	public:
		int totalLayerNumber;
		TString dcName;

		DCConvertCal(){}
		~DCConvertCal(){}
		void loadParameters(){
			convertPara = new DCConvertCalPara(dcName,totalLayerNumber);
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
		}
		void print(){
			cout<<"Printing Converted Data:"<<endl;
			for (int i = 0; i < (int)driftLength.size(); ++i) {
				cout<< getLayerId(i)<<":"<<getWireId(i)<<":"<<getTdc(i)<<":"<<getDriftLength(i)<<endl;
			}

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
		double getDriftLength(int i){
			return driftLength[i];
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
