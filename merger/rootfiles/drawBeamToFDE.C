{
	TCanvas *c1 = new TCanvas("Beam ToF713 dE13","Beam ToF713 dE13",1200,900);
	tree->Draw("F13Q:TOF713>>hToF713(1000,180,300,1000,0,2500)","","colz");

//	TCanvas *c2 = new TCanvas("Beam ToF37 dE7","Beam ToF37 dE7",1200,900);
//	tree->Draw("F7Q:TOF37>>hToF37(1000,290,320,1000,0,4000)","","colz");
}

