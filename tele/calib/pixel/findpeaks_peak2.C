int runnum=599;

int npeaks=1;

TString Neck="((Target_X+2.13)<4&&(Target_X+2.13)>-4&&(Target_Y+1.6)>15&&(Target_Y+1.6)<25)";
TString R3="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<21";
TString R1="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";
TString peak2="!("+R1+")&&"+R3+"&&!("+Neck+")";

int LLmin=790;
int LLmax=855;

int LRTmin=1065;
int LRTmax=1145;

int LRBmin=960;
int LRBmax=1045;

int RLTmin=1010;
int RLTmax=1080;

int RLBmin=888;
int RLBmax=948;



int RRBmin=955;
int RRBmax=1030;

int RRTmin=935;
int RRTmax=1015;





int nbin=500;
int Min=500;
int Max=2500;

int SiLFmin=6100;
int SiLFmax=9100;
int SiLBmin=6100;
int SiLBmax=9100;



double esti_peak_sigma=5;




void pixel(int fid,int bid,int runnum);
void LL(int fid,int bid,int runnum);
void LL(int fid,int bid,int runnum,TTree *tree);
void LRT(int fid,int bid,int runnum,TTree *tree);
void LRB(int fid,int bid,int runnum,TTree *tree);
void inside_target(TTree *tree);
void target_frame();
void find(TH1D *temp,double *fpeaks,double esti_peak_sigma);
void out_cali_par(int fid,int bid,int runnum,double *fpeaks,TString name);
void Draw(int fid,int bid,int runnum,TString CsI,TTree *tree);

void findpeaks_peak2()
{

	// inside target marker run 596,599 for(int i=23;i<24;i++)
	// inside target marker run 596,599 for(int i=9;i<10;i++)
	//for(int i=1;i<31;i++)
	for(int i=4;i<6;i++)
	//for(int i=13;i<17;i++)
		for(int j=16;j<17;j++)
	//	for(int j=0;j<32;j++)
		{
			pixel(i,j,runnum);

		}





}
void pixel(int fid,int bid,int runnum)
{
	//TString inputname=Form("pixelrootfiles/pixel%d_%d_run0%d_insidetarget.root",fid,bid,runnum);
	TString inputname=Form("pixelrootfiles/pixel%d_%d_run0%d.root",fid,bid,runnum);
	cout<<inputname<<endl;
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *tree=(TTree*)f->Get("tree");

	TString cname=Form("cpixel%d_%d_run0%d_out",fid,bid,runnum);
	TCanvas *cpixel=new TCanvas(cname,cname);
	cpixel->Divide(2,2);

	if(runnum==596||runnum==599){

		cpixel->cd(1);
		Draw(fid,bid,runnum,"LL",tree);
		cpixel->cd(2);
		Draw(fid,bid,runnum,"LRT",tree);
		cpixel->cd(3);
		Draw(fid,bid,runnum,"LRB",tree);

		//cpixel->SaveAs(Form("pixelrootfiles/pixel%d_%d_run0%d.pdf",fid,bid,runnum));
		//cpixel->Write();
	}
	if(runnum==597||runnum==598){

		cpixel->cd(1);
		Draw(fid,bid,runnum,"RLT",tree);
		cpixel->cd(2);
		Draw(fid,bid,runnum,"RRT",tree);
		cpixel->cd(3);
		Draw(fid,bid,runnum,"RLB",tree);
		cpixel->cd(4);
		Draw(fid,bid,runnum,"RRB",tree);

		//cpixel->SaveAs(Form("pixelrootfiles/pixel%d_%d_run0%d.pdf",fid,bid,runnum));
		//cpixel->Write();
	}



	cpixel->SaveAs(Form("pixelrootfiles/pixel%d_%d_run0%d.pdf",fid,bid,runnum));
//	cpixel->Close();
//	f->Close();

}
void Draw(int fid,int bid,int runnum,TString CsI,TTree *tree)
{



	TString hname=Form("_pixel%d_%d_run0%d",fid,bid,runnum);
	hname="h"+CsI+hname;
	TString draw=">>"+hname+Form("(%d,%d,%d)",nbin,Min,Max);
	draw="pixel"+CsI+draw;
	TString color="";
	int ADCmax=0;
	int ADCmin=0;
	if(CsI=="LL") {ADCmax=LLmax;ADCmin=LLmin;}
	if(CsI=="LRT") {ADCmax=LRTmax;ADCmin=LRTmin;}
	if(CsI=="LRB") {ADCmax=LRBmax;ADCmin=LRBmin;}
	if(CsI=="RRT") {ADCmax=RRTmax;ADCmin=RRTmin;}
	if(CsI=="RRB") {ADCmax=RRBmax;ADCmin=RRBmin;}
	if(CsI=="RLT") {ADCmax=RLTmax;ADCmin=RLTmin;}
	if(CsI=="RLB") {ADCmax=RLBmax;ADCmin=RLBmin;}

	TString CsIname="pixel"+CsI;
	TString Low=Form(">%d",ADCmin);
	TString High=Form("<%d",ADCmax);
	TString ADCLimit=CsIname+Low+"&&"+CsIname+High;
	TString condition=peak2+"&&"+ADCLimit;


	//cout<<condition<<endl;



	tree->Draw(draw,condition,color);
	TH1D *temp = (TH1D*)gDirectory->Get(hname);

	//if(temp->GetEntries()>20&&temp->GetBinContent(temp->GetMaximumBin())>10)
	{

		double fpeaks[3]={0};
		find(temp,fpeaks,esti_peak_sigma);

		out_cali_par(fid,bid,runnum,fpeaks,CsI);

		//temp->Draw();
		TF1 *fpeak = new TF1("fpeak","gaus(0)",Min,Max);
		fpeak->SetParameters(&fpeaks[0]);
		fpeak->SetNpx(2000);
		//fpeak->Draw("same");


	}


}


