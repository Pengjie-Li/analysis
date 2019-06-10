{
	TString condition= "";
	TString conditionL= "rdcX[0]<150";
	TString conditionR= "rdcX[1]>250";
	TCanvas *c1 =new TCanvas("ToF vs dE","ToF vs dE",1600,700);
	c1->Divide(2,1);
	c1->cd(1);
	CalTreeESPRI->Draw("plasQ[0]:plasT[0]>>hToFLeft(1000,-14000,-12000,1000,0,35)",conditionL,"colz");
	c1->cd(2);
	CalTreeESPRI->Draw("plasQ[1]:plasT[1]>>hToFRight(1000,-14000,-12000,1000,0,35)",conditionR,"colz");
}
