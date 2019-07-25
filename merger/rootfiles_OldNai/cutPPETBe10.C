{
//========= Macro generated from object: ppET/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("ppET",7);
   cutg->SetVarX("protonTheta");
   cutg->SetVarY("(espriPlasDeltaE+2*espriNaiEnergy)");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,61.7216,84.387);
   cutg->SetPoint(1,68.9072,39.8379);
   cutg->SetPoint(2,70.7036,46.4304);
   cutg->SetPoint(3,63.3308,94.7751);
   cutg->SetPoint(4,61.3099,86.3847);
   cutg->SetPoint(5,61.7964,84.387);
   cutg->SetPoint(6,61.7216,84.387);
   cutg->Draw("");
}
