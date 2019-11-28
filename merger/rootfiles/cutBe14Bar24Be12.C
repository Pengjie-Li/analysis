{
//========= Macro generated from object: Be14Bar24Be12/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("Be14Bar24Be12",11);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1591.44,1985.24);
   cutg->SetPoint(1,1580.9,1955.73);
   cutg->SetPoint(2,1567.2,1796.34);
   cutg->SetPoint(3,1572.47,1642.86);
   cutg->SetPoint(4,1586.17,1542.5);
   cutg->SetPoint(5,1618.84,1566.12);
   cutg->SetPoint(6,1620.95,1737.31);
   cutg->SetPoint(7,1628.33,1914.4);
   cutg->SetPoint(8,1615.68,1967.53);
   cutg->SetPoint(9,1593.55,1967.53);
   cutg->SetPoint(10,1591.44,1985.24);
   cutg->Draw("");
}
