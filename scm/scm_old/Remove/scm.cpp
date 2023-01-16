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


        for(int i=0;i<32;i++)
                {
			LF[i]=0;
                        TString lfname=Form("lfpixel%d",i);
                        tree->SetBranchAddress(lfname,&LF[i]);

			LB[i]=0;
                        TString lbname=Form("lbpixel%d",i);
                        tree->SetBranchAddress(lbname,&LB[i]);

			RF[i]=0;
                        TString rfname=Form("rfpixel%d",i);
                        tree->SetBranchAddress(rfname,&RF[i]);

			RB[i]=0;
                        TString rbname=Form("rbpixel%d",i);
                        tree->SetBranchAddress(rbname,&RB[i]);


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

	for(int i=0;i<32;i++)
		{
			lfpixel[i]=*LF[i];
			lbpixel[i]=*LB[i];

			rfpixel[i]=*RF[i];
			rbpixel[i]=*RB[i];
	
		}



}


void SCM::Build()
{
	g=new TFile("after_remove.root","recreate");

}
void SCM::Remove()
{

RemoveLF();
RemoveLB();
RemoveRF();
RemoveRB();




}

void SCM::RemoveLF()
{
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{
		if(lfpixel[i].Np()>10) // 10 Points is the least points for fitting
		{

			DrawLF(lfpixel,i);
			bool status;
			//lfpixel[i].k=0.972351;
			//lfpixel[i].b=-18.161;
			status=lfpixel[i].Remove();
			if(status) ReDrawLF(lfpixel,i);

			status=lfpixel[i].Refill();
			status=lfpixel[i].Least_Square_Fit();
			if(status) ReReDrawLF(lfpixel,i);

		}

	}


}

void SCM::RemoveLB()
{
	for(int i=0;i<32;i++)
	//for(int i=0;i<1;i++)
	//for(int i=0;i<1;i++)
	{
		if(lbpixel[i].Np()>10) // 10 Points is the least points for fitting
		{

			DrawLB(lbpixel,i);
			bool status;
			//lbpixel[i].k=1.08472;
			//lbpixel[i].b=93.0197;
			status=lbpixel[i].Remove();
			if(status) ReDrawLB(lbpixel,i);

			status=lbpixel[i].Refill();
			status=lbpixel[i].Least_Square_Fit();
			if(status) ReReDrawLB(lbpixel,i);

		}

	}


}


void SCM::DrawLF(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        lfgr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        lfgr[i]->SetName(Form("lfgr%d",i));
        lfgr[i]->Draw("AP");

        lfgr[i]->Write();

}

void SCM::ReDrawLF(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        lfregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        lfregr[i]->SetName(Form("lfregr%d",i));
        lfregr[i]->Draw("AP");

        lfregr[i]->Write();

}

void SCM::ReReDrawLF(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        lfreregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        lfreregr[i]->SetName(Form("lfreregr%d",i));
        lfreregr[i]->Draw("AP");

        lfreregr[i]->Write();

}

void SCM::DrawLB(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        lbgr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        lbgr[i]->SetName(Form("lbgr%d",i));
        lbgr[i]->Draw("AP");

        lbgr[i]->Write();

}

void SCM::ReDrawLB(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        lbregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        lbregr[i]->SetName(Form("lbregr%d",i));
        lbregr[i]->Draw("AP");

        lbregr[i]->Write();

}

void SCM::ReReDrawLB(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        lbreregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        lbreregr[i]->SetName(Form("lbreregr%d",i));
        lbreregr[i]->Draw("AP");

        lbreregr[i]->Write();

}


void SCM::RemoveRF()
{
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{
		if(rfpixel[i].Np()>10) // 10 Points is the least points for fitting
		{

			DrawRF(rfpixel,i);
			bool status;
			//rfpixel[i].k=0.88153;
			//rfpixel[i].b=24.103;
			status=rfpixel[i].Remove();
			if(status) ReDrawRF(rfpixel,i);

			status=rfpixel[i].Refill();
			status=rfpixel[i].Least_Square_Fit();
			if(status) ReReDrawRF(rfpixel,i);

		}

	}


}

void SCM::RemoveRB()
{
	for(int i=0;i<32;i++)
	{
		if(rbpixel[i].Np()>10) // 10 Points is the least points for fitting
		{

			DrawRB(rbpixel,i);
			bool status;

			status=rbpixel[i].Remove();
			if(status) ReDrawRB(rbpixel,i);

			status=rbpixel[i].Refill();
			status=rbpixel[i].Least_Square_Fit();
			if(status) ReReDrawRB(rbpixel,i);

		}

	}


}


