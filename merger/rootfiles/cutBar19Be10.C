{
//========= Macro generated from object: Bar19Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Bar19Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18181.3,2684.93);
   cutg->SetPoint(1,18253.6,2759.13);
   cutg->SetPoint(2,18304.5,2627.85);
   cutg->SetPoint(3,18286.9,2376.71);
   cutg->SetPoint(4,18200.9,2393.84);
   cutg->SetPoint(5,18169.6,2530.82);
   cutg->SetPoint(6,18185.2,2673.52);
   cutg->SetPoint(7,18181.3,2684.93);
   cutg->Draw("");
}
