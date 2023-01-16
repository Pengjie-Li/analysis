{
//========= Macro generated from object: Background/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Background",5);
   cutg->SetVarX("espriAngle");
   cutg->SetVarY("protonEnergy");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,50.1027,22.774);
   cutg->SetPoint(1,52.2539,21.9178);
   cutg->SetPoint(2,52.3502,131.721);
   cutg->SetPoint(3,50.1348,131.935);
   cutg->SetPoint(4,50.1027,22.774);
   cutg->Draw("same");
}
