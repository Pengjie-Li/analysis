void LoadData(double SiPeak[4][32],double SiSigma[4][32],double SiFWHM[4][32])
{
	ifstream in;

	TString inputname="DSSD_Strip_Resolution.txt";
	cout<<inputname<<endl;

	in.open(inputname);
	double peak;
	double sigma;
	double  FWHM;
	int i=0;int j=0;
	while (1)
	{
		in >>peak>>sigma>>FWHM;
		if (!in.good()) break;

		SiPeak[i][j]=peak;
		SiSigma[i][j]=sigma;
		SiFWHM[i][j]=FWHM;
		j++;
		if(j==32) {i++;j=0;}


	}




}

void Draw_reso()
{

	double  SiPeak[4][32]={0};
	double SiSigma[4][32]={0};
	double  SiFWHM[4][32]={0};


	LoadData(SiPeak,SiSigma,SiFWHM);

	TCanvas *cPeak=new TCanvas("Peak","Peak",1800,900);
	cPeak->Divide(2,2);                                                                               
	TCanvas *cSigma=new TCanvas("Sigma","Sigma",1800,900);
	cSigma->Divide(2,2);                                                                               
	TCanvas *cFWHM=new TCanvas("FWHM","FWHM",1800,900);
	cFWHM->Divide(2,2);                                                                               



	TGraph *grPeak[4];                                                                                    
	TGraph *grSigma[4];                                                                                    
	TGraph *grFWHM[4];                                                                                    

	double ch[32]={0};
	for(int i=0;i<32;i++) ch[i]=i;
	for(int i=0;i<4;i++)                                                                              
	{
		cPeak->cd(i+1);
		grPeak[i]=new TGraph(32,ch,&SiPeak[i][0]);                                                                    
		grPeak[i]->SetMarkerStyle(8);
		switch (i)
		{
			case 0: grPeak[i]->SetTitle("SiLF"); break;
			case 1: grPeak[i]->SetTitle("SiLB"); break;
			case 2: grPeak[i]->SetTitle("SiRF"); break;
			case 3: grPeak[i]->SetTitle("SiRB"); break;
		}

		//grPeak[i]->SetTitle(Form("Si%d",i));
		grPeak[i]->SetMarkerSize(1);
		grPeak[i]->SetMarkerColor(4);
		grPeak[i]->GetYaxis()->SetRangeUser(0,10000);

		grPeak[i]->GetXaxis()->SetTitle("Strip ID");
		grPeak[i]->GetXaxis()->CenterTitle();
		grPeak[i]->GetYaxis()->SetTitle("SiE(keV)");
		grPeak[i]->GetYaxis()->CenterTitle();

		grPeak[i]->Draw("AP");


	}

	for(int i=0;i<4;i++)                                                                              
	{
		cSigma->cd(i+1);
		grSigma[i]=new TGraph(32,ch,&SiSigma[i][0]);                                                                    
		grSigma[i]->SetMarkerStyle(8);
		switch (i)
		{
			case 0: grSigma[i]->SetTitle("SiLF"); break;
			case 1: grSigma[i]->SetTitle("SiLB"); break;
			case 2: grSigma[i]->SetTitle("SiRF"); break;
			case 3: grSigma[i]->SetTitle("SiRB"); break;
		}

		//grSigma[i]->SetTitle(Form("Si%d",i));
		grSigma[i]->SetMarkerSize(1);
		grSigma[i]->SetMarkerColor(4);
		grSigma[i]->GetYaxis()->SetRangeUser(0,1000);

		grSigma[i]->GetXaxis()->SetTitle("Strip ID");
		grSigma[i]->GetXaxis()->CenterTitle();
		grSigma[i]->GetYaxis()->SetTitle("SiE(keV)");
		grSigma[i]->GetYaxis()->CenterTitle();

		grSigma[i]->Draw("AP");


	}

	for(int i=0;i<4;i++)                                                                              
	{
		cFWHM->cd(i+1);
		grFWHM[i]=new TGraph(32,ch,&SiFWHM[i][0]);                                                                    
		grFWHM[i]->SetMarkerStyle(8);
		switch (i)
		{
			case 0: grFWHM[i]->SetTitle("SiLF"); break;
			case 1: grFWHM[i]->SetTitle("SiLB"); break;
			case 2: grFWHM[i]->SetTitle("SiRF"); break;
			case 3: grFWHM[i]->SetTitle("SiRB"); break;
		}

		//grFWHM[i]->SetTitle(Form("Si%d",i));
		grFWHM[i]->SetMarkerSize(1);
		grFWHM[i]->SetMarkerColor(4);
		grFWHM[i]->GetYaxis()->SetRangeUser(0,2000);

		grFWHM[i]->GetXaxis()->SetTitle("Strip ID");
		grFWHM[i]->GetXaxis()->CenterTitle();
		grFWHM[i]->GetYaxis()->SetTitle("SiE(keV)");
		grFWHM[i]->GetYaxis()->CenterTitle();

		grFWHM[i]->Draw("AP");


	}


}
