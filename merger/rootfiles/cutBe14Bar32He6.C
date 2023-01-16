{
//========= Macro generated from object: Be14Bar32He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar32He6",7);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1511.64,326.636);
   cutg->SetPoint(1,1484.22,332.377);
   cutg->SetPoint(2,1487.27,539.036);
   cutg->SetPoint(3,1529.91,447.187);
   cutg->SetPoint(4,1524.84,332.377);
   cutg->SetPoint(5,1513.67,315.155);
   cutg->SetPoint(6,1511.64,326.636);
   cutg->Draw("");
}
