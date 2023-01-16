{
	TString condition= "";
	TString conditionL= "rdcX[0]<150";
	TString conditionR= "rdcX[1]>250";
	conditionL = condition; conditionR = condition;
	int tMin = -700;
	//int tMax = -610;
	int tMax = -500;
	TCanvas *c1 =new TCanvas("ToF vs dE","ToF vs dE",1600,700);
	c1->Divide(2,1);
	c1->cd(1);
	tree->Draw(Form("plasQ[0]:plasT[0]>>hToFLeft(1000,%d,%d,1000,0,35)",tMin,tMax),conditionL,"colz");
	c1->cd(2);
	tree->Draw(Form("plasQ[1]:plasT[1]>>hToFRight(1000,%d,%d,1000,0,35)",tMin,tMax),conditionR,"colz");
}
