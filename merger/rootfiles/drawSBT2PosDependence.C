{
	TCanvas *cPos = new TCanvas("cPos","cPos",1000,500);
	cPos->Divide(2,1);
	cPos->cd(1);
	tree->Draw("0.5*(SBT2TCal[0]+SBT2TCal[1]):SBT2TCal[0]-SBT2TCal[1]>>Before(200,-5,-1,1000,215,230)","Trig_DSB","colz");
	cPos->cd(2);
	tree->Draw("SBT2T:SBT2TCal[0]-SBT2TCal[1]>>After(200,-5,-1,1000,215,230)","Trig_DSB","colz");
}
