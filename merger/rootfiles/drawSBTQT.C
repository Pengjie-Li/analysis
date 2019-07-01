{
	TCanvas *cSBT1 = new TCanvas("SBT1QT","SBT1QT",900,900);
	tree->Draw("SBT1T:SBT1Q>>(1000,0,2000,500,215,225)","Trig_DSB","colz");

	TCanvas *cSBT2 = new TCanvas("SBT2QT","SBT2QT",900,900);
	tree->Draw("SBT2T:SBT2Q>>(1000,0,2000,500,215,225)","Trig_DSB","colz");

}
