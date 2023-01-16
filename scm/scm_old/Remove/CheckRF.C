{
	TCanvas *cRF=new TCanvas("cRF","cRF",800,800);
	cRF->Divide(6,6);
	TGraphErrors *gRF[32];

	TCanvas *cRF1=new TCanvas("cRF1","cRF1",800,800);
	cRF1->Divide(6,6);
	TGraphErrors *gRF1[32];
	
	TCanvas *cRF2=new TCanvas("cRF2","cRF2",800,800);
	cRF2->Divide(6,6);
	TGraphErrors *gRF2[32];
	
	//for(int i=0;i<32;i++)
	for(int i=0;i<32;i++)
	{
		cRF->cd(i+1);
		TGraphErrors *gRF[i]= (TGraphErrors*)gDirectory->Get(Form("lfgr%d",i));
		if(gRF[i]) gRF[i]->Draw("AP");


		cRF1->cd(i+1);
		TGraphErrors *gRF1[i]= (TGraphErrors*)gDirectory->Get(Form("lfregr%d",i));
		if(gRF1[i]) gRF1[i]->Draw("AP");

		cRF2->cd(i+1);
		TGraphErrors *gRF2[i]= (TGraphErrors*)gDirectory->Get(Form("lfreregr%d",i));
		if(gRF2[i]) gRF2[i]->Draw("AP");


	}



}
