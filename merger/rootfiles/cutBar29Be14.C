{
//========= Macro generated from object: Bar29Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar29Be14",8);
   cutg->SetVarX("0.5*(hodTRaw[0][29]+hodTRaw[1][29])");
   cutg->SetVarY("hodBarQCal[29]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1597.57,1962.69);
   cutg->SetPoint(1,1630.85,2599.89);
   cutg->SetPoint(2,1655.64,2376);
   cutg->SetPoint(3,1651.07,1974.17);
   cutg->SetPoint(4,1626.28,1733.07);
   cutg->SetPoint(5,1602.14,1830.65);
   cutg->SetPoint(6,1600.84,2031.57);
   cutg->SetPoint(7,1597.57,1962.69);
   cutg->Draw("");
}
