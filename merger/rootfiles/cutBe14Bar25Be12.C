{
//========= Macro generated from object: Be14Bar25Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar25Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][25]+hodTRaw[1][25])");
   cutg->SetVarY("hodBarQCal[25]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,1589.77,2588.4);
   cutg->SetPoint(1,1614.75,3036.17);
   cutg->SetPoint(2,1629.95,3277.27);
   cutg->SetPoint(3,1640.81,3455.22);
   cutg->SetPoint(4,1665.79,3409.3);
   cutg->SetPoint(5,1667.96,3237.08);
   cutg->SetPoint(6,1653.84,2967.28);
   cutg->SetPoint(7,1636.47,2806.54);
   cutg->SetPoint(8,1623.44,2640.07);
   cutg->SetPoint(9,1613.66,2490.82);
   cutg->SetPoint(10,1596.29,2473.59);
   cutg->SetPoint(11,1607.15,2479.33);
   cutg->SetPoint(12,1590.86,2617.11);
   cutg->SetPoint(13,1589.77,2588.4);
   cutg->Draw("");
}
