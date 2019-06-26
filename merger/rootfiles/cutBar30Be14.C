{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar30Be14",10);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1516.77,1988.67);
   cutg->SetPoint(1,1496.31,1752.51);
   cutg->SetPoint(2,1521.64,1609.2);
   cutg->SetPoint(3,1543.06,1580.94);
   cutg->SetPoint(4,1565.47,1617.27);
   cutg->SetPoint(5,1579.1,1794.9);
   cutg->SetPoint(6,1573.26,1954.36);
   cutg->SetPoint(7,1549.88,2055.28);
   cutg->SetPoint(8,1520.66,2037.11);
   cutg->SetPoint(9,1516.77,1988.67);
   cutg->Draw("");
}
