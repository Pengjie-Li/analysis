{
	TString Trig_DSB = "Trig_DSB";
	TString Trig_BxESPRI = "Trig_BxESPRI";
	TString Trig_BxESPRIxTEL = "Trig_BxESPRIxTEL";

	TString gateL = "plasTRaw[0]>0&&plasTRaw[1]>0";
	TString gateR = "plasTRaw[2]>0&&plasTRaw[3]>0";

	//gateL = gateL +"&&"+Trig_BxESPRIxTEL;
	//gateR = gateR +"&&"+Trig_BxESPRIxTEL;

	TCanvas *c1 = new TCanvas(" plasTdiff vs Y  "," plasTdiff vs Y  ",1700,800);	
	c1->Divide(2,1);
	c1->cd(1);
	tree->Draw("(rdcY[0]-227.5):(plasTCal[0]-plasTCal[1])>>hLeft(100,-10,10,100,-250,250)",gateL,"colz");

	c1->cd(2);
	tree->Draw("(rdcY[1]-227.5):(plasTCal[2]-plasTCal[3])>>hRight(100,-10,10,100,-250,250)",gateR,"colz");
}


