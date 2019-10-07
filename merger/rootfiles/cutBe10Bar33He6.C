{
//========= Macro generated from object: Be10Bar33He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar33He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][33]+hodTRaw[1][33])");
   cutg->SetVarY("hodBarQCal[33]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1582.14,400.131);
   cutg->SetPoint(1,1650.94,380.42);
   cutg->SetPoint(2,1689.17,478.975);
   cutg->SetPoint(3,1696.81,590.67);
   cutg->SetPoint(4,1658.59,597.24);
   cutg->SetPoint(5,1619.09,584.1);
   cutg->SetPoint(6,1585.96,564.389);
   cutg->SetPoint(7,1579.59,452.694);
   cutg->SetPoint(8,1579.59,413.272);
   cutg->SetPoint(9,1582.14,400.131);
   cutg->Draw("");
}
