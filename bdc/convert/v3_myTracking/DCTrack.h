class Track1D{
	private:
		int chi2;	
		int nHitLayer;
	public:
		Track1D(){}
		~Track1D(){}
		double getChi2(){
			return 0;
		}
		int getNHit(){
			return 1;
		}
};

class TrackArray{
	private:
		Track1D trackArray[200]; 
	public:
		TrackArray(){
		}
		~TrackArray(){}
		void add(Track1D *tr){
		}

};
class DCTrack{
	private:
		int nPattern;
		int nHitLayer;
		vector<vector<int> > wireArrayLayer;
		vector<vector<double> > xArrayLayer;
		vector<vector<double> > dlArrayLayer;
		vector<double> zArrayLayer;

		vector<vector<double> > layerPatternArray;
		vector<vector<double> > wirePatternArray;
		vector<vector<double> > xPatternArray;
		vector<vector<double> > dlPatternArray;
		TrackArray *trackArray;
	
		void calPattern(){
			for (int i = 0; i < xArrayLayer.size(); ++i) {
				if(xArrayLayer[i].size()>0) {
					nPattern *= xArrayLayer[i].size();
					//cout<<xArrayLayer[i].size()<<endl;
					nHitLayer++;
				}
			}
		}
	public:
		void init(){
			nPattern = 1;
			nHitLayer = 0;
			xArrayLayer.clear();
			wireArrayLayer.clear();
			dlArrayLayer.clear();
			zArrayLayer.clear();

			layerPatternArray.clear();
			wirePatternArray.clear();
			xPatternArray.clear();
			dlPatternArray.clear();
	
		}

		DCTrack(){
			trackArray = new TrackArray();
		}
		~DCTrack(){}
		void loadData(vector<int> wire,vector<double> xy,vector<double> dl,double z){
			wireArrayLayer.push_back(wire);
			xArrayLayer.push_back(xy);
			dlArrayLayer.push_back(dl);
			zArrayLayer.push_back(z);
		}
		void tracking(){
			calPattern();
			//if(npattern<0 || npattern>pow(10,numlayer)) return;
			generatePattern();
			checkPattern();
			sort();
		//	print();
		}
		void generatePattern(){
			
			int np = 1;
			layerPatternArray.resize(nPattern);
			wirePatternArray.resize(nPattern);
			xPatternArray.resize(nPattern);
			dlPatternArray.resize(nPattern);
			for (int i = 0;  i < xArrayLayer.size(); ++i) {
				if(xArrayLayer[i].size()>0){
					for (int j = 0; j < nPattern; j+=np) {
						for (int k = 0; k < np; ++k) {
							layerPatternArray[j+k].push_back(i);
							wirePatternArray[j+k].push_back(wireArrayLayer[i][(j%(np*xArrayLayer[i].size()))/np]);
							xPatternArray[j+k].push_back(xArrayLayer[i][(j%(np*xArrayLayer[i].size()))/np]);
							dlPatternArray[j+k].push_back(dlArrayLayer[i][(j%(np*dlArrayLayer[i].size()))/np]);
						}

					}
					np *= xArrayLayer[i].size();
				}

			}
		}

		void removeWrongPattern(){
		}
		void checkPattern(){
			removeWrongPattern();
			for(Int_t i=0;i<nPattern;i++){
				Track1D *tr = CalcTrack1D(xPatternArray[i],dlPatternArray[i]);
				//cout<<"layer_name="<<layer_name<<"npattern="<<i<<endl;
				if( tr->getChi2()<9999. && tr->getNHit() == nHitLayer){
					trackArray->add(tr);
				}
				else{
					delete tr;
				}
			}

		}
		Track1D * CalcTrack1D(vector<double> x,vector<double> dl){
			Track1D *tr = new Track1D();
			return tr;
		}
		void sort(){}
		void print(){

			cout<<"Number of Pattern: "<<nPattern<<endl;
			for (int i = 0; i < nPattern; ++i) {
				cout<<"Pattern: "<<i<<endl;
				for (int j = 0; j < xPatternArray[i].size(); ++j) {
					//cout<<xPatternArray[i][j]<<"\t"<<dlPatternArray[i][j]<<endl;	
					cout<<layerPatternArray[i][j]<<"\t"<<wirePatternArray[i][j]<<"\t"<<xPatternArray[i][j]<<"\t"<<dlPatternArray[i][j]<<endl;	
				}

			}
		}
};
