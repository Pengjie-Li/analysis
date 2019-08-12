double Zmax=1;
double Zmin=-1;

void Init(double S[32][32]);
void Call(int runnum,TString peak);
void Call(int runnum,TString CsIname,TString peak,double temp[32][32]);
void Call(int runnum,TString CsIname,TString peak);
void Draw3D(double Speak[32][32]);
void Calculate(double fpeak[32][32],double Speak[32][32]);
void Calculate(double fpeak[32][32],double Smean[32][32],TString CsI);
void Calculate(double fpeak[32][32],double Smean[32][32],int runnum,TString CsI,TString peak);
void Load(TString inputname,double fpeak[32][32]);
void  LL596();
void Draw2D(int runnum,double Speak[32][32]);
void Draw2D(int runnum,TString peak,double Speak[32][32]);
void Draw2D(int runnum,TString peak,TString CsIname,double Speak[32][32]);
void Draw2D(int runnum,TH2D *h,double Speak[32][32]);
void Draw2D(int runnum,TH2D *h,double Speak[32][32],int peak1);
double getMax(double s1,double s2,double s3,double s4);
double getMin(double s1,double s2,double s3,double s4);
void Average(double Speak[32][32]);

void Draw_uf()
{
	gStyle->SetOptStat(0);

	/** Call function
	 *  Global: Call(runnum);
	 *  Merge peak: Call(runnum,CsIname);
	 *  Merge CsI: Call(runnum,peak);
	 *  Base: Call(runnum,CsIname,peak);
	 */

//	Call(596,"peak5");
//	Call(596,"LL","peak5");
//	Call(597,"peak5");
	
//	Call(598,"peak5");
//	Call(598,"peak2");
//	Call(598,"peak1");
//	Call(599,"peak5");
//	Call(599,"peak2");
//	Call(599,"peak1");
//
//	Call(596,"peak5");
	Call(597,"peak5");
	//Call(598,"RRB","peak2");
	//Call(598,"RRT","peak2");
	//Call(598,"RLT","peak2");
	//Call(598,"RLB","peak2");
	//Call(599,"LL","peak5");
	//Call(599,"LRT","peak5");
	//Call(599,"LRB","peak5");


	//Call(599,"LL","peak2");
	//Call(599,"LRT","peak2");
	//Call(599,"LRB","peak2");


}
void Call(int runnum,TString peak)
{
	double Speak[32][32]={0};
	double S1[32][32]={0};
	double S2[32][32]={0};
	double S3[32][32]={0};
	double S4[32][32]={0};

	if(runnum==597||runnum==598){
		Call(runnum,"RLT",peak,S1);
		Call(runnum,"RLB",peak,S2);
		Call(runnum,"RRT",peak,S3);
		Call(runnum,"RRB",peak,S4);
	}
	if(runnum==596||runnum==599){
		Call(runnum,"LL",peak,S1);
		Call(runnum,"LRT",peak,S2);
		Call(runnum,"LRB",peak,S3);
		Init(S4);
	}
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++){
		//for(int j=15;j<16;j++){

			//cout<<i<<" "<<j<<" "<<S1[i][j]<<" "<<S2[i][j]<<" "<<S3[i][j]<<" "<<S4[i][j]<<endl;
			//Speak[i][j]=getMax(S1[i][j],S2[i][j],S3[i][j],S4[i][j]);
			Speak[i][j]=getMin(S1[i][j],S2[i][j],S3[i][j],S4[i][j]);
			//if(Speak[i][j]!=-999) cout<<i<<" "<<j<<" "<<Speak[i][j]<<endl;
		}
