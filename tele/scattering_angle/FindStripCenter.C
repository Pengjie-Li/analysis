void FindStripCenter(){
	int isLR = 0;
	int runNumber = 595;
	int pixelId =-1;

//	for(int id = 25;id<32;id++){
	for(int id = 12;id<19;id++){
	
			//findStripCenter(runNumber,isLR,-1,id);
			findStripCenter(runNumber,isLR,id,-1);
		}
}
void findStripCenter(int runNumber,int isLR,int fid,int bid){
	TFile *inputFile;
	if(isLR == 0) inputFile=new TFile(Form("./rootfiles/StripL%d_%d_run%d.root",fid,bid,runNumber),"UPDATE");
	else inputFile=new TFile(Form("./rootfiles/StripR%d_%d_run%d.root",fid,bid,runNumber),"UPDATE");
	TTree *tree = gDirectory->Get("tree");

	gStyle->SetStatH(0.15);
	gStyle->SetStatW(0.18);
	gStyle->SetOptFit(1);
	
	TString cName = gDirectory->GetName();
	TString hName = Form("h%d_%d_run%d",fid,bid,runNumber);
	TString draw;
	if(fid == -1) draw ="pixelX";
	if(bid == -1) draw ="pixelY";
	//tree->Draw("pixelX>>"+hName+"(200,-20,20)",multi+"&&"+R1+"&&"+leftCsI,"colz");
	TCanvas *c =new TCanvas(cName,cName,800,800);
	tree->Draw(draw+">>"+hName+"(100,-50,50)");
	TH1F *h =(TH1F *)gDirectory->Get(hName);
	h->Fit("gaus","Q");
	TF1 *fit = (TF1 *)h->GetFunction("gaus");

	//cout<<"\t"<<fid<<"\t"<<bid<<"\t"<<fitX->GetParameter(1)<<"\t"<<fitY->GetParameter(1)<<endl;
	cout<<"\t"<<fid<<"\t"<<bid<<"\t"<<fit->GetParameter(1)<<"\t"<<fit->GetParError(1)<<endl;

	h->Write();
	c->Write();
	//inputFile->Write();
	//inputFile->Close();
}
