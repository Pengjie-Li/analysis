{
	TCanvas *cPos = new TCanvas("cPos","cPos",1000,500);
	cPos->Divide(2,1);
	cPos->cd(1);
	tree->Draw("0.5*(SBT1TCal[0]+SBT1TCal[1]):SBT1TCal[0]-SBT1TCal[1]>>Before(1000,0,4000,1000,215,230)","Trig_DSB","colz");
	cPos->cd(2);
	tree->Draw("SBT1T:SBT1TCal[0]-SBT1TCal[1]>>After(1000,0,4000,1000,215,230)","Trig_DSB","colz");
}
