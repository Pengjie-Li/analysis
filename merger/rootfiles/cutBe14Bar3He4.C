{
//========= Macro generated from object: Be14Bar3He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar3He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][3]+hodTRaw[1][3])");
   cutg->SetVarY("hodBarQCal[3]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18543,881.857);
   cutg->SetPoint(1,18661.2,1071.73);
   cutg->SetPoint(2,18752.5,1082.28);
   cutg->SetPoint(3,18790.1,987.342);
   cutg->SetPoint(4,18790.1,892.405);
   cutg->SetPoint(5,18714.9,797.468);
   cutg->SetPoint(6,18607.4,713.08);
   cutg->SetPoint(7,18559.1,776.371);
   cutg->SetPoint(8,18532.2,892.405);
   cutg->SetPoint(9,18532.2,892.405);
   cutg->SetPoint(10,18543,881.857);
   cutg->Draw("");
}
