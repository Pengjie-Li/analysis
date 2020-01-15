#include "ldp.h"

double LDP::sqr(double x){ return x*x; }
LDP::LDP()
{
}

LDP::LDP(int ref)
{
	refback=ref;
	reffront=ref;
}
LDP::LDP(int ref1,int ref2)
{
	refback=ref1;
	reffront=ref2;
}
LDP::LDP(int ref1,int ref2,int run)
{
	refback=ref1;
	reffront=ref2;
	runnum=run;
}
void LDP::Open()
{
        tree= new TChain("CalTreeSILICONS");

	tree->Add("rootfiles/run0596/run0596_SILICONS.root");
	tree->Add("rootfiles/run0599/run0599_SILICONS.root");
	tree->Add("rootfiles/run0597/run0597_SILICONS.root");
	tree->Add("rootfiles/run0595/run0595_SILICONS.root");
	tree->Add("rootfiles/run0598/run0598_SILICONS.root");

        for(int run=426;run<439;run++)
	tree->Add(Form("rootfiles/run0%d/run0%d_SILICONS.root",run,run));

        for(int run=370;run<390;run++)
	tree->Add(Form("rootfiles/run0%d/run0%d_SILICONS.root",run,run));



//	tree->Add("rootfiles/run0597_Beamv8.root");
//	tree->Add("rootfiles/run0595_Beamv8.root");
//	tree->Add("rootfiles/run0598_Beamv8.root");

	Init();

}
void LDP::Open(TString inputname)
{

        tree= new TChain("tree_BEAM");

//	tree->Add("rootfiles/run0597_Beamv8.root");
//	tree->Add("rootfiles/run0595_Beamv8.root");
//	tree->Add("rootfiles/run0598_Beamv8.root");

	Init();

}

void LDP::LoadPar()
{
	ifstream in;

	//TString inputname="./rootfiles/parameters/ped_run0597_Beamv8.txt";
	TString inputname="./rootfiles/parameters/ped_run0596_Beamv8.txt";
//	inputname.ReplaceAll("rootfiles","");
//	inputname.ReplaceAll("root","txt");
//	inputname.ReplaceAll("./","");
//	inputname.ReplaceAll("/","");
//	inputname="./rootfiles/parameters/ped_"+inputname;
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
		if(side>1) continue;

		ped[side][strip]=pedestral;
		pedsigma[side][strip]=sig;
		pedthrd[side][strip]=thr;

	}
	in.close();


	inputname="./rootfiles/parameters/ped_run0597_Beamv8.txt";

	in.open(inputname);

	while (1)
	{
		in >>side>>strip>>pedestral>>sig>>thr;
		if (!in.good()) break;
		if(side<2) continue;

		ped[side][strip]=pedestral;
		pedsigma[side][strip]=sig;
		pedthrd[side][strip]=thr;
//cout<<pedestral<<endl;

	}
in.close();



}
void LDP::Init()
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
void LDP::Load()
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

		//cout<<(*SiRF_rawADC)[15]<<endl;
		//cout<<(ped[2][0]+pedsigma[2][0]*10)<<endl;
		//if(rfadc[0]>300) cout<<rfadc[0]<<"   "<<rfadc[31]<<endl;
		int fid=-1;
		int bid=-1;
		int nhit=remove_multihit(rfadc,rbadc,fid,bid);
		//cout<<nhit<<endl;

		//if(fid==0&&bid==0) cout<<fid<<"  "<<bid<<"  "<<pixel[fid][bid].n<<endl;
		if(nhit>1||nhit==0) continue;
		if(select(rfadc[fid],rbadc[bid]))
			pixel[fid][bid].Fill(rfadc[fid],rbadc[bid]);
                if(ientry%10000==0) cout<<"Loading data into pixel:"<<ientry<<endl;

	}



}

void LDP::LoadL()
{
	Long64_t nentries = tree->GetEntries();

	//nentries=100000;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		tree->GetEntry(ientry);
		lfadc.clear();
		lbadc.clear();

		lfadc=*SiLF_rawADC;
		lbadc=*SiLB_rawADC;

		//cout<<(*SiRF_rawADC)[15]<<endl;
		//cout<<(ped[2][0]+pedsigma[2][0]*10)<<endl;
		//if(rfadc[0]>300) cout<<rfadc[0]<<"   "<<rfadc[31]<<endl;
		int fid=-1;
		int bid=-1;
		int nhit=left_remove_multihit(lfadc,lbadc,fid,bid);
		//cout<<fid<<"  "<<bid<<"  "<<pixel[fid][bid].n<<endl;
		//if(fid==0&&bid==0) cout<<fid<<"  "<<bid<<"  "<<pixel[fid][bid].n<<endl;

		//cout<<nhit<<endl;
		if(nhit>1||nhit==0) continue;

		if(bid==15)
		{
			if(select(lfadc[fid],lbadc[bid]))
				lfpixel[fid].Fill(lfadc[fid],lbadc[bid]);
		}
		if(fid==15)
		{
			if(select(lfadc[fid],lbadc[bid]))
				lbpixel[bid].Fill(lbadc[bid],lfadc[fid]);

		}
		if(ientry%10000==0) cout<<"Loading data into pixel:"<<ientry<<endl;

	}



}

