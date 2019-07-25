{
	TCanvas *c1 = new TCanvas("Beam Line Plastic","Beam Line Plastic",900,900);	
	c1->Divide(2,2);
	c1->cd(1);
	gPad->SetLogy();
	tree->Draw("F3_Time>>hF3(100,500,600)");

	c1->cd(2);
	gPad->SetLogy();
	tree->Draw("F7_Time>>hF7(100,500,600)");

	c1->cd(3);
	gPad->SetLogy();
	tree->Draw("F13_Time>>hF13(100,200,250)");

	c1->cd(4);
	gPad->SetLogy();
	tree->Draw("SBV_Time>>hSBV(100,200,250)");
}
