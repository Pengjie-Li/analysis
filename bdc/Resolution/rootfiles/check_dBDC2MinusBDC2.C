{
	TCanvas *c_dBDC2MinusBDC2 = new TCanvas("c_dBDC2MinusBDC2","c_dBDC2MinusBDC2",1400,600);
	c_dBDC2MinusBDC2->Divide(2,1);
	c_dBDC2MinusBDC2->cd(1);
	tree->Draw("dBDC2_X-BDC2_X>>hX(100,-5,5)");

	c_dBDC2MinusBDC2->cd(2);
	tree->Draw("dBDC2_Y-BDC2_Y>>hY(100,-5,5)");



}
