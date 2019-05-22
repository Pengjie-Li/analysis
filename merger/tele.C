{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Mon Apr  8 14:12:17 2019 by ROOT version5.34/20)
//   from TTree CalTreeTELE/Convert Raw Cal Sync
//   found on file: run0212_TELE.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0212_TELE.root");
   if (!f) {
      f = new TFile("run0212_TELE.root");
   }
    f->GetObject("CalTreeTELE",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t           energyRaw[4][32];
   Int_t           timeRaw[4][32];
   Int_t           CsIEnergyRaw[7];
   Int_t           CsITimeRaw[7];
   Int_t           RefTime1;
   Int_t           RefTime2;
   Double_t        energyCal[4][32];
   Double_t        timeCal[4][32];
   Double_t        csiEnergyCal[7];
   Double_t        csiTimeCal[7];

   // Set branch addresses.
   CalTreeTELE->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeTELE->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeTELE->SetBranchAddress("energyRaw",energyRaw);
   CalTreeTELE->SetBranchAddress("timeRaw",timeRaw);
   CalTreeTELE->SetBranchAddress("CsIEnergyRaw",CsIEnergyRaw);
   CalTreeTELE->SetBranchAddress("CsITimeRaw",CsITimeRaw);
   CalTreeTELE->SetBranchAddress("RefTime1",&RefTime1);
   CalTreeTELE->SetBranchAddress("RefTime2",&RefTime2);
   CalTreeTELE->SetBranchAddress("energyCal",energyCal);
   CalTreeTELE->SetBranchAddress("timeCal",timeCal);
   CalTreeTELE->SetBranchAddress("csiEnergyCal",csiEnergyCal);
   CalTreeTELE->SetBranchAddress("csiTimeCal",csiTimeCal);

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
