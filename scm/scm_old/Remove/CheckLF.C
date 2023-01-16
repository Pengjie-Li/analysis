{
	TCanvas *cLF=new TCanvas("cLF","cLF",800,800);
	cLF->Divide(6,6);
	TGraphErrors *gLF[32];

	TCanvas *cLF1=new TCanvas("cLF1","cLF1",800,800);
	cLF1->Divide(6,6);
	TGraphErrors *gLF1[32];
	
	TCanvas *cLF2=new TCanvas("cLF2","cLF2",800,800);
	cLF2->Divide(6,6);
	TGraphErrors *gLF2[32];
	
	//for(int i=0;i<32;i++)
	for(int i=0;i<32;i++)
	{
		cLF->cd(i+1);
		TGraphErrors *gLF[i]= (TGraphErrors*)gDirectory->Get(Form("lfgr%d",i));
		if(gLF[i]) gLF[i]->Draw("AP");


		cLF1->cd(i+1);
		TGraphErrors *gLF1[i]= (TGraphErrors*)gDirectory->Get(Form("lfregr%d",i));
		if(gLF1[i]) gLF1[i]->Draw("AP");

		cLF2->cd(i+1);
		TGraphErrors *gLF2[i]= (TGraphErrors*)gDirectory->Get(Form("lfreregr%d",i));
		if(gLF2[i]) gLF2[i]->Draw("AP");


	}



}
