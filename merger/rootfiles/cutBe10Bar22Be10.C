{
//========= Macro generated from object: Be10Bar22Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar22Be10",14);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18353.6,2593.61);
   cutg->SetPoint(1,18358,2365.3);
   cutg->SetPoint(2,18391,2319.63);
   cutg->SetPoint(3,18439.4,2365.3);
   cutg->SetPoint(4,18498.9,2365.3);
   cutg->SetPoint(5,18534.1,2445.21);
   cutg->SetPoint(6,18527.5,2547.95);
   cutg->SetPoint(7,18492.3,2587.9);
   cutg->SetPoint(8,18459.3,2690.64);
   cutg->SetPoint(9,18408.6,2696.35);
   cutg->SetPoint(10,18382.2,2679.22);
   cutg->SetPoint(11,18344.8,2553.65);
   cutg->SetPoint(12,18344.8,2553.65);
   cutg->SetPoint(13,18353.6,2593.61);
   cutg->Draw("");
}
