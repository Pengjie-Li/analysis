{
	TCanvas *cF7Time = new TCanvas("cF7Time","cF7Time",1200,900);
	cF7Time->Divide(2,2);
	gPad->SetLogy();
	cF7Time->cd(1);
	gPad->SetLogy();
	tree->Draw("F7TRaw[0]>>F7TRaw0(500,30000,40000)");
	cF7Time->cd(2);
	gPad->SetLogy();
	tree->Draw("F7TRaw[1]>>F7TRaw1(500,30000,40000)");
	cF7Time->cd(3);
	gPad->SetLogy();
	tree->Draw("F7TCal[0]>>F7TCal0(400,400,800)");
	cF7Time->cd(4);
	gPad->SetLogy();
	tree->Draw("F7TCal[1]>>F7TCal1(400,400,800)");
}
