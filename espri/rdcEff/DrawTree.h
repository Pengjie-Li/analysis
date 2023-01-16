// Quadratic background function
Double_t background(Double_t *x, Double_t *par) {
   return par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0];
   //return par[0] + par[1]*x[0];
}
Double_t gaussianPeak(Double_t *x,Double_t *par){
		return par[0]*TMath::Exp(-(((x[0]-par[1])*(x[0]-par[1]))/(2*par[2]*par[2]))); 
}
// Lorenzian Peak function
Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[1]/TMath::Pi()) /
    TMath::Max( 1.e-10,(x[0]-par[2])*(x[0]-par[2])
   + .25*par[1]*par[1]);
}

// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par) {
  //return gaussianPeak(x,&par[0])+ gaussianPeak(x,&par[3]) +gaussianPeak(x,&par[6]) +  background(x,&par[9]);
  return gaussianPeak(x,&par[0])+ gaussianPeak(x,&par[3]) +  background(x,&par[6]);
  //return gaussianPeak(x,&par[0])+ gaussianPeak(x,&par[3]) +gaussianPeak(x,&par[6]);
}
class DrawTree{
	private:
		TChain *tree;
		int markerStyle;
		TString gate;

		TString varX;
		TString varY;
		TString varH;

		int binX,binY;
		double minX,minY,maxX,maxY;
		int binH;
		double minH,maxH;

		TString hName;
	public:
		DrawTree(){
			tree = new TChain("tree");
			markerStyle = 1;
		}
		void addFile(TString fileName){
			tree->Add(fileName);
		}
		void setMarkerStyle(int style){
			markerStyle = style;
		}
		void scan(TString var){
			tree->Scan(var,gate);
		}

		TString getGate(){
			return gate;
		}
		void loadCut(){

                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar32He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar33He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar34He6.C");

						gROOT->ProcessLine(".x rootfiles/cutBe10Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar17He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar18He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar19He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar20He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar21He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar22He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar23He4.C");


                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar28He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar29He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar30He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar31He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar32He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar36He8.C");


						gROOT->ProcessLine(".x rootfiles/cutBe12Bar9He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar10He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar24He6.C");



                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar3He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar4He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar5He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar6He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar7He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar8He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He4.C");

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar24He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar26He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar32He6.C");

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar36He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar37He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar38He8.C");

		}
		void setDCAlias(){
				gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/rootfiles/dcAlias.C");
		}
		void setAlias(TString var1,TString var2){
				tree->SetAlias(var1,var2);
		}
		void setConstantAlias(){
				gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/alias/constantAlias.C");
		}
		void setTofAlias(){
				gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/alias/tofAlias.C");
		}
		void setPPAlias(){

			gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/alias/ppAlias.C");

		}
		void setPPAlphaAlias(){

			gROOT->ProcessLine(".x /Volumes/LPJ/S12/analysis/alias/ppAlphaAlias.C");

		}
		void setPPBe10Alias(){
			setConstantAlias();
			setPPAlias();
			setTofAlias();
			tree->SetAlias("MassBe","MassBe10*1");
		}
		void setPPBe12Alias(){
				setConstantAlias();
				setPPAlias();
				setTofAlias();
				tree->SetAlias("MassBe","MassBe12*1");
		}
		void setPPBe14Alias(){
				setConstantAlias();
				setPPAlias();
				setTofAlias();
				tree->SetAlias("MassBe","MassBe14*1");
		}
		void setPPAlphaBe10Alias(){
				setConstantAlias();
				setPPAlphaAlias();
				tree->SetAlias("MassBe","MassBe10*1");
				tree->SetAlias("residueRestMass","MassHe6*AMU");
		}
		void setPPAlphaBe12Alias(){
				setConstantAlias();
				setPPAlphaAlias();
				tree->SetAlias("MassBe","MassBe12*1");
				tree->SetAlias("residueRestMass","MassHe8*AMU");
		}
		void setPPAlphaBe14Alias(){
				setConstantAlias();
				setPPAlphaAlias();
				tree->SetAlias("MassBe","MassBe14*1");
				tree->SetAlias("residueRestMass","MassHe10*AMU");
		}

		void setGate(TString g){
			gate = g;
		}
		void addGate(TString g){
			gate = gate+"&&"+g;
		}

