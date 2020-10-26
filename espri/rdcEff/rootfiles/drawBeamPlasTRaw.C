{
	TCanvas *c1 = new TCanvas("Beam Line Plastic","Beam Line Plastic",900,900);	
	c1->Divide(4,2);
	//F3
	c1->cd(1);
	gPad->SetLogy();
	tree->Draw("F3TRaw[0]>>hF3_0(200,30000,40000)");
	c1->cd(2);
	gPad->SetLogy();
	tree->Draw("F3TRaw[1]>>hF3_1(200,30000,40000)");

	//F7
	c1->cd(3);
	gPad->SetLogy();
	tree->Draw("F7TRaw[0]>>hF7_0(200,30000,40000)");
	c1->cd(4);
	gPad->SetLogy();
	tree->Draw("F7TRaw[1]>>hF7_1(200,30000,40000)");

	//SBT1
	c1->cd(5);
	gPad->SetLogy();
	tree->Draw("SBT1TRaw[0]>>hSBT1_0(200,10000,20000)");
	c1->cd(6);
	gPad->SetLogy();
	tree->Draw("SBT1TRaw[1]>>hSBT1_1(200,10000,20000)");

	//SBT2
	c1->cd(7);
	gPad->SetLogy();
	tree->Draw("SBT2TRaw[0]>>hSBT2_0(200,10000,20000)");
	c1->cd(8);
	gPad->SetLogy();
	tree->Draw("SBT2TRaw[1]>>hSBT2_1(200,10000,20000)");

}
