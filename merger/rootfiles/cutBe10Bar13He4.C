{
//========= Macro generated from object: Be10Bar13He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar13He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18358.6,977.528);
   cutg->SetPoint(1,18358.6,977.528);
   cutg->SetPoint(2,18318.7,780.899);
   cutg->SetPoint(3,18401.8,685.393);
   cutg->SetPoint(4,18488.4,752.809);
   cutg->SetPoint(5,18544.9,887.64);
   cutg->SetPoint(6,18461.7,966.292);
   cutg->SetPoint(7,18358.6,977.528);
   cutg->SetPoint(8,18385.2,971.91);
   cutg->SetPoint(9,18358.6,977.528);
   cutg->Draw("");
}
