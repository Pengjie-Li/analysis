{
//========= Macro generated from object: Bar30Right/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar30Right",7);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1571.34,2043.79);
   cutg->SetPoint(1,1971.05,2071.42);
   cutg->SetPoint(2,1992.41,1535.47);
   cutg->SetPoint(3,1815.26,1463.64);
   cutg->SetPoint(4,1572.23,1546.52);
   cutg->SetPoint(5,1569.56,2065.89);
   cutg->SetPoint(6,1571.34,2043.79);
   cutg->Draw("");
}
