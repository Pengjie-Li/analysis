{
//========= Macro generated from object: Be14Bar13He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar13He6",9);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18729.3,1007.75);
   cutg->SetPoint(1,18860.8,971.99);
   cutg->SetPoint(2,18953.2,1037.54);
   cutg->SetPoint(3,18917.7,1192.49);
   cutg->SetPoint(4,18839.5,1216.33);
   cutg->SetPoint(5,18779,1097.14);
   cutg->SetPoint(6,18718.6,1007.75);
   cutg->SetPoint(7,18718.6,1007.75);
   cutg->SetPoint(8,18729.3,1007.75);
   cutg->Draw("");
}
