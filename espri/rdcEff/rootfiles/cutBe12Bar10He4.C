{
//========= Macro generated from object: Be12Bar10He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar10He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18152.8,969.649);
   cutg->SetPoint(1,18050.7,865.815);
   cutg->SetPoint(2,17997.5,682.109);
   cutg->SetPoint(3,18009.8,514.377);
   cutg->SetPoint(4,18079.2,450.479);
   cutg->SetPoint(5,18242.6,490.415);
   cutg->SetPoint(6,18291.7,602.236);
   cutg->SetPoint(7,18422.4,905.751);
   cutg->SetPoint(8,18324.3,969.649);
   cutg->SetPoint(9,18242.6,977.636);
   cutg->SetPoint(10,18181.4,993.61);
   cutg->SetPoint(11,18152.8,969.649);
   cutg->Draw("");
}
