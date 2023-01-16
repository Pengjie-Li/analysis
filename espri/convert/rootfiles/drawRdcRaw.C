{
	bool kWire = true;
	bool kTDC = false;

	if(kTDC){
		TCanvas *cLPlane = new TCanvas("cLPlane TDC","cLPlane TDC",800,700);
		cLPlane->Divide(3,3);
		for(int i=0;i<7;i++){
			cLPlane->cd(i+1);
			CalTreeESPRI->Draw(Form("rdcTDC>>hLTDC%d(1500,-1000,500)",i),Form("rdcPlaneID==(17+%d)",i));
		}

		TCanvas *cRPlane = new TCanvas("cRPlane TDC","cRPlane TDC",800,700);
		cRPlane->Divide(3,3);
		for(int i=0;i<7;i++){
			cRPlane->cd(i+1);
			CalTreeESPRI->Draw(Form("rdcTDC>>hRTDC%d(1500,-1000,500)",i),Form("rdcPlaneID==(24+%d)",i));
		}
	}

	if(kWire){
		TCanvas *cLTDCWireID = new TCanvas("cLTDCWireID TDC vs WireID","cLTDCWireID TDC vs WireID",800,700);
		cLTDCWireID->Divide(3,3);
		for(int i=0;i<7;i++){
			cLTDCWireID->cd(i+1);
			CalTreeESPRI->Draw(Form("rdcWireID:rdcTDC>>hLTDC%d(1500,-1000,500,32,0.5,32.5)",i),Form("rdcPlaneID==(17+%d)",i),"colz");
		}

		TCanvas *cRTDCWireID = new TCanvas("cRTDCWireID TDC","cRTDCWireID TDC",800,700);
		cRTDCWireID->Divide(3,3);
		for(int i=0;i<7;i++){
			cRTDCWireID->cd(i+1);
			CalTreeESPRI->Draw(Form("rdcWireID:rdcTDC>>hRTDC%d(1500,-1000,500,32,0.5,32.5)",i),Form("rdcPlaneID==(24+%d)",i),"colz");
		}
	}


}
