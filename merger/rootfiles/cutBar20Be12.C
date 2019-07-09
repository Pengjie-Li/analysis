{
//========= Macro generated from object: Bar20Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar20Be12",8);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18282.8,2519.52);
   cutg->SetPoint(1,18325.8,2255.45);
   cutg->SetPoint(2,18382.6,2226.75);
   cutg->SetPoint(3,18449.1,2347.3);
   cutg->SetPoint(4,18429.5,2502.3);
   cutg->SetPoint(5,18361,2565.44);
   cutg->SetPoint(6,18316,2508.04);
   cutg->SetPoint(7,18282.8,2519.52);
   cutg->Draw("");
}
