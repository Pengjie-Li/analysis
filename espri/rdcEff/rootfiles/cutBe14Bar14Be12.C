{
//========= Macro generated from object: Be14Bar14Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar14Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18762.9,2956.79);
   cutg->SetPoint(1,18674.6,2805.9);
   cutg->SetPoint(2,18640.1,2730.45);
   cutg->SetPoint(3,18647.8,2593.28);
   cutg->SetPoint(4,18697.7,2469.82);
   cutg->SetPoint(5,18786,2538.41);
   cutg->SetPoint(6,18893.4,2600.14);
   cutg->SetPoint(7,19008.6,2668.72);
   cutg->SetPoint(8,18993.2,2812.76);
   cutg->SetPoint(9,18931.8,2949.93);
   cutg->SetPoint(10,18881.9,3004.8);
   cutg->SetPoint(11,18816.7,2991.08);
   cutg->SetPoint(12,18797.5,2984.22);
   cutg->SetPoint(13,18762.9,2956.79);
   cutg->Draw("same");
}
