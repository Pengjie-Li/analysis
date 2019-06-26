{
//========= Macro generated from object: Bar29Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar29Be14",8);
   cutg->SetVarX("0.5*(hodTRaw[0][29]+hodTRaw[1][29])");
   cutg->SetVarY("hodBarQCal[29]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1597.64,2165.26);
   cutg->SetPoint(1,1627.34,2608.3);
   cutg->SetPoint(2,1659.09,2404.36);
   cutg->SetPoint(3,1654.99,1961.32);
   cutg->SetPoint(4,1631.95,1827.71);
   cutg->SetPoint(5,1610.95,1799.58);
   cutg->SetPoint(6,1602.76,1834.74);
   cutg->SetPoint(7,1597.64,2165.26);
   cutg->Draw("");
}
