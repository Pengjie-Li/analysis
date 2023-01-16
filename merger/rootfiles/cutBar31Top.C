{
//========= Macro generated from object: Bar31Top/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar31Top",7);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1531.11,3237.5);
   cutg->SetPoint(1,1549.57,1516.48);
   cutg->SetPoint(2,1665.24,1526.95);
   cutg->SetPoint(3,1638.03,3436.28);
   cutg->SetPoint(4,1542.77,3446.74);
   cutg->SetPoint(5,1534.02,3216.58);
   cutg->SetPoint(6,1531.11,3237.5);
   cutg->Draw("");
}
