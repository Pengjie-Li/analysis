{
//========= Macro generated from object: ppCut/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("ppCut",10);
   cutg->SetVarX("protonTheta");
   cutg->SetVarY("(2*espriNaiEnergy+espriPlasDeltaE)");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,61.1036,47.9117);
   cutg->SetPoint(1,64.6545,65.9706);
   cutg->SetPoint(2,72.428,42.115);
   cutg->SetPoint(3,72.476,66.6394);
   cutg->SetPoint(4,65.6622,87.1507);
   cutg->SetPoint(5,64.8944,92.5015);
   cutg->SetPoint(6,61.3436,67.0853);
   cutg->SetPoint(7,60.5278,59.728);
   cutg->SetPoint(8,61.1996,49.0265);
   cutg->SetPoint(9,61.1036,47.9117);
   cutg->Draw("");
}
