{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.08/04
   
   TCutG *cutg = new TCutG("Be14Bar32Be14",10);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1602.5,1591.15);
   cutg->SetPoint(1,1605.29,1459.07);
   cutg->SetPoint(2,1612.37,1421.97);
   cutg->SetPoint(3,1624.74,1438.29);
   cutg->SetPoint(4,1630.02,1530.3);
   cutg->SetPoint(5,1622.04,1646.05);
   cutg->SetPoint(6,1614.37,1643.09);
   cutg->SetPoint(7,1604.3,1626.76);
   cutg->SetPoint(8,1603.5,1586.69);
   cutg->SetPoint(9,1602.5,1591.15);
   cutg->Draw("");
}
