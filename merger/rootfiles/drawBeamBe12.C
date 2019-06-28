{

	tree->Draw("F13Q:TOF713>>hToF713(1000,150,350,1000,0,4000)","Trig_DSB","colz");
	gROOT->ProcessLine(".x cutBeamBe12.C");
}
