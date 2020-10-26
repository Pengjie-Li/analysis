{
//========= Macro generated from object: Beam/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Beam",14);
   cutg->SetVarX("TOF713");
   cutg->SetVarY("F13Q");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,234.319,866.447);
   cutg->SetPoint(1,234.016,812.425);
   cutg->SetPoint(2,234.036,731.393);
   cutg->SetPoint(3,234.143,665.366);
   cutg->SetPoint(4,234.485,620.348);
   cutg->SetPoint(5,234.955,611.345);
   cutg->SetPoint(6,235.317,641.357);
   cutg->SetPoint(7,235.483,701.381);
   cutg->SetPoint(8,235.346,794.418);
   cutg->SetPoint(9,235.121,833.433);
   cutg->SetPoint(10,234.838,857.443);
   cutg->SetPoint(11,234.485,872.449);
   cutg->SetPoint(12,234.358,869.448);
   cutg->SetPoint(13,234.319,866.447);
   cutg->Draw("same");
}
