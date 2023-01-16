{
	TCanvas *cF3Time = new TCanvas("cF3Time","cF3Time",1200,900);
	cF3Time->Divide(2,2);
	gPad->SetLogy();
	cF3Time->cd(1);
	gPad->SetLogy();
	tree->Draw("F3TRaw[0]>>F3TRaw0(500,30000,40000)");
	cF3Time->cd(2);
	gPad->SetLogy();
	tree->Draw("F3TRaw[1]>>F3TRaw1(500,30000,40000)");
	cF3Time->cd(3);
	gPad->SetLogy();
	tree->Draw("F3TCal[0]>>F3TCal0(400,400,800)");
	cF3Time->cd(4);
	gPad->SetLogy();
	tree->Draw("F3TCal[1]>>F3TCal1(400,400,800)");
}
