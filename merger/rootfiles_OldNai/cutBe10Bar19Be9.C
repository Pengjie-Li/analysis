{
//========= Macro generated from object: Be10Bar19Be9/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar19Be9",12);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18338.2,2941.78);
   cutg->SetPoint(1,18294.1,2759.13);
   cutg->SetPoint(2,18261.1,2644.98);
   cutg->SetPoint(3,18289.7,2576.48);
   cutg->SetPoint(4,18355.8,2525.11);
   cutg->SetPoint(5,18437.2,2587.9);
   cutg->SetPoint(6,18441.6,2684.93);
   cutg->SetPoint(7,18452.7,2839.04);
   cutg->SetPoint(8,18419.6,2924.66);
   cutg->SetPoint(9,18355.8,2981.74);
   cutg->SetPoint(10,18347,2970.32);
   cutg->SetPoint(11,18338.2,2941.78);
   cutg->Draw("");
}
