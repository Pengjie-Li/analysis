{
//========= Macro generated from object: Be14Bar18He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar18He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][18]+hodTRaw[1][18])");
   cutg->SetVarY("hodBarQCal[18]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,17901.4,544.776);
   cutg->SetPoint(1,18008,521.814);
   cutg->SetPoint(2,18132.9,584.96);
   cutg->SetPoint(3,18157.3,722.732);
   cutg->SetPoint(4,18090.3,768.657);
   cutg->SetPoint(5,18011.1,734.214);
   cutg->SetPoint(6,17907.5,716.992);
   cutg->SetPoint(7,17880.1,682.549);
   cutg->SetPoint(8,17877,596.441);
   cutg->SetPoint(9,17901.4,544.776);
   cutg->SetPoint(10,17919.7,533.295);
   cutg->SetPoint(11,17901.4,544.776);
   cutg->Draw("");
}
