{
	TCanvas *cDEE = new TCanvas("dE(plas) vs E(nai)","dE(plas) vs E(nai)",1400,800);
	tree->Draw("espriPlasDeltaE:espriNaiEnergy>>hdEE(1000,0,200,1000,0,40)","","colz");

	
}
