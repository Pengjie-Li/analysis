{
//========= Macro generated from object: Be10Bar14He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar14He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18322,926.966);
   cutg->SetPoint(1,18282.1,887.64);
   cutg->SetPoint(2,18265.4,780.899);
   cutg->SetPoint(3,18308.7,707.865);
   cutg->SetPoint(4,18361.9,668.539);
   cutg->SetPoint(5,18401.8,702.247);
   cutg->SetPoint(6,18471.7,741.573);
   cutg->SetPoint(7,18478.4,853.933);
   cutg->SetPoint(8,18408.5,932.584);
   cutg->SetPoint(9,18368.6,932.584);
   cutg->SetPoint(10,18341.9,926.966);
   cutg->SetPoint(11,18322,926.966);
   cutg->Draw("");
}
