{
	TCanvas *cSlew = new TCanvas("cSlew","cSlew",1000,500);
	cSlew->Divide(2,1);
	cSlew->cd(1);
	tree->Draw("0.5*(SBT2TCal[0]+SBT2TCal[1]):SBT2Q>>Before(1000,0,4000,1000,215,230)","Trig_DSB","colz");
	cSlew->cd(2);
	tree->Draw("SBT2TSlew:SBT2Q>>After(1000,0,4000,1000,215,230)","Trig_DSB","colz");
}
