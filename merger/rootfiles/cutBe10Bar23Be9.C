{
//========= Macro generated from object: Be10Bar23Be9/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar23Be9",14);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18155.9,2542.24);
   cutg->SetPoint(1,18140.3,2445.21);
   cutg->SetPoint(2,18144.2,2365.3);
   cutg->SetPoint(3,18150,2291.1);
   cutg->SetPoint(4,18171.5,2228.31);
   cutg->SetPoint(5,18196.9,2222.6);
   cutg->SetPoint(6,18247.8,2273.97);
   cutg->SetPoint(7,18259.5,2353.88);
   cutg->SetPoint(8,18269.3,2450.91);
   cutg->SetPoint(9,18247.8,2530.82);
   cutg->SetPoint(10,18208.7,2616.44);
   cutg->SetPoint(11,18181.3,2599.32);
   cutg->SetPoint(12,18169.6,2593.61);
   cutg->SetPoint(13,18155.9,2542.24);
   cutg->Draw("");
}
