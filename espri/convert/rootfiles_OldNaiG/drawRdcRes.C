{
	TCanvas *cLeft = new TCanvas("Left Residue","Left Residue",800,700);
	cLeft->Divide(3,3);
	for(int i=0;i<7;i++){
		cLeft->cd(i+1);
		CalTreeESPRI->Draw(Form("rdcRes[0][%d]>>hLeftRes%d(100,-1.4,1.4)",i,i));
	}

	TCanvas *cRight = new TCanvas("Right Residue","Right Residue",800,700);
	cRight->Divide(3,3);
	for(int i=0;i<7;i++){
		cRight->cd(i+1);
		CalTreeESPRI->Draw(Form("rdcRes[1][%d]>>hRightRes%d(100,-1.4,1.4)",i,i));
	}

	
}
