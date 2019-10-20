class DCTdcPara{
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
		DCTdcPara(TString detName){
			detectorName = detName;
			totalLayerNumber = 8;

			openCalibrationFile();
			loadTGraphCurve();
		}
		~DCTdcPara(){}
		double calDriftLength(int layerId,int wireId,int tdc){
			return gCalib[layerId]->Eval(tdc);
		}
};


class DCDetectorPara{
	private:
		DCTdcPara *dcTdcPara;
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
			dcTdcPara = new DCTdcPara(dcName);
			pitch = 5;//mm
			loadLayer();
			print();
		}
		~DCDetectorPara(){}
		int getLayerDirection(int layerId){
			return dcDirection[layerId];
		}
		double getWireXPosition(int layerId,int wireId){
			return dcXYPosition[layerId]-wireId*pitch;
		}
		double getWireZPosition(int layerId){
			return dcZPosition[layerId];
		}
		double calDriftLength(int layerId,int wireId,int tdc){
			return dcTdcPara->calDriftLength(layerId,wireId,tdc);
		}

};

class Track1D{
	private:
	public:
		Track1D(){
			x=0;a=0;chi2=99999.;ndf=-1;nhit=0;
			dl=NULL; lid=NULL;wid=NULL;tdc=NULL;wpos=NULL;xpos=NULL;zpos=NULL;


		}
		~Track1D(){
			delete [] dl;
			delete [] lid;
			delete [] wid;
			delete [] tdc;
			delete [] wpos;
			delete [] xpos;
			delete [] zpos;
		}
		Track1D& operator=(const Track1D &right);
		Double_t x;
		Double_t a;
		Double_t chi2;
		Int_t ndf;
		Int_t nhit;

		Double_t *dl;
		Int_t *lid;
		Int_t *wid;
		Int_t *tdc;
		Double_t *wpos;
		Double_t *xpos;
		Double_t *zpos;

		// overriding functions for sorting based on chi2
		Bool_t IsEqual(TObject *obj) const {return chi2 == ((Track1D*)obj)->chi2;}
		Bool_t IsSortable() const { return kTRUE; }
		Int_t Compare(const TObject *obj) const {
			if (chi2 < ((Track1D*)obj)->chi2) return -1;
			else if (chi2 > ((Track1D*)obj)->chi2) return 1;
			else return 0;
		}
		void print(){
			for (int i = 0; i < nhit; ++i) {
				cout<<setw(4)<<i<<" layer = "<<setw(4)<<lid[i]<<" wire = "<<setw(4)<<wid[i]<<" wpos = "<<setw(8)<<wpos[i]<<" tdc = "<<setw(8)<<tdc[i]<<" dl = "<<setw(8)<<dl[i]<<" xpos = "<<setw(8)<<xpos[i]<<" zpos = "<<setw(8)<<zpos[i]<<endl;	
			}
			cout<<"x = "<<x<<" a = "<<a<<" chi2 = "<<chi2<<endl;
		}
};

class TrackPattern{
	private:

		DCDetectorPara *dcDetectorPara;
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
		void loadPara(DCDetectorPara *para){
			dcDetectorPara = para;
		}
		bool checkWirePosition(){
			int nl = hitArray.size();
			int *wid = new int[nl];
			for(Int_t l=0;l<nl;l++){
				wid[l] = hitArray[l].getWire();
				if(l>0&&abs(wid[l]-wid[l-1])>1) return false;
			}
			return true;
		}
		Track1D * tracking(){
			//cout<<"come on Tracking"<<endl;

			Track1D *tr = new Track1D;
			TMatrixD vec(2,1); vec.Zero();
			TMatrixD mat(2,2);  vec.Zero();

			Int_t nl = hitArray.size();
			//cout<<"In each Hits(Pattern) How Many wires included:"<<nl<<endl;
			Int_t npattern = (Int_t)pow(2,nl);
			Double_t *xpos = new Double_t[nl];

			Int_t *lid = new Int_t[nl];
			Int_t *wid = new Int_t[nl];
			Int_t *tdc = new Int_t[nl];
			Double_t *wpos = new Double_t[nl];
			Double_t *dl = new Double_t[nl];
			Double_t *zpos = new Double_t[nl];

			tr->lid = new Int_t[nl];
			tr->wid = new Int_t[nl];
			tr->tdc = new Int_t[nl];
			tr->wpos = new Double_t[nl];
			tr->dl = new Double_t[nl];
			tr->xpos = new Double_t[nl];
			tr->zpos = new Double_t[nl];


			Double_t bestchi2 = 9999.;


			for(Int_t l=0;l<nl;l++){
				lid[l] = hitArray[l].getLayer();
				wid[l] = hitArray[l].getWire();
				tdc[l] = hitArray[l].getTdc();
				dl[l] = dcDetectorPara->calDriftLength(lid[l],wid[l],tdc[l]);
				wpos[l] = dcDetectorPara->getWireXPosition(lid[l],wid[l]);
				zpos[l] = dcDetectorPara->getWireZPosition(lid[l]);
			}

			cout<<"nPattern = "<<npattern<<endl;
			for(Int_t i=0;i<npattern;i++){

				Double_t tmpx, tmpa = 0;
				cout<<"tmpx = " <<tmpx<<" tmpa = "<<tmpa<<endl;
				for(Int_t j=0;j<3;j++){// Needed????!
					vec.Zero();
					mat.Zero();
					for(Int_t l=0;l<nl;l++){
						dl[l] *= sqrt(1+tmpa*tmpa);

						Int_t sign = i&((Int_t)pow(2,l)) ? 1 : -1;
						xpos[l] = wpos[l] + sign*dl[l];

						vec(0,0) += xpos[l];
						vec(1,0) += zpos[l] * xpos[l];

						mat(0,0) ++;
						mat(0,1) += zpos[l];
						mat(1,1) += zpos[l] * zpos[l];

					}
					mat(1,0) = mat(0,1);

					Double_t det = mat(0,0) * mat(1,1) - mat(0,1) * mat(1,0);

					cout<<"fabs(det)="<<fabs(det)<<endl;
					if(fabs(det)<1e-5) continue;
					TMatrixD rxvec(2,1) ;
					rxvec = mat.Invert() * vec;
					tmpx = rxvec(0,0);
					tmpa = rxvec(1,0);
				}

				Double_t chi2 = 0;
				for(Int_t j=0;j<nl;j++)
					chi2 += pow(tmpx+tmpa*zpos[j] - xpos[j],2);


				if(chi2<bestchi2){
					bestchi2 = chi2;
					tr->x = tmpx;
					tr->a = tmpa;
					tr->chi2 = bestchi2;
					tr->ndf = nl-2-1;
					tr->nhit = nl;
					for(Int_t j=0;j<nl;j++){
						//tr->dl[j] = dl[j]/sqrt(1+tmpa*tmpa); // drift length
						tr->xpos[j] = xpos[j];
					}
				}

			}
			for(Int_t l=0;l<nl;l++){
				tr->lid[l]  = lid[l] ;
				tr->wid[l]  = wid[l] ;
				tr->tdc[l]  = tdc[l] ;
				tr->dl[l]   = dl[l]  ;
				tr->wpos[l] = wpos[l];
				tr->zpos[l] = zpos[l];
			}


			delete [] dl;
			delete [] xpos;
			delete [] zpos;
			delete [] lid;
			return tr;

		}

};
class TrackHit{
	private:
		DCDetectorPara *dcDetectorPara;
		vector<DCLayerHit> hitArray;
		vector<TrackPattern> trackPattern;
		vector<Track1D*> trackArray;
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
		void removeImpossiblePattern(){
			for (int i = 0; i < nPattern; ++i) {
				if(!trackPattern[i].checkWirePosition()){
					cout<<"Pattern "<<i<<" Bad!!"<<endl;
					nPattern--;
					trackPattern.erase(trackPattern.begin()+i);
					i--;
				}
			}
		}
		void trackEachPattern(){
			for (int i = 0; i < trackPattern.size(); ++i) {
				trackPattern[i].loadPara(dcDetectorPara);
				trackArray.push_back(trackPattern[i].tracking());
			}
		}



	public:
		TrackHit(){
		}
		~TrackHit(){}
		void init(){
			nPattern = 1;
			nHitLayer = 0;
			hitArray.clear();
			trackPattern.clear();
			trackArray.clear();
		}
		void loadData(DCLayerHit hit){
			hitArray.push_back(hit);
		}
		void loadPara(DCDetectorPara *para){
			dcDetectorPara = para;
		}
		void tracking(){
			calPattern();
			generatePattern();
			removeImpossiblePattern();
			trackEachPattern();
		}
		void print(){
			cout<<"nPattern = "<< nPattern<<endl;
			for (int i = 0; i < hitArray.size(); ++i) {
					hitArray[i].print();
			}
			for (int i = 0; i < trackPattern.size(); ++i) {
				cout<<"Pattern Number:"<< i <<endl;
				trackPattern[i].print();	
				trackArray[i]->print();
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
			xTrackHit->loadPara(dcDetectorPara);
			yTrackHit->loadPara(dcDetectorPara);
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
