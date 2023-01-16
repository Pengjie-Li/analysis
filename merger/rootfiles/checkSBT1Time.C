{
	TCanvas *cSBT1Time = new TCanvas("cSBT1Time","cSBT1Time",1200,900);
	cSBT1Time->Divide(2,2);
	gPad->SetLogy();
	cSBT1Time->cd(1);
	gPad->SetLogy();
	tree->Draw("SBT1TRaw[0]>>SBT1TRaw0(500,10000,18000)");
	cSBT1Time->cd(2);
	gPad->SetLogy();
	tree->Draw("SBT1TRaw[1]>>SBT1TRaw1(500,10000,18000)");
	cSBT1Time->cd(3);
	gPad->SetLogy();
	tree->Draw("SBT1TCal[0]>>SBT1TCal0(500,160,280)");
	cSBT1Time->cd(4);
	gPad->SetLogy();
	tree->Draw("SBT1TCal[1]>>SBT1TCal1(500,160,280)");
}
