{
//========= Macro generated from object: Bar31Bottom/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar31Bottom",6);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1560.27,1270.62);
   cutg->SetPoint(1,1617.61,182.564);
   cutg->SetPoint(2,1763.42,208.719);
   cutg->SetPoint(3,1708.01,1228.78);
   cutg->SetPoint(4,1559.29,1270.62);
   cutg->SetPoint(5,1560.27,1270.62);
   cutg->Draw("");
}
