{
//========= Macro generated from object: Be12Bar3He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar3He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][3]+hodTRaw[1][3])");
   cutg->SetVarY("hodBarQCal[3]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18618.5,1153.35);
   cutg->SetPoint(1,18487.7,1137.38);
   cutg->SetPoint(2,18418.3,905.751);
   cutg->SetPoint(3,18446.9,698.083);
   cutg->SetPoint(4,18491.8,578.275);
   cutg->SetPoint(5,18602.1,634.185);
   cutg->SetPoint(6,18683.8,753.994);
   cutg->SetPoint(7,18687.9,1097.44);
   cutg->SetPoint(8,18638.9,1153.35);
   cutg->SetPoint(9,18618.5,1153.35);
   cutg->Draw("");
}
