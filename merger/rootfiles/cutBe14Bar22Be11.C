{
//========= Macro generated from object: Be14Bar22Be11/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar22Be11",12);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18211.7,2324.34);
   cutg->SetPoint(1,18211.7,2261.19);
   cutg->SetPoint(2,18231.2,2175.09);
   cutg->SetPoint(3,18299.6,2146.38);
   cutg->SetPoint(4,18332.2,2192.31);
   cutg->SetPoint(5,18351.8,2289.9);
   cutg->SetPoint(6,18332.2,2387.49);
   cutg->SetPoint(7,18296.4,2439.15);
   cutg->SetPoint(8,18234.5,2467.85);
   cutg->SetPoint(9,18205.1,2364.52);
   cutg->SetPoint(10,18208.4,2335.82);
   cutg->SetPoint(11,18211.7,2324.34);
   cutg->Draw("");
}
