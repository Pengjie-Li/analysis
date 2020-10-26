{
//========= Macro generated from object: Be12Bar4He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar4He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][4]+hodTRaw[1][4])");
   cutg->SetVarY("hodBarQCal[4]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18549,1041.53);
   cutg->SetPoint(1,18385.6,905.751);
   cutg->SetPoint(2,18377.5,650.16);
   cutg->SetPoint(3,18430.6,530.351);
   cutg->SetPoint(4,18573.5,634.185);
   cutg->SetPoint(5,18683.8,793.93);
   cutg->SetPoint(6,18720.6,1001.6);
   cutg->SetPoint(7,18622.5,1097.44);
   cutg->SetPoint(8,18573.5,1081.47);
   cutg->SetPoint(9,18549,1041.53);
   cutg->Draw("");
}
