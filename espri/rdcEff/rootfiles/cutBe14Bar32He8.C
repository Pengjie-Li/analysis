{
//========= Macro generated from object: Be14Bar32He8/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar32He8",12);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1737.34,677.409);
   cutg->SetPoint(1,1642.93,619.428);
   cutg->SetPoint(2,1585.15,566.279);
   cutg->SetPoint(3,1600.65,472.865);
   cutg->SetPoint(4,1624.61,422.938);
   cutg->SetPoint(5,1754.26,463.202);
   cutg->SetPoint(6,1799.35,521.183);
   cutg->SetPoint(7,1827.54,595.269);
   cutg->SetPoint(8,1814.85,653.25);
   cutg->SetPoint(9,1768.35,669.356);
   cutg->SetPoint(10,1750.03,674.188);
   cutg->SetPoint(11,1737.34,677.409);
   cutg->Draw("");
}
