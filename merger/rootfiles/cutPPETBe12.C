{
//========= Macro generated from object: ppET/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("ppET",7);
   cutg->SetVarX("protonTheta");
   cutg->SetVarY("(espriPlasDeltaE+2*espriNaiEnergy)");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,62.2216,84.387);
   cutg->SetPoint(1,69.4072,39.8379);
   cutg->SetPoint(2,71.2036,46.4304);
   cutg->SetPoint(3,63.8308,94.7751);
   cutg->SetPoint(4,61.8099,86.3847);
   cutg->SetPoint(5,62.2964,84.387);
   cutg->SetPoint(6,62.2216,84.387);
   cutg->Draw("");
}
