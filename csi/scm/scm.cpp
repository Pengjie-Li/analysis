#include "scm.h"
#include "Pixel.h"

double SCM::sqr(double x){ return x*x; }
SCM::SCM()
{

	cout<<"reference back strip="<<endl;
	cin>>refback;

}

SCM::SCM(int ref)
{
	refback=ref;
}
void SCM::Open()
{

}
void SCM::Open(TString inputname)
{
	f = new TFile(inputname,"READ");
	tree=(TTree*)f->Get("tree_BEAM");
	//tree->Print();
	Init();

}

void SCM::LoadPar(TString inputname)
{
	ifstream in;
	inputname.ReplaceAll("rootfiles","");
	inputname.ReplaceAll("root","txt");
	inputname.ReplaceAll("./","");
	inputname.ReplaceAll("/","");
	inputname="./rootfiles/parameters/ped_"+inputname;
	cout<<inputname<<endl;

	for(int i=0;i<4;i++)
		for(int j=0;j<32;j++)
		{
			ped[i][j]=0;
			pedsigma[i][j]=0;
			pedthrd[i][j]=0;
		}

	in.open(inputname);
	int side;
	int strip;
	double  pedestral;
	double  sig;
	double thr;
	while (1)
	{
		in >>side>>strip>>pedestral>>sig>>thr;
		if (!in.good()) break;

		ped[side][strip]=pedestral;
		pedsigma[side][strip]=sig;
		pedthrd[side][strip]=thr;

	}

}
void SCM::Init()
{
	SiLF_rawADC=0;
	SiLB_rawADC=0;
	SiRF_rawADC=0;
	SiRB_rawADC=0;

	tree->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
	tree->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
	tree->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
	tree->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);

}
void SCM::Load()
{
	Long64_t nentries = tree->GetEntries();

	//nentries=100000;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		tree->GetEntry(ientry);
		lfadc.clear();
		lbadc.clear();
		rfadc.clear();
		rbadc.clear();

		lfadc=*SiLF_rawADC;
		lbadc=*SiLB_rawADC;
		rfadc=*SiRF_rawADC;
		rbadc=*SiRB_rawADC;

		//cout<<(*SiLF_rawADC)[15]<<endl;
		//cout<<lfadc[15]<<endl;
		int fid=-1;
		int bid=-1;
		int nhit=remove_multihit(lfadc,lbadc,fid,bid);
		//cout<<nhit<<endl;
		if(nhit>1||nhit==0) continue;
		if(select(lfadc[fid],lbadc[bid]))
			pixel[fid][bid].Fill(lfadc[fid],lbadc[bid]);

	}



}
bool SCM::select(double x,double y)
{
	if(x>4095||y>4095) return false;
	if(y>1.2*x+300) return false;
	if(x>1.2*y+300) return false;
	return true;

}
int SCM::remove_multihit(vector<double>  *fadc,vector<double>  *badc)
{
	int nhit=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
			if((*fadc)[i]>300&&(*badc)[j]>300) nhit++;
	return nhit;

}
int SCM::remove_multihit(vector<double>  fadc,vector<double>  badc,int &fid,int &bid)
{
	int nhit=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			//if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>pedthrd[0][j])
			if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>(ped[0][j]+pedsigma[0][j]*10))
			{
				nhit++;
				fid=i;bid=j;
			}
			//cout<<pedthrd[0][i]<<"  "<<pedthrd[1][j]<<endl;
		}

	return nhit;

}
void SCM::Build()
{
	g=new TFile("checking_scm.root","recreate");

}
void SCM::Fit()
{
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
				//for(int i=15;i<16;i++)
					//for(int j=16;j<17;j++)
		{
			bool status;
			status=pixel[i][j].Fit();
			Draw(i,j);
			status=pixel[i][j].Refit();
			ReDraw(i,j);
			Output(i,j);
		}


}
void SCM::Output(int i,int j)
{
	TString outputname="fit_calibration_parameters.txt";
	cout<<outputname<<endl;
	ofstream fout(outputname,ios_base::app | ios_base::out);
	fout <<"\t"<<i << "\t" << j<< "\t" << pixel[i][j].k<<"\t"<<pixel[i][j].ek<< "\t" << pixel[i][j].b<<"\t"<<pixel[i][j].eb<<endl;
	fout.close();
}
void SCM::Draw(int i,int j)
{
	vector<double> xarray=pixel[i][j].xarray;
	vector<double> yarray=pixel[i][j].yarray;
	vector<double> xerror=pixel[i][j].xerror;
	vector<double> yerror=pixel[i][j].yerror;

	gr[i][j]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
	gr[i][j]->SetName(Form("gr%d_%d",i,j));
	gr[i][j]->Draw("AP");
	fit[i][j]=new TF1(Form("fit%d_%d",i,j),"pol1",0,4100);
	fit[i][j]->SetParameters(pixel[i][j].b,pixel[i][j].k);
	fit[i][j]->Draw("same");

	gr[i][j]->Write();
	fit[i][j]->Write();



}
void SCM::ReDraw(int i,int j)
{
	vector<double> xarray=pixel[i][j].xarray;
	vector<double> yarray=pixel[i][j].yarray;
	vector<double> xerror=pixel[i][j].xerror;
	vector<double> yerror=pixel[i][j].yerror;

	regr[i][j]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
	regr[i][j]->SetName(Form("regr%d_%d",i,j));
	regr[i][j]->Draw("AP");
	refit[i][j]=new TF1(Form("refit%d_%d",i,j),"pol1",0,4100);
	refit[i][j]->SetParameters(pixel[i][j].b,pixel[i][j].k);
	refit[i][j]->Draw("same");

	dy[i][j]=new TH1F(Form("dy%d_%d",i,j),"dy distribution",200,-10,10);
	for(int iv=0;iv<yerror.size();iv++) dy[i][j]->Fill(yerror[iv]);

	dy[i][j]->Write();
	regr[i][j]->Write();
	refit[i][j]->Write();


}
void SCM::OverAllSCM()
{
	for(int side=0;side<1;side++)
		for(int strip=0;strip<32;strip++)
			CalSCM(side,strip);

}
void SCM::CalSCM(int side,int strip)
{
	k[side][strip]=0;
	b[side][strip]=0;
	ek[side][strip]=0;
	eb[side][strip]=0;

	if(side==0)
	{

		double dk=pixel[strip][refback].k;
		double db=pixel[strip][refback].b;
		double dek=pixel[strip][refback].ek;
		double deb=pixel[strip][refback].eb;
		//cout<<dk<<"  "<<db<<" "<<dek<<"  "<<deb<<endl;

		double nomk=0;
		double nomb=0;
		double denomk=0;
		double denomb=0;

		if(dek!=0&&deb!=0)
		{
			nomk=dk/(dek*dek);
			nomb=db/(deb*deb);
			denomk=1/(dek*dek);
			denomb=1/(deb*deb);
		}

		for(int i=0;i<32;i++)
			for(int j=0;j<32;j++)
			{
				if(i==strip) continue;
				if(j==refback) continue;

				if((!pixel[i][refback].status)||(!pixel[i][j].status)||(!pixel[strip][j].status)) continue;
				//cout<<pixel[i][refback].status<<"  "<<pixel[i][j].status<<"  "<<pixel[strip][j].status<<endl;

				double k1=pixel[i][refback].k;
				double b1=pixel[i][refback].b;
				double ek1=pixel[i][refback].ek;
				double eb1=pixel[i][refback].eb;

				double k2=pixel[i][j].k;
				double b2=pixel[i][j].b;
				double ek2=pixel[i][j].ek;
				double eb2=pixel[i][j].eb;


				double k3=pixel[strip][j].k;
				double b3=pixel[strip][j].b;
				double ek3=pixel[strip][j].ek;
				double eb3=pixel[strip][j].eb;



				double ck=k1*k3/k2;
				double cb=b1+(b3-b2)*k1/k2;
				double cek2=sqr(k3/k2)*sqr(ek1)+sqr(k1/k2)*sqr(ek3)+sqr(k3*k1/(k2*k2))*sqr(ek2);
				double ceb2=sqr(eb1)+sqr((b3-b2)/k2)*sqr(ek1)+sqr(k1/k2)*(sqr(eb3)+sqr(eb2))+sqr(k1*(b3-b2)/sqr(k2))*sqr(ek2);
				//cout<<"ck="<<ck<<" cb="<<cb<<" cek2="<<cek2<<"  ceb2="<<endl;

				nomk+=ck/cek2;
				nomb+=cb/ceb2;
				denomk+=1/cek2;
				denomb+=1/ceb2;

				//cout<<nomk<<"  "<<nomb<<" "<<denomk<<"  "<<denomb<<endl;
			}

		k[side][strip]=nomk/denomk;
		b[side][strip]=nomb/denomb;
		ek[side][strip]=sqrt(1/denomk);
		eb[side][strip]=sqrt(1/denomb);

		cout<<side<<"\t"<<strip<<"\t"<<k[side][strip]<<"\t"<<b[side][strip]<<"\t"<<ek[side][strip]<<"\t"<<eb[side][strip]<<endl;
	}


}
void SCM::Write()
{



}
