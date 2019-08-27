{
	TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
	cPad->Divide(2,4);
	for (int i = 0; i < 7; ++i) {
		cPad->cd(i+1);
		tree->Draw(Form("csiEnergyCal[%d]>>hCsI%d(1000,10,700)",i,i));
	}
}
