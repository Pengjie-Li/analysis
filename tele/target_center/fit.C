
void fit(){
//AnalysisTree->Draw("Target_Y:Target_X>>htarget(1000,-50,50,1000,-50,50)","SiLB_E>9000&&SiLB_E<10000","colz")
// AnalysisTree->Draw("Target_Y:Target_X>>htarget(500,-50,50,500,-50,50)","SiRB_E>9000&&SiRB_E<9500","colz")
	//TH2F *htarget=(TH2F*)gDirectory->Get("htarget");
        TH2F *htarget=(TH2F*)gDirectory->Get("htarget");
	htarget->Draw("colz");

	TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",-20,20,-20,20);

	f2->SetNpx(100);
	f2->SetNpy(100);
	f2->SetParameters(1,0,3,0,3); 
	htarget->Fit(f2);
}
