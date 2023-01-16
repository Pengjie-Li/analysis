void FindPixelCenter(){
	int isLR = 1;
	int runNumber = 598;
	int pixelId =-1;
	for(int i=13;i<19;i++){
		for(int j=13;j<19;j++){
//	for(int i=15;i<16;i++){
//		for(int j=15;j<16;j++){
	
			findPixelCenter(runNumber,isLR,i,j);
		}
	}
}
void findPixelCenter(int runNumber,int isLR,int fid,int bid){
	TFile *inputFile;
	if(isLR == 0) inputFile=new TFile(Form("./rootfiles/PixelL%d_%d_run%d.root",fid,bid,runNumber),"UPDATE");
	else inputFile=new TFile(Form("./rootfiles/PixelR%d_%d_run%d.root",fid,bid,runNumber),"UPDATE");
	TTree *tree = gDirectory->Get("tree");

	gStyle->SetStatH(0.15);
	gStyle->SetStatW(0.18);
	gStyle->SetOptFit(1);
	
	TString leftCsI = "(CsILL_CAL>400||CsILRT_CAL>400||CsILRB_CAL>400)";
	TString rightCsI = "(CsIRLT_CAL>400||CsIRLB_CAL>400||CsIRRT_CAL>400||CsIRRB_CAL>400)";
	TString R1="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";
	TString multi;
	if(isLR == 0) multi = "multiplicityLB==1&&multiplicityLF==1";
	else multi =  "multiplicityRB==1&&multiplicityRF==1";
	TString cName = gDirectory->GetName();
	TString hNameX = Form("hX%d_%d_run%d",fid,bid,runNumber);
	TString hNameY = Form("hY%d_%d_run%d",fid,bid,runNumber);
	//tree->Draw("pixelX>>"+hName+"(200,-20,20)",multi+"&&"+R1+"&&"+leftCsI,"colz");
	TCanvas *c =new TCanvas(cName,cName,1400,800);
	c->Divide(2,1);
	c->cd(1);
	tree->Draw("pixelX>>"+hNameX+"(200,-20,20)",multi+"&&"+R1,"colz");
	TH1F *hX =(TH1F *)gDirectory->Get(hNameX);
	hX->Fit("gaus","Q");
	TF1 *fitX = (TF1 *)hX->GetFunction("gaus");

	c->cd(2);
	tree->Draw("pixelY>>"+hNameY+"(200,-20,20)",multi+"&&"+R1,"colz");
	TH1F *hY =(TH1F *)gDirectory->Get(hNameY);
	hY->Fit("gaus","Q");
	TF1 *fitY = (TF1 *)hY->GetFunction("gaus");
	cout<<"\t"<<fid<<"\t"<<bid<<"\t"<<fitX->GetParameter(1)<<"\t"<<fitY->GetParameter(1)<<endl;

	hX->Write();
	hY->Write();
	c->Write();
	//inputFile->Write();
	inputFile->Close();
}

