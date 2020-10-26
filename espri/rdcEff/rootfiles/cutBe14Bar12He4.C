{
//========= Macro generated from object: Be14Bar12He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar12He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18107.8,818.565);
   cutg->SetPoint(1,18226,934.599);
   cutg->SetPoint(2,18328.1,976.793);
   cutg->SetPoint(3,18376.4,881.857);
   cutg->SetPoint(4,18349.6,797.468);
   cutg->SetPoint(5,18258.2,681.435);
   cutg->SetPoint(6,18209.9,607.595);
   cutg->SetPoint(7,18134.7,575.949);
   cutg->SetPoint(8,18102.4,597.046);
   cutg->SetPoint(9,18097.1,808.017);
   cutg->SetPoint(10,18107.8,818.565);
   cutg->Draw("");
}
