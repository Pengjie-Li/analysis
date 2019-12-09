{

	double offset = 1.24;
	//double gain = 0.39;
	//double gain = 0.5;
	double gain = 0.38;
        gROOT->ProcessLine(".x cutBeamBe10.C");

        gROOT->ProcessLine(".x cutBeamB15.C");
        gROOT->ProcessLine(".x cutBeamBe12.C");
        gROOT->ProcessLine(".x cutBeamLi9.C");
        gROOT->ProcessLine(".x cutBeamHe6.C");
        gROOT->ProcessLine(".x cutBeamH3.C");

	TCanvas *cPos = new TCanvas("cPos","cPos",1200,1000);
	cPos->Divide(2,2);
	cPos->cd(1);
	tree->Draw("0.5*(SBT1TCal[0]+SBT1TCal[1]):SBT1TCal[0]-SBT1TCal[1]>>Before(200,-1,4,1000,215,230)","Trig_DSB&&Beam","colz");
	cPos->cd(2);
	//tree->Draw("0.5*(SBT1TCal[0]+SBT1TCal[1])+0.39*(SBT1TCal[0]-(SBT1TCal[1]+1.24)):(SBT1TCal[0]-(SBT1TCal[1]+1.24))>>After(400,-4,4,400,218,224)","Trig_DSB&&Beam","colz");
	tree->Draw(Form("0.5*(SBT1TCal[0]+SBT1TCal[1])+%f*(SBT1TCal[0]-(SBT1TCal[1]+%f)):(SBT1TCal[0]-(SBT1TCal[1]+%f))>>After(200,-2.5,2.5,400,218,224)",gain,offset,offset),"Trig_DSB&&Beam","colz");
	cPos->cd(3);
	tree->Draw("0.5*(SBT1TCal[0]+SBT1TCal[1])>>hBefore(400,218,224)","Trig_DSB&&Beam");
	cPos->cd(4);
	tree->Draw(Form("0.5*(SBT1TCal[0]+SBT1TCal[1])+%f*(SBT1TCal[0]-(SBT1TCal[1]+%f))>>hAfter(400,218,224)",gain,offset,offset),"Trig_DSB&&Beam");



}
