{
//========= Macro generated from object: Be12Bar7He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar7He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][7]+hodTRaw[1][7])");
   cutg->SetVarY("hodBarQCal[7]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18369.3,977.636);
   cutg->SetPoint(1,18242.6,793.93);
   cutg->SetPoint(2,18234.5,642.173);
   cutg->SetPoint(3,18279.4,474.441);
   cutg->SetPoint(4,18381.5,522.364);
   cutg->SetPoint(5,18528.6,642.173);
   cutg->SetPoint(6,18618.5,841.853);
   cutg->SetPoint(7,18573.5,993.61);
   cutg->SetPoint(8,18471.4,961.661);
   cutg->SetPoint(9,18414.2,985.623);
   cutg->SetPoint(10,18414.2,985.623);
   cutg->SetPoint(11,18369.3,977.636);
   cutg->Draw("");
}
