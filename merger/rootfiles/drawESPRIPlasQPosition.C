{
	gROOT->ProcessLine(".x setAlias.C");
	TCanvas *c1 = new TCanvas("c1","c1",1500,900);
	c1->Divide(2,1);
	c1->cd(1);
	tree->Draw("plasQLPed:rdcY[0]>>hL(50,0,500,500,10,4000)","plasQRaw[0]!=-9999&&plasQRaw[1]!=-9999","colz");
	c1->cd(2);
	tree->Draw("plasQRPed:rdcY[1]>>hR(50,0,500,500,10,4000)","plasQRaw[2]!=-9999&&plasQRaw[3]!=-9999","colz");
}
