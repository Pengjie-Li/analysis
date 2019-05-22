{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Thu Mar 21 13:57:11 2019 by ROOT version5.34/20)
//   from TTree CalTreeHOD/Convert Raw Cal Sync
//   found on file: run0310_HOD.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0310_HOD.root");
   if (!f) {
      f = new TFile("run0310_HOD.root");
   }
    f->GetObject("CalTreeHOD",tree);

//Declaration of leaves types
   Int_t           timeUpRaw[40];
   Int_t           timeDownRaw[40];
   Int_t           energyUpRaw[40];
   Int_t           energyDownRaw[40];

   // Set branch addresses.
   CalTreeHOD->SetBranchAddress("timeUpRaw",timeUpRaw);
   CalTreeHOD->SetBranchAddress("timeDownRaw",timeDownRaw);
   CalTreeHOD->SetBranchAddress("energyUpRaw",energyUpRaw);
   CalTreeHOD->SetBranchAddress("energyDownRaw",energyDownRaw);

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
