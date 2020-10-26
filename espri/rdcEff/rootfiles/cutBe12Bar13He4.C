{
//========= Macro generated from object: Be12Bar13He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar13He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,17997.5,450.479);
   cutg->SetPoint(1,18152.8,506.39);
   cutg->SetPoint(2,18328.4,642.173);
   cutg->SetPoint(3,18324.3,921.725);
   cutg->SetPoint(4,18128.3,897.764);
   cutg->SetPoint(5,17993.5,809.904);
   cutg->SetPoint(6,17924,650.16);
   cutg->SetPoint(7,17944.4,530.351);
   cutg->SetPoint(8,17964.9,498.403);
   cutg->SetPoint(9,17993.5,490.415);
   cutg->SetPoint(10,17993.5,490.415);
   cutg->SetPoint(11,17997.5,450.479);
   cutg->Draw("");
}
