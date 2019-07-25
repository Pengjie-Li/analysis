class FitHisto{
	private:
		int isLR;
		int barID;

		TH2F *h;
		TProfile *hP;
		TF1 *f;
	public:
		FitHisto(){barID =-1;}
		void setName(int lr){
			isLR = lr;
		}
		void setName(int lr,int id){
			isLR = lr;
			barID = id;
		}
		~FitHisto(){}
		void loadHisto(TH2F *hInput){
			h = hInput;
			h->Draw("colz");
		}
		void profileX(){
			hP = h->ProfileX();
			TString hPName = (barID == -1)?Form("hP%d",isLR):Form("hP%d_%d",isLR,barID);
			hP->SetName(hPName);
			hP->Draw("same");
		}
		void fitRange(){
			TString fName = (barID == -1)?Form("fit%d",isLR):Form("fit%d_%d",isLR,barID);
			f = new TF1(fName,"pol2",63,69);
			hP->Fit(f,"RQ");
		}
		void draw(){
			h->Draw("colz");
			hP->Draw("same");
		}
		double getYPed(double angle){
			return f->Eval(angle);
		}
		void save(){
			hP->Write();
			f->Write();
		}
};
void fitPlas(int isLR){
	TString hName = Form("hPed%d",isLR);
	TH2F *hPlas = (TH2F*)gDirectory->Get(hName);
	//hPlas->Draw("colz");
	FitHisto *fh = new FitHisto();
	fh->setName(isLR);
	fh->loadHisto(hPlas);
	fh->profileX();
	fh->fitRange();
	cout<<"\t"<<isLR<<"\t"<<fh->getYPed(63)<<"\t"<<fh->getYPed(64)<<"\t"<<fh->getYPed(65)<<"\t"<<fh->getYPed(66)<<"\t"<<fh->getYPed(67)<<"\t"<<fh->getYPed(68)<<"\t"<<fh->getYPed(69)<<endl;

}
void fitNai(int isLR,int barID){
	TString hName = Form("hPed%d_%d",isLR,barID);
	TH2F *hNai = (TH2F*)gDirectory->Get(hName);
	//hNai->Draw("colz");
	FitHisto *fh = new FitHisto();
	fh->setName(isLR,barID);
	fh->loadHisto(hNai);
	fh->profileX();
	fh->fitRange();
	cout<<"\t"<<isLR<<"\t"<<barID<<"\t"<<fh->getYPed(63)<<"\t"<<fh->getYPed(64)<<"\t"<<fh->getYPed(65)<<"\t"<<fh->getYPed(66)<<"\t"<<fh->getYPed(67)<<"\t"<<fh->getYPed(68)<<"\t"<<fh->getYPed(69)<<endl;
	fh->save();


}
void fitPlasAll(){
	TCanvas *cPlas = new TCanvas("cPlas","cPlas",1200,700);
	cPlas->Divide(2,1);
	cPlas->cd(1);
	fitPlas(0);
	cPlas->cd(2);
	fitPlas(1);
	cPlas->Write();
}
void fitNaiAll(){
	TCanvas *cNai = new TCanvas("cNai","cNai",1200,700);
	cNai->Divide(4,4);
	//fitPlas(0);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {

			cNai->cd(8*i+j+1);
			fitNai(i,j);
		}

	}
	cNai->Write();
}
void fitHisto(){
	TString fileName = "calibHisto.root";
	TFile *inputFile = new TFile(fileName,"UPDATE");
	fitPlasAll();
	//fitNaiAll();


}
