{

	//tree->Draw("F13Q:tof>>hToF713(1000,220,250,1000,0,2000)","Trig_DSB","colz");
	tree->Draw("F13Q:TOF713>>hToF713(1000,220,250,1000,0,2000)","Trig_DSB","colz");
	gROOT->ProcessLine(".x cutBeamBe10.C");
}
