{
//========= Macro generated from object: Bar22Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar22Be12",8);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18227.9,2467.85);
   cutg->SetPoint(1,18357.1,2473.59);
   cutg->SetPoint(2,18355.2,2152.12);
   cutg->SetPoint(3,18282.8,2043.05);
   cutg->SetPoint(4,18241.6,2180.83);
   cutg->SetPoint(5,18233.8,2404.71);
   cutg->SetPoint(6,18247.5,2462.11);
   cutg->SetPoint(7,18227.9,2467.85);
   cutg->Draw("");
}
