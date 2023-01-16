{
//========= Macro generated from object: Be14Bar15He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar15He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][15]+hodTRaw[1][15])");
   cutg->SetVarY("hodBarQCal[15]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18718.6,983.909);
   cutg->SetPoint(1,18811,971.99);
   cutg->SetPoint(2,18857.2,1061.38);
   cutg->SetPoint(3,18828.8,1150.77);
   cutg->SetPoint(4,18715,1132.9);
   cutg->SetPoint(5,18675.9,1091.18);
   cutg->SetPoint(6,18690.2,960.071);
   cutg->SetPoint(7,18715,960.071);
   cutg->SetPoint(8,18715,960.071);
   cutg->SetPoint(9,18718.6,983.909);
   cutg->Draw("");
}
