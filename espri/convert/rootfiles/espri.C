{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Jan  1 16:39:24 2020 by ROOT version5.34/20)
//   from TTree CalTreeESPRI/Convert Raw Cal Sync
//   found on file: run0300_ESPRI.root_test
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0300_ESPRI.root_test");
   if (!f) {
      f = new TFile("run0300_ESPRI.root_test");
   }
    f->GetObject("CalTreeESPRI",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   vector<int>     plasTdcRaw0;
   vector<int>     plasTdcRaw1;
   vector<int>     plasTdcRaw2;
   vector<int>     plasTdcRaw3;
   vector<int>     rdcTdc;
   vector<int>     rdcPlaneId;
   vector<int>     rdcWireId;
   vector<int>     rdcLayerId;
   vector<int>     rdcPlaneNHit;
   Int_t           naiQRaw[4][7];
   Int_t           plasQRaw[4];
   Int_t           plasTRaw[4];
   Int_t           plasTimeRef;
   Int_t           rdcHit;
   Int_t           rdcHitSide[2];
   Double_t        rdcHitX[2];
   Double_t        rdcHitY[2];
   Double_t        rdcHitChi2[2];
   Double_t        rdcX[2];
   Double_t        rdcY[2];
   Double_t        rdcA[2];
   Double_t        rdcB[2];
   Double_t        rdcChi2[2];
   Double_t        rdcDL[2][7];
   Double_t        rdcTch[2][7];
   Double_t        rdcRes[2][7];
   Int_t           naiHit;
   Int_t           naiSide[1];
   Int_t           naiBarId[1];
   Int_t           naiHitQPed[1];
   Double_t        naiQPed[4][7];
   Double_t        naiBarQPed[2][7];
   Int_t           plasHit;
   Int_t           plasSide[1];
   Double_t        plasQPed[4];
   Double_t        plasBarQPed[2];
   Double_t        plasTCal[4];
   Double_t        plasTRef[4];
   Int_t           espriHit;
   Int_t           espriSide[1];

   // Set branch addresses.
   CalTreeESPRI->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeESPRI->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw0",&plasTdcRaw0);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw1",&plasTdcRaw1);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw2",&plasTdcRaw2);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw3",&plasTdcRaw3);
   CalTreeESPRI->SetBranchAddress("rdcTdc",&rdcTdc);
   CalTreeESPRI->SetBranchAddress("rdcPlaneId",&rdcPlaneId);
   CalTreeESPRI->SetBranchAddress("rdcWireId",&rdcWireId);
   CalTreeESPRI->SetBranchAddress("rdcLayerId",&rdcLayerId);
   CalTreeESPRI->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
   CalTreeESPRI->SetBranchAddress("naiQRaw",naiQRaw);
   CalTreeESPRI->SetBranchAddress("plasQRaw",plasQRaw);
   CalTreeESPRI->SetBranchAddress("plasTRaw",plasTRaw);
   CalTreeESPRI->SetBranchAddress("plasTimeRef",&plasTimeRef);
   CalTreeESPRI->SetBranchAddress("rdcHit",&rdcHit);
   CalTreeESPRI->SetBranchAddress("rdcHitSide",rdcHitSide);
   CalTreeESPRI->SetBranchAddress("rdcHitX",rdcHitX);
   CalTreeESPRI->SetBranchAddress("rdcHitY",rdcHitY);
   CalTreeESPRI->SetBranchAddress("rdcHitChi2",rdcHitChi2);
   CalTreeESPRI->SetBranchAddress("rdcX",rdcX);
   CalTreeESPRI->SetBranchAddress("rdcY",rdcY);
   CalTreeESPRI->SetBranchAddress("rdcA",rdcA);
   CalTreeESPRI->SetBranchAddress("rdcB",rdcB);
   CalTreeESPRI->SetBranchAddress("rdcChi2",rdcChi2);
   CalTreeESPRI->SetBranchAddress("rdcDL",rdcDL);
   CalTreeESPRI->SetBranchAddress("rdcTch",rdcTch);
   CalTreeESPRI->SetBranchAddress("rdcRes",rdcRes);
   CalTreeESPRI->SetBranchAddress("naiHit",&naiHit);
   CalTreeESPRI->SetBranchAddress("naiSide",naiSide);
   CalTreeESPRI->SetBranchAddress("naiBarId",naiBarId);
   CalTreeESPRI->SetBranchAddress("naiHitQPed",naiHitQPed);
   CalTreeESPRI->SetBranchAddress("naiQPed",naiQPed);
   CalTreeESPRI->SetBranchAddress("naiBarQPed",naiBarQPed);
   CalTreeESPRI->SetBranchAddress("plasHit",&plasHit);
   CalTreeESPRI->SetBranchAddress("plasSide",plasSide);
   CalTreeESPRI->SetBranchAddress("plasQPed",plasQPed);
   CalTreeESPRI->SetBranchAddress("plasBarQPed",plasBarQPed);
   CalTreeESPRI->SetBranchAddress("plasTCal",plasTCal);
   CalTreeESPRI->SetBranchAddress("plasTRef",plasTRef);
   CalTreeESPRI->SetBranchAddress("espriHit",&espriHit);
   CalTreeESPRI->SetBranchAddress("espriSide",espriSide);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// CalTreeESPRI->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = CalTreeESPRI->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += CalTreeESPRI->GetEntry(i);
//   }
}
