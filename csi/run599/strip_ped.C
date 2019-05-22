
void Ped_SiLF();
void Ped_SiLB();
void Ped_SiRF();
void Ped_SiRB();
void strip_ped()
{
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);



	TString inputname="./rootfiles/run0599_Beamv8.root";
	//cout<<"inputname"<<inputname<<endl;
	TFile *f = new TFile(inputname,"UPDATE");

	Ped_SiLF();
	Ped_SiLB();
	Ped_SiRF();
	Ped_SiRB();



}

void Ped_SiLF()
{

        TH2F * hSiLFped = (TH2F*)gDirectory->Get("hSiLF")->Clone("hSiLFped");
        hSiLFped->GetXaxis()->SetTitle("Channel No.");
        hSiLFped->GetYaxis()->SetTitle("ADC channel");
        TCanvas *cSiLFped = new TCanvas("cSiLFped","cSiLFped",850,500);
        cSiLFped->cd();
        hSiLFped->GetYaxis()->SetRangeUser(0,300);
        gPad->SetLogz();
        hSiLFped->Draw("colz");

        TF1* foo = new TF1("foo","gaus",0,300);
        hSiLFped->FitSlicesY(foo,0,32,0,"QNR",0);
        hSiLFped_1->SetLineColor(1);
        hSiLFped_1->SetLineWidth(2);
        TH1D *hSiLFped_3 = new TH1D(*hSiLFped_1);
        hSiLFped_3->SetMarkerStyle(8);
        hSiLFped_3->SetMarkerSize(.8);
        hSiLFped_1->Draw("same");
        hSiLFped_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="ped_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<0 << "\t" << i << "\t" << hSiLFped_1->GetBinContent(i+1) << "\t" << hSiLFped_2->GetBinContent(i+1) << "\t" << hSiLFped_1->GetBinContent(i+1) + 5*(hSiLFped_2->GetBinContent(i+1)) <<endl;
                cout <<0 << "\t" << i << "\t" << hSiLFped_1->GetBinContent(i+1) << "\t" << hSiLFped_2->GetBinContent(i+1) << "\t" << hSiLFped_1->GetBinContent(i+1) + 5*(hSiLFped_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiLFped->Write();
}

void Ped_SiLB()
{

        TH2F * hSiLBped = (TH2F*)gDirectory->Get("hSiLB")->Clone("hSiLBped");
        hSiLBped->GetXaxis()->SetTitle("Channel No.");
        hSiLBped->GetYaxis()->SetTitle("ADC channel");
        TCanvas *cSiLBped = new TCanvas("cSiLBped","cSiLBped",850,500);
        cSiLBped->cd();
        hSiLBped->GetYaxis()->SetRangeUser(0,200);
        gPad->SetLogz();
        hSiLBped->Draw("colz");

        TF1* foo = new TF1("foo","gaus",0,200);
        hSiLBped->FitSlicesY(foo,0,32,0,"QNR",0);
        hSiLBped_1->SetLineColor(1);
        hSiLBped_1->SetLineWidth(2);
        TH1D *hSiLBped_3 = new TH1D(*hSiLBped_1);
        hSiLBped_3->SetMarkerStyle(8);
        hSiLBped_3->SetMarkerSize(.8);
        hSiLBped_1->Draw("same");
        hSiLBped_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="ped_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<1 << "\t" << i << "\t" << hSiLBped_1->GetBinContent(i+1) << "\t" << hSiLBped_2->GetBinContent(i+1) << "\t" << hSiLBped_1->GetBinContent(i+1) + 5*(hSiLBped_2->GetBinContent(i+1)) <<endl;
                cout <<1 << "\t" << i << "\t" << hSiLBped_1->GetBinContent(i+1) << "\t" << hSiLBped_2->GetBinContent(i+1) << "\t" << hSiLBped_1->GetBinContent(i+1) + 5*(hSiLBped_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiLBped->Write();
	
}
void Ped_SiRF()
{

        TH2F * hSiRFped = (TH2F*)gDirectory->Get("hSiRF")->Clone("hSiRFped");
        hSiRFped->GetXaxis()->SetTitle("Channel No.");
        hSiRFped->GetYaxis()->SetTitle("ADC channel");
        TCanvas *cSiRFped = new TCanvas("cSiRFped","cSiRFped",850,500);
        cSiRFped->cd();
        hSiRFped->GetYaxis()->SetRangeUser(0,500);
        gPad->SetLogz();
        hSiRFped->Draw("colz");

        TF1* foo = new TF1("foo","gaus",0,500);
        hSiRFped->FitSlicesY(foo,0,32,0,"QNR",0);
        hSiRFped_1->SetLineColor(1);
        hSiRFped_1->SetLineWidth(2);
        TH1D *hSiRFped_3 = new TH1D(*hSiRFped_1);
        hSiRFped_3->SetMarkerStyle(8);
        hSiRFped_3->SetMarkerSize(.8);
        hSiRFped_1->Draw("same");
        hSiRFped_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="ped_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout << 2 << "\t" <<i << "\t" << hSiRFped_1->GetBinContent(i+1) << "\t" << hSiRFped_2->GetBinContent(i+1) << "\t" << hSiRFped_1->GetBinContent(i+1) + 5*(hSiRFped_2->GetBinContent(i+1)) <<endl;
                cout << 2 << "\t" <<i << "\t" << hSiRFped_1->GetBinContent(i+1) << "\t" << hSiRFped_2->GetBinContent(i+1) << "\t" << hSiRFped_1->GetBinContent(i+1) + 5*(hSiRFped_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	
	cSiRFped->Write();
}

void Ped_SiRB()
{

        TH2F * hSiRBped = (TH2F*)gDirectory->Get("hSiRB")->Clone("hSiRBped");
        hSiRBped->GetXaxis()->SetTitle("Channel No.");
        hSiRBped->GetYaxis()->SetTitle("ADC channel");
        TCanvas *cSiRBped = new TCanvas("cSiRBped","cSiRBped",850,500);
        cSiRBped->cd();
        hSiRBped->GetYaxis()->SetRangeUser(0,500);
        gPad->SetLogz();
        hSiRBped->Draw("colz");

        TF1* foo = new TF1("foo","gaus",0,500);
        hSiRBped->FitSlicesY(foo,0,32,0,"QNR",0);
        hSiRBped_1->SetLineColor(1);
        hSiRBped_1->SetLineWidth(2);
        TH1D *hSiRBped_3 = new TH1D(*hSiRBped_1);
        hSiRBped_3->SetMarkerStyle(8);
        hSiRBped_3->SetMarkerSize(.8);
        hSiRBped_1->Draw("same");
        hSiRBped_3->Draw("same");

	TString outputname=gFile->GetName();
	outputname.ReplaceAll("rootfiles","");
	outputname.ReplaceAll("root","txt");
	outputname.ReplaceAll("./","");
	outputname.ReplaceAll("/","");
	outputname="ped_"+outputname;
	cout<<outputname<<endl;

	ofstream fout(outputname,ios_base::app | ios_base::out);
        for(Int_t i = 0; i<32; i++){
                fout <<3 << "\t" << i << "\t" << hSiRBped_1->GetBinContent(i+1) << "\t" << hSiRBped_2->GetBinContent(i+1) << "\t" << hSiRBped_1->GetBinContent(i+1) + 5*(hSiRBped_2->GetBinContent(i+1)) <<endl;
                cout <<3 << "\t" << i << "\t" << hSiRBped_1->GetBinContent(i+1) << "\t" << hSiRBped_2->GetBinContent(i+1) << "\t" << hSiRBped_1->GetBinContent(i+1) + 5*(hSiRBped_2->GetBinContent(i+1)) <<endl;
        }
        fout.close();

	cSiRBped->Write();
	
}
