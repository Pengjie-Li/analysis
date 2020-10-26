{
	TCanvas *cSBT = new TCanvas("SBTQTRaw","SBTQTRaw",1200,1000);
	cSBT->Divide(2,2);
	cSBT->cd(1);
	tree->Draw("SBT1TRaw[0]:SBT1QRaw[0]>>hSBT10(1000,0,4000,1000,13500,14500)","Trig_DSB","colz");
	cSBT->cd(2);
	tree->Draw("SBT1TRaw[1]:SBT1QRaw[1]>>hSBT11(1000,0,4000,1000,13500,14500)","Trig_DSB","colz");
	cSBT->cd(3);
	tree->Draw("SBT2TRaw[0]:SBT2QRaw[0]>>hSBT20(1000,0,4000,1000,13500,14500)","Trig_DSB","colz");
	cSBT->cd(4);
	tree->Draw("SBT2TRaw[1]:SBT2QRaw[1]>>hSBT21(1000,0,4000,1000,13500,14500)","Trig_DSB","colz");
}
