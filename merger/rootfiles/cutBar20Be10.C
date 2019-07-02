{
//========= Macro generated from object: Bar20Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar20Be10",7);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18458.3,2789.16);
   cutg->SetPoint(1,18616.7,2759.04);
   cutg->SetPoint(2,18613.9,2512.05);
   cutg->SetPoint(3,18477.8,2457.83);
   cutg->SetPoint(4,18416.7,2548.19);
   cutg->SetPoint(5,18441.7,2831.33);
   cutg->SetPoint(6,18458.3,2789.16);
   cutg->Draw("");
}