void SCM::DrawRF(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        rfgr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        rfgr[i]->SetName(Form("rfgr%d",i));
        rfgr[i]->Draw("AP");

        rfgr[i]->Write();

}

void SCM::ReDrawRF(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        rfregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        rfregr[i]->SetName(Form("rfregr%d",i));
        rfregr[i]->Draw("AP");

        rfregr[i]->Write();

}

void SCM::ReReDrawRF(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        rfreregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        rfreregr[i]->SetName(Form("rfreregr%d",i));
        rfreregr[i]->Draw("AP");

        rfreregr[i]->Write();

}

void SCM::DrawRB(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        rbgr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        rbgr[i]->SetName(Form("rbgr%d",i));
        rbgr[i]->Draw("AP");

        rbgr[i]->Write();

}

void SCM::ReDrawRB(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        rbregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        rbregr[i]->SetName(Form("rbregr%d",i));
        rbregr[i]->Draw("AP");

        rbregr[i]->Write();

}

void SCM::ReReDrawRB(TNewPixel p[32],int i)
{
        vector<double> xarray=p[i].xarray;
        vector<double> yarray=p[i].yarray;
        vector<double> xerror=p[i].xerror;
        vector<double> yerror=p[i].yerror;

        rbreregr[i]=new TGraphErrors(xarray.size(),&xarray[0],&yarray[0],&xerror[0],&yerror[0]);
        rbreregr[i]->SetName(Form("rbreregr%d",i));
        rbreregr[i]->Draw("AP");

        rbreregr[i]->Write();

}



//void SCM::Fit()
//{
//	for(int i=0;i<32;i++)
//		for(int j=0;j<32;j++)
//			//	for(int i=0;i<16;i++)
//			//		for(int j=15;j<16;j++)
//		{
//
//			//cout<<pixel[i][j].Np()<<endl;
//			if(pixel[i][j].Np()>10) // 10 Points is the least points for fitting
//			{
//
//				Draw(i,j);
//				bool status;
//				status=pixel[i][j].Least_Square_Fit();
//
//			}
//			else pixel[i][j].Init();
//
//			Output(i,j);
//		}
//
//
//}
void SCM::Fit()
{

//	FitLF();
//	FitLB();
//	FitRF();
//	FitRB();


	GFitLF();
	GFitLB();
	GFitRF();
	GFitRB();


}

void SCM::FitLF()
{

	cout<<" Now Fitting LF"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<lfpixel[i].Np()<<endl;
		bool status;
		status=lfpixel[i].Least_Square_Fit();
	}
}


void SCM::FitLB()
{

	cout<<" Now Fitting LB"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=0;i<1;i++)
	//for(int i=0;i<32;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<lbpixel[i].Np()<<endl;
		bool status;
		status=lbpixel[i].Least_Square_Fit();
	}
}

void SCM::FitRF()
{

	cout<<" Now Fitting RF"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<rfpixel[i].Np()<<endl;
		bool status;
		status=rfpixel[i].Least_Square_Fit();
	}
}

void SCM::FitRB()
{

	cout<<" Now Fitting RB"<<endl;
	for(int i=0;i<32;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<rbpixel[i].Np()<<endl;
		bool status;
		status=rbpixel[i].Least_Square_Fit();
	}
}

void SCM::Residue()
{

	ResidueLF();
	ResidueLB();
	ResidueRF();
	ResidueRB();


}



void SCM::ResidueLF()
{

	cout<<" Now Checking Residue LF"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		hlf[i]=new TH1F(Form("hlf%d",i),Form("hlf%d",i),40,-20,20);
                if(lfpixel[i].Np()<3) continue;
                for(int j=0;j<lfpixel[i].Np();j++)
		{
			double rd=lfpixel[i].yarray[j]-(lfpixel[i].k*lfpixel[i].xarray[j]+lfpixel[i].b);
			hlf[i]->Fill(rd);
		}
		hlf[i]->Write();
		hlf[i]->Fit("gaus","Q");
		double mean=hlf[i]->GetFunction("gaus")->GetParameter(1);
		double sigma=hlf[i]->GetFunction("gaus")->GetParameter(2);
                cout<<"LF strip="<<i<<" Residue mean="<<mean<<" sigma="<<sigma<<endl;
	}
}


void SCM::ResidueLB()
{
	cout<<" Now Checking Residue LB"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		hlb[i]=new TH1F(Form("hlb%d",i),Form("hlb%d",i),40,-20,20);
                if(lbpixel[i].Np()<3) continue;
                for(int j=0;j<lbpixel[i].Np();j++)
		{
			double rd=lbpixel[i].yarray[j]-(lbpixel[i].k*lbpixel[i].xarray[j]+lbpixel[i].b);
			hlb[i]->Fill(rd);
		}
		hlb[i]->Write();
		hlb[i]->Fit("gaus","Q");
		double mean=hlb[i]->GetFunction("gaus")->GetParameter(1);
		double sigma=hlb[i]->GetFunction("gaus")->GetParameter(2);
                cout<<"LB strip="<<i<<" Residue mean="<<mean<<" sigma="<<sigma<<endl;
	}


}

