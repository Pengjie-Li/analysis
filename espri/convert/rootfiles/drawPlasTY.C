{
	TCanvas *c1 = new TCanvas(" plasTdiff vs Y  "," plasTdiff vs Y  ",1700,800);	
	c1->Divide(2,1);
	c1->cd(1);
	CalTreeESPRI->Draw("(rdcY[0]-227.5):(plasTCal[0]-plasTCal[1])>>hLeft(100,-10,10,100,-250,250)","plasTRaw[0]>0&&plasTRaw[1]>0","colz");

	c1->cd(2);
	CalTreeESPRI->Draw("(rdcY[1]-227.5):(plasTCal[2]-plasTCal[3])>>hRight(100,-10,10,100,-250,250)","plasTRaw[2]>0&&plasTRaw[3]>0","colz");
}


