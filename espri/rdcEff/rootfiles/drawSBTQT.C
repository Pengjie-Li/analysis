{
	TCanvas *cSBT1 = new TCanvas("SBT1QT","SBT1QT",900,900);
	tree->Draw("SBT1Q:SBT1T>>hSBT1(500,215,225,1000,0,2000)","Trig_DSB","colz");

	TCanvas *cSBT2 = new TCanvas("SBT2QT","SBT2QT",900,900);
	tree->Draw("SBT2Q:SBT2T>>hSBT2(500,215,225,1000,0,2000)","Trig_DSB","colz");

}
