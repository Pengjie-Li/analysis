{
	gROOT->ProcessLine(".x cutBeamBe14.C"); 
	tree->Draw("Ek713>>hEk(300,140,170)","Trig_DSB&&Beam");
	TH1F *hEk = (TH1F*)gDirectory->Get("hEk");
		
	TF1 *leftEdge = new TF1("leftEdge","gaus",143.5,146);
	TF1 *rightEdge = new TF1("rightEdge","gaus",162,164);
	hEk->Fit(leftEdge,"R");
	hEk->Fit(rightEdge,"R+");
	std::cout<<leftEdge->GetParameter(1)<<" "<<rightEdge->GetParameter(1)<<" "<<0.5*(leftEdge->GetParameter(1)+rightEdge->GetParameter(1))<<endl;

}
