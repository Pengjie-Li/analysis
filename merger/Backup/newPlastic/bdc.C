{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Tue Mar  5 17:32:38 2019 by ROOT version5.34/20)
//   from TTree CalTreeBDC/Analysis Tree BDC
//   found on file: run0310_BDC.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0310_BDC.root");
   if (!f) {
      f = new TFile("run0310_BDC.root");
   }
    f->GetObject("CalTreeBDC",tree);

//Declaration of leaves types
   Int_t           RunNumber;
   Long64_t        EventNumber;
   Int_t           BDC1_nhits;
   vector<double>  BDC1_TDC;
   vector<double>  BDC1_layerid;
   vector<double>  BDC1_wireid;
   vector<int>     BDC1_layer_hits;
   Int_t           BDC1_nlayerx;
   Int_t           BDC1_nlayery;
   vector<double>  BDC1_Track_dl;
   vector<double>  BDC1_Track_XY;
   vector<double>  BDC1_Track_Z;
   vector<double>  BDC1_Track_dXY;
   Double_t        BDC1_X;
   Double_t        BDC1_Y;
   Double_t        BDC1_ThetaX;
   Double_t        BDC1_ThetaY;
   Int_t           BDC2_nhits;
   vector<double>  BDC2_TDC;
   vector<double>  BDC2_layerid;
   vector<double>  BDC2_wireid;
   vector<int>     BDC2_layer_hits;
   Int_t           BDC2_nlayerx;
   Int_t           BDC2_nlayery;
   vector<double>  BDC2_Track_dl;
   vector<double>  BDC2_Track_XY;
   vector<double>  BDC2_Track_Z;
   vector<double>  BDC2_Track_dXY;
   Double_t        BDC2_X;
   Double_t        BDC2_Y;
   Double_t        BDC2_ThetaX;
   Double_t        BDC2_ThetaY;

   // Set branch addresses.
   CalTreeBDC->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeBDC->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeBDC->SetBranchAddress("BDC1_nhits",&BDC1_nhits);
   CalTreeBDC->SetBranchAddress("BDC1_TDC",&BDC1_TDC);
   CalTreeBDC->SetBranchAddress("BDC1_layerid",&BDC1_layerid);
   CalTreeBDC->SetBranchAddress("BDC1_wireid",&BDC1_wireid);
   CalTreeBDC->SetBranchAddress("BDC1_layer_hits",&BDC1_layer_hits);
   CalTreeBDC->SetBranchAddress("BDC1_nlayerx",&BDC1_nlayerx);
   CalTreeBDC->SetBranchAddress("BDC1_nlayery",&BDC1_nlayery);
   CalTreeBDC->SetBranchAddress("BDC1_Track_dl",&BDC1_Track_dl);
   CalTreeBDC->SetBranchAddress("BDC1_Track_XY",&BDC1_Track_XY);
   CalTreeBDC->SetBranchAddress("BDC1_Track_Z",&BDC1_Track_Z);
   CalTreeBDC->SetBranchAddress("BDC1_Track_dXY",&BDC1_Track_dXY);
   CalTreeBDC->SetBranchAddress("BDC1_X",&BDC1_X);
   CalTreeBDC->SetBranchAddress("BDC1_Y",&BDC1_Y);
   CalTreeBDC->SetBranchAddress("BDC1_ThetaX",&BDC1_ThetaX);
   CalTreeBDC->SetBranchAddress("BDC1_ThetaY",&BDC1_ThetaY);
   CalTreeBDC->SetBranchAddress("BDC2_nhits",&BDC2_nhits);
   CalTreeBDC->SetBranchAddress("BDC2_TDC",&BDC2_TDC);
   CalTreeBDC->SetBranchAddress("BDC2_layerid",&BDC2_layerid);
   CalTreeBDC->SetBranchAddress("BDC2_wireid",&BDC2_wireid);
   CalTreeBDC->SetBranchAddress("BDC2_layer_hits",&BDC2_layer_hits);
   CalTreeBDC->SetBranchAddress("BDC2_nlayerx",&BDC2_nlayerx);
   CalTreeBDC->SetBranchAddress("BDC2_nlayery",&BDC2_nlayery);
   CalTreeBDC->SetBranchAddress("BDC2_Track_dl",&BDC2_Track_dl);
   CalTreeBDC->SetBranchAddress("BDC2_Track_XY",&BDC2_Track_XY);
   CalTreeBDC->SetBranchAddress("BDC2_Track_Z",&BDC2_Track_Z);
   CalTreeBDC->SetBranchAddress("BDC2_Track_dXY",&BDC2_Track_dXY);
   CalTreeBDC->SetBranchAddress("BDC2_X",&BDC2_X);
   CalTreeBDC->SetBranchAddress("BDC2_Y",&BDC2_Y);
   CalTreeBDC->SetBranchAddress("BDC2_ThetaX",&BDC2_ThetaX);
   CalTreeBDC->SetBranchAddress("BDC2_ThetaY",&BDC2_ThetaY);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreeBDC->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreeBDC->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreeBDC->GetEntry(i);
//   }
}
