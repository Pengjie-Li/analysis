{
//========= Macro generated from object: Be14Bar33Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar33Be14",12);
   cutg->SetVarX("0.5*(hodTRaw[0][33]+hodTRaw[1][33])");
   cutg->SetVarY("hodBarQCal[33]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1659.94,1772.2);
   cutg->SetPoint(1,1666.7,1509.35);
   cutg->SetPoint(2,1640.64,1427.57);
   cutg->SetPoint(3,1597.2,1398.36);
   cutg->SetPoint(4,1561.49,1468.46);
   cutg->SetPoint(5,1559.56,1760.51);
   cutg->SetPoint(6,1576.93,1889.02);
   cutg->SetPoint(7,1606.85,1935.75);
   cutg->SetPoint(8,1638.71,1877.34);
   cutg->SetPoint(9,1656.08,1818.93);
   cutg->SetPoint(10,1659.94,1789.72);
   cutg->SetPoint(11,1659.94,1772.2);
   cutg->Draw("");
}
