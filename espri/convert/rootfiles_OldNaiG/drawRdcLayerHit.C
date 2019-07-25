{
CalTreeESPRI->Draw("rdcPlaneNHit[4]>>(10,0.5,10.5)","")
	TCanvas *cLeft = new TCanvas("Left LayerHit","Left LayerHit",800,700);
	cLeft->Divide(3,3);
	for(int i=0;i<7;i++){
		cLeft->cd(i+1);
		CalTreeESPRI->Draw(Form("rdcPlaneNHit[%d]>>hLeftHit%d(10,0.5,10.5)",i,i));
	}

	TCanvas *cRight = new TCanvas("Right LayerHit","Right LayerHit",800,700);
	cRight->Divide(3,3);
	for(int i=0;i<7;i++){
		cRight->cd(i+1);
		CalTreeESPRI->Draw(Form("rdcPlaneNHit[%d]>>hRightHit%d(10,0.5,10.5)",i+7,i+7));
	}

	
}
