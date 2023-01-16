
void findpeaks()
{
// get TH2F and make projection on strip id
// find peaks and fit

// Open input files
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int runnum=596;

	TString inputname=Form("./analysedrootfiles/run0%d_analysed_v1.root",runnum);
	//cout<<"inputname"<<inputname<<endl;
	TFile *f = new TFile(inputname,"UPDATE");

        TH2F * hSiF = (TH2F*)gDirectory->Get("hSiLFCal")->Clone("hSiLFCal");
        TH2F * hSiB = (TH2F*)gDirectory->Get("hSiLBCal")->Clone("hSiLBCal");
	//hSiLFCal->Draw("colz");
	//hSiLBCal->Draw("colz");


	TCanvas *Front=new TCanvas("Front","Front",800,800);
	TCanvas *Back=new TCanvas("Back","Back",800,800);
	TCanvas *SiF16=new TCanvas("SiF16","SiF16",800,800);
	TCanvas *SiF32=new TCanvas("SiF32","SiF32",800,800);
	TCanvas *SiB16=new TCanvas("SiB16","SiB16",800,800);
	TCanvas *SiB32=new TCanvas("SiB32","SiB32",800,800);

	SiF16->Divide(4,4);
	SiF32->Divide(4,4);
	SiB16->Divide(4,4);
	SiB32->Divide(4,4);

	TH1D *hSiF1D=hSiF->ProjectionY();
	Front->cd();
	hSiF1D->Draw();
	TH1D *hSiB1D=hSiB->ProjectionY();
	Back->cd();
	hSiB1D->Draw();

	double SiFPeak=0;
	double SiBPeak=0;
	double SiFSigma=0;
	double SiBSigma=0;

	search_peaks(hSiF1D,SiFPeak,SiFSigma);
	search_peaks(hSiB1D,SiBPeak,SiBSigma);


        //hSiF->GetYaxis()->SetRangeUser(SiFPeak-3*SiFSigma,SiFPeak+3*SiFSigma);
        //hSiB->GetYaxis()->SetRangeUser(SiBPeak-3*SiBSigma,SiBPeak+3*SiBSigma);

	TH1D *hSiFstrip[32];
	TH1D *hSiBstrip[32];
	double SiFpeak[32]={0};
	double SiFsigma[32]={0};
	double SiBpeak[32]={0};
	double SiBsigma[32]={0};
	
	for(int id=0;id<32;id++)
	{
		hSiFstrip[id] = hSiF->ProjectionY(Form("hSiFstrip%d",id),id,id,"");
		hSiFstrip[id]->SetName(Form("hSiFstrip%d",id));
		hSiFstrip[id]->SetTitle(Form("hSiFstrip%d",id));
		hSiFstrip[id]->Rebin();
                //hSiFstrip[id]->SetAxisRange(SiFPeak-10*SiFSigma,SiFPeak+10*SiFSigma,"X");

		//hSiFstrip[id]->GetXaxis()->SetLimits(SiFPeak-3*SiFSigma,SiFPeak+3*SiFSigma);
		if(id<16) SiF16->cd(id+1);
		else SiF32->cd(id+1-16);
		hSiFstrip[id]->Draw();
		search_peaks(hSiFstrip[id],SiFpeak[id],SiFsigma[id]);
		gPad->Modified();
		gPad->Update();

		hSiBstrip[id] = hSiB->ProjectionY(Form("hSiBstrip%d",id),id,id,"");
		hSiBstrip[id]->SetName(Form("hSiBstrip%d",id));
		hSiBstrip[id]->SetTitle(Form("hSiBstrip%d",id));
		if(id<16) SiB16->cd(id+1);
		else SiB32->cd(id+1-16);
		hSiBstrip[id]->Draw();
		search_peaks(hSiBstrip[id],SiBpeak[id],SiBsigma[id]);
		gPad->Modified();
		gPad->Update();



	}




}

void search_peaks(TH1D *temp,double &peak,double &sigma)
{
     double estimate_peak_sigma=100;
     TSpectrum *s = new TSpectrum(5,5);// (Number of peaks, sigma)
     Int_t nfound = s->Search(temp,estimate_peak_sigma,"",0.1); // histo_name, peak_sigma,"",threshold_percentage
     //Int_t nfound = s->Search(temp,estimate_peak_sigma,"nobackground new",0.1); // histo_name, peak_sigma,"",threshold_percentage
     //Int_t nfound = s->Search(temp,estimate_peak_sigma,"",0.05); // histo_name, peak_sigma,"",threshold_percentage
     cout<<"how many peaks found "<<nfound<<endl;
 

     Int_t npeaks = 0;
     Float_t *xpeaks = s->GetPositionX();
     //Double_t *xpeaks = s->GetPositionX();
 
     Double_t par[15]={0};
     // fit parameter
     Double_t fpar[15]={0};
 
     for (int p=0;p<nfound;p++) {
         Double_t xp = xpeaks[p];
         Int_t bin = temp->GetXaxis()->FindBin(xp);
         Double_t yp = temp->GetBinContent(bin);
 
         par[3*npeaks+0] = yp;
         par[3*npeaks+1] = xp;
         //par[3*npeaks+2] = estimate_peak_sigma>ratio*estimate_peak_sigma?estimate_peak_sigma:ratio*estimate_peak_sigma;
         par[3*npeaks+2] = estimate_peak_sigma;
         cout<<"npeaks="<<npeaks<<" yp="<<yp<<" xp="<<xp<<endl;
         npeaks++;
     }
     printf("Found %d useful peaks to fit\n",npeaks);
     printf("Now fitting: Be patient\n");
 
 
     // range of f needed to be adjusted
     int afr1=5;
     int abr1=20;

     double fr1=par[1]-afr1*par[2];
     double br1=par[1]+abr1*par[2];
 
 
     TF1 *peak1 = new TF1("peak1","gaus(0)",fr1,br1);
     peak1->SetParameters(&par[0]);
     peak1->SetNpx(2000);
     temp->Fit(peak1,"R");
     peak1->GetParameters(&fpar[0]);
     peak1->Draw("same");
     peak=fpar[1];
     sigma=fpar[2];
 



}
