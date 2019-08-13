{
//========= Macro generated from object: Bar30Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar30Be14",7);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1512.76,1859.36);
   cutg->SetPoint(1,1556.47,2129.16);
   cutg->SetPoint(2,1566.26,1859.36);
   cutg->SetPoint(3,1550.6,1578.07);
   cutg->SetPoint(4,1517.33,1514.93);
   cutg->SetPoint(5,1510.15,1865.1);
   cutg->SetPoint(6,1512.76,1859.36);
   cutg->Draw("");
}
