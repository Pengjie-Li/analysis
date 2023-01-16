{
	TCanvas *cSBVTime = new TCanvas("cSBVTime","cSBVTime",1200,900);
	cSBVTime->Divide(2,2);
	gPad->SetLogy();
	cSBVTime->cd(1);
	gPad->SetLogy();
	tree->Draw("SBVTRaw[0]>>SBVTRaw0(500,10000,25000)");
	cSBVTime->cd(2);
	gPad->SetLogy();
	tree->Draw("SBVTRaw[1]>>SBVTRaw1(500,10000,25000)");
	cSBVTime->cd(3);
	gPad->SetLogy();
	tree->Draw("SBVTCal[0]>>SBVTCal0(500,150,350)");
	cSBVTime->cd(4);
	gPad->SetLogy();
	tree->Draw("SBVTCal[1]>>SBVTCal1(500,150,350)");
}
