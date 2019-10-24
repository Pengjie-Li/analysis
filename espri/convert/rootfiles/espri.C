{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Thu Oct 24 13:55:11 2019 by ROOT version5.34/20)
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
   vector<int>     rdc;
   vector<int>     rdcPlaneId;
   vector<int>     rdcWireId;
   vector<int>     rdcLayerId;
   vector<int>     rdcPlaneNHit;
   Int_t           naiQRaw[4][7];
   Int_t           plasQRaw[4];
   Int_t           plasTRaw[4];
   Int_t           plasTimeRef;
   Int_t           rdcMult;
   Double_t        rdcX[2];
   Double_t        rdcY[2];
   Double_t        rdcA[2];
   Double_t        rdcB[2];
   Double_t        rdcChi2[2];
   Double_t        rdcDL[2][7];
   Double_t        rdcTch[2][7];
   Double_t        rdcRes[2][7];
   Double_t        naiQCal[4][7];
   Double_t        naiQPed[4][7];
   Double_t        naiBarQCal[2][7];
   Double_t        naiQ[2];
   Int_t           naiQId[2];
   Double_t        plasQCal[4];
   Double_t        plasQPed[4];
   Double_t        plasTCal[4];
   Double_t        plasQ[2];
   Double_t        plasT[2];

   // Set branch addresses.
   CalTreeESPRI->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeESPRI->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw0",&plasTdcRaw0);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw1",&plasTdcRaw1);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw2",&plasTdcRaw2);
   CalTreeESPRI->SetBranchAddress("plasTdcRaw3",&plasTdcRaw3);
   CalTreeESPRI->SetBranchAddress("rdc",&rdc);
   CalTreeESPRI->SetBranchAddress("rdcPlaneId",&rdcPlaneId);
   CalTreeESPRI->SetBranchAddress("rdcWireId",&rdcWireId);
   CalTreeESPRI->SetBranchAddress("rdcLayerId",&rdcLayerId);
   CalTreeESPRI->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
   CalTreeESPRI->SetBranchAddress("naiQRaw",naiQRaw);
   CalTreeESPRI->SetBranchAddress("plasQRaw",plasQRaw);
   CalTreeESPRI->SetBranchAddress("plasTRaw",plasTRaw);
   CalTreeESPRI->SetBranchAddress("plasTimeRef",&plasTimeRef);
   CalTreeESPRI->SetBranchAddress("rdcMult",&rdcMult);
   CalTreeESPRI->SetBranchAddress("rdcX",rdcX);
   CalTreeESPRI->SetBranchAddress("rdcY",rdcY);
   CalTreeESPRI->SetBranchAddress("rdcA",rdcA);
   CalTreeESPRI->SetBranchAddress("rdcB",rdcB);
   CalTreeESPRI->SetBranchAddress("rdcChi2",rdcChi2);
   CalTreeESPRI->SetBranchAddress("rdcDL",rdcDL);
   CalTreeESPRI->SetBranchAddress("rdcTch",rdcTch);
   CalTreeESPRI->SetBranchAddress("rdcRes",rdcRes);
   CalTreeESPRI->SetBranchAddress("naiQCal",naiQCal);
   CalTreeESPRI->SetBranchAddress("naiQPed",naiQPed);
   CalTreeESPRI->SetBranchAddress("naiBarQCal",naiBarQCal);
   CalTreeESPRI->SetBranchAddress("naiQ",naiQ);
   CalTreeESPRI->SetBranchAddress("naiQId",naiQId);
   CalTreeESPRI->SetBranchAddress("plasQCal",plasQCal);
   CalTreeESPRI->SetBranchAddress("plasQPed",plasQPed);
   CalTreeESPRI->SetBranchAddress("plasTCal",plasTCal);
   CalTreeESPRI->SetBranchAddress("plasQ",plasQ);
   CalTreeESPRI->SetBranchAddress("plasT",plasT);

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