//
	//Draw2D(runnum,Speak);
	Draw2D(runnum,peak,Speak);
	Average(Speak);


}
void Init(double S[32][32]){
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++){
			S[i][j]=-999;
		}


}
double getMax(double s1,double s2,double s3,double s4){
	double temp=0;
	if(TMath::Abs(s1)>TMath::Abs(temp)&&s1!=-999) temp=s1;
	if(TMath::Abs(s2)>TMath::Abs(temp)&&s2!=-999) temp=s2;
	if(TMath::Abs(s3)>TMath::Abs(temp)&&s3!=-999) temp=s3;
	if(TMath::Abs(s4)>TMath::Abs(temp)&&s4!=-999) temp=s4;
	if(temp==0) temp=-999;
	return temp;
}
double getMin(double s1,double s2,double s3,double s4){
	double temp=-999;
	if(TMath::Abs(s1)<TMath::Abs(temp)&&s1!=-999) temp=s1;
	if(TMath::Abs(s2)<TMath::Abs(temp)&&s2!=-999) temp=s2;
	if(TMath::Abs(s3)<TMath::Abs(temp)&&s3!=-999) temp=s3;
	if(TMath::Abs(s4)<TMath::Abs(temp)&&s4!=-999) temp=s4;
	if(temp==0) temp=-999;
	return temp;
}




// Base function
void Call(int runnum,TString CsIname,TString peak)
{

	double Speak[32][32]={0};
	Call(runnum,CsIname,peak,Speak);
}
// Core
void Call(int runnum,TString CsIname,TString peak,double Speak[32][32])
{

	TString inputname="result/Fix_"+peak+"_"+CsIname+Form("pixel_run0%d.txt",runnum);
	double fpeak[32][32]={0};

	Load(inputname,fpeak);
	Calculate(fpeak,Speak,runnum,CsIname,peak);
	Draw2D(runnum,CsIname,Speak);
	Average(Speak);

}

void Load(TString inputname,double fpeak[32][32])
{
	ifstream in;
	in.open(inputname);

	int fid;
	int bid;
	double  constant;
	double  mean;
	double sigma;
	while (1)
	{
		in >>fid>>bid>>constant>>mean>>sigma;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;

		fpeak[fid][bid]=mean;
		//cout<<"fid="<<fid<<"  bid="<<bid<<" mean="<<mean<<endl;
	}
	in.close();

}
// ADC percent
void Calculate(double fpeak[32][32],double Smean[32][32])
{
	int npixel=0;
	double pmean=0;

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			if(fpeak[i][j]>500) 
			{

				npixel++;
				pmean+=fpeak[i][j];

			}


		}


	pmean/=npixel;

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			Smean[i][j]=0;

			if(fpeak[i][j]>500) 
			{


				Smean[i][j]=(fpeak[i][j]-pmean)/pmean*100;
				Smean[i][j]=ceil(Smean[i][j]*100)/100.;

				if(Smean[i][j]==0) Smean[i][j]=0.01;
				//cout<<"fid="<<i<<" bid="<<j<<" per="<<Smean[i][j]<<"%"<<endl;
			}





		}



}
void Calculate(double fpeak[32][32],double Smean[32][32],int runnum,TString CsI,TString peak)
{

	double k=0;
	double b=0;
	double Ein=0;

	if(CsI=="LL"){ k=0.464291;b=-150.243;}
	else	if(CsI=="LRT"){ k=0.306815;b=-101.453;}
	else	if(CsI=="LRB"){ k=0.353228;b=-117.866;}

	else	if(CsI=="RLT"){ k=0.357925;b=-139.651;}
	else	if(CsI=="RLB"){ k=0.40584; b=-137.378;}
	else	if(CsI=="RRT"){ k=0.350254;b=-105.061;}
	else	if(CsI=="RRB"){ k=0.350748;b=-108.566;}
	else  {cout<<"ERROR!"<<endl;}

	if(peak=="peak5"&&runnum<598) Ein=621.96;
	if(peak=="peak2"&&runnum<598) Ein=582.94;
	if(peak=="peak1"&&runnum<598) Ein=569.94;

	if(peak=="peak5"&&runnum>597) Ein=474.63;
	if(peak=="peak2"&&runnum>597) Ein=427.01;
	if(peak=="peak1"&&runnum>597) Ein=410.29;




	//cout<<k<<" "<<b<<endl;
	cout<<"Ein="<<Ein<<endl;

	int npixel=0;
	double pmean=0;

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			if(fpeak[i][j]>500) 
			{

				npixel++;
				fpeak[i][j]=k*fpeak[i][j]+b;// ADC to MeV
				pmean+=fpeak[i][j];

			}


		}


	pmean/=npixel;

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			Smean[i][j]=-999;

			if(fpeak[i][j]>100) 
			{


				//Smean[i][j]=(fpeak[i][j]-pmean)/pmean*100;
				Smean[i][j]=(fpeak[i][j]-pmean)/Ein;
				Smean[i][j]=ceil(Smean[i][j]*10000)/100.;

				if(Smean[i][j]==0) Smean[i][j]=0.001;
				//cout<<"fid="<<i<<" bid="<<j<<" per="<<Smean[i][j]<<"%"<<endl;
			}





		}



}


