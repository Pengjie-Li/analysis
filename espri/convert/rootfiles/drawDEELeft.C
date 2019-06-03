{
	gROOT->ProcessLine(".x leftPlastic.C");
	TCanvas *cDEE = new TCanvas("dE(plas) vs E(nai)","dE(plas) vs E(nai)",1400,800);
	CalTreeESPRI->Draw("plasQ[0]:naiQ[0]>>hdEELeft(1000,0,150,1000,0,35)","leftPlastic","colz");
	
}
