
void get_par()
{
	double Lped[4][32]={0};
	double Lpedsigma[4][32]={0};
	double Lpedthrd[4][32]={0};
	double Lpeak[4][32]={0};
	double Lpeaksigma[4][32]={0};
	double Lpeakthrd[4][32]={0};
	double Hped[4][32]={0};
	double Hpedsigma[4][32]={0};
	double Hpedthrd[4][32]={0};
	double Hpeak[4][32]={0};
	double Hpeaksigma[4][32]={0};
	double Hpeakthrd[4][32]={0};



	Load(596,0,Lped,Lpedsigma,Lpedthrd);
	Load(596,1,Lpeak,Lpeaksigma,Lpeakthrd);
	Load(599,0,Hped,Hpedsigma,Hpedthrd);
	Load(599,1,Hpeak,Hpeaksigma,Hpeakthrd);


	double Dped[4][32]={0};
	double Ladc[4][32]={0};
	double Hadc[4][32]={0};
	double Energy[2]={6.10,7.14};
	double ch2E[4][32]={0};
	//double Energy[3]={0,6.10,7.14};
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<32;j++)
		{
			Ladc[i][j]=Lpeak[i][j]-Lped[i][j];
			Hadc[i][j]=Hpeak[i][j]-Hped[i][j];
			Dped[i][j]=Hped[i][j]-Lped[i][j];
			//ch2E[i][j]=0.5*(Energy[1]/Hadc[i][j]+Energy[0]/Ladc[i][j]);
			//ch2E[i][j]=(Energy[1]/Hadc[i][j]);
			ch2E[i][j]=(Energy[0]/Ladc[i][j]);
		}
	}


	//PrintA(Dped);
	PrintA(ch2E);

	TString outputname="calibration_parameters.txt";
	cout<<outputname<<endl;
//
	ofstream fout(outputname,ios_base::app | ios_base::out);
	for(Int_t i = 0; i<32; i++){
		fout << 0 << "\t"<<i << "\t" << ch2E[0][i]<<"\t"<<Lped[0][i] <<endl;
	}
	for(Int_t i = 0; i<32; i++){
		fout << 1 << "\t"<<i << "\t" << ch2E[1][i]<<"\t"<<Lped[1][i] <<endl;
	}

	fout.close();


	TCanvas *c[2];
        c[0]=new TCanvas("LF","LFFit",1800,1000);
        c[1]=new TCanvas("LB","LBFit",1800,1000);
	c[0]->Divide(8,4);
	c[1]->Divide(8,4);

	for(int i=0;i<2;i++)
	for(int j=0;j<32;j++)
	{
		c[i]->cd(j+1);
		TGraph *gr;
		double adc[3]={0};
		adc[0]=0;
		//adc[0]=Lped[i][j];
		adc[1]=Ladc[i][j];
		adc[2]=Hadc[i][j];
		double E[3]={0,6.10,7.14};
		gr=new TGraph(3,adc,E);
		gr->Draw();
		gr->Fit("pol1");
		TF1 *f = gr->GetFunction("pol1");
		double p0 = f->GetParameter(0);
		double p1 = f->GetParameter(1);
		f->Draw("same");
		c[i]->Modified();
		c[i]->Update();

	}

}

void PrintA(double ped[4][32])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<32;j++)
		{
			cout<<i<<"\t"<<j<<"\t"<<ped[i][j]<<endl;
		}
	}




}
void Load(int runnum,int pp,double val[4][32],double sigma[4][32],double thrd[4][32])
{
	ifstream in;
	TString par_name=Form("_run0%d_Beamv8.txt",runnum);
	TString npp;
	if(pp==0) npp="ped";
	else npp="peak";
	par_name=npp+par_name;

	cout<<par_name<<endl;;
	in.open(par_name);
	int side;
	int strip;
	double  pedestral;
	double  sig;
	double thr;
	while (1)
	{
		in >>side>>strip>>pedestral>>sig>>thr;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;

		val[side][strip]=pedestral;
		sigma[side][strip]=sig;
		thrd[side][strip]=thr;



	}
}
void Print(double ped[4][32],double sigma[4][32],double thrd[4][32])
{
	for(int side=0;side<4;side++)
		for(int strip=0;strip<32;strip++)
			cout<< side<<"\t"<<strip<<"\t"<<ped[side][strip]<<"\t"<<sigma[side][strip]<<"\t"<<thrd[side][strip]<<"\t"<<endl;

}
