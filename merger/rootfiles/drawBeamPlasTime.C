{
	TCanvas *c1 = new TCanvas("Beam Line Plastic","Beam Line Plastic",900,900);	
	c1->Divide(2,2);
	c1->cd(1);
	gPad->SetLogy();
	tree->Draw("F3T>>hF3(500,450,650)");

	c1->cd(2);
	gPad->SetLogy();
	tree->Draw("F7T>>hF7(500,450,650)");

	c1->cd(3);
	gPad->SetLogy();
	tree->Draw("F13T>>hF13(500,100,300)");

	c1->cd(4);
	gPad->SetLogy();
	tree->Draw("SBVT>>hSBV(500,150,350)");
}
