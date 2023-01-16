{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Jun  7 09:16:48 2019 by ROOT version5.34/20)
//   from TTree CalTreePLA/Convert Raw Cal Sync
//   found on file: run0360_PLA.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0360_PLA.root");
   if (!f) {
      f = new TFile("run0360_PLA.root");
   }
    f->GetObject("CalTreePLA",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t           F3TRaw[2];
   Int_t           F3QRaw[2];
   Double_t        F3TCal[2];
   Double_t        F3QCal[2];
   Double_t        F3T;
   Double_t        F3Q;
   Int_t           F7TRaw[2];
   Int_t           F7QRaw[2];
   Double_t        F7TCal[2];
   Double_t        F7QCal[2];
   Double_t        F7T;
   Double_t        F7Q;
   Int_t           SBT1TRaw[2];
   Int_t           SBT1QRaw[2];
   Double_t        SBT1TCal[2];
   Double_t        SBT1QCal[2];
   Double_t        SBT1T;
   Double_t        SBT1Q;
   Int_t           SBT2TRaw[2];
   Int_t           SBT2QRaw[2];
   Double_t        SBT2TCal[2];
   Double_t        SBT2QCal[2];
   Double_t        SBT2T;
   Double_t        SBT2Q;
   Double_t        F13T;
   Double_t        F13Q;
   Int_t           SBVTRaw[2];
   Int_t           SBVQRaw[2];
   Double_t        SBVTCal[2];
   Double_t        SBVQCal[2];
   Double_t        SBVT;
   Double_t        SBVQ;

   // Set branch addresses.
   CalTreePLA->SetBranchAddress("EventNumber",&EventNumber);
   CalTreePLA->SetBranchAddress("RunNumber",&RunNumber);
   CalTreePLA->SetBranchAddress("F3TRaw",F3TRaw);
   CalTreePLA->SetBranchAddress("F3QRaw",F3QRaw);
   CalTreePLA->SetBranchAddress("F3TCal",F3TCal);
   CalTreePLA->SetBranchAddress("F3QCal",F3QCal);
   CalTreePLA->SetBranchAddress("F3T",&F3T);
   CalTreePLA->SetBranchAddress("F3Q",&F3Q);
   CalTreePLA->SetBranchAddress("F7TRaw",F7TRaw);
   CalTreePLA->SetBranchAddress("F7QRaw",F7QRaw);
   CalTreePLA->SetBranchAddress("F7TCal",F7TCal);
   CalTreePLA->SetBranchAddress("F7QCal",F7QCal);
   CalTreePLA->SetBranchAddress("F7T",&F7T);
   CalTreePLA->SetBranchAddress("F7Q",&F7Q);
   CalTreePLA->SetBranchAddress("SBT1TRaw",SBT1TRaw);
   CalTreePLA->SetBranchAddress("SBT1QRaw",SBT1QRaw);
   CalTreePLA->SetBranchAddress("SBT1TCal",SBT1TCal);
   CalTreePLA->SetBranchAddress("SBT1QCal",SBT1QCal);
   CalTreePLA->SetBranchAddress("SBT1T",&SBT1T);
   CalTreePLA->SetBranchAddress("SBT1Q",&SBT1Q);
   CalTreePLA->SetBranchAddress("SBT2TRaw",SBT2TRaw);
   CalTreePLA->SetBranchAddress("SBT2QRaw",SBT2QRaw);
   CalTreePLA->SetBranchAddress("SBT2TCal",SBT2TCal);
   CalTreePLA->SetBranchAddress("SBT2QCal",SBT2QCal);
   CalTreePLA->SetBranchAddress("SBT2T",&SBT2T);
   CalTreePLA->SetBranchAddress("SBT2Q",&SBT2Q);
   CalTreePLA->SetBranchAddress("F13T",&F13T);
   CalTreePLA->SetBranchAddress("F13Q",&F13Q);
   CalTreePLA->SetBranchAddress("SBVTRaw",SBVTRaw);
   CalTreePLA->SetBranchAddress("SBVQRaw",SBVQRaw);
   CalTreePLA->SetBranchAddress("SBVTCal",SBVTCal);
   CalTreePLA->SetBranchAddress("SBVQCal",SBVQCal);
   CalTreePLA->SetBranchAddress("SBVT",&SBVT);
   CalTreePLA->SetBranchAddress("SBVQ",&SBVQ);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreePLA->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreePLA->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreePLA->GetEntry(i);
//   }
}
