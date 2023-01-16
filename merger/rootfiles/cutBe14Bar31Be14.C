{
//========= Macro generated from object: Be14Bar31Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar31Be14",12);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1604.92,1795.56);
   cutg->SetPoint(1,1555.69,1497.66);
   cutg->SetPoint(2,1565.35,1217.29);
   cutg->SetPoint(3,1602.99,1158.88);
   cutg->SetPoint(4,1654.15,1223.13);
   cutg->SetPoint(5,1671.53,1427.57);
   cutg->SetPoint(6,1674.42,1550.23);
   cutg->SetPoint(7,1652.22,1725.47);
   cutg->SetPoint(8,1633.88,1813.08);
   cutg->SetPoint(9,1613.61,1813.08);
   cutg->SetPoint(10,1602.99,1789.72);
   cutg->SetPoint(11,1604.92,1795.56);
   cutg->Draw("");
}
