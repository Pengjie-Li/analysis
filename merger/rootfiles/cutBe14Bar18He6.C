{
//========= Macro generated from object: Be14Bar18He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar18He6",11);
   cutg->SetVarX("0.5*(hodTRaw[0][18]+hodTRaw[1][18])");
   cutg->SetVarY("hodBarQCal[18]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18559.4,837.543);
   cutg->SetPoint(1,18693.4,831.803);
   cutg->SetPoint(2,18757.4,958.094);
   cutg->SetPoint(3,18705.6,1141.79);
   cutg->SetPoint(4,18626.4,1181.97);
   cutg->SetPoint(5,18577.7,1107.35);
   cutg->SetPoint(6,18559.4,1009.76);
   cutg->SetPoint(7,18553.3,940.873);
   cutg->SetPoint(8,18574.6,837.543);
   cutg->SetPoint(9,18583.8,826.062);
   cutg->SetPoint(10,18559.4,837.543);
   cutg->Draw("");
}
