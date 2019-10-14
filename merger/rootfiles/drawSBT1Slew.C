{
	TCanvas *cSlew = new TCanvas("cSlew","cSlew",1000,500);
	cSlew->Divide(2,1);
	cSlew->cd(1);
	tree->Draw("0.5*(SBT1TCal[0]+SBT1TCal[1]):SBT1Q>>Before(1000,0,4000,1000,215,230)","Trig_DSB","colz");
	cSlew->cd(2);
	tree->Draw("SBT1TSlew:SBT1Q>>After(1000,0,4000,1000,215,230)","Trig_DSB","colz");
}
