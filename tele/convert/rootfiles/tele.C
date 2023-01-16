{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Jan  8 21:17:12 2020 by ROOT version5.34/20)
//   from TTree CalTreeTELE/Convert Raw Cal Sync
//   found on file: run0292_TELE.root_test
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0292_TELE.root_test");
   if (!f) {
      f = new TFile("run0292_TELE.root_test");
   }
    f->GetObject("CalTreeTELE",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t           dssdQRaw[4][32];
   Int_t           dssdTRaw[2][32];
   Int_t           RefTime1;
   Int_t           RefTime2;
   Int_t           csiQRaw[7];
   Int_t           csiTRaw[7];
   Int_t           dssdQHit;
   Int_t           dssdQHitSide[10];
   Int_t           dssdQHitStripId[10];
   Double_t        dssdQHitQPed[10];
   Double_t        dssdQPed[4][32];
   Int_t           dssdTHit;
   Int_t           dssdTHitSide[10];
   Int_t           dssdTHitStripId[10];
   Double_t        dssdTHitTCal[10];
   Float_t         dssdHit;
   Int_t           dssdHitSide[0];
   Int_t           dssdHitFid[0];
   Int_t           dssdHitBid[0];
   Double_t        dssdHitFQPed[0];
   Double_t        dssdHitBQPed[0];
   Double_t        dssdHitTCal[0];
   Int_t           csiQHit;
   Int_t           csiQHitId[5];
   Double_t        csiQHitQPed[5];
   Double_t        csiQPed[7];
   Int_t           csiTHit;
   Int_t           csiTHitId[4];
   Double_t        csiTHitTCal[4];
   Float_t         csiHit;
   Int_t           csiHitId[0];
   Double_t        csiHitQPed[0];
   Double_t        csiHitTCal[0];
   Int_t           teleHit;
   Int_t           teleHitSide[3];
   Int_t           teleHitFid[3];
   Int_t           teleHitBid[3];
   Double_t        teleHitDssdFQPed[3];
   Double_t        teleHitDssdBQPed[3];
   Double_t        teleHitDssdTCal[3];
   Int_t           teleHitCid[3];
   Double_t        teleHitCsiQPed[3];
   Double_t        teleHitCsiTCal[3];

   // Set branch addresses.
   CalTreeTELE->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeTELE->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeTELE->SetBranchAddress("dssdQRaw",dssdQRaw);
   CalTreeTELE->SetBranchAddress("dssdTRaw",dssdTRaw);
   CalTreeTELE->SetBranchAddress("RefTime1",&RefTime1);
   CalTreeTELE->SetBranchAddress("RefTime2",&RefTime2);
   CalTreeTELE->SetBranchAddress("csiQRaw",csiQRaw);
   CalTreeTELE->SetBranchAddress("csiTRaw",csiTRaw);
   CalTreeTELE->SetBranchAddress("dssdQHit",&dssdQHit);
   CalTreeTELE->SetBranchAddress("dssdQHitSide",dssdQHitSide);
   CalTreeTELE->SetBranchAddress("dssdQHitStripId",dssdQHitStripId);
   CalTreeTELE->SetBranchAddress("dssdQHitQPed",dssdQHitQPed);
   CalTreeTELE->SetBranchAddress("dssdQPed",dssdQPed);
   CalTreeTELE->SetBranchAddress("dssdTHit",&dssdTHit);
   CalTreeTELE->SetBranchAddress("dssdTHitSide",dssdTHitSide);
   CalTreeTELE->SetBranchAddress("dssdTHitStripId",dssdTHitStripId);
   CalTreeTELE->SetBranchAddress("dssdTHitTCal",dssdTHitTCal);
   CalTreeTELE->SetBranchAddress("dssdHit",&dssdHit);
   CalTreeTELE->SetBranchAddress("dssdHitSide",&dssdHitSide);
   CalTreeTELE->SetBranchAddress("dssdHitFid",&dssdHitFid);
   CalTreeTELE->SetBranchAddress("dssdHitBid",&dssdHitBid);
   CalTreeTELE->SetBranchAddress("dssdHitFQPed",&dssdHitFQPed);
   CalTreeTELE->SetBranchAddress("dssdHitBQPed",&dssdHitBQPed);
   CalTreeTELE->SetBranchAddress("dssdHitTCal",&dssdHitTCal);
   CalTreeTELE->SetBranchAddress("csiQHit",&csiQHit);
   CalTreeTELE->SetBranchAddress("csiQHitId",csiQHitId);
   CalTreeTELE->SetBranchAddress("csiQHitQPed",csiQHitQPed);
   CalTreeTELE->SetBranchAddress("csiQPed",csiQPed);
   CalTreeTELE->SetBranchAddress("csiTHit",&csiTHit);
   CalTreeTELE->SetBranchAddress("csiTHitId",csiTHitId);
   CalTreeTELE->SetBranchAddress("csiTHitTCal",csiTHitTCal);
   CalTreeTELE->SetBranchAddress("csiHit",&csiHit);
   CalTreeTELE->SetBranchAddress("csiHitId",&csiHitId);
   CalTreeTELE->SetBranchAddress("csiHitQPed",&csiHitQPed);
   CalTreeTELE->SetBranchAddress("csiHitTCal",&csiHitTCal);
   CalTreeTELE->SetBranchAddress("teleHit",&teleHit);
   CalTreeTELE->SetBranchAddress("teleHitSide",teleHitSide);
   CalTreeTELE->SetBranchAddress("teleHitFid",teleHitFid);
   CalTreeTELE->SetBranchAddress("teleHitBid",teleHitBid);
   CalTreeTELE->SetBranchAddress("teleHitDssdFQPed",teleHitDssdFQPed);
   CalTreeTELE->SetBranchAddress("teleHitDssdBQPed",teleHitDssdBQPed);
   CalTreeTELE->SetBranchAddress("teleHitDssdTCal",teleHitDssdTCal);
   CalTreeTELE->SetBranchAddress("teleHitCid",teleHitCid);
   CalTreeTELE->SetBranchAddress("teleHitCsiQPed",teleHitCsiQPed);
   CalTreeTELE->SetBranchAddress("teleHitCsiTCal",teleHitCsiTCal);

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
