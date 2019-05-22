	

void findpeaks()
{
	// get TH2F and make projection on strip id
	// find peaks and fit

	// Open input files
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
//	gStyle->SetOptStat(1111111);

//	int runnum=596;
//	double rmin=4000;
//	double rmax=10000;
//	double fmin=7000;
//	double fmax=9000;



	int runnum=599;
	double rmin=4000;
	double rmax=18000;
	double fmin=9000;
	double fmax=13000;



//	int runnum=597;
//	double rmin=4000;
//	double rmax=10000;
//	double fmin=6000;
//	double fmax=8000;

//	int runnum=598;
//	double rmin=4000;
//	double rmax=18000;
//	double fmin=8000;
//	double fmax=13000;




	TString inputname=Form("./analysedrootfiles/run0%d_analysed_v1.root",runnum);
	//cout<<"inputname"<<inputname<<endl;
	TFile *f = new TFile(inputname,"UPDATE");

	Peak_SiLF(rmin,rmax,fmin,fmax);
	Peak_SiLB(rmin,rmax,fmin,fmax);
	Peak_SiRF(rmin,rmax,fmin,fmax);
	Peak_SiRB(rmin,rmax,fmin,fmax);
	
	//	Peak_SiRF();
	//	Peak_SiRB();



}
void Peak_SiLF(double rmin,double rmax,double fmin,double fmax)
{



	TH2F * hSiLF = (TH2F*)gDirectory->Get("hSiLFCal")->Clone("hSiLF");
	//hSiLFCal->Draw("colz");
	//hSiLBCal->Draw("colz");
	hSiLF->GetXaxis()->SetTitle("Channel No.");
	hSiLF->GetYaxis()->SetTitle("ADC channel");
	hSiLF->RebinY(3);
	hSiLF->GetYaxis()->SetRangeUser(rmin,rmax);
	TCanvas *cSiLF = new TCanvas("cSiLF","cSiLF",850,500);
	cSiLF->cd();
	gPad->SetLogz();
	hSiLF->Draw("colz");


	TF1* foo = new TF1("foo","gaus",fmin,fmax);
	hSiLF->FitSlicesY(foo,0,32,0,"QNR",0);
	hSiLF_1->SetLineColor(1);
	hSiLF_1->SetLineWidth(2);
	TH1D *hSiLF_3 = new TH1D(*hSiLF_1);
	hSiLF_3->SetMarkerStyle(8);
	hSiLF_3->SetMarkerSize(.8);
	hSiLF_1->Draw("same");
	hSiLF_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="peak_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<0 << "\t" << i << "\t" << hSiLF_1->GetBinContent(i+1) << "\t" << hSiLF_2->GetBinContent(i+1) << "\t" << hSiLF_1->GetBinContent(i+1) + 5*(hSiLF_2->GetBinContent(i+1)) <<endl;
                cout <<0 << "\t" << i << "\t" << hSiLF_1->GetBinContent(i+1) << "\t" << hSiLF_2->GetBinContent(i+1) << "\t" << hSiLF_1->GetBinContent(i+1) + 5*(hSiLF_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiLF->Write();


}

void Peak_SiLB(double rmin,double rmax,double fmin,double fmax)
{



	TH2F * hSiLB = (TH2F*)gDirectory->Get("hSiLBCal")->Clone("hSiLB");
	//hSiLBCal->Draw("colz");
	//hSiLBCal->Draw("colz");
	hSiLB->GetXaxis()->SetTitle("Channel No.");
	hSiLB->GetYaxis()->SetTitle("ADC channel");
	hSiLB->RebinY(3);
	hSiLB->GetYaxis()->SetRangeUser(rmin,rmax);
	TCanvas *cSiLB = new TCanvas("cSiLB","cSiLB",850,500);
	cSiLB->cd();
	gPad->SetLogz();
	hSiLB->Draw("colz");


	TF1* foo = new TF1("foo","gaus",fmin,fmax);
	hSiLB->FitSlicesY(foo,0,32,0,"QNR",0);
	hSiLB_1->SetLineColor(1);
	hSiLB_1->SetLineWidth(2);
	TH1D *hSiLB_3 = new TH1D(*hSiLB_1);
	hSiLB_3->SetMarkerStyle(8);
	hSiLB_3->SetMarkerSize(.8);
	hSiLB_1->Draw("same");
	hSiLB_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="peak_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<1 << "\t" << i << "\t" << hSiLB_1->GetBinContent(i+1) << "\t" << hSiLB_2->GetBinContent(i+1) << "\t" << hSiLB_1->GetBinContent(i+1) + 5*(hSiLB_2->GetBinContent(i+1)) <<endl;
                cout <<1 << "\t" << i << "\t" << hSiLB_1->GetBinContent(i+1) << "\t" << hSiLB_2->GetBinContent(i+1) << "\t" << hSiLB_1->GetBinContent(i+1) + 5*(hSiLB_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiLB->Write();


}

void Peak_SiRF(double rmin,double rmax,double fmin,double fmax)
{



	TH2F * hSiRF = (TH2F*)gDirectory->Get("hSiRFCal")->Clone("hSiRF");
	//hSiRFCal->Draw("colz");
	//hSiLBCal->Draw("colz");
	hSiRF->GetXaxis()->SetTitle("Channel No.");
	hSiRF->GetYaxis()->SetTitle("ADC channel");
	hSiRF->RebinY(3);
	hSiRF->GetYaxis()->SetRangeUser(rmin,rmax);
	TCanvas *cSiRF = new TCanvas("cSiRF","cSiRF",850,500);
	cSiRF->cd();
	gPad->SetLogz();
	hSiRF->Draw("colz");


	TF1* foo = new TF1("foo","gaus",fmin,fmax);
	hSiRF->FitSlicesY(foo,0,32,0,"QNR",0);
	hSiRF_1->SetLineColor(1);
	hSiRF_1->SetLineWidth(2);
	TH1D *hSiRF_3 = new TH1D(*hSiRF_1);
	hSiRF_3->SetMarkerStyle(8);
	hSiRF_3->SetMarkerSize(.8);
	hSiRF_1->Draw("same");
	hSiRF_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="peak_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<0 << "\t" << i << "\t" << hSiRF_1->GetBinContent(i+1) << "\t" << hSiRF_2->GetBinContent(i+1) << "\t" << hSiRF_1->GetBinContent(i+1) + 5*(hSiRF_2->GetBinContent(i+1)) <<endl;
                cout <<0 << "\t" << i << "\t" << hSiRF_1->GetBinContent(i+1) << "\t" << hSiRF_2->GetBinContent(i+1) << "\t" << hSiRF_1->GetBinContent(i+1) + 5*(hSiRF_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiRF->Write();


}

void Peak_SiRB(double rmin,double rmax,double fmin,double fmax)
{



	TH2F * hSiRB = (TH2F*)gDirectory->Get("hSiRBCal")->Clone("hSiRB");
	//hSiRBCal->Draw("colz");
	//hSiRBCal->Draw("colz");
	hSiRB->GetXaxis()->SetTitle("Channel No.");
	hSiRB->GetYaxis()->SetTitle("ADC channel");
	hSiRB->RebinY(3);
	hSiRB->GetYaxis()->SetRangeUser(rmin,rmax);
	TCanvas *cSiRB = new TCanvas("cSiRB","cSiRB",850,500);
	cSiRB->cd();
	gPad->SetLogz();
	hSiRB->Draw("colz");


	TF1* foo = new TF1("foo","gaus",fmin,fmax);
	hSiRB->FitSlicesY(foo,0,32,0,"QNR",0);
	hSiRB_1->SetLineColor(1);
	hSiRB_1->SetLineWidth(2);
	TH1D *hSiRB_3 = new TH1D(*hSiRB_1);
	hSiRB_3->SetMarkerStyle(8);
	hSiRB_3->SetMarkerSize(.8);
	hSiRB_1->Draw("same");
	hSiRB_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="peak_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<1 << "\t" << i << "\t" << hSiRB_1->GetBinContent(i+1) << "\t" << hSiRB_2->GetBinContent(i+1) << "\t" << hSiRB_1->GetBinContent(i+1) + 5*(hSiRB_2->GetBinContent(i+1)) <<endl;
                cout <<1 << "\t" << i << "\t" << hSiRB_1->GetBinContent(i+1) << "\t" << hSiRB_2->GetBinContent(i+1) << "\t" << hSiRB_1->GetBinContent(i+1) + 5*(hSiRB_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiRB->Write();


}

