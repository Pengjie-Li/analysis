{
//========= Macro generated from object: Bar20Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar20Be14",8);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18729.3,2943.84);
   cutg->SetPoint(1,18807.5,3234.78);
   cutg->SetPoint(2,18862.9,3106.22);
   cutg->SetPoint(3,18847.8,2842.35);
   cutg->SetPoint(4,18822.6,2781.46);
   cutg->SetPoint(5,18752,2740.87);
   cutg->SetPoint(6,18724.3,2943.84);
   cutg->SetPoint(7,18729.3,2943.84);
   cutg->Draw("");
}
