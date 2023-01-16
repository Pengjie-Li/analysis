{
//========= Macro generated from object: Bar31Right/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar31Right",6);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1636.08,1589.72);
   cutg->SetPoint(1,1631.22,1244.47);
   cutg->SetPoint(2,1891.72,1254.93);
   cutg->SetPoint(3,1899.5,1589.72);
   cutg->SetPoint(4,1639,1610.64);
   cutg->SetPoint(5,1636.08,1589.72);
   cutg->Draw("");
}
