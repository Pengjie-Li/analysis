{
//========= Macro generated from object: Be14Bar31Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar31Be14",12);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1615.41,2917.22);
   cutg->SetPoint(1,1566.07,2149.01);
   cutg->SetPoint(2,1564.9,1433.77);
   cutg->SetPoint(3,1587.22,1149.01);
   cutg->SetPoint(4,1658.88,1142.38);
   cutg->SetPoint(5,1687.08,1473.51);
   cutg->SetPoint(6,1692.95,1804.64);
   cutg->SetPoint(7,1685.9,2188.74);
   cutg->SetPoint(8,1690.6,2592.72);
   cutg->SetPoint(9,1649.48,2963.58);
   cutg->SetPoint(10,1624.81,2963.58);
   cutg->SetPoint(11,1615.41,2917.22);
   cutg->Draw("same");
}
