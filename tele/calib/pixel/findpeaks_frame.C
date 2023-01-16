int runnum=596;
int npeaks=1;

int llbin=1000;
int llmin=500;
int llmax=2500;

int lrtbin=1000;
int lrtmin=500; 
int lrtmax=2500;

int lrbbin=1000;
int lrbmin=500; 
int lrbmax=2500;

int Rtarget=16;
int SiLFmin=6100;
int SiLFmax=9100;
int SiLBmin=6100;
int SiLBmax=9100;

int Frame1=27;
int Frame2=-27;
int Neckxmin=-4;
int Neckxmax=4;
int Neckymin=13;
int Neckymax=27;




//int runnum=599;
//int npeaks=1;
//
//int llbin=1000;
//int llmin=500;
//int llmax=2500;
//
//int lrtbin=1000;
//int lrtmin=500; 
//int lrtmax=2500;
//
//int lrbbin=1000;
//int lrbmin=500; 
//int lrbmax=2500;
//
//int Rtarget=16;
//int SiLFmin=9500;
//int SiLFmax=14100;
//int SiLBmin=9500;
//int SiLBmax=14100;
//int Frame1=27;
//int Frame2=-27;
//int Neckxmin=-4;
//int Neckxmax=4;
//int Neckymin=13;
//int Neckymax=27;




double esti_peak_sigma_LL=5;
double esti_peak_sigma_LRT=5;
double esti_peak_sigma_LRB=5;




void pixel(int fid,int bid,int runnum);
void LL(int fid,int bid,int runnum);
void LL(int fid,int bid,int runnum,TTree *tree);
void LRT(int fid,int bid,int runnum,TTree *tree);
void LRB(int fid,int bid,int runnum,TTree *tree);
void inside_target(TTree *tree);
void target_frame();
void find(TH1D *temp,double *fpeaks,double esti_peak_sigma);
void out_cali_par(int fid,int bid,int runnum,double *fpeaks,TString name);

