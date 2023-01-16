{
//========= Macro generated from object: Be10Bar20Be9/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar20Be9",11);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18285.3,2662.1);
   cutg->SetPoint(1,18232.5,2405.25);
   cutg->SetPoint(2,18254.5,2279.68);
   cutg->SetPoint(3,18333.7,2199.77);
   cutg->SetPoint(4,18366.8,2234.02);
   cutg->SetPoint(5,18413,2393.84);
   cutg->SetPoint(6,18410.8,2473.74);
   cutg->SetPoint(7,18391,2559.36);
   cutg->SetPoint(8,18355.8,2616.44);
   cutg->SetPoint(9,18294.1,2650.68);
   cutg->SetPoint(10,18285.3,2662.1);
   cutg->Draw("");
}
