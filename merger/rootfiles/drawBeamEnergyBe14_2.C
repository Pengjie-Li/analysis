{
	gROOT->ProcessLine(".x cutBeamBe14.C"); 
	tree->Draw("Ek713>>hEk(300,140,170)","Trig_DSB&&Beam");
	TH1F *hEk = (TH1F*)gDirectory->Get("hEk");
		
	TF1 *leftEdge = new TF1("leftEdge","gaus",142.5,145.5);
	TF1 *rightEdge = new TF1("rightEdge","gaus",161.5,163.5);
	hEk->Fit(leftEdge,"R");
	hEk->Fit(rightEdge,"R+");
	std::cout<<leftEdge->GetParameter(1)<<" "<<rightEdge->GetParameter(1)<<" "<<0.5*(leftEdge->GetParameter(1)+rightEdge->GetParameter(1))<<endl;

}
