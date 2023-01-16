{
	
	gROOT->Reset();
	TF1 *fit = new TF1("fit","gaus",0,250);
	fit->ReleaseParameter(0);
	fit->ReleaseParameter(1);
	fit->ReleaseParameter(2);
	//gMinuit->mncler();
	TCanvas *cPed = new TCanvas("cPed","cPed",1500,800);
	cPed->Divide(2,2);
	cPed->cd(1);
	CalTreeESPRI->Draw("plasQRaw[0]>>hPed0(1500,100,250)");
	TH1F *hPed0 = (TH1F*)gDirectory->Get("hPed0");
	//fit->SetParameter(0,180e3);
	fit->SetParameter(1,119);
	fit->SetParameter(2,1.5);
	hPed0->Fit(fit);

	cPed->cd(2);
	TF1 *fit = new TF1("fit","gaus",0,250);
	CalTreeESPRI->Draw("plasQRaw[1]>>hPed1(1500,100,250)");
	TH1F *hPed1 = (TH1F*)gDirectory->Get("hPed1");
	fit->SetParameter(1,140);
	fit->SetParameter(2,2);
	hPed1->Fit(fit);

	cPed->cd(3);
	TF1 *fit = new TF1("fit","gaus",0,250);
	CalTreeESPRI->Draw("plasQRaw[2]>>hPed2(1500,100,250)");
	TH1F *hPed2 = (TH1F*)gDirectory->Get("hPed2");
	fit->SetParameter(1,136);
	fit->SetParameter(2,2);
	hPed2->Fit(fit);

	cPed->cd(4);
	TF1 *fit = new TF1("fit","gaus",0,250);
	CalTreeESPRI->Draw("plasQRaw[3]>>hPed3(1500,50,200)");
	TH1F *hPed3 = (TH1F*)gDirectory->Get("hPed3");
	fit->SetParameter(1,136);
	fit->SetParameter(2,2);
	hPed3->Fit(fit);





	//CalTreeESPRI->Draw("plasQRaw[1]>>hPed1(250,0,250)");
}
