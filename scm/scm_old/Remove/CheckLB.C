{
	TCanvas *cLB=new TCanvas("cLB","cLB",800,800);
	cLB->Divide(6,6);
	TGraphErrors *gLB[32];

	TCanvas *cLB1=new TCanvas("cLB1","cLB1",800,800);
	cLB1->Divide(6,6);
	TGraphErrors *gLB1[32];
	
	TCanvas *cLB2=new TCanvas("cLB2","cLB2",800,800);
	cLB2->Divide(6,6);
	TGraphErrors *gLB2[32];
	
	//for(int i=0;i<32;i++)
	for(int i=0;i<32;i++)
	{
		cLB->cd(i+1);
		TGraphErrors *gLB[i]= (TGraphErrors*)gDirectory->Get(Form("lfgr%d",i));
		if(gLB[i]) gLB[i]->Draw("AP");


		cLB1->cd(i+1);
		TGraphErrors *gLB1[i]= (TGraphErrors*)gDirectory->Get(Form("lfregr%d",i));
		if(gLB1[i]) gLB1[i]->Draw("AP");

		cLB2->cd(i+1);
		TGraphErrors *gLB2[i]= (TGraphErrors*)gDirectory->Get(Form("lfreregr%d",i));
		if(gLB2[i]) gLB2[i]->Draw("AP");


	}



}
