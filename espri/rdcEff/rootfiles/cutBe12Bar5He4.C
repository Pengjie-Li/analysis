{
//========= Macro generated from object: Be12Bar5He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar5He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][5]+hodTRaw[1][5])");
   cutg->SetVarY("hodBarQCal[5]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18508.2,1033.55);
   cutg->SetPoint(1,18381.5,889.776);
   cutg->SetPoint(2,18373.4,618.211);
   cutg->SetPoint(3,18451,570.288);
   cutg->SetPoint(4,18573.5,658.147);
   cutg->SetPoint(5,18671.6,746.006);
   cutg->SetPoint(6,18724.7,897.764);
   cutg->SetPoint(7,18700.2,1065.5);
   cutg->SetPoint(8,18602.1,1105.43);
   cutg->SetPoint(9,18532.7,1065.5);
   cutg->SetPoint(10,18508.2,1033.55);
   cutg->Draw("");
}
