void FindPixelCenter(){
	double sigma = 0.45;
	TFile *inputFile;
	inputFile=new TFile(Form("./rootfiles/DSSDPixelByBDC%4.2f_%4.2f.root",sigma,sigma),"UPDATE");
	TTree *tree =(TTree*)gDirectory->Get("tree");


	for(int i=13;i<19;i++){
		for(int j=13;j<19;j++){
//	for(int i=15;i<16;i++){
//		for(int j=13;j<14;j++){
	
			findPixelCenter(tree,i,j);
		}
	}
}
void findPixelCenter(TTree *tree,int fid,int bid){
	gStyle->SetStatH(0.15);
	gStyle->SetStatW(0.18);
	gStyle->SetOptFit(1);
	

	TString condition = Form("DSSD_Fid==%d&&DSSD_Bid==%d",fid,bid);
	TString cName = Form("c%d_%d",fid,bid);
	TString hNameX = Form("hX%d_%d",fid,bid);
	TString hNameY = Form("hY%d_%d",fid,bid);
	//tree->Draw("pixelX>>"+hName+"(200,-20,20)",multi+"&&"+R1+"&&"+leftCsI,"colz");
	TCanvas *c =new TCanvas(cName,cName,1400,800);
	c->Divide(2,1);
	c->cd(1);
	tree->Draw("DSSD_X>>"+hNameX+"(400,-20,20)",condition,"colz");
	TH1F *hX =(TH1F *)gDirectory->Get(hNameX);
	hX->Fit("gaus","Q");
	TF1 *fitX = (TF1 *)hX->GetFunction("gaus");

	c->cd(2);

	tree->Draw("DSSD_Y>>"+hNameY+"(400,-20,20)",condition,"colz");
	TH1F *hY =(TH1F *)gDirectory->Get(hNameY);
	hY->Fit("gaus","Q");
	TF1 *fitY = (TF1 *)hY->GetFunction("gaus");
	cout<<"\t"<<fid<<"\t"<<bid<<"\t"<<fitX->GetParameter(1)<<"\t"<<fitY->GetParameter(1)<<"\t"<<fitX->GetParameter(2)<<"\t"<<fitY->GetParameter(2)<<endl;

	hX->Write();
	hY->Write();
	c->Write();
	//inputFile->Write();
	//inputFile->Close();
}
