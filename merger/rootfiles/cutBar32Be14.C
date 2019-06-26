{
//========= Macro generated from object: Bar32Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar32Be14",9);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1602.14,1626.62);
   cutg->SetPoint(1,1598.83,1514.2);
   cutg->SetPoint(2,1606.43,1417.05);
   cutg->SetPoint(3,1620.79,1430.92);
   cutg->SetPoint(4,1630.86,1516.97);
   cutg->SetPoint(5,1626.74,1646.05);
   cutg->SetPoint(6,1612.37,1690.46);
   cutg->SetPoint(7,1612.37,1690.46);
   cutg->SetPoint(8,1602.14,1626.62);
   cutg->Draw("");
}
