{
//========= Macro generated from object: Be14Bar20Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar20Be14",13);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18791.6,3150.98);
   cutg->SetPoint(1,18755.8,2990.24);
   cutg->SetPoint(2,18755.8,2944.32);
   cutg->SetPoint(3,18775.3,2846.73);
   cutg->SetPoint(4,18788.3,2812.28);
   cutg->SetPoint(5,18814.4,2869.69);
   cutg->SetPoint(6,18833.9,2955.8);
   cutg->SetPoint(7,18860,3064.87);
   cutg->SetPoint(8,18850.2,3145.24);
   cutg->SetPoint(9,18833.9,3179.68);
   cutg->SetPoint(10,18817.7,3179.68);
   cutg->SetPoint(11,18794.9,3145.24);
   cutg->SetPoint(12,18791.6,3150.98);
   cutg->Draw("");
}
