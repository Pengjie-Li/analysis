{
//========= Macro generated from object: Bar30Central/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar30Central",7);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1495.67,2054.84);
   cutg->SetPoint(1,1501.01,1585.2);
   cutg->SetPoint(2,1572.23,1552.05);
   cutg->SetPoint(3,1574.01,2032.74);
   cutg->SetPoint(4,1501.01,2043.79);
   cutg->SetPoint(5,1501.01,2043.79);
   cutg->SetPoint(6,1495.67,2054.84);
   cutg->Draw("");
}
