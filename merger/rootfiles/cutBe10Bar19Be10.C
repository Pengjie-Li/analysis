{
//========= Macro generated from object: Be10Bar19Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar19Be10",12);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18538.5,3135.84);
   cutg->SetPoint(1,18492.3,3033.11);
   cutg->SetPoint(2,18487.9,2861.87);
   cutg->SetPoint(3,18490.1,2776.26);
   cutg->SetPoint(4,18512.1,2690.64);
   cutg->SetPoint(5,18587,2702.05);
   cutg->SetPoint(6,18639.8,2879);
   cutg->SetPoint(7,18657.4,2976.03);
   cutg->SetPoint(8,18628.8,3084.47);
   cutg->SetPoint(9,18582.6,3175.8);
   cutg->SetPoint(10,18542.9,3170.09);
   cutg->SetPoint(11,18538.5,3135.84);
   cutg->Draw("");
}