void find(TH1D *temp,double *fpeaks,double esti_peak_sigma)
{


	double estimate_peak_sigma=esti_peak_sigma;

	//Use TSpectrum to find the peak candidates
	TSpectrum *s = new TSpectrum(2*npeaks,5);
	Int_t nfound = s->Search(temp,estimate_peak_sigma,"nobackground new",0.1); // histo_name, peak_sigma,"",threshold_percentage
	//Int_t nfound = s->Search(temp,estimate_peak_sigma,"",0.05); // histo_name, peak_sigma,"",threshold_percentage
	cout<<"how many peaks found "<<nfound<<endl;


	if(nfound!=1)
	{


		double ratio=0.5;
		//while(1)
		for(int m=0;m<10;m++)
		{
			if(m%2==0) nfound = s->Search(temp,ratio*estimate_peak_sigma,"",0.2);
			else nfound = s->Search(temp,ratio*estimate_peak_sigma,"nobackground",0.05);

			if(nfound==1) break;
			ratio+=0.1;

		}



	}


	//if(temp!=null) temp->Draw();
	temp->Draw();

	printf("Found %d candidate peaks to fit\n",nfound);


	Double_t *xpeaks = s->GetPositionX();

	Double_t par[15]={0};
	// fit parameter
	Double_t fpar[15]={0};

	for (int p=0;p<nfound;p++) {
		Double_t xp = xpeaks[p];
		Int_t bin = temp->GetXaxis()->FindBin(xp);
		Double_t yp = temp->GetBinContent(bin);

		par[3*p+0] = yp;
		par[3*p+1] = xp;
		//par[3*npeaks+2] = estimate_peak_sigma>ratio*estimate_peak_sigma?estimate_peak_sigma:ratio*estimate_peak_sigma;
		par[3*p+2] = estimate_peak_sigma;
		cout<<"npeaks="<<p<<" yp="<<yp<<" xp="<<xp<<endl;
	}
	printf("Found %d useful peaks to fit\n",npeaks);
	printf("Now fitting: Be patient\n");


	// range of f needed to be adjusted
	//par[0]=10;
	//par[1]=1813;
	//par[2]=9;

	double afr1=10;
	double abr1=10;
	double fr1=par[1]-afr1*par[2];
	double br1=par[1]+abr1*par[2];


	TF1 *peak1 = new TF1("peak1","gaus(0)",fr1,br1);
	peak1->SetParameters(&par[0]);
	//peak1->FixParameter(1, xbinmax);
	//peak1->SetParameter(2, 0.02);  // sigma
	peak1->SetParLimits(0, 0.001, 10000);
	peak1->SetParLimits(1, 0.001, 4000);
	peak1->SetParLimits(2, 0.001, 40);
	//peak1->SetParameters(&par[0]);
	peak1->SetNpx(2000);
	temp->Fit(peak1,"R");
	peak1->GetParameters(&fpeaks[0]);
        //peak1->ReleaseParameter(3);
	//peak1->Draw("same");

	delete peak1;
	delete s;

	//	peak1->Delete();

	//	s->Delete();

}

void out_cali_par(int fid,int bid,int runnum,double *fpeaks,TString name)
{

	TString inputname=Form("pixel_run0%d.root",runnum);
	inputname=name+inputname;
	TString outputname="peak2_"+inputname;
	outputname.ReplaceAll("root","txt");
	ofstream out(outputname,ios_base::app | ios_base::out);
	out.flags (ios::left);
	out<<setw(20)<<fid<<setw(20)<<bid<<setw(20)<<setw(20)<<fpeaks[0]<<setw(20)<<fpeaks[1]<<setw(20)<<fpeaks[2]<<endl;
	out.close();

}

