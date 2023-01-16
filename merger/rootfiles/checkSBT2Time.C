{
	TCanvas *cSBT2Time = new TCanvas("cSBT2Time","cSBT2Time",1200,900);
	cSBT2Time->Divide(2,2);
	gPad->SetLogy();
	cSBT2Time->cd(1);
	gPad->SetLogy();
	tree->Draw("SBT2TRaw[0]>>SBT2TRaw0(500,10000,18000)");
	cSBT2Time->cd(2);
	gPad->SetLogy();
	tree->Draw("SBT2TRaw[1]>>SBT2TRaw1(500,10000,18000)");
	cSBT2Time->cd(3);
	gPad->SetLogy();
	tree->Draw("SBT2TCal[0]>>SBT2TCal0(500,160,280)");
	cSBT2Time->cd(4);
	gPad->SetLogy();
	tree->Draw("SBT2TCal[1]>>SBT2TCal1(500,160,280)");
}
