{
//========= Macro generated from object: Be14Bar27Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar27Be12",11);
   cutg->SetVarX("0.5*(hodTRaw[0][27]+hodTRaw[1][27])");
   cutg->SetVarY("hodBarQCal[27]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1561.18,1941.7);
   cutg->SetPoint(1,1534.31,1667.35);
   cutg->SetPoint(2,1549.67,1516.46);
   cutg->SetPoint(3,1594.45,1482.17);
   cutg->SetPoint(4,1621.32,1667.35);
   cutg->SetPoint(5,1623.87,1859.4);
   cutg->SetPoint(6,1616.2,1982.85);
   cutg->SetPoint(7,1590.61,2010.29);
   cutg->SetPoint(8,1573.98,1975.99);
   cutg->SetPoint(9,1573.98,1975.99);
   cutg->SetPoint(10,1561.18,1941.7);
   cutg->Draw("same");
}