void LDP::CheckRawLF()
{
	cout<<"Checking Raw LF pixel"<<endl;
	for(int fid=0;fid<32;fid++)
	{
		cout<<"fid="<<fid<<" No. Points in Raw Pixel: "<<lfpixel[fid].Np()<<endl;
		DrawLF(lfpixel,fid);

	}
	cout<<"End of Checking Raw LF pixel"<<endl;

}

void LDP::CheckRawLB()
{
	cout<<"Checking Raw LB pixel"<<endl;
	for(int bid=0;bid<32;bid++)
	{
		cout<<"bid="<<bid<<" No. Points in Raw Pixel: "<<lbpixel[bid].Np()<<endl;
		DrawLB(lbpixel,bid);

	}
	cout<<"End of Checking Raw LB pixel"<<endl;

}


void LDP::LoadR()
{
	Long64_t nentries = tree->GetEntries();

	//nentries=100000;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		tree->GetEntry(ientry);
		rfadc.clear();
		rbadc.clear();

		rfadc=*SiRF_rawADC;
		rbadc=*SiRB_rawADC;

		//cout<<(*SiRF_rawADC)[15]<<endl;
		//cout<<(ped[2][0]+pedsigma[2][0]*10)<<endl;
		//if(rfadc[0]>300) cout<<rfadc[0]<<"   "<<rfadc[31]<<endl;
		int fid=-1;
		int bid=-1;
		int nhit=right_remove_multihit(rfadc,rbadc,fid,bid);
		//cout<<fid<<"  "<<bid<<"  "<<pixel[fid][bid].n<<endl;
		//if(fid==0&&bid==0) cout<<fid<<"  "<<bid<<"  "<<pixel[fid][bid].n<<endl;

		//cout<<nhit<<endl;
		if(nhit>1||nhit==0) continue;

		if(bid==15)
		{
			if(select(rfadc[fid],rbadc[bid]))
				rfpixel[fid].Fill(rfadc[fid],rbadc[bid]);
		}
		if(fid==15)
		{
			if(select(rfadc[fid],rbadc[bid]))
				rbpixel[bid].Fill(rbadc[bid],rfadc[fid]);

		}
		if(ientry%10000==0) cout<<"Loading data into pixel:"<<ientry<<endl;

	}



}

void LDP::CheckRawRF()
{
	cout<<"Checking Raw RF pixel"<<endl;
	for(int fid=0;fid<32;fid++)
	{
		cout<<"fid="<<fid<<" No. Points in Raw Pixel: "<<rfpixel[fid].Np()<<endl;
		DrawRF(rfpixel,fid);

	}
	cout<<"End of Checking Raw RF pixel"<<endl;

}



void LDP::CheckRawRB()
{
	cout<<"Checking Raw RB pixel"<<endl;
	for(int bid=0;bid<32;bid++)
	{
		cout<<"bid="<<bid<<" No. Points in Raw Pixel: "<<rbpixel[bid].Np()<<endl;
		DrawRB(rbpixel,bid);

	}
	cout<<"End of Checking Raw RB pixel"<<endl;

}

bool LDP::select(double x,double y)
{
	if(x>4095||y>4095) return false;
	if(y>1.2*x+300) return false;
	if(x>1.2*y+300) return false;
	return true;

}
int LDP::remove_multihit(vector<double>  fadc,vector<double>  badc)
{
	int nhit=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
			if(fadc[i]>300&&badc[j]>300) nhit++;
	return nhit;

}
int LDP::remove_multihit(vector<double>  fadc,vector<double>  badc,int &fid,int &bid)
{
	int nhit=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			//if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>pedthrd[0][j])

			//cout<<fadc[i]<<"  "<<(ped[2][i]+pedsigma[2][i]*10)<<"  "<<badc[j]<<"  "<<(ped[3][j]+pedsigma[3][j]*10)<<endl;
			if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>(ped[1][j]+pedsigma[1][j]*10))
			{
				nhit++;
				fid=i;bid=j;
			}
			//cout<<pedthrd[1][i]<<"  "<<pedthrd[1][j]<<endl;
		}

	return nhit;

}

