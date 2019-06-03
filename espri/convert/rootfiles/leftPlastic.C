{
//========= Macro generated from object: leftPlastic/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("leftPlastic",6);
   cutg->SetVarX("plasTCal[1]");
   cutg->SetVarY("plasTCal[0]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineWidth(3);
   cutg->SetLineColor(2);
   
   cutg->SetPoint(0,-27019.4,-24945.9);
   cutg->SetPoint(1,-22534.1,-20989.4);
   cutg->SetPoint(2,-21412.8,-22282.9);
   cutg->SetPoint(3,-25225.3,-26239.4);
   cutg->SetPoint(4,-26795.1,-25478.6);
   cutg->SetPoint(5,-27019.4,-24945.9);
   cutg->Draw("");
}
