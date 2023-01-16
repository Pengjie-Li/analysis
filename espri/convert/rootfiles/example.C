{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Tue Jun  4 09:52:59 2019 by ROOT version5.34/20)
//   from TTree CalTreeESPRI/Convert Raw Cal Sync
//   found on file: run0360_ESPRI.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0360_ESPRI.root");
   if (!f) {
      f = new TFile("run0360_ESPRI.root");
   }
    f->GetObject("CalTreeESPRI",tree);

//Declaration of leaves types
   Int_t           EventNumber;
   Int_t           RunNumber;
   vector<int>     rdcTDC;
   vector<int>     rdcPlaneID;
   vector<int>     rdcWireID;
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
   Double_t        naiQId[2];
   Double_t        plasQCal[4];
   Double_t        plasQPed[4];
   Double_t        plasTCal[4];
   Double_t        plasQ[2];
   Double_t        plasT[2];

   // Set branch addresses.
   CalTreeESPRI->SetBranchAddress("EventNumber",&EventNumber);
   CalTreeESPRI->SetBranchAddress("RunNumber",&RunNumber);
   CalTreeESPRI->SetBranchAddress("rdcTDC",&rdcTDC);
   CalTreeESPRI->SetBranchAddress("rdcPlaneID",&rdcPlaneID);
   CalTreeESPRI->SetBranchAddress("rdcWireID",&rdcWireID);
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