void Calculate(double fpeak[32][32],double Smean[32][32],TString CsI)
{
	double k=0;
	double b=0;

	if(CsI=="LL"){ k=0.464291;b=-150.243;}
	else	if(CsI=="LRT"){ k=0.306815;b=-101.453;}
	else	if(CsI=="LRB"){ k=0.353228;b=-117.866;}

	else	if(CsI=="RLT"){ k=0.357925;b=-139.651;}
	else	if(CsI=="RLB"){ k=0.40584; b=-137.378;}
	else	if(CsI=="RRT"){ k=0.350254;b=-105.061;}
	else	if(CsI=="RRB"){ k=0.350748;b=-108.566;}
	else  {cout<<"ERROR!"<<endl;}


	//cout<<k<<" "<<b<<endl;

	int npixel=0;
	double pmean=0;

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			if(fpeak[i][j]>500) 
			{

				npixel++;
				fpeak[i][j]=k*fpeak[i][j]+b;// ADC to MeV
				pmean+=fpeak[i][j];

			}


		}


	pmean/=npixel;

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			Smean[i][j]=-999;

			if(fpeak[i][j]>100) 
			{


				//Smean[i][j]=(fpeak[i][j]-pmean)/pmean*100;
				Smean[i][j]=(fpeak[i][j]-pmean);
				Smean[i][j]=ceil(Smean[i][j]*100)/100.;

				if(Smean[i][j]==0) Smean[i][j]=0.001;
				//cout<<"fid="<<i<<" bid="<<j<<" per="<<Smean[i][j]<<"MeV"<<endl;
			}





		}



}

