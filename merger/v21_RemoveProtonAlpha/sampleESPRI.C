{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Mon May 13 15:58:09 2019 by ROOT version5.34/20)
//   from TTree CalTreeESPRI/Convert Raw Cal Sync
//   found on file: run0360_ESPRI.root_RdcParameters
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0360_ESPRI.root_RdcParameters");
   if (!f) {
      f = new TFile("run0360_ESPRI.root_RdcParameters");
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
   Double_t        naiQ[2][7];
   Double_t        naiQL;
   Double_t        naiQR;
   Double_t        naiQLId;
   Double_t        naiQRId;
   Double_t        plasQCal[4];
   Double_t        plasTCal[4];
   Double_t        plasQL;
   Double_t        plasQR;
   Double_t        plasTL;
   Double_t        plasTR;

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
   CalTreeESPRI->SetBranchAddress("naiQ",naiQ);
   CalTreeESPRI->SetBranchAddress("naiQL",&naiQL);
   CalTreeESPRI->SetBranchAddress("naiQR",&naiQR);
   CalTreeESPRI->SetBranchAddress("naiIdQL",&naiQLId);
   CalTreeESPRI->SetBranchAddress("naiIdQR",&naiQRId);
   CalTreeESPRI->SetBranchAddress("plasQCal",plasQCal);
   CalTreeESPRI->SetBranchAddress("plasTCal",plasTCal);
   CalTreeESPRI->SetBranchAddress("plasQL",&plasQL);
   CalTreeESPRI->SetBranchAddress("plasQR",&plasQR);
   CalTreeESPRI->SetBranchAddress("plasTL",&plasTL);
   CalTreeESPRI->SetBranchAddress("plasTR",&plasTR);

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
