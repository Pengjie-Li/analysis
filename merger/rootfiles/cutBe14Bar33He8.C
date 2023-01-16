{
//========= Macro generated from object: Be14Bar33He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar33He8",10);
   cutg->SetVarX("0.5*(hodTRaw[0][33]+hodTRaw[1][33])");
   cutg->SetVarY("hodBarQCal[33]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1622.32,567.738);
   cutg->SetPoint(1,1695.43,636.625);
   cutg->SetPoint(2,1725.89,613.662);
   cutg->SetPoint(3,1724.88,556.257);
   cutg->SetPoint(4,1694.42,470.149);
   cutg->SetPoint(5,1634.5,470.149);
   cutg->SetPoint(6,1623.33,487.371);
   cutg->SetPoint(7,1625.37,561.998);
   cutg->SetPoint(8,1667,596.441);
   cutg->SetPoint(9,1622.32,567.738);
   cutg->Draw("");
}
