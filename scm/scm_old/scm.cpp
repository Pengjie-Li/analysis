#include "scm.h"

double SCM::sqr(double x){ return x*x; }
SCM::SCM()
{

	cout<<"reference back strip="<<endl;
	cin>>refback;

}

SCM::SCM(int ref)
{
	refback=ref;
	reffront=ref;
}
SCM::SCM(int ref1,int ref2)
{
	refback=ref1;
	reffront=ref2;
}
SCM::SCM(int ref1,int ref2,int run)
{
	refback=ref1;
	reffront=ref2;
}
void SCM::Open()
{

}
void SCM::Open(TString inputname)
{
	f = new TFile(inputname,"READ");
	tree=(TTree*)f->Get("tree");
	//tree->Print();
	Init();

}


void SCM::Init()
{
         

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			P[i][j]=0;
                        TString bname=Form("pixel%d_%d",i,j);

			tree->SetBranchAddress(bname,&P[i][j]);
			//tree->SetBranchAddress(bname,&pixel[i][j]);
		}



}
void SCM::Load()
{

	tree->GetEntry(0);

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			pixel[i][j]=*P[i][j];
		}


}


void SCM::Build()
{
	g=new TFile("checking_scm.root","recreate");

}
void SCM::Fit()
{
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
//	for(int i=0;i<16;i++)
//		for(int j=15;j<16;j++)
		{

			//cout<<pixel[i][j].Np()<<endl;
			if(pixel[i][j].Np()>10) // 10 Points is the least points for fitting
			{

				Draw(i,j);
				bool status;
				status=pixel[i][j].Least_Square_Fit();

			}
			else pixel[i][j].Init();

			Output(i,j);
		}


}
void SCM::Output(int i,int j)
{
	TString outputname="./runs/fit_calibration_parameters.txt";
	cout<<outputname<<endl;
	ofstream fout(outputname,ios_base::app |ios_base::out);
	fout <<"\t"<<i << "\t" << j<< "\t" << pixel[i][j].k<<"\t"<<pixel[i][j].b<< "\t" << pixel[i][j].ek<<"\t"<<pixel[i][j].eb<<endl;
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

	redy[i][j]=new TH1F(Form("redy%d_%d",i,j),"dy distribution",200,-10,10);
	for(int iv=0;iv<yerror.size();iv++) redy[i][j]->Fill(yerror[iv]);

	redy[i][j]->Write();
	regr[i][j]->Write();
	refit[i][j]->Write();


}
void SCM::ReReDraw(int i,int j)
{
	vector<double> xarray=pixel[i][j].xarray;
	vector<double> yarray=pixel[i][j].yarray;
	vector<double> xerror=pixel[i][j].xerror;
	vector<double> yerror=pixel[i][j].yerror;

	reregr[i][j]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
	reregr[i][j]->SetName(Form("reregr%d_%d",i,j));
	reregr[i][j]->Draw("AP");
	rerefit[i][j]=new TF1(Form("rerefit%d_%d",i,j),"pol1",0,4100);
	rerefit[i][j]->SetParameters(pixel[i][j].b,pixel[i][j].k);
	rerefit[i][j]->Draw("same");

	reredy[i][j]=new TH1F(Form("reredy%d_%d",i,j),"dy distribution",200,-10,10);
	for(int iv=0;iv<yerror.size();iv++) reredy[i][j]->Fill(yerror[iv]);

	reredy[i][j]->Write();
	reregr[i][j]->Write();
	rerefit[i][j]->Write();


}
//void SCM::OverAllSCM()
//{
//
//	for(int side=0;side<2;side++)
//		for(int strip=0;strip<32;strip++)
//		{
//			CalSCM(side,strip);
//		}
//
//
//}
void SCM::LoadFitPar()
{

	ifstream in;
	TString inputname="./runs/fit_calibration_parameters.txt";

	in.open(inputname);

	int i;
	int j;
	double  temp_k;
	double  temp_b;
	double  temp_ek;
	double  temp_eb;
	
	while (1)
	{
		in >>i>>j>>temp_k>>temp_b>>temp_ek>>temp_eb;
		if (!in.good()) break;

		pixel[i][j].k=temp_k;
		pixel[i][j].b=temp_b;
		pixel[i][j].ek=temp_ek;
		pixel[i][j].eb=temp_eb;
		pixel[i][j].status=true;
		pixel[i][j].S=1;

		//cout <<"\t"<<i << "\t" << j<< "\t" << pixel[i][j].k<<"\t"<<pixel[i][j].b<< "\t" << pixel[i][j].ek<<"\t"<<pixel[i][j].eb<<endl;
	
	}
	in.close();



}
void SCM::OverAllSCM()
{

	TString outputname="runs/scm_par.txt";
	ofstream fout(outputname, ios_base::out);

	//for(int side=1;side<2;side++)
	for(int side=0;side<2;side++)
		//for(int strip=7;strip<8;strip++)
		for(int strip=0;strip<32;strip++)
		{
			CalSCM(side,strip);
			fout<<side<<"\t"<<strip<<"\t"<<k[side][strip]<<"\t"<<b[side][strip]<<"\t"<<ek[side][strip]<<"\t"<<eb[side][strip]<<endl;
			cout<<side<<"\t"<<strip<<"\t"<<k[side][strip]<<"\t"<<b[side][strip]<<"\t"<<ek[side][strip]<<"\t"<<eb[side][strip]<<endl;

			Check(side,strip); 
		}
	fout.close();


}
void SCM::CalSCM(int side,int strip)
{
	k[side][strip]=0;
	b[side][strip]=0;
	ek[side][strip]=0;
	eb[side][strip]=0;

	double nomk=0;
	double nomb=0;
	double denomk=0;
	double denomb=0;

	if(side==0)
	{

		double dk=pixel[strip][refback].k;
		double db=pixel[strip][refback].b;
		double dek=pixel[strip][refback].ek;
		double deb=pixel[strip][refback].eb;

		cout<<"strip="<<strip<<" refback="<<refback<<" Number of Points= "<<pixel[strip][refback].Np()<<" "<<dek<<"  "<<deb<<endl;

		cout<<"Fitting:"<<"k="<<dk<<" b="<<db<<" ek="<<dek<<" eb="<<deb<<endl;
		if(dek!=0&&deb!=0)
		{
			nomk=dk/(dek*dek);
			nomb=db/(deb*deb);
			denomk=1/(dek*dek);
			denomb=1/(deb*deb);
		}

		if(pixel[strip][refback].n<50)
		{
			for(int i=0;i<32;i++)
				for(int j=0;j<32;j++)
				{

					if(i==strip) continue;
					if(j==refback) continue;


					//cout<<pixel[i][refback].status<<"  "<<pixel[i][j].status<<"  "<<pixel[strip][j].status<<endl;
					//cout<<pixel[i][refback].S<<"  "<<pixel[i][j].S<<"  "<<pixel[strip][j].S<<endl;
					if((!pixel[i][refback].status)||(!pixel[i][j].status)||(!pixel[strip][j].status)) continue;
					//if((pixel[i][refback].S>10)||(pixel[i][j].S>10)||(pixel[strip][j].S>10)) continue;

					if((pixel[i][refback].n<50)||(pixel[i][j].n<50)||(pixel[strip][j].n<10)) continue;
					//cout<<pixel[i][refback].status<<"  "<<pixel[i][j].status<<"  "<<pixel[strip][j].status<<endl;

					//cout<<"i="<<i<<"  j="<<j<<endl;

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

					if((k1==0)||(b1==0)||(ek1==0)||(eb1==0)) continue;
					if((k2==0)||(b2==0)||(ek2==0)||(eb2==0)) continue;
					if((k3==0)||(b3==0)||(ek3==0)||(eb3==0)) continue;
				

					double ck=k1*k3/k2;
					double cb=b1+(b3-b2)*k1/k2;
					double cek2=sqr(k3/k2)*sqr(ek1)+sqr(k1/k2)*sqr(ek3)+sqr(k3*k1/(k2*k2))*sqr(ek2);
					double ceb2=sqr(eb1)+sqr((b3-b2)/k2)*sqr(ek1)+sqr(k1/k2)*(sqr(eb3)+sqr(eb2))+sqr(k1*(b3-b2)/sqr(k2))*sqr(ek2);
					//cout<<"ck="<<ck<<" cb="<<cb<<" cek2="<<cek2<<"  ceb2="<<ceb2<<endl;

					if(ck&&cb&&cek2&&ceb2)
					{
						nomk+=ck/cek2;
						nomb+=cb/ceb2;
						denomk+=1/cek2;
						denomb+=1/ceb2;
					}

					//cout<<nomk<<"  "<<nomb<<" "<<denomk<<"  "<<denomb<<endl;
				}
		}

	}




	if(side==1)
	{

		double dk= pixel[reffront][strip].k;
		double db= pixel[reffront][strip].b;
		double dek=pixel[reffront][strip].ek;
		double deb=pixel[reffront][strip].eb;

		//cout<<"reffront="<<reffront<<" strip="<<strip<<"  "<<dk<<"  "<<db<<" "<<dek<<"  "<<deb<<endl;
		cout<<"reffront="<<reffront<<" strip="<<strip<<" Number of Points= "<<pixel[reffront][strip].Np()<<" "<<dek<<"  "<<deb<<endl;
		deb=deb*dk/(db*db)-dek/db;
		dek=-dek/(dk*dk);
		db=-db/dk;
		dk=1./dk;

		cout<<"Fitting:"<<"k="<<dk<<" b="<<db<<" ek="<<dek<<" eb="<<deb<<endl;


		//cout<<"reffront="<<reffront<<" strip="<<strip<<"  "<<dk<<"  "<<db<<" "<<dek<<"  "<<deb<<endl;

		if(dek!=0&&deb!=0)
		{
			nomk=dk/(dek*dek);
			nomb=db/(deb*deb);
			denomk=1./(dek*dek);
			denomb=1./(deb*deb);
		}

		if(pixel[reffront][strip].n<50)
		{
			//for(int i=15;i<16;i++)
		for(int i=0;i<32;i++)
				//for(int j=17;j<18;j++)
			for(int j=0;j<32;j++)
				{
					if(i==strip) continue;
					if(j==reffront) continue;

					if((!pixel[reffront][i].status)||(!pixel[j][i].status)||(!pixel[j][strip].status)) continue;
					if((pixel[reffront][i].n<50)||(pixel[j][i].n<50)||(pixel[j][strip].n<10)) continue;
					//if((pixel[reffront][i].S>10)||(pixel[j][i].S>10)||(pixel[j][strip].S>10)) continue;
					//if((pixel[reffront][i].n<15)||(pixel[i][j].n<15)||(pixel[strip][j].n<15)) continue;

					//cout<<pixel[i][refback].status<<"  "<<pixel[i][j].status<<"  "<<pixel[strip][j].status<<endl;

					double k1= pixel[reffront][i].k;
					double b1= pixel[reffront][i].b;
					double ek1=pixel[reffront][i].ek;
					double eb1=pixel[reffront][i].eb;

					if((k1==0)||(b1==0)||(ek1==0)||(eb1==0)) continue;
					eb1=eb1*k1/(b1*b1)-ek1/b1;
					ek1=-ek1/(k1*k1);
					b1=-b1/k1;
                                        k1=1./k1;
					//cout<<"reffront="<<reffront<<" i="<<i<<"  "<<k1<<"  "<<b1<<" "<<ek1<<"  "<<eb1<<endl;

					double k2= pixel[j][i].k;
					double b2= pixel[j][i].b;
					double ek2=pixel[j][i].ek;
					double eb2=pixel[j][i].eb;
					if((k2==0)||(b2==0)||(ek2==0)||(eb2==0)) continue;
					eb2=eb2*k2/(b2*b2)-ek2/b2;
					ek2=-ek2/(k2*k2);
					b2=-b2/k2;
                                        k2=1./k2;

					//cout<<"j="<<j<<" i="<<i<<"  "<<k2<<"  "<<b2<<" "<<ek2<<"  "<<eb2<<endl;

					double k3= pixel[j][strip].k;
					double b3= pixel[j][strip].b;
					double ek3=pixel[j][strip].ek;
					double eb3=pixel[j][strip].eb;
					if((k3==0)||(b3==0)||(ek3==0)||(eb3==0)) continue;
					eb3=eb3*k3/(b3*b3)-ek3/b3;
					ek3=-ek3/(k3*k3);
					b3=-b3/k3;
                                        k3=1./k3;
	
					//cout<<"j="<<j<<" strip="<<i<<"  "<<k3<<"  "<<b3<<" "<<ek3<<"  "<<eb3<<endl;

					double ck=k1*k3/k2;
					double cb=b1+(b3-b2)*k1/k2;
					double cek2=sqr(k3/k2)*sqr(ek1)+sqr(k1/k2)*sqr(ek3)+sqr(k3*k1/(k2*k2))*sqr(ek2);
					double ceb2=sqr(eb1)+sqr((b3-b2)/k2)*sqr(ek1)+sqr(k1/k2)*(sqr(eb3)+sqr(eb2))+sqr(k1*(b3-b2)/sqr(k2))*sqr(ek2);

					//cout<<"ck="<<ck<<" cb="<<cb<<" cek2="<<cek2<<"  ceb2="<<ceb2<<endl;
					//cout<<"delta nomk="<<ck/cek2<<" delta denomk="<<1/cek2<<"delta nomb="<<cb/ceb2<<" delta denomb="<<1/ceb2<<endl;

					nomk+=ck/cek2;
					nomb+=cb/ceb2;
					denomk+=1/cek2;
					denomb+=1/ceb2;

				//	cout<<"i="<<i<<"  j="<<j<<endl;
				//	cout<<"nomk="<<nomk<<" nomb="<<nomb<<" denomk="<<denomk<<" denomb="<<denomb<<endl;
				//	cout<<"temp_k="<<nomk/denomk<<" temp_b="<<nomb/denomb<<endl;
				}
		}

	}

	if(nomk&&denomk)
	{

		k[side][strip]=nomk/denomk;
		b[side][strip]=nomb/denomb;
		ek[side][strip]=sqrt(1/denomk);
		eb[side][strip]=sqrt(1/denomb);
	}

	//cout<<side<<"\t"<<strip<<"\t"<<k[side][strip]<<"\t"<<b[side][strip]<<"\t"<<ek[side][strip]<<"\t"<<eb[side][strip]<<endl;



}
void SCM::Check(int side,int strip)
{

        TString sname;
	if(side==0) sname=Form("Front%d",strip);
	else sname=Form("Back%d",strip);
	Residue[side][strip]=new TH1F(sname,sname,100,-10,10);
	vector<double> xadc;
	vector<double> yadc;
	xadc.clear();
	yadc.clear();
	if(side==0) {xadc=pixel[strip][refback].xarray; yadc=pixel[strip][refback].yarray;}
	else {xadc=pixel[reffront][strip].yarray; yadc=pixel[reffront][strip].xarray;}

	for(int j=0;j<xadc.size();j++)
	{
		Residue[side][strip]->Fill(yadc[j]-k[side][strip]*xadc[j]-b[side][strip]);

	}

	Residue[side][strip]->Write();

}
void SCM::Write()
{



}
