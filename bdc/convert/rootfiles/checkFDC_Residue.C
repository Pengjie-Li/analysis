{
	TCanvas *cFDCResidue = new TCanvas("cFDCResidue","cFDCResidue",1200,600);
	cFDCResidue->Divide(4,2);
	for(int i=0;i<8;i++){
		cFDCResidue->cd(i+1);
		CalTreeFDC->Draw(Form("FDC0_Track_dXY[%d]>>hFDCResidue%d(100,-1,1)",i,i));
	}
}
