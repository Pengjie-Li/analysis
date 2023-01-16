
void Load();
void DSSDL();
void pixel_peak()
{
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);



	TString inputname="./rootfiles/run0599_Beamv8.root";
	//cout<<"inputname"<<inputname<<endl;
	TFile *f = new TFile(inputname,"UPDATE");
	Double_t ped[4][32]={0};
	Double_t sigma[4][32]={0};
	Double_t thrd[4][32]={0};


	Load(ped,sigma,thrd);
	//Print(ped,sigma,thrd);
	DSSDLF();
	DSSDLB();


}
void Load(double ped[4][32],double sigma[4][32],double thrd[4][32])
{
	ifstream in;
	TString par_name=gFile->GetName();
	par_name.ReplaceAll("rootfiles","");
	par_name.ReplaceAll("root","txt");
	par_name.ReplaceAll("./","");
	par_name.ReplaceAll("/","");
	par_name="ped_"+par_name;
	cout<<par_name<<endl;


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

		ped[side][strip]=pedestral;
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
void DSSDLF()
{
 
        Int_t rmin=1200;
        Int_t rmax=2500;

	TH2F * hSiLFpeak = (TH2F*)gDirectory->Get("hSiLF")->Clone("hSiLFpeak");
	//hSiLFpeak->Rebin(3);
	hSiLFpeak->GetXaxis()->SetTitle("Channel No.");
	hSiLFpeak->GetYaxis()->SetTitle("ADC channel");
	TCanvas *cSiLFpeak = new TCanvas("cSiLFpeak","cSiLFpeak",850,500);
	cSiLFpeak->cd();
	hSiLFpeak->GetYaxis()->SetRangeUser(rmin,rmax);
	gPad->SetLogz();
	hSiLFpeak->Draw("colz");

	TF1* foo = new TF1("foo","gaus",rmin,rmax);
	hSiLFpeak->FitSlicesY(foo,0,32,0,"QNR",0);
	hSiLFpeak_1->SetLineColor(1);
	hSiLFpeak_1->SetLineWidth(2);
	TH1D *hSiLFpeak_3 = new TH1D(*hSiLFpeak_1);
	hSiLFpeak_3->SetMarkerStyle(8);
	hSiLFpeak_3->SetMarkerSize(.8);
	hSiLFpeak_1->Draw("same");
	hSiLFpeak_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="peak_"+outputname;
	cout<<outputname<<endl;
//
	ofstream fout(outputname,ios_base::app | ios_base::out);
	for(Int_t i = 0; i<32; i++){
		fout << 0 << "\t"<<i << "\t" << hSiLFpeak_1->GetBinContent(i+1) << "\t" << hSiLFpeak_2->GetBinContent(i+1) << "\t" << hSiLFpeak_1->GetBinContent(i+1) + 5*(hSiLFpeak_2->GetBinContent(i+1)) <<endl;
		cout << i << "\t" << hSiLFpeak_1->GetBinContent(i+1) << "\t" << hSiLFpeak_2->GetBinContent(i+1) << "\t" << hSiLFpeak_1->GetBinContent(i+1) + 5*(hSiLFpeak_2->GetBinContent(i+1)) <<endl;
	}
	fout.close();

	cSiLFpeak->Write();
}

void DSSDLB()
{
 
        Int_t rmin=1200;
        Int_t rmax=2500;

	TH2F * hSiLBpeak = (TH2F*)gDirectory->Get("hSiLB")->Clone("hSiLBpeak");
	//hSiLBpeak->Rebin(3);
	hSiLBpeak->GetXaxis()->SetTitle("Channel No.");
	hSiLBpeak->GetYaxis()->SetTitle("ADC channel");
	TCanvas *cSiLBpeak = new TCanvas("cSiLBpeak","cSiLBpeak",850,500);
	cSiLBpeak->cd();
	hSiLBpeak->GetYaxis()->SetRangeUser(rmin,rmax);
	gPad->SetLogz();
	hSiLBpeak->Draw("colz");

	TF1* foo = new TF1("foo","gaus",rmin,rmax);
	hSiLBpeak->FitSlicesY(foo,0,32,0,"QNR",0);
	hSiLBpeak_1->SetLineColor(1);
	hSiLBpeak_1->SetLineWidth(2);
	TH1D *hSiLBpeak_3 = new TH1D(*hSiLBpeak_1);
	hSiLBpeak_3->SetMarkerStyle(8);
	hSiLBpeak_3->SetMarkerSize(.8);
	hSiLBpeak_1->Draw("same");
	hSiLBpeak_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="peak_"+outputname;
	cout<<outputname<<endl;
//
	ofstream fout(outputname,ios_base::app | ios_base::out);
	for(Int_t i = 0; i<32; i++){
		fout << 1 << "\t" << i << "\t" << hSiLBpeak_1->GetBinContent(i+1) << "\t" << hSiLBpeak_2->GetBinContent(i+1) << "\t" << hSiLBpeak_1->GetBinContent(i+1) + 5*(hSiLBpeak_2->GetBinContent(i+1)) <<endl;
		cout << i << "\t" << hSiLBpeak_1->GetBinContent(i+1) << "\t" << hSiLBpeak_2->GetBinContent(i+1) << "\t" << hSiLBpeak_1->GetBinContent(i+1) + 5*(hSiLBpeak_2->GetBinContent(i+1)) <<endl;
	}
	fout.close();

	cSiLBpeak->Write();
}

