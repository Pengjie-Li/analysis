{
//========= Macro generated from object: Be14Bar23Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar23Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18374.6,2404.71);
   cutg->SetPoint(1,18433.2,2508.04);
   cutg->SetPoint(2,18462.5,2576.92);
   cutg->SetPoint(3,18439.7,2703.21);
   cutg->SetPoint(4,18377.8,2749.14);
   cutg->SetPoint(5,18332.2,2708.96);
   cutg->SetPoint(6,18319.2,2634.33);
   cutg->SetPoint(7,18306.1,2582.66);
   cutg->SetPoint(8,18302.9,2519.52);
   cutg->SetPoint(9,18319.2,2427.67);
   cutg->SetPoint(10,18345.2,2398.97);
   cutg->SetPoint(11,18371.3,2387.49);
   cutg->SetPoint(12,18374.6,2404.71);
   cutg->Draw("");
}
