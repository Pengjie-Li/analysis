{
//========= Macro generated from object: Be14Bar24Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar24Be12",15);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,1584.34,1583.81);
   cutg->SetPoint(1,1623.44,1618.25);
   cutg->SetPoint(2,1624.52,1692.88);
   cutg->SetPoint(3,1626.69,1882.32);
   cutg->SetPoint(4,1621.26,1979.91);
   cutg->SetPoint(5,1619.09,2106.2);
   cutg->SetPoint(6,1622.35,2312.86);
   cutg->SetPoint(7,1622.35,2519.52);
   cutg->SetPoint(8,1590.86,2439.15);
   cutg->SetPoint(9,1581.08,2169.35);
   cutg->SetPoint(10,1577.82,1939.72);
   cutg->SetPoint(11,1568.05,1778.99);
   cutg->SetPoint(12,1574.57,1624);
   cutg->SetPoint(13,1587.6,1566.59);
   cutg->SetPoint(14,1584.34,1583.81);
   cutg->Draw("");
}
