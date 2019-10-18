{
//========= Macro generated from object: Be14Bar5He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar5He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][5]+hodTRaw[1][5])");
   cutg->SetVarY("hodBarQCal[5]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18451.6,860.759);
   cutg->SetPoint(1,18623.6,1029.54);
   cutg->SetPoint(2,18784.7,1092.83);
   cutg->SetPoint(3,18870.7,1092.83);
   cutg->SetPoint(4,18860,945.148);
   cutg->SetPoint(5,18806.2,871.308);
   cutg->SetPoint(6,18623.6,713.08);
   cutg->SetPoint(7,18516.1,670.886);
   cutg->SetPoint(8,18467.8,776.371);
   cutg->SetPoint(9,18478.5,691.983);
   cutg->SetPoint(10,18451.6,860.759);
   cutg->Draw("");
}
