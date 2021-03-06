{

	double offset = -2.8;
	double gain = 0.3;// run 598
	//double gain = 0.43;// run 596
	TString gate = "Trig_DSB&&Beam";
	//TString gate = "";
	
	TCanvas *cPos = new TCanvas("cPos","cPos",1200,1000);
	cPos->Divide(2,3);
	cPos->cd(1);
	tree->Draw("0.5*(SBT2TCal[0]+SBT2TCal[1]):SBT2TCal[0]-SBT2TCal[1]>>hTDiffBefore(200,-6,-1,1000,215,230)",gate,"colz");
	cPos->cd(2);
	tree->Draw(Form("0.5*(SBT2TCal[0]+SBT2TCal[1])+%f*(SBT2TCal[0]-(SBT2TCal[1]+%f)):(SBT2TCal[0]-(SBT2TCal[1]+%f))>>hTDiffAfter(200,-2.5,2.5,1000,215,230)",gain,offset,offset),gate,"colz");
	//tree->Draw(Form("0.5*(SBT2TCal[0]+SBT2TCal[1])+%f*(SBT2TCal[0]-(SBT2TCal[1]+%f)):(SBT2TCal[0]-(SBT2TCal[1]+%f))>>hTDiffAfter(200,-2.5,2.5,100,220,221.5)",gain,offset,offset),gate,"colz");
	cPos->cd(3);
	tree->Draw("0.5*(SBT2TCal[0]+SBT2TCal[1]):log(SBT2QCal[0]/SBT2QCal[1])>>hQDiffBefore(500,-1,1,1000,215,230)",gate,"colz");
	cPos->cd(4);
	tree->Draw(Form("0.5*(SBT2TCal[0]+SBT2TCal[1])+%f*(SBT2TCal[0]-(SBT2TCal[1]+%f)):log(SBT2QCal[0]/SBT2QCal[1])>>hQDiffAfter(500,-1,1,1000,215,230)",gain,offset),gate,"colz");
	//tree->Draw(Form("0.5*(SBT2TCal[0]+SBT2TCal[1])+%f*(SBT2TCal[0]-(SBT2TCal[1]+%f)):log(SBT2QCal[0]/SBT2QCal[1])>>hQDiffAfter(500,-1,1,100,220,221.5)",gain,offset),gate,"colz");
	cPos->cd(5);
	gPad->SetLogy();
	tree->Draw("0.5*(SBT2TCal[0]+SBT2TCal[1])>>hBefore(400,218,224)",gate);
	TH1F *hBefore = (TH1F *)gDirectory->Get("hBefore");
	hBefore->Fit("gaus");
	cPos->cd(6);
	gPad->SetLogy();
	tree->Draw(Form("0.5*(SBT2TCal[0]+SBT2TCal[1])+%f*(SBT2TCal[0]-(SBT2TCal[1]+%f))>>hAfter(400,218,224)",gain,offset,offset),gate);
	TH1F *hAfter = (TH1F *)gDirectory->Get("hAfter");
	hAfter->Fit("gaus");
	



}