		void setVar(TString vY,TString vX){
			varX = vX;	
			varY = vY;	
		}
		void setVar(TString vH){
			varH = vH;
		}
		void setBin(int bX,double miX,double maX,int bY,double miY,double maY){
			binX = bX; minX = miX; maxX = maX;
			binY = bY; minY = miY; maxY = maY;
		}
		void setBin(int bH,double miH,double maH){
			binH = bH; minH = miH; maxH = maH;
		}
		void setName(TString hN){
			hName = hN;
		}
		void drawH(){
			TString draw = varH + Form(">>")+ hName + Form("(%d,%2f,%2f)",binH,minH,maxH);	
			tree->Draw(draw,gate);
		}
		void scaleH(double scl){
				TH1F *h = (TH1F*)gDirectory->Get(hName);
				h->Scale(scl);
		}
		void fitGaus(double min,double max){
				TH1F *h = (TH1F*)gDirectory->Get(hName);
				h->Fit("gaus","R","",min,max);
		}
		void fitExBe10_back(){

				//TH1F *hEx = (TH1F*)gDirectory->Get("hEx");
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);

				//double bgPar[4];
//				double par[9];
//				par[0] = 50;
//				par[3] = 200;
//				par[3] = 50;
//				par[1]= 0;par[2]= 0.7;
//				par[4]= 3.3;par[5]= 0.7;
//				par[7]= 6;par[8]= 2;
//	
//				TF1 *f1 = new TF1("f1","gaus(0)",-1.5,1);
//				TF1 *f2 = new TF1("f2","gaus(0)",2.5,4.2);
//				TF1 *f3 = new TF1("f3","gaus(0)",0,15);
//				//TF1 *f3 = new TF1("f3","landau(0)",5,10);
//				//TF1 *f = new TF1("f","gaus(0)+gaus(3)+landau(6)",-2,10);
//				TF1 *f = new TF1("f","gaus(0)+gaus(3)+gaus(6)",-2,7);
//				hEx->Fit(f1,"R");
//				hEx->Fit(f2,"R+");
//				hEx->Fit(f3,"R+");
//				f1->GetParameters(&par[0]);
//				f2->GetParameters(&par[3]);
//				f3->GetParameters(&par[6]);
//				f->SetParameters(par);
//				hEx->Fit(f,"R+");

				double par[10];
				par[0] = 50;
				par[3] = 200;
				par[1]= 0;par[2]= 0.7;
				par[4]= 3.3;par[5]= 0.7;

				TF1 *bg = new TF1("bg",background,-4.5,6,2);
				hEx->Fit(bg,"R+");
				bg->GetParameters(&par[6]);
				// create a TF1 with the range from 0 to 3 and 6 parameters
				TF1 *fitFcn = new TF1("fitFcn",fitFunction,-4.5,6,10);
				fitFcn->SetNpx(500);
				fitFcn->SetLineWidth(4);
				fitFcn->SetLineColor(kMagenta);

				//fitFcn->SetParameters(bgPar[0],bgPar[1],bgPar[2],50,0,0.8,300,3.3,0.7);
				fitFcn->SetParameters(par);
				//hEx->Fit("fitFcn","R0");
				hEx->Fit("fitFcn","R+");

			//	// second try: set start values for some parameters
				//fitFcn->FixParameter(4,0); // width
				fitFcn->SetParameter(1,0); // width
				//fitFcn->SetParLimits(1,-0.1,0.1);
				fitFcn->SetParameter(2,0.8);   // peak

				fitFcn->SetParameter(4,3.36); // width
				//fitFcn->SetParLimits(4,3.3,3.45);
				fitFcn->SetParameter(5,0.7);   // peak

