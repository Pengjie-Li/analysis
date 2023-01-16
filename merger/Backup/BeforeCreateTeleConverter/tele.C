{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Mar  6 10:21:58 2019 by ROOT version5.34/20)
//   from TTree CalTreeSILICONS/Analysis Tree SILICONS
//   found on file: run0310_SILICONS.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0310_SILICONS.root");
   if (!f) {
      f = new TFile("run0310_SILICONS.root");
   }
    f->GetObject("CalTreeSILICONS",tree);

//Declaration of leaves types
   Int_t           RunNumber;
   Long64_t        EventNumber;
   vector<int>     Silicons_ID;
   vector<double>  Silicons_X;
   vector<double>  Silicons_Y;
   vector<double>  Silicons_Z;
   vector<double>  Silicons_Time;
   vector<double>  Silicons_Energy;
   Int_t           Silicons_Multiplicity;
   vector<double>  SiLF_rawADC;
   vector<double>  SiLB_rawADC;
   vector<double>  SiRF_rawADC;
   vector<double>  SiRB_rawADC;
   vector<double>  SiLF_rawTDC;
   vector<double>  SiLB_rawTDC;
   vector<double>  SiRF_rawTDC;
   vector<double>  SiRB_rawTDC;
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

   // Set branch addresses.
   CalTreeSILICONS->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeSILICONS->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeSILICONS->SetBranchAddress("Silicons_ID",&Silicons_ID);
   CalTreeSILICONS->SetBranchAddress("Silicons_X",&Silicons_X);
   CalTreeSILICONS->SetBranchAddress("Silicons_Y",&Silicons_Y);
   CalTreeSILICONS->SetBranchAddress("Silicons_Z",&Silicons_Z);
   CalTreeSILICONS->SetBranchAddress("Silicons_Time",&Silicons_Time);
   CalTreeSILICONS->SetBranchAddress("Silicons_Energy",&Silicons_Energy);
   CalTreeSILICONS->SetBranchAddress("Silicons_Multiplicity",&Silicons_Multiplicity);
   CalTreeSILICONS->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
   CalTreeSILICONS->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
   CalTreeSILICONS->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
   CalTreeSILICONS->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);
   CalTreeSILICONS->SetBranchAddress("SiLF_rawTDC",&SiLF_rawTDC);
   CalTreeSILICONS->SetBranchAddress("SiLB_rawTDC",&SiLB_rawTDC);
   CalTreeSILICONS->SetBranchAddress("SiRF_rawTDC",&SiRF_rawTDC);
   CalTreeSILICONS->SetBranchAddress("SiRB_rawTDC",&SiRB_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsILL_rawADC",&CsILL_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsILRT_rawADC",&CsILRT_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsILRB_rawADC",&CsILRB_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsIRLT_rawADC",&CsIRLT_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsIRLB_rawADC",&CsIRLB_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsIRRT_rawADC",&CsIRRT_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsIRRB_rawADC",&CsIRRB_rawADC);
   CalTreeSILICONS->SetBranchAddress("CsILL_rawTDC",&CsILL_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsILRT_rawTDC",&CsILRT_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsILRB_rawTDC",&CsILRB_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsIRLT_rawTDC",&CsIRLT_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsIRLB_rawTDC",&CsIRLB_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsIRRT_rawTDC",&CsIRRT_rawTDC);
   CalTreeSILICONS->SetBranchAddress("CsIRRB_rawTDC",&CsIRRB_rawTDC);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreeSILICONS->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreeSILICONS->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreeSILICONS->GetEntry(i);
//   }
}