void Average(double Speak[32][32])
{
	double sum=0;
	int count=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			if((Speak[i][j]!=-999)&&(TMath::Abs(Speak[i][j])>0)) {
				count++;
				sum+=TMath::Abs(Speak[i][j]);
				//cout<<"i="<<i<<" j="<<j<<" Uniformity="<<Speak[i][j]<<endl;
			}
		}
	//cout<<"sum="<<sum<<endl;
	//cout<<"count="<<count<<endl;
	cout<<"Average Uniformity="<<sum/count<<endl;

}
void Draw2D(int runnum,TString peak,TString CsIname,double Speak[32][32])
{

	TString hname=CsIname+Form("_run%d",runnum)+peak;
	TCanvas *c=new TCanvas(hname,hname,900,800);
	c->cd();

	//TH2F *h=new TH2F(hname,hname,32,0.5,32.5,32,0.5,32.5);
	TH2D *h=new TH2D(hname,hname,32,-0.5,31.5,32,-0.5,31.5);
	Draw2D(runnum,h,Speak);

}
void Draw2D(int runnum,TString peak,double Speak[32][32])
{

	TString hname=Form("run%d_",runnum)+peak;
	TCanvas *c=new TCanvas(hname,hname,900,800);
	c->cd();

	TH2D *h=new TH2D(hname,hname,32,-0.5,31.5,32,-0.5,31.5);

	if(peak=="peak1") Draw2D(runnum,h,Speak,1);
	else Draw2D(runnum,h,Speak);
}
void Draw2D(int runnum,double Speak[32][32])
{

	TString hname=Form("run%d",runnum);
	TCanvas *c=new TCanvas(hname,hname,900,800);
	c->cd();

	TH2D *h=new TH2D(hname,hname,32,-0.5,31.5,32,-0.5,31.5);
	Draw2D(runnum,h,Speak);

}
void Draw2D(int runnum,TH2D *h,double Speak[32][32])
{
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			if(runnum==596||runnum==599){
				//if(Speak[31-j][i]!=-999){
					h->Fill(i,j,Speak[31-j][i]);
					if(Speak[31-j][i]!=-999&&Speak[31-j][i]>Zmax) Zmax=Speak[31-j][i];
					if(Speak[31-j][i]!=-999&&Speak[31-j][i]<Zmin) Zmin=Speak[31-j][i];
	

					//h->SetBinContent(i,j,Speak[31-j][i]);
					//h->Fill(i,j);
				//}
			}
			if(runnum==597||runnum==598){
				//if(Speak[31-j][31-i]!=-999){
					h->Fill(i,j,Speak[31-j][31-i]);
					if(Speak[31-j][31-i]!=-999&&Speak[31-j][31-i]>Zmax) Zmax=Speak[31-j][31-i];
					if(Speak[31-j][31-i]!=-999&&Speak[31-j][31-i]<Zmin) Zmin=Speak[31-j][31-i];
	

					//h->SetBinContent(i,j,Speak[31-j][31-i]);
				//}
			}

		}

	h->GetZaxis()->SetRangeUser(Zmin, Zmax);
	h->Draw("colz");
}


void Draw2D(int runnum,TH2D *h,double Speak[32][32],int peak1)
{
	cout<<"special peak1:"<<peak1<<endl;

	if(runnum==596||runnum==599){
		
	//	for(int i=0;i<32;i++)
	//	{
	//		h->Fill(i,0.,Speak[31][i]);
	//	}

		for(int i=0;i<32;i=i+2)
			for(int j=1;j<32;j=j+2)
			{
				//if(Speak[31-j][i]!=-999)
				h->Fill(i,j,Speak[31-j][i]);
				h->Fill(i+1,j,Speak[31-j][i]);
				h->Fill(i,j-1,Speak[31-j][i]);
				h->Fill(i+1,j-1,Speak[31-j][i]);
				if(Speak[31-j][i]!=-999&&Speak[31-j][i]>Zmax) Zmax=Speak[31-j][i];
				if(Speak[31-j][i]!=-999&&Speak[31-j][i]<Zmin) Zmin=Speak[31-j][i];


				//h->SetBinContent(i,j,Speak[31-j][i]);
				//h->Fill(i,j);
			}
	}
	else if(runnum==597||runnum==598){
		for(int i=0;i<32;i++)
		{
			//h->Fill(i,0.,Speak[31][31-i]);
			//h->Fill(0.,i,Speak[31-i][31]);
		}
		for(int i=1;i<32;i=i+2)
			for(int j=1;j<32;j=j+2)
			{
				h->Fill(i,j,Speak[31-j][31-i]);
				h->Fill(i-1,j,Speak[31-j][31-i]);
				h->Fill(i,j-1,Speak[31-j][31-i]);
				h->Fill(i-1,j-1,Speak[31-j][31-i]);
				if(Speak[31-j][31-i]!=-999&&Speak[31-j][31-i]>Zmax) Zmax=Speak[31-j][31-i];
				if(Speak[31-j][31-i]!=-999&&Speak[31-j][31-i]<Zmin) Zmin=Speak[31-j][31-i];


			}

	}

	h->GetZaxis()->SetRangeUser(Zmin, Zmax);
	h->Draw("colz");
}




void Draw3D(double Speak[32][32])
{
	TH3F *h=new TH3F("LL","LL",32,-0.5,31.5,32,-0.5,31.5,100,-1,1);

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			h->Fill(i,j,Speak[i][j]);
		}

	h->Draw("BOX");
}
