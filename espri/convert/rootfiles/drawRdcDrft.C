{
	TCanvas *cLeft = new TCanvas("Left  Drift","Left  Drift",800,700);
	cLeft->Divide(3,3);
	for(int i=0;i<7;i++){
		cLeft->cd(i+1);
		CalTreeESPRI->Draw(Form("abs(rdcDL[0][%d])>>hLeftDrf%d(100,0,14)",i,i));
	}

	TCanvas *cRight = new TCanvas("Right  Drift","Right  Drift",800,700);
	cRight->Divide(3,3);
	for(int i=0;i<7;i++){
		cRight->cd(i+1);
		CalTreeESPRI->Draw(Form("abs(rdcDL[1][%d])>>hRightDrf%d(100,0,14)",i,i));
	}

	
}
