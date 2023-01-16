{
	TCanvas *cBDC1Residue = new TCanvas("cBDC1Residue","cBDC1Residue",1200,600);
	cBDC1Residue->Divide(4,2);
	for(int i=0;i<8;i++){
		cBDC1Residue->cd(i+1);
		CalTreeBDC->Draw(Form("BDC1_Track_dXY[%d]>>hBDC1Residue%d(100,-1,1)",i,i));
	}

	TCanvas *cBDC2Residue = new TCanvas("cBDC2Residue","cBDC2Residue",1200,600);
	cBDC2Residue->Divide(4,2);
	for(int i=0;i<8;i++){
		cBDC2Residue->cd(i+1);
		CalTreeBDC->Draw(Form("BDC2_Track_dXY[%d]>>hBDC2Residue%d(100,-1,1)",i,i));
	}

}
