{
//========= Macro generated from object: Bar28Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar28Be14",8);
   cutg->SetVarX("0.5*(hodTRaw[0][28]+hodTRaw[1][28])");
   cutg->SetVarY("hodBarQCal[28]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1614.54,1738.81);
   cutg->SetPoint(1,1649.11,2421.93);
   cutg->SetPoint(2,1673.25,2479.33);
   cutg->SetPoint(3,1675.86,2226.75);
   cutg->SetPoint(4,1654.33,1641.22);
   cutg->SetPoint(5,1628.24,1532.15);
   cutg->SetPoint(6,1606.05,1658.44);
   cutg->SetPoint(7,1614.54,1738.81);
   cutg->Draw("");
}
