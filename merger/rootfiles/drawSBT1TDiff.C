{
	double offset = 1.24;
	double gain = 0.39;
        gROOT->ProcessLine(".x cutBeamBe10.C");

        gROOT->ProcessLine(".x cutBeamB15.C");
        gROOT->ProcessLine(".x cutBeamBe12.C");
        gROOT->ProcessLine(".x cutBeamLi9.C");
        gROOT->ProcessLine(".x cutBeamHe6.C");
        gROOT->ProcessLine(".x cutBeamH3.C");

	TCanvas *cPos = new TCanvas("cPos","cPos",1200,1000);
	cPos->Divide(2,1);
	cPos->cd(1);
	tree->Draw("SBT1TCal[0]:SBT1TCal[1]+1.24>>Before(1000,200,240,1000,200,240)","","colz");
	cPos->cd(2);
	tree->Draw(Form("0.5*(SBT1TCal[0]+SBT1TCal[1])+%f*(SBT1TCal[0]-(SBT1TCal[1]+%f)):(SBT1TCal[0]-(SBT1TCal[1]+%f))>>hAfter(200,-2,2,400,218,224)",gain,offset,offset),"Trig_DSB&&Beam","colz");



}
