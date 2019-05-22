{
	TCanvas *cDEE = new TCanvas("dE(plas) vs E(nai)","dE(plas) vs E(nai)",1400,800);
	cDEE->Divide(2,1);
	cDEE->cd(1);
	CalTreeESPRI->Draw("plasQL:naiQL>>hdEEL(1000,0,4000,1000,0,4000)","","colz");
	cDEE->cd(2);
	CalTreeESPRI->Draw("plasQR:naiQR>>hdEER(1000,0,4000,1000,0,4000)","","colz");

	
}
