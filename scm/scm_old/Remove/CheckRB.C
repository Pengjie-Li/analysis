{
	TCanvas *cRB=new TCanvas("cRB","cRB",800,800);
	cRB->Divide(6,6);
	TGraphErrors *gRB[32];

	TCanvas *cRB1=new TCanvas("cRB1","cRB1",800,800);
	cRB1->Divide(6,6);
	TGraphErrors *gRB1[32];
	
	TCanvas *cRB2=new TCanvas("cRB2","cRB2",800,800);
	cRB2->Divide(6,6);
	TGraphErrors *gRB2[32];
	
	//for(int i=0;i<32;i++)
	for(int i=0;i<32;i++)
	{
		cRB->cd(i+1);
		TGraphErrors *gRB[i]= (TGraphErrors*)gDirectory->Get(Form("lfgr%d",i));
		if(gRB[i]) gRB[i]->Draw("AP");


		cRB1->cd(i+1);
		TGraphErrors *gRB1[i]= (TGraphErrors*)gDirectory->Get(Form("lfregr%d",i));
		if(gRB1[i]) gRB1[i]->Draw("AP");

		cRB2->cd(i+1);
		TGraphErrors *gRB2[i]= (TGraphErrors*)gDirectory->Get(Form("lfreregr%d",i));
		if(gRB2[i]) gRB2[i]->Draw("AP");


	}



}
