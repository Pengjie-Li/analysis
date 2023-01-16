{
//========= Macro generated from object: Be14Bar30Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar30Be14",12);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1533.49,2280.37);
   cutg->SetPoint(1,1491.99,2093.46);
   cutg->SetPoint(2,1484.27,1789.72);
   cutg->SetPoint(3,1495.85,1521.03);
   cutg->SetPoint(4,1526.74,1410.05);
   cutg->SetPoint(5,1583.69,1561.92);
   cutg->SetPoint(6,1600.1,1830.61);
   cutg->SetPoint(7,1597.2,2099.3);
   cutg->SetPoint(8,1580.79,2239.49);
   cutg->SetPoint(9,1534.46,2245.33);
   cutg->SetPoint(10,1530.6,2257.01);
   cutg->SetPoint(11,1533.49,2280.37);
   cutg->Draw("same");
}
