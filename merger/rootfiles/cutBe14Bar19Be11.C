{
//========= Macro generated from object: Be14Bar19Be11/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar19Be11",14);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18342,2886.91);
   cutg->SetPoint(1,18342,2720.44);
   cutg->SetPoint(2,18345.2,2651.55);
   cutg->SetPoint(3,18374.6,2617.11);
   cutg->SetPoint(4,18374.6,2617.11);
   cutg->SetPoint(5,18443,2668.77);
   cutg->SetPoint(6,18456,2731.92);
   cutg->SetPoint(7,18446.2,2818.03);
   cutg->SetPoint(8,18439.7,2881.17);
   cutg->SetPoint(9,18403.9,2898.39);
   cutg->SetPoint(10,18377.8,2886.91);
   cutg->SetPoint(11,18355,2881.17);
   cutg->SetPoint(12,18345.2,2875.43);
   cutg->SetPoint(13,18342,2886.91);
   cutg->Draw("");
}
