{
//========= Macro generated from object: Be14Bar18Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar18Be12",16);
   cutg->SetVarX("0.5*(hodTRaw[0][18]+hodTRaw[1][18])");
   cutg->SetVarY("hodBarQCal[18]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18555.7,3045.95);
   cutg->SetPoint(1,18524.9,2936.21);
   cutg->SetPoint(2,18521.1,2847.05);
   cutg->SetPoint(3,18532.6,2613.85);
   cutg->SetPoint(4,18571,2572.7);
   cutg->SetPoint(5,18667,2634.43);
   cutg->SetPoint(6,18778.3,2757.89);
   cutg->SetPoint(7,18789.8,2888.2);
   cutg->SetPoint(8,18755.2,3032.24);
   cutg->SetPoint(9,18690,3128.26);
   cutg->SetPoint(10,18647.8,3107.68);
   cutg->SetPoint(11,18636.3,3299.73);
   cutg->SetPoint(12,18544.1,3183.13);
   cutg->SetPoint(13,18536.5,3080.25);
   cutg->SetPoint(14,18536.5,3080.25);
   cutg->SetPoint(15,18555.7,3045.95);
   cutg->Draw("same");
}
