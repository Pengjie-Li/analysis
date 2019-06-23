{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Sun Jun 23 20:24:13 2019 by ROOT version5.34/20)
//   from TTree CalTreeHOD/Convert Raw Cal Sync
//   found on file: run0360_HOD.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0360_HOD.root");
   if (!f) {
      f = new TFile("run0360_HOD.root");
   }
    f->GetObject("CalTreeHOD",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t           hodID[40];
   Int_t           hodTRaw[2][40];
   Int_t           hodQRaw[2][40];
   Double_t        hodTCal[2][40];
   Double_t        hodQCal[2][40];
   Double_t        hodBarQCal[40];

   // Set branch addresses.
   CalTreeHOD->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeHOD->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeHOD->SetBranchAddress("hodID",hodID);
   CalTreeHOD->SetBranchAddress("hodTRaw",hodTRaw);
   CalTreeHOD->SetBranchAddress("hodQRaw",hodQRaw);
   CalTreeHOD->SetBranchAddress("hodTCal",hodTCal);
   CalTreeHOD->SetBranchAddress("hodQCal",hodQCal);
   CalTreeHOD->SetBranchAddress("hodBarQCal",hodBarQCal);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreeHOD->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreeHOD->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreeHOD->GetEntry(i);
//   }
}
