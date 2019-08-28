int runnum=596;

int npeaks=1;
TString R2="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";
TString peak5=R2;


int LLmin;
int LLmax;

int LRTmin;
int LRTmax;

int LRBmin;
int LRBmax;

int RLTmin;
int RLTmax;

int RRTmin;
int RRTmax;


int RLBmin;
int RLBmax;

int RRBmin;
int RRBmax;


int nbin=500;
int Min=0;
int Max=700;


double esti_peak_sigma=5;




void SetPeakRegion(int runnum);
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

void drawPixelCsI()
{

	SetPeakRegion(runnum);

	//pixel(i,j,runnum);
	pixel(15,15,596);
//	for(int i=1;i<31;i++)
//		for(int i=15;i<16;i++)
//		for(int j=25;j<26;j++)
//		//for(int j=0;j<32;j++)
//		//for(int j=0;j<32;j++)
//		{
//			pixel(i,j,runnum);
//
//		}
//
//



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

	if(runnum==596||runnum==599){
		cpixel->Divide(2,2);
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

		cpixel->Divide(2,2);
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



	cpixel->SaveAs(Form("pixelrootfiles/peak5_pixel%d_%d_run0%d.pdf",fid,bid,runnum));
//	cpixel->Close();
//	f->Close();

}
void Draw(int fid,int bid,int runnum,TString CsI,TTree *tree)
{



	TString hname=Form("_pixel%d_%d_run0%d",fid,bid,runnum);
	hname="h"+CsI+hname;
	TString draw=">>"+hname+Form("(%d,%d,%d)",nbin,Min,Max);
	draw="0.47190*pixel"+CsI+"-158.15979"+draw;
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
	TString condition=peak5+"&&"+ADCLimit;
	

	//cout<<condition<<endl;



	tree->Draw(draw,condition,color);
	//TH1D *temp = (TH1D*)gDirectory->Get(hname);


}


void out_cali_par(int fid,int bid,int runnum,double *fpeaks,TString name)
{

	TString inputname=Form("pixel_run0%d.root",runnum);
	inputname=name+inputname;
	TString outputname="peak5_"+inputname;
	outputname.ReplaceAll("root","txt");
	ofstream out(outputname,ios_base::app | ios_base::out);
	out.flags (ios::left);
	out<<setw(20)<<fid<<setw(20)<<bid<<setw(20)<<setw(20)<<fpeaks[0]<<setw(20)<<fpeaks[1]<<setw(20)<<fpeaks[2]<<endl;
	out.close();

}
void SetPeakRegion(int runnum){
	// 598,599
	//LL: 965,1020
	//LRT: 1315,1375
	//LRB: 1180,1245

	//RLT: 1230,1290
	//RRT: 1155,1215
	//RLB: 1075,1135
	//RRB:1170,1220

	// 596,597
	//LL: 1355, 1420
	//LRT: 1900,2060
	//LRB: 1700,1850
	//RLT: 1740,1840
	//RRT: 1680,1760
	//RLB:1530,1620
	//RRB: 1670,1820
	if(runnum==598||runnum==599){

		LLmin=965;
		LLmax=1020;

		LRTmin=1315;
		LRTmax=1375;

		LRBmin=1180;
		LRBmax=1245;

		RLTmin=1230;
		RLTmax=1290;

		RRTmin=1155;
		RRTmax=1215;


		RLBmin=1075;
		RLBmax=1135;



		RRBmin=1170;
		RRBmax=1220;
	}else if(runnum==595||runnum==596||runnum==597){
	// 596,597
	//LL: 1355, 1420
	//LRT: 1900,2060
	//LRB: 1700,1850
	//RLT: 1740,1840
	//RRT: 1680,1760
	//RLB:1530,1620
	//RRB: 1670,1820
	
		LLmin=500;
		LLmax=4000;


	//	LLmin=1355;
	//	LLmax=1420;

		LRTmin=1900;
		LRTmax=2060;

		LRBmin=1700;
		LRBmax=1845;

		RLTmin=1740;
		RLTmax=1840;

		RRTmin=1680;
		RRTmax=1760;


		RLBmin=1530;
		RLBmax=1620;



		RRBmin=1670;
		RRBmax=1820;

	}
	else cout<<"Error! on selecting CsI peaks interval"<<endl;
	//
}

