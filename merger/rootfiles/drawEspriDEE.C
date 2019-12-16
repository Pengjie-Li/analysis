{
	int isCheck = 0;
	TCanvas *cDEE = new TCanvas("dE(plas) vs E(nai)","dE(plas) vs E(nai)",800,800);
	tree->Draw("espriPlasE:espriNaiE>>hdEE(1000,0,200,1000,0,40)","","colz");
	gROOT->ProcessLine(".x cutProtonBe14.C");
	if(isCheck){
		TCanvas *cCheck = new TCanvas("cCheck","cCheck",1600,800);
		cCheck->Divide(2,1);
		cCheck->cd(1);
		tree->Draw("plasQ[0]:naiQ[0]>>hdEEL(1000,0,200,1000,0,40)","","colz");
		gROOT->ProcessLine(".x cutProtonBe14.C");
		cCheck->cd(2);
		tree->Draw("plasQ[1]:naiQ[1]>>hdEER(1000,0,200,1000,0,40)","","colz");
		gROOT->ProcessLine(".x cutProtonBe14.C");
	}

	
}