void SCM::ResidueRF()
{

	cout<<" Now Checking Residue RF"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		hrf[i]=new TH1F(Form("hrf%d",i),Form("hrf%d",i),40,-20,20);
                if(rfpixel[i].Np()<3) continue;
                for(int j=0;j<rfpixel[i].Np();j++)
		{
			double rd=rfpixel[i].yarray[j]-(rfpixel[i].k*rfpixel[i].xarray[j]+rfpixel[i].b);
			hrf[i]->Fill(rd);
		}
		hrf[i]->Write();
		hrf[i]->Fit("gaus","Q");
		double mean=hrf[i]->GetFunction("gaus")->GetParameter(1);
		double sigma=hrf[i]->GetFunction("gaus")->GetParameter(2);
                cout<<"RF strip="<<i<<" Residue mean="<<mean<<" sigma="<<sigma<<endl;
	}

}

void SCM::ResidueRB()
{

	cout<<" Now Checking Residue RB"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		hrb[i]=new TH1F(Form("hrb%d",i),Form("hrb%d",i),40,-20,20);
                if(rbpixel[i].Np()<3) continue;
                for(int j=0;j<rbpixel[i].Np();j++)
		{
			double rd=rbpixel[i].yarray[j]-(rbpixel[i].k*rbpixel[i].xarray[j]+rbpixel[i].b);
			hrb[i]->Fill(rd);
		}
		hrb[i]->Write();
		hrb[i]->Fit("gaus","Q");
		double mean=hrb[i]->GetFunction("gaus")->GetParameter(1);
		double sigma=hrb[i]->GetFunction("gaus")->GetParameter(2);
                cout<<"RB strip="<<i<<" Residue mean="<<mean<<" sigma="<<sigma<<endl;
	}

}

void SCM::GFitLF()
{

	cout<<" Now Fitting LF"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<lfpixel[i].Np()<<endl;
		bool status;
		status=lfpixel[i].GFit();
	}
}


void SCM::GFitLB()
{

	cout<<" Now Fitting LB"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=0;i<1;i++)
	//for(int i=0;i<32;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<lbpixel[i].Np()<<endl;
		bool status;
		status=lbpixel[i].GFit();
	}
}

void SCM::GFitRF()
{

	cout<<" Now Fitting RF"<<endl;
	for(int i=0;i<32;i++)
	//for(int i=1;i<2;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<rfpixel[i].Np()<<endl;
		bool status;
		status=rfpixel[i].GFit();
	}
}


void SCM::GFitRB()
{

	cout<<" Now Fitting RB"<<endl;
	for(int i=0;i<32;i++)
	{

		cout<<"strip="<<i<<" No. of points="<<rbpixel[i].Np()<<endl;
		bool status;
		status=rbpixel[i].GFit();
	}
}



void SCM::Output()
{
	TString outputname="fit_calibration_parameters.txt";
	cout<<outputname<<endl;
	ofstream fout(outputname,ios_base::out);

	cout<<"Now Output fitting parameters for LF"<<endl;
	for(int i=0;i<32;i++)
	fout <<"\t"<<0 << "\t" << i<< "\t" << lfpixel[i].k<<"\t"<<lfpixel[i].b<< "\t" << lfpixel[i].ek<<"\t"<<lfpixel[i].eb<<endl;

	for(int i=0;i<32;i++)
	fout <<"\t"<<1 << "\t" << i<< "\t" << lbpixel[i].k<<"\t"<<lbpixel[i].b<< "\t" << lbpixel[i].ek<<"\t"<<lbpixel[i].eb<<endl;

	for(int i=0;i<32;i++)
	fout <<"\t"<<2 << "\t" << i<< "\t" << rfpixel[i].k<<"\t"<<rfpixel[i].b<< "\t" << rfpixel[i].ek<<"\t"<<rfpixel[i].eb<<endl;

	for(int i=0;i<32;i++)
	fout <<"\t"<<3 << "\t" << i<< "\t" << rbpixel[i].k<<"\t"<<rbpixel[i].b<< "\t" << rbpixel[i].ek<<"\t"<<rbpixel[i].eb<<endl;


	fout.close();


}
void SCM::Output(int i,int j)
{
	TString outputname="fit_calibration_parameters.txt";
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

			//Check(side,strip); 
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

void SCM::Write()
{



}
