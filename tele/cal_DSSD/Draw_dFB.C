
void Draw_dFB(){

	gStyle->SetOptStat(1111111);

	//TString filename="run596_checking_calibration.root";
	//TString filename="run597_checking_calibration.root";
	//TString filename="run598_checking_calibration.root";
	//TString filename="run599_checking_calibration.root";
	//TString filename="run599_checking_calibration_v2.root";
	//TString filename="run596_checking_calibration_v2.root";
	//TString filename="run597_checking_calibration_v2.root";
	//TString filename="run598_checking_calibration_v2.root";
	//TString filename="run300_checking_calibration.root";
	
	TString filename="run596_checking_calibration_v4.root";
	//TString filename="run596_checking_calibration_v3.root";
	//TString filename="run599_checking_calibration_v3.root";
	//TString filename="run598_checking_calibration_v3.root";
	//TString filename="run598_checking_calibration_v2.root";
	//TString filename="run598_checking_calibration.root";
	//TString filename="run300_checking_calibration.root";
	TFile *f = new TFile(filename,"UPDATE");
	TTree *tree=f->Get("tree");

	//Declaration of leaves types
	Double_t        SiLF_ADC[32];
	Double_t        SiLB_ADC[32];
	Double_t        SiLF_SCM[32];
	Double_t        SiLB_SCM[32];
	Double_t        SiLF_E[32];
	Double_t        SiLB_E[32];
	Double_t        SiRF_ADC[32];
	Double_t        SiRB_ADC[32];
	Double_t        SiRF_SCM[32];
	Double_t        SiRB_SCM[32];
	Double_t        SiRF_E[32];
	Double_t        SiRB_E[32];

	// Set branch addresses.
	tree->SetBranchAddress("SiLF_ADC",SiLF_ADC);
	tree->SetBranchAddress("SiLB_ADC",SiLB_ADC);
	tree->SetBranchAddress("SiLF_SCM",SiLF_SCM);
	tree->SetBranchAddress("SiLB_SCM",SiLB_SCM);
	tree->SetBranchAddress("SiLF_E",SiLF_E);
	tree->SetBranchAddress("SiLB_E",SiLB_E);
	tree->SetBranchAddress("SiRF_ADC",SiRF_ADC);
	tree->SetBranchAddress("SiRB_ADC",SiRB_ADC);
	tree->SetBranchAddress("SiRF_SCM",SiRF_SCM);
	tree->SetBranchAddress("SiRB_SCM",SiRB_SCM);
	tree->SetBranchAddress("SiRF_E",SiRF_E);
	tree->SetBranchAddress("SiRB_E",SiRB_E);

	//     This is the loop skeleton
	//       To read only selected branches, Insert statements like:
	// tree->SetBranchStatus("*",0);  // disable all branches
	// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

        TH1F *hSiL_dFB=new TH1F("hSiL_dFB","hSiL_dFB",400,-200,200);
        TH1F *hSiR_dFB=new TH1F("hSiR_dFB","hSiR_dFB",400,-200,200);


        TH2F *hSiL_FB=new TH2F("hSiL_FB","hSiL_FB",1000,-2000,30000,1000,-2000,30000);
        TH2F *hSiR_FB=new TH2F("hSiR_FB","hSiR_FB",1000,-2000,30000,1000,-2000,30000);
        //TH2F *hSiRF=new TH2F("hSiRF_dFB","hSiRF_dFB",)
	Long64_t nentries = tree->GetEntries();

	Long64_t nbytes = 0;
	//nentries=100000;
	for (Long64_t i=0; i<nentries;i++) {
		nbytes += tree->GetEntry(i);
		double Max_SiLF=MaxE(SiLF_E);
		double Max_SiLB=MaxE(SiLB_E);

		double Max_SiRF=MaxE(SiRF_E);
		double Max_SiRB=MaxE(SiRB_E);

		//if((Max_SiLF>Max_SiRF)&&(Max_SiLB>Max_SiRB))
		{
			//if(abs(Max_SiLF-Max_SiLB)<1000 && Max_SiLF>3000)
			{
				hSiL_dFB->Fill(Max_SiLF-Max_SiLB);
				hSiL_FB->Fill(Max_SiLF,Max_SiLB);
			}
		}
		//if((Max_SiLF<Max_SiRF)&&(Max_SiLB<Max_SiRB))
		{
			//if(abs(Max_SiRF-Max_SiRB)<1000 && Max_SiRF>3000)
			{
				hSiR_dFB->Fill(Max_SiRF-Max_SiRB);
				hSiR_FB->Fill(Max_SiRF,Max_SiRB);
			}
		}

		if((i%1000)==0) cout<<i<<endl;
	}

	TCanvas *cSiL_dFB= new TCanvas("cSiL_dFB","cSiL_dFB",800,800);
	cSiL_dFB->cd();
	hSiL_dFB->Draw();
	hSiL_dFB->Write();

	TCanvas *cSiR_dFB= new TCanvas("cSiR_dFB","cSiR_dFB",800,800);
	cSiR_dFB->cd();
	hSiR_dFB->Draw();
	hSiR_dFB->Write();


	TCanvas *cSiL_FB= new TCanvas("cSiL_FB","cSiL_FB",800,800);
	cSiL_FB->cd();
	hSiL_FB->Draw();
	hSiL_FB->Write();

	TCanvas *cSiR_FB= new TCanvas("cSiR_FB","cSiR_FB",800,800);
	cSiR_FB->cd();
	hSiR_FB->Draw();
	hSiR_FB->Write();

}

double  MaxE(double *E)
{
	double max=-1000;
	for(int i=0;i<32;i++)
		if(E[i]>max) max=E[i];

	return max;
}