void findpeaks_frame()
{

	// inside target marker run 596,599 for(int i=23;i<24;i++)
	// inside target marker run 596,599 for(int i=9;i<10;i++)
	for(int i=22;i<23;i++)
		//	for(int i=0;i<32;i++)
		//for(int j=10;j<12;j++)
		for(int j=0;j<32;j++)
		//for(int j=15;j<16;j++)
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

	cpixel->cd(1);
	LL(fid,bid,runnum,tree);
	cpixel->cd(2);
	LRT(fid,bid,runnum,tree);
	cpixel->cd(3);
	LRB(fid,bid,runnum,tree);

	cpixel->Write();
	//f->Close();

}
void LL(int fid,int bid,int runnum,TTree *tree)
{



	TString hname=Form("hLL_pixel%d_%d_run0%d",fid,bid,runnum);
	TString draw="pixelLL>>"+hname+Form("(%d,%d,%d)",llbin,llmin,llmax);
	TString condition1=Form("sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))>%d",Rtarget);
	TString condition2=Form("&&pixelF>%d&&pixelF<%d",SiLFmin,SiLFmax);
	TString condition3=Form("&&pixelB>%d&&pixelB<%d",SiLBmin,SiLBmax);
	TString condition4=Form("&&(Target_X+2.13)<%d&&(Target_X+2.13)>%d&&(Target_Y+1.1)<%d&&(Target_Y+1.1)>%d",Frame1,Frame2,Frame1,Frame2);
	TString condition5=Form("&&!((Target_X+2.13)<%d&&(Target_X+2.13)>%d&&(Target_Y+1.1)>%d&&(Target_Y+1.1)<%d)",Neckxmax,Neckxmin,Neckymin,Neckymax);

	TString condition=condition1+condition2+condition3+condition4+condition5;
	TString color="";

	tree->Draw(draw,condition,color);
	TH1D *temp =  (TH1D*)gDirectory->Get(hname);

	if(temp->GetEntries()>20&&temp->GetBinContent(temp->GetMaximumBin())>10)
	{

		double fpeaks[3]={0};
		find(temp,fpeaks,esti_peak_sigma_LL);

		out_cali_par(fid,bid,runnum,fpeaks,"LL");

		//temp->Draw();
		TF1 *fpeak = new TF1("fpeak","gaus(0)",llmin,llmax);
		fpeak->SetParameters(&fpeaks[0]);
		fpeak->SetNpx(2000);
		//fpeak->Draw("same");


	}


}
void LRT(int fid,int bid,int runnum,TTree *tree)
{



	TString hname=Form("hLRT_pixel%d_%d_run0%d.root",fid,bid,runnum);
	TString draw="pixelLRT>>"+hname+Form("(%d,%d,%d)",lrtbin,lrtmin,lrtmax);
	TString condition1=Form("sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))>%d",Rtarget);
	TString condition2=Form("&&pixelF>%d&&pixelF<%d",SiLFmin,SiLFmax);
	TString condition3=Form("&&pixelB>%d&&pixelB<%d",SiLBmin,SiLBmax);

	TString condition4=Form("&&(Target_X+2.13)<%d&&(Target_X+2.13)>%d&&(Target_Y+1.1)<%d&&(Target_Y+1.1)>%d",Frame1,Frame2,Frame1,Frame2);
	TString condition5=Form("&&!((Target_X+2.13)<%d&&(Target_X+2.13)>%d&&(Target_Y+1.1)>%d&&(Target_Y+1.1)<%d)",Neckxmax,Neckxmin,Neckymin,Neckymax);

	TString condition=condition1+condition2+condition3+condition4+condition5;

	TString color="";

	tree->Draw(draw,condition,color);
	TH1D *temp =  (TH1D*)gDirectory->Get(hname);

	//if(temp->GetEntries()>20)
	if(temp->GetEntries()>20&&temp->GetBinContent(temp->GetMaximumBin())>10)
	{


		double fpeaks[3]={0};
		find(temp,fpeaks,esti_peak_sigma_LRT);

		out_cali_par(fid,bid,runnum,fpeaks,"LRT");

//		temp->Draw();
		TF1 *fpeak = new TF1("fpeak","gaus(0)",lrtmin,lrtmax);
		fpeak->SetParameters(&fpeaks[0]);
		fpeak->SetNpx(2000);
//		fpeak->Draw("same");

	}


}
void LRB(int fid,int bid,int runnum,TTree *tree)
{



	TString hname=Form("hLRB_pixel%d_%d_run0%d.root",fid,bid,runnum);
	TString draw="pixelLRB>>"+hname+Form("(%d,%d,%d)",lrbbin,lrbmin,lrbmax);
	TString condition1=Form("sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.1)*(Target_Y+1.1))>%d",Rtarget);
	TString condition2=Form("&&pixelF>%d&&pixelF<%d",SiLFmin,SiLFmax);
	TString condition3=Form("&&pixelB>%d&&pixelB<%d",SiLBmin,SiLBmax);
	TString condition4=Form("&&(Target_X+2.13)<%d&&(Target_X+2.13)>%d&&(Target_Y+1.1)<%d&&(Target_Y+1.1)>%d",Frame1,Frame2,Frame1,Frame2);
	TString condition5=Form("&&!((Target_X+2.13)<%d&&(Target_X+2.13)>%d&&(Target_Y+1.1)>%d&&(Target_Y+1.1)<%d)",Neckxmax,Neckxmin,Neckymin,Neckymax);

	TString condition=condition1+condition2+condition3+condition4+condition5;

	TString color="";

	tree->Draw(draw,condition,color);
	TH1D *temp =  (TH1D*)gDirectory->Get(hname);

	//if(temp->GetEntries()>20)
	if(temp->GetEntries()>20&&temp->GetBinContent(temp->GetMaximumBin())>10)
	{


		double fpeaks[3]={0};
		find(temp,fpeaks,esti_peak_sigma_LRB);

		out_cali_par(fid,bid,runnum,fpeaks,"LRB");

		//temp->Draw();
		TF1 *fpeak = new TF1("fpeak","gaus(0)",lrbmin,lrbmax);

		fpeak->SetNpx(2000);
		fpeak->SetParameters(&fpeaks[0]);
		//fpeak->Draw("same");



	}



}
void target_frame()
{



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
	double afr1=10;
	double abr1=10;
	double fr1=par[1]-afr1*par[2];
	double br1=par[1]+abr1*par[2];


	TF1 *peak1 = new TF1("peak1","gaus(0)",fr1,br1);
	peak1->SetParameters(&par[0]);
	peak1->SetNpx(2000);
	temp->Fit(peak1,"R");
	peak1->GetParameters(&fpeaks[0]);
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
	TString outputname="par_"+inputname;
	outputname.ReplaceAll("root","txt");
	ofstream out(outputname,ios_base::app | ios_base::out);
	out.flags (ios::left);
	out<<setw(20)<<fid<<setw(20)<<bid<<setw(20)<<setw(20)<<fpeaks[0]<<setw(20)<<fpeaks[1]<<setw(20)<<fpeaks[2]<<endl;
	out.close();

}

