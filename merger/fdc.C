{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Mar  6 10:14:52 2019 by ROOT version5.34/20)
//   from TTree CalTreeFDC/Analysis Tree FDC
//   found on file: run0310_FDCG.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0310_FDCG.root");
   if (!f) {
      f = new TFile("run0310_FDCG.root");
   }
    f->GetObject("CalTreeFDC",tree);

//Declaration of leaves types
   Int_t           RunNumber;
   Long64_t        EventNumber;
   Int_t           FDC0_nhits;
   vector<double>  FDC0_TDC;
   vector<double>  FDC0_layerid;
   vector<double>  FDC0_wireid;
   vector<int>     FDC0_layer_hits;
   Int_t           FDC0_nlayerx;
   Int_t           FDC0_nlayery;
   vector<double>  FDC0_Track_dl;
   vector<double>  FDC0_Track_XY;
   vector<double>  FDC0_Track_Z;
   vector<double>  FDC0_Track_dXY;
   Double_t        FDC0_X;
   Double_t        FDC0_Y;
   Double_t        FDC0_ThetaX;
   Double_t        FDC0_ThetaY;
   Double_t        FDC2_X;
   Double_t        FDC2_Y;
   Double_t        FDC2_ThetaX;
   Double_t        FDC2_ThetaY;

   // Set branch addresses.
   CalTreeFDC->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeFDC->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeFDC->SetBranchAddress("FDC0_nhits",&FDC0_nhits);
   CalTreeFDC->SetBranchAddress("FDC0_TDC",&FDC0_TDC);
   CalTreeFDC->SetBranchAddress("FDC0_layerid",&FDC0_layerid);
   CalTreeFDC->SetBranchAddress("FDC0_wireid",&FDC0_wireid);
   CalTreeFDC->SetBranchAddress("FDC0_layer_hits",&FDC0_layer_hits);
   CalTreeFDC->SetBranchAddress("FDC0_nlayerx",&FDC0_nlayerx);
   CalTreeFDC->SetBranchAddress("FDC0_nlayery",&FDC0_nlayery);
   CalTreeFDC->SetBranchAddress("FDC0_Track_dl",&FDC0_Track_dl);
   CalTreeFDC->SetBranchAddress("FDC0_Track_XY",&FDC0_Track_XY);
   CalTreeFDC->SetBranchAddress("FDC0_Track_Z",&FDC0_Track_Z);
   CalTreeFDC->SetBranchAddress("FDC0_Track_dXY",&FDC0_Track_dXY);
   CalTreeFDC->SetBranchAddress("FDC0_X",&FDC0_X);
   CalTreeFDC->SetBranchAddress("FDC0_Y",&FDC0_Y);
   CalTreeFDC->SetBranchAddress("FDC0_ThetaX",&FDC0_ThetaX);
   CalTreeFDC->SetBranchAddress("FDC0_ThetaY",&FDC0_ThetaY);
   CalTreeFDC->SetBranchAddress("FDC2_X",&FDC2_X);
   CalTreeFDC->SetBranchAddress("FDC2_Y",&FDC2_Y);
   CalTreeFDC->SetBranchAddress("FDC2_ThetaX",&FDC2_ThetaX);
   CalTreeFDC->SetBranchAddress("FDC2_ThetaY",&FDC2_ThetaY);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreeFDC->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreeFDC->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreeFDC->GetEntry(i);
//   }
}
