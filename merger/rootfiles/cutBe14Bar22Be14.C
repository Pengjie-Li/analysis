{
//========= Macro generated from object: Be14Bar23Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar22Be14",9);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18672.2,2930.42);
   cutg->SetPoint(1,18626.6,2712.28);
   cutg->SetPoint(2,18672.2,2608.96);
   cutg->SetPoint(3,18711.3,2603.21);
   cutg->SetPoint(4,18747.1,2723.77);
   cutg->SetPoint(5,18756.9,2878.76);
   cutg->SetPoint(6,18740.6,2987.83);
   cutg->SetPoint(7,18756.9,2913.2);
   cutg->SetPoint(8,18672.2,2930.42);
   cutg->Draw("");
}
