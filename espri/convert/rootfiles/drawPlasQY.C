{
	TCanvas *c1 = new TCanvas(" plasQdiff vs Y  "," plasQdiff vs Y  ",1700,800);	
	c1->Divide(2,1);
	c1->cd(1);
	CalTreeESPRI->Draw("rdcY[0]-227.5:(TMath::Log(plasQCal[0])-TMath::Log(plasQCal[1]))>>hLeft(1000,-3,3,1000,-250,250)","","colz");
	c1->cd(2);
	CalTreeESPRI->Draw("rdcY[1]-227.5:(TMath::Log(plasQCal[2])-TMath::Log(plasQCal[3]))>>hRight(1000,-3,3,1000,-250,250)","","colz");

}
