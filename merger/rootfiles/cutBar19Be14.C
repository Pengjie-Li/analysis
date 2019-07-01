{
//========= Macro generated from object: Bar19Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar19Be14",7);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18797.4,3532.48);
   cutg->SetPoint(1,18767.1,2984.44);
   cutg->SetPoint(2,18908.3,2943.84);
   cutg->SetPoint(3,18951.1,3512.18);
   cutg->SetPoint(4,18943.5,3613.67);
   cutg->SetPoint(5,18804.9,3573.07);
   cutg->SetPoint(6,18797.4,3532.48);
   cutg->Draw("");
}
