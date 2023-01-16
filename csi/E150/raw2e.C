//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Aug 10 12:18:43 2018 by ROOT version5.34/20)
//   from TTree tree_BEAM/Analysis Tree BEAM
//   found on file: run0595_Beamv8.root
//////////////////////////////////////////////////////////



void raw2e(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int dDSSD=1;
	int dCsI=1;
	int dMap=1;
	int dMapCsI=1;
	int runnum=599;
	TString inputname=Form("./rootfiles/run0%d_Beamv8.root",runnum);
	TFile *f = new TFile(inputname,"READ");
	TTree *tree_BEAM=(TTree*)f->Get("tree_BEAM");



	//Declaration of leaves types
	vector<double>  *SiLF_rawADC;
	vector<double>  *SiLB_rawADC;
	vector<double>  *SiRF_rawADC;
	vector<double>  *SiRB_rawADC;
	vector<double>  *SiLF_rawTDC;
	vector<double>  *SiLB_rawTDC;
	vector<double>  *SiRF_rawTDC;
	vector<double>  *SiRB_rawTDC;
	Double_t        CsILL_rawADC;
	Double_t        CsILRT_rawADC;
	Double_t        CsILRB_rawADC;
	Double_t        CsIRLT_rawADC;
	Double_t        CsIRLB_rawADC;
	Double_t        CsIRRT_rawADC;
	Double_t        CsIRRB_rawADC;
	Double_t        CsILL_rawTDC;
	Double_t        CsILRT_rawTDC;
	Double_t        CsILRB_rawTDC;
	Double_t        CsIRLT_rawTDC;
	Double_t        CsIRLB_rawTDC;
	Double_t        CsIRRT_rawTDC;
	Double_t        CsIRRB_rawTDC;

	tree_BEAM->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
	tree_BEAM->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
	tree_BEAM->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
	tree_BEAM->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);
	tree_BEAM->SetBranchAddress("SiLF_rawTDC",&SiLF_rawTDC);
	tree_BEAM->SetBranchAddress("SiLB_rawTDC",&SiLB_rawTDC);
	tree_BEAM->SetBranchAddress("SiRF_rawTDC",&SiRF_rawTDC);
	tree_BEAM->SetBranchAddress("SiRB_rawTDC",&SiRB_rawTDC);
	tree_BEAM->SetBranchAddress("CsILL_rawADC",&CsILL_rawADC);
	tree_BEAM->SetBranchAddress("CsILRT_rawADC",&CsILRT_rawADC);
	tree_BEAM->SetBranchAddress("CsILRB_rawADC",&CsILRB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLT_rawADC",&CsIRLT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLB_rawADC",&CsIRLB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRT_rawADC",&CsIRRT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRB_rawADC",&CsIRRB_rawADC);
	tree_BEAM->SetBranchAddress("CsILL_rawTDC",&CsILL_rawTDC);
	tree_BEAM->SetBranchAddress("CsILRT_rawTDC",&CsILRT_rawTDC);
	tree_BEAM->SetBranchAddress("CsILRB_rawTDC",&CsILRB_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRLT_rawTDC",&CsIRLT_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRLB_rawTDC",&CsIRLB_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRRT_rawTDC",&CsIRRT_rawTDC);
	tree_BEAM->SetBranchAddress("CsIRRB_rawTDC",&CsIRRB_rawTDC);



	TString outputname=Form("cali_run%d.root",runnum);
	TFile *g=new TFile(outputname,"RECREATE");
	TTree *tree=new TTree("tree","tree");
	vector<double>  SiLF;
	vector<double>  SiLB;
	tree->Branch("SiLF",&SiLF);
	tree->Branch("SiLB",&SiLB);

	Long64_t nentries = tree_BEAM->GetEntries();

	double kf[32]={0};
	double pedf[32]={0};
	double kb[32]={0};
	double pedb[32]={0};
	Load(kf,pedf,kb,pedb);
	nentries=100000;
	Long64_t nbytes = 0;

	TH2F *hLF=new TH2F("hLF","hLF",32,-0.5,31.5,1000,0,25);
	TH2F *hLB=new TH2F("hLB","hLB",32,-0.5,31.5,1000,0,25);

	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree_BEAM->GetEntry(ientry);

		SiLF.resize(32,-1);
		SiLB.resize(32,-1);

		for(int i=0;i<32;i++)
		{
			//SiLF[i]=1*((*SiLF_rawADC)[i]-pedf[i]);
			SiLF[i]=kf[i]*((*SiLF_rawADC)[i]-pedf[i]);
			//SiLB[i]=1*((*SiLB_rawADC)[i]-pedb[i]);
			SiLB[i]=kb[i]*((*SiLB_rawADC)[i]-pedb[i]);
			hLF->Fill(i,SiLF[i]);
			hLB->Fill(i,SiLB[i]);

			//cout<<kf[i]<<"\t"<<SiLF[i]<<endl;
		}
		tree->Fill();

		if(ientry%10000==0) cout<<ientry<<endl;

	}
	tree->Write();
	hLF->Write();
	hLB->Write();
	g->Close();

}

void Load(double *kf,double *pedf,double *kb,double *pedb)
{
	ifstream in;
	TString par_name="calibration_parameters.txt";

	in.open(par_name);
	int side;
	int strip;
	double  k;
	double  ped;
	while (1)
	{
		in >>side>>strip>>k>>ped;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;

		if(side==0)
		{
			kf[strip]=k;
			pedf[strip]=ped;
		}
		if(side==1)
		{
			kb[strip]=k;
			pedb[strip]=ped;
		}


	}
}