int LDP::left_remove_multihit(vector<double>  fadc,vector<double>  badc,int &fid,int &bid)
{
	int nhit=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			//if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>pedthrd[0][j])

			//cout<<fadc[i]<<"  "<<(ped[2][i]+pedsigma[2][i]*10)<<"  "<<badc[j]<<"  "<<(ped[3][j]+pedsigma[3][j]*10)<<endl;
			if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>(ped[1][j]+pedsigma[1][j]*10))
			{
				nhit++;
				fid=i;bid=j;
			}
			//cout<<pedthrd[1][i]<<"  "<<pedthrd[1][j]<<endl;
		}

	return nhit;

}

int LDP::right_remove_multihit(vector<double>  fadc,vector<double>  badc,int &fid,int &bid)
{
	int nhit=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
			//if(fadc[i]>(ped[0][i]+pedsigma[0][i]*10)&&badc[j]>pedthrd[0][j])

			//cout<<fadc[i]<<"  "<<(ped[2][i]+pedsigma[2][i]*10)<<"  "<<badc[j]<<"  "<<(ped[3][j]+pedsigma[3][j]*10)<<endl;
			if(fadc[i]>(ped[2][i]+pedsigma[2][i]*10)&&badc[j]>(ped[3][j]+pedsigma[3][j]*10))
			{
				nhit++;
				fid=i;bid=j;
			}
			//cout<<pedthrd[1][i]<<"  "<<pedthrd[1][j]<<endl;
		}

	return nhit;

}
void LDP::Build()
{
	g=new TFile("load_pixel_data.root","recreate");

}
void LDP::Remove()
{
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
//	for(int i=0;i<16;i++)
//		for(int j=15;j<16;j++)
		{
			if(pixel[i][j].Np()>10) // 10 Points is the least points for fitting
			{

				Draw(i,j);
				bool status;
				status=pixel[i][j].Least_Square_Fit();

				status=pixel[i][j].Remove();
				if(status) ReDraw(i,j);

				status=pixel[i][j].Refill();
				status=pixel[i][j].Least_Square_Fit();
				if(status) ReReDraw(i,j);
				//			status=pixel[i][j].Fit();
				//			Draw(i,j);
				//			status=pixel[i][j].Refit();
				//			ReDraw(i,j);
				//			status=pixel[i][j].ReRefit();
				//			ReReDraw(i,j);
				//
				//			//status=pixel[i][j].FitB(0.001);
				//			//status=pixel[i][j].ReFitB();

			}
			else pixel[i][j].Init();

			Output(i,j);
		}


}
void LDP::Output(int i,int j)
{
	cout <<"\t"<<i << "\t" << j<< "\t" << pixel[i][j].k<<"\t"<<pixel[i][j].b<< "\t" << pixel[i][j].ek<<"\t"<<pixel[i][j].eb<<endl;
}

void LDP::DrawLF(TNewPixel p[32],int i)
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
void LDP::DrawLB(TNewPixel p[32],int i)
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
void LDP::DrawRF(TNewPixel p[32],int i)
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
void LDP::DrawRB(TNewPixel p[32],int i)
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
void LDP::Draw(int i,int j)
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
void LDP::ReDraw(int i,int j)
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
void LDP::ReReDraw(int i,int j)
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

void LDP::Write()
{

	treeW=new TTree("tree","A Tree with Events");

	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++)
		{
                        TString bname=Form("pixel%d_%d",i,j);

			treeW->Branch(bname,&pixel[i][j]);
		}

	for(int i=0;i<32;i++)
		{
                        TString lfname=Form("lfpixel%d",i);
			treeW->Branch(lfname,&lfpixel[i]);

			TString lbname=Form("lbpixel%d",i);
			treeW->Branch(lbname,&lbpixel[i]);

			TString rfname=Form("rfpixel%d",i);
			treeW->Branch(rfname,&rfpixel[i]);

			TString rbname=Form("rbpixel%d",i);
			treeW->Branch(rbname,&rbpixel[i]);


		}



	treeW->Fill();
	treeW->Write();
//	treeW->Branch("",&);
//
//	for(int i=0;i<32;i++)
//		for(int j=0;j<32;j++)
//		{
//			xarray.clear();
//			yarray.clear();
//
//
//
//		}
//


}
