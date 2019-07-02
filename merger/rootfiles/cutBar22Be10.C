{
//========= Macro generated from object: Bar22Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar22Be10",7);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18341.7,2614.46);
   cutg->SetPoint(1,18486.1,2596.39);
   cutg->SetPoint(2,18547.2,2403.61);
   cutg->SetPoint(3,18441.7,2361.45);
   cutg->SetPoint(4,18352.8,2343.37);
   cutg->SetPoint(5,18333.3,2590.36);
   cutg->SetPoint(6,18341.7,2614.46);
   cutg->Draw("");
}
