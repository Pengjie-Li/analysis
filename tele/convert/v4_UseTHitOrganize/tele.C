{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Sun Oct  6 18:57:58 2019 by ROOT version5.34/20)
//   from TTree CalTreeTELE/Convert Raw Cal Sync
//   found on file: rootfiles/run0596_TELE.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfiles/run0596_TELE.root");
   if (!f) {
      f = new TFile("rootfiles/run0596_TELE.root");
   }
    f->GetObject("CalTreeTELE",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t           dssdQRaw[4][32];
   Int_t           dssdTRaw[4][32];
   Int_t           RefTime1;
   Int_t           RefTime2;
   Int_t           csiQRaw[7];
   Int_t           csiTRaw[7];
   Double_t        dssdQScm[4][32];
   Double_t        dssdQCal[4][32];
   Double_t        dssdTCal[4][32];
   Double_t        csiQPed[7];
   Double_t        csiQSync[7];
   Double_t        csiQCal[7];
   Double_t        csiTCal[7];

   // Set branch addresses.
   CalTreeTELE->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeTELE->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeTELE->SetBranchAddress("dssdQRaw",dssdQRaw);
   CalTreeTELE->SetBranchAddress("dssdTRaw",dssdTRaw);
   CalTreeTELE->SetBranchAddress("RefTime1",&RefTime1);
   CalTreeTELE->SetBranchAddress("RefTime2",&RefTime2);
   CalTreeTELE->SetBranchAddress("csiQRaw",csiQRaw);
   CalTreeTELE->SetBranchAddress("csiTRaw",csiTRaw);
   CalTreeTELE->SetBranchAddress("dssdQScm",dssdQScm);
   CalTreeTELE->SetBranchAddress("dssdQCal",dssdQCal);
   CalTreeTELE->SetBranchAddress("dssdTCal",dssdTCal);
   CalTreeTELE->SetBranchAddress("csiQPed",csiQPed);
   CalTreeTELE->SetBranchAddress("csiQSync",csiQSync);
   CalTreeTELE->SetBranchAddress("csiQCal",csiQCal);
   CalTreeTELE->SetBranchAddress("csiTCal",csiTCal);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreeTELE->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreeTELE->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreeTELE->GetEntry(i);
//   }
}
