{
//========= Macro generated from object: Bar22Be14/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar22Be14",7);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18638.6,2646.14);
   cutg->SetPoint(1,18754.5,2578.48);
   cutg->SetPoint(2,18769.7,2930.31);
   cutg->SetPoint(3,18684,3025.03);
   cutg->SetPoint(4,18595.8,2869.42);
   cutg->SetPoint(5,18636.1,2673.21);
   cutg->SetPoint(6,18638.6,2646.14);
   cutg->Draw("");
}
