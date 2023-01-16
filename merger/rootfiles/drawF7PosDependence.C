{

	double offset = 2.8;
	double gain = 1.1;// run 598
	//double gain = 0.43;// run 596
	TString gate = "Trig_DSB&&Beam";
	//TString gate = "";
	tree->SetAlias("f7t_slew","(0.5*(F7TCal[0]+F7TCal[1])-(-1.06072e-03*F7Q+1.15839e+00/sqrt(sqrt(sqrt(F7Q+92.5)))))+20");

	TCanvas *cPos = new TCanvas("cPos","cPos",1200,2000);
	cPos->Divide(2,3);
	cPos->cd(1);
	tree->Draw("f7t_slew:F7TCal[0]-F7TCal[1]>>hTDiffBefore(200,1.5,3.5,200,543,573)",gate,"colz");
	cPos->cd(2);
	tree->Draw(Form("f7t_slew+%f*(F7TCal[0]-(F7TCal[1]+%f)):(F7TCal[0]-(F7TCal[1]+%f))>>hTDiffAfter(200,-1,1,200,543,573)",gain,offset,offset),gate,"colz");
	cPos->cd(3);
	tree->Draw("f7t_slew:log(F7QCal[0]/F7QCal[1])>>hQDiffBefore(200,-1,1,200,543,573)",gate,"colz");
	cPos->cd(4);
	tree->Draw(Form("f7t_slew+%f*(F7TCal[0]-(F7TCal[1]+%f)):log(F7QCal[0]/F7QCal[1])>>hQDiffAfter(200,-1,1,200,543,573)",gain,offset),gate,"colz");
	cPos->cd(5);
	gPad->SetLogy();
	tree->Draw("f7t_slew>>hBefore(400,543,573)",gate);
	TH1F *hBefore = (TH1F *)gDirectory->Get("hBefore");
	hBefore->Fit("gaus");
	cPos->cd(6);
	gPad->SetLogy();
	tree->Draw(Form("f7t_slew+%f*(F7TCal[0]-(F7TCal[1]+%f))>>hAfter(400,543,573)",gain,offset,offset),gate);
	TH1F *hAfter = (TH1F *)gDirectory->Get("hAfter");
	hAfter->Fit("gaus");
	



}
