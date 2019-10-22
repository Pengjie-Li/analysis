class Fit2DOffset{
	private:
		int fitMin;
		int fitMax;
	public:
		Fit2DOffset(){}
		~Fit2DOffset(){}
		void setRange(int min,int max){
			fitMin = min;
			fitMax = max;
		}
		void fit(TH2F *hTRaw){
			hTRaw->Draw("colz");
			TProfile *hp = hTRaw->ProfileX();
			hp->Draw("*same");
			hp->Fit("pol1","","",fitMin,fitMax);
		}
};
void checkFit(int id){
	Fit2DOffset *f2o = new Fit2DOffset();
	TH2F *hHodBar = (TH2F*)gDirectory->Get(Form("hTRaw%d",id));	
	if(id>23) f2o->setRange(500,4000);
	else f2o->setRange(500,30000);
	f2o->fit(hHodBar);

}
void fitOffset(){
	TString fileName = "checkTRawOffset298_330.root";
	TFile *inputFile = new TFile(fileName,"READ");
	//TH2F *hHodBar[40];
	checkFit(30);
}