				hEx->Fit("fitFcn","RV+","ep");
				//Double_t par[6];
				//f1->GetParameters(&par[0]);
				//f2->GetParameters(&par[3]);
				//f->SetParameters(par);
				//hEx->Fit(f,"R+");
				//f->GetParameters(&par[0]);
				////cout<<par[1]<<"\t"<<par[2]<<"\t"<<par[4]<<"\t"<<par[5]<<"\t"<<endl;
				//cout<<"gs Peak:"<<endl;
				//cout<<"Mean = "<<par[1]<<" MeV"<<endl;
				//cout<<"Sigma = "<<par[2]<<" MeV"<<endl;
				//cout<<"fex Peak:"<<endl;
				//cout<<"Mean = "<<par[4]<<" MeV"<<endl;
				//cout<<"Sigma = "<<par[5]<<" MeV"<<endl;
		}
		void fitExBe10(int side, int barId){
				//TF1 *f1 = new TF1("f1","gaus",-2,1);
				//TF1 *f = new TF1("f","gaus(0)+gaus(3)",-2,5);
				TF1 *f1 = new TF1("f1","gaus",-1.5,1);
				TF1 *f2 = new TF1("f2","gaus",2.5,4.2);
				TF1 *f = new TF1("f","gaus(0)+gaus(3)",-1.5,4.2);
				TString hName = Form("hExEnergy_%d_%d",side,barId);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[6];
				hEx->Fit(f1,"QR");
				hEx->Fit(f2,"QR+");
				f1->GetParameters(&par[0]);
				f2->GetParameters(&par[3]);
				f->SetParameters(par);
				hEx->Fit(f,"QR+");
				f->GetParameters(&par[0]);
				cout<<side<<"  "<<barId<<" "<<par[4]<<"\t"<<par[5]<<"\t"<<endl;
		}
		void fitExBe12(int side, int barId){
				TF1 *f = new TF1("f","gaus",1,3);
				TString hName = Form("hExEnergy_%d_%d",side,barId);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[3];
				hEx->Fit(f,"QR");
				f->GetParameters(&par[0]);
				cout<<side<<"  "<<barId<<" "<<par[1]<<"\t"<<par[2]<<"\t"<<endl;
		}
		void fitExBe14(int side, int barId){
				TF1 *f = new TF1("f","gaus",-3,2);
				TString hName = Form("hExEnergy_%d_%d",side,barId);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				f->SetParameter(1,0);
				f->SetParameter(2,1);
				Double_t par[3];
				hEx->Fit(f,"QR");
				f->GetParameters(&par[0]);
				cout<<side<<"  "<<barId<<" "<<par[1]<<"\t"<<par[2]<<"\t"<<endl;

		}

		void fitExBe10(){
				//TF1 *f1 = new TF1("f1","gaus",-2,1);
				//TF1 *f = new TF1("f","gaus(0)+gaus(3)",-2,5);
				TF1 *f1 = new TF1("f1","gaus",-1.5,1);
				TF1 *f2 = new TF1("f2","gaus",2.5,4.2);
				TF1 *f = new TF1("f","gaus(0)+gaus(3)",-1.5,4.2);
				//TH1F *hEx = (TH1F*)gDirectory->Get("hEx");
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[6];
				hEx->Fit(f1,"R");
				hEx->Fit(f2,"R+");
				f1->GetParameters(&par[0]);
				f2->GetParameters(&par[3]);
				f->SetParameters(par);
				hEx->Fit(f,"R+");
				f->GetParameters(&par[0]);
				//cout<<par[1]<<"\t"<<par[2]<<"\t"<<par[4]<<"\t"<<par[5]<<"\t"<<endl;
				cout<<"gs Peak:"<<endl;
				cout<<"Mean = "<<par[1]<<" MeV"<<endl;
				cout<<"Sigma = "<<par[2]<<" MeV"<<endl;
				cout<<"fex Peak:"<<endl;
				cout<<"Mean = "<<par[4]<<" MeV"<<endl;
				cout<<"Sigma = "<<par[5]<<" MeV"<<endl;
		}
		void fitExBe12(){
				TF1 *f = new TF1("f","gaus",1,3);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[3];
				hEx->Fit(f,"R");
				f->GetParameters(&par[0]);
				cout<<"fex Peak:"<<endl;
				cout<<"Mean = "<<par[1]<<" MeV"<<endl;
				cout<<"Sigma = "<<par[2]<<" MeV"<<endl;
	
		}
		void fitExBe14(){
				TF1 *f = new TF1("f","gaus",-5,5);
				//TH1F *hEx = (TH1F*)gDirectory->Get("hEx");
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[3];
				hEx->Fit(f,"R");
				f->GetParameters(&par[0]);
				cout<<"gs Peak:"<<endl;
				cout<<"Mean = "<<par[1]<<" MeV"<<endl;
				cout<<"Sigma = "<<par[2]<<" MeV"<<endl;

		}
		void fitPhi(){
				TF1 *f = new TF1("f","gaus",-100,260);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[3];
				hEx->Fit(f,"QR");
				f->GetParameters(&par[0]);
				cout<<"Phi "<<par[1]<<"  "<<par[2]<<endl;

		}
		void fitPPAlpha(){
				TF1 *f = new TF1("f","gaus",-3,3);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[3];
				hEx->Fit(f,"QR");
				f->GetParameters(&par[0]);
				hEx->Fit(f,"Q","R",par[1]-2*par[2],par[1]+2*par[2]);
				f->GetParameters(&par[0]);
				cout<<"ppAlpha "<<par[1]<<"  "<<par[2]<<endl;

		}

		void setTeleAngleAlias(int i,int j){
				switch (i) {
						case 0:
								tree->SetAlias("alphaAngle",Form("teleAngleLeft[%d]",j));			
								break;
						case 1:
								tree->SetAlias("alphaAngle",Form("teleAngleRight[%d]",j));			
								break;
						case 2:
								tree->SetAlias("alphaAngle",Form("teleAngleUp[%d]",j));			
								break;
						case 3:
								tree->SetAlias("alphaAngle",Form("teleAngleDown[%d]",j));			
								break;
						default:
								break;
								
				}
		}
		void fitPPAlpha(int i,int j){
				TF1 *f = new TF1("f","gaus",-3,3);
				TH1F *hEx = (TH1F*)gDirectory->Get(hName);
				Double_t par[3];
				hEx->Fit(f,"QR");
				f->GetParameters(&par[0]);
				hEx->Fit(f,"Q","R",par[1]-2*par[2],par[1]+2*par[2]);
				f->GetParameters(&par[0]);
				cout<<i<<"  "<<j<<"  "<<par[1]<<"  "<<par[2]<<endl;

		}
		void draw2H(){
			TString draw = varY+":"+varX + ">>" + hName + Form("(%d,%2f,%2f,%d,%2f,%2f)",binX,minX,maxX,binY,minY,maxY);	
			tree->Draw(draw,gate);
		}
		void draw2D(){
			TString draw = varY+":"+varX + ">>" + hName + Form("(%d,%2f,%2f,%d,%2f,%2f)",binX,minX,maxX,binY,minY,maxY);	
			tree->Draw(draw,gate,"colz");
		}
		void extractQPedAndErrorBe14(){
				TH2F *h = (TH2F*)gDirectory->Get(hName);
				TProfile *hp = h->ProfileX();
				hp->Draw("same");
				//cout<<hp->GetSize()<<endl;

				cout<<hp->GetBinContent(1)<<" "<<(hp->GetBinError(1))<<" "<<hp->GetBinContent(2)<<" "<<(hp->GetBinError(2))<<endl;	
		}

		void extractQPedAndError(){
				TH2F *h = (TH2F*)gDirectory->Get(hName);
				TProfile *hp = h->ProfileX();
				hp->Draw("same");
				//cout<<hp->GetSize()<<endl;
				for (int i = 0; i < 7; ++i) {

						if(hp->GetSize()==82) cout<<hp->GetBinContent(32+4*i)<<" "<<hp->GetBinError(32+4*i)<<" ";	
						//if(hp->GetSize()==42) cout<<hp->GetBinContent(16+2*i)<<" ";	
						//if(hp->GetSize()==42) cout<<hp->GetBinContent(16+2*i)<<" "<<(hp->GetBinEntries(16+2*i))<<" ";	
						if(hp->GetSize()==42) cout<<(hp->GetBinEntries(16+2*i))<<" ";	
						if(hp->GetSize()==22) cout<<hp->GetBinContent(8+i)<<" "<<hp->GetBinError(8+i)<<" ";	

						//	if(hp->GetSize()==82) cout<<hp->GetBinContent(32+4*i)<<" "<<hp->GetBinError(32+4*i)<<" ";	
				//	if(hp->GetSize()==42) cout<<hp->GetBinContent(16+2*i)<<" "<<sqrt(hp->GetBinEntries(16+2*i))*hp->GetBinError(16+2*i)<<" ";	
				//	if(hp->GetSize()==22) cout<<hp->GetBinContent(8+i)<<" "<<hp->GetBinError(8+i)<<" ";	
				}
				cout<<endl;
	
			//	for (int i = 0; i < 7; ++i) {
			//		cout<<hp->GetBinError(16+2*i)<<" ";	
			//	}
				//cout<<endl;
		}
		void proj2DAndFit(){
				//TF1 *f = new TF1("f","pol3");
				TF1 *f = new TF1("f","pol3");
				TH2F *h = (TH2F*)gDirectory->Get(hName);
				TProfile *hp = h->ProfileX();
				hp->Draw("same");
				//hp->Fit(f,"Q","R",62.5,69.5);
				//hp->Fit(f,"Q","R",62.5,70);
				//hp->Fit(f,"Q","R",62,69.5);
				//hp->Fit(f,"Q","WR",63,70);
				hp->Fit(f,"Q","R",65.5,70);
				//hp->Fit(f,"Q","R",63,70.5);
				cout<<f->Eval(63)<<" "<<f->Eval(64)<<" "<<f->Eval(65)<<" "<<f->Eval(66)<<" "<<f->Eval(67)<<" "<<f->Eval(68)<<" "<<f->Eval(69)<<endl;
		}
		void saveH1Root(){

			TH1F *hOutput = (TH1F*)gDirectory->Get(hName);
			//TFile *output = new TFile("output.root","UPDATE");
			hOutput->Write();
			//output->Close();
		}
		void saveH2Root(){

			//cout<<"Name:"<<hName<<endl;
			TH2F *hOutput = (TH2F*)gDirectory->Get(hName);
			//TFile *output = new TFile("output.root","UPDATE");
			hOutput->Write();
			//output->Close();
		}




		~DrawTree(){
			delete tree;
		}
};

