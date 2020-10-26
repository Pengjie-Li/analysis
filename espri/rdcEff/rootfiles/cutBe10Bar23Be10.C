{
//========= Macro generated from object: Be10Bar23Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar23Be10",11);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18337.7,2770.55);
   cutg->SetPoint(1,18306.4,2610.73);
   cutg->SetPoint(2,18318.2,2450.91);
   cutg->SetPoint(3,18337.7,2428.08);
   cutg->SetPoint(4,18408.1,2468.04);
   cutg->SetPoint(5,18474.6,2605.02);
   cutg->SetPoint(6,18486.3,2702.05);
   cutg->SetPoint(7,18472.6,2747.72);
   cutg->SetPoint(8,18380.7,2810.5);
   cutg->SetPoint(9,18357.3,2810.5);
   cutg->SetPoint(10,18337.7,2770.55);
   cutg->Draw("");
}
