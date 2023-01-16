{
//========= Macro generated from object: Be14Bar28He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar27He6",7);
   cutg->SetVarX("0.5*(hodTRaw[0][28]+hodTRaw[1][28])");
   cutg->SetVarY("hodBarQCal[28]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1508.59,424.225);
   cutg->SetPoint(1,1544.13,418.484);
   cutg->SetPoint(2,1549.21,556.257);
   cutg->SetPoint(3,1529.91,573.479);
   cutg->SetPoint(4,1507.58,475.89);
   cutg->SetPoint(5,1501.48,424.225);
   cutg->SetPoint(6,1508.59,424.225);
   cutg->Draw("");
}
