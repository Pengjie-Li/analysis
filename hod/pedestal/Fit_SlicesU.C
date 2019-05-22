void Fit_SlicesU()
{
	TH2F * h2d = (TH2F*)gDirectory->Get("hHodIdEnergyUpRaw")->Clone("h2d");
	h2d->GetXaxis()->SetTitle("Channel No.");
	h2d->GetYaxis()->SetTitle("QDC channel");
	TCanvas *c1 = new TCanvas("c1","c1",850,500);
	c1->cd();
	h2d->GetYaxis()->SetRangeUser(100,350);
	h2d->Draw("colz");

	TF1* foo = new TF1("foo","gaus",100,500);
	h2d->FitSlicesY(foo,0,40,0,"QNR",0);
	h2d_1->SetLineColor(1);
	h2d_1->SetLineWidth(2);
	TH1D *h2d_3 = new TH1D(*h2d_1);
	h2d_3->SetMarkerStyle(8);
	h2d_3->SetMarkerSize(.8);
	h2d_1->Draw("same");
	h2d_3->Draw("same");

	std::ofstream fout;
	Int_t run;
	cout << "Enter run number: ";
	cin >> run;
	fout.open(Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/hod/pedestal/txtfiles/HOD_up_%04d.txt",run));
	for(Int_t i = 0; i<40; i++){
		fout << i << "\t" << h2d_1->GetBinContent(i+1) << "\t" << h2d_2->GetBinContent(i+1) << "\t" << h2d_1->GetBinContent(i+1) + 5*(h2d_2->GetBinContent(i+1)) <<endl;
		cout << i << "\t" << h2d_1->GetBinContent(i+1) << "\t" << h2d_2->GetBinContent(i+1) << "\t" << h2d_1->GetBinContent(i+1) + 5*(h2d_2->GetBinContent(i+1)) <<endl;
	}
	fout.close();
}
