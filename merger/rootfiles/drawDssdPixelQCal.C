{
	TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
	cPad->Divide(2,2);
	cPad->cd(1);	
	tree->Draw(Form("dssdEnergyCal[0][%d]>>hLF%d_%d(100,4000,12000)",fid,fid,bid),Form("dssdEnergyCal[1][%d]>4",bid));
	cPad->cd(2);	
	tree->Draw(Form("dssdEnergyCal[1][%d]>>hLB%d_%d(100,4000,12000)",bid,fid,bid),Form("dssdEnergyCal[0][%d]>4",fid));
	cPad->cd(3);	

	tree->Draw(Form("dssdEnergyCal[2][%d]>>hRF%d_%d(100,4000,12000)",fid,fid,bid),Form("dssdEnergyCal[3][%d]>4",bid));
	cPad->cd(4);	
	tree->Draw(Form("dssdEnergyCal[3][%d]>>hRB%d_%d(100,4000,12000)",bid,fid,bid),Form("dssdEnergyCal[2][%d]>4",fid));
}
