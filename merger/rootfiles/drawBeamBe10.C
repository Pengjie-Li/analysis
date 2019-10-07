{

	tree->Draw("F13Q:TOF713>>hToF713(1000,200,300,1000,0,2000)","Trig_DSB","colz");
	gROOT->ProcessLine(".x cutBeamBe10.C");
}
