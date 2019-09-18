{
//========= Macro generated from object: Be14Bar20Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar20Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18456,2766.36);
   cutg->SetPoint(1,18420.2,2645.81);
   cutg->SetPoint(2,18423.4,2553.96);
   cutg->SetPoint(3,18449.5,2479.33);
   cutg->SetPoint(4,18495.1,2467.85);
   cutg->SetPoint(5,18524.4,2490.82);
   cutg->SetPoint(6,18550.5,2553.96);
   cutg->SetPoint(7,18579.8,2657.29);
   cutg->SetPoint(8,18550.5,2737.66);
   cutg->SetPoint(9,18504.9,2789.32);
   cutg->SetPoint(10,18475.6,2783.58);
   cutg->SetPoint(11,18462.5,2772.1);
   cutg->SetPoint(12,18456,2766.36);
   cutg->Draw("");
}
