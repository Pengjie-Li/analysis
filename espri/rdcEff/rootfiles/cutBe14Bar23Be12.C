{
//========= Macro generated from object: Be14Bar23Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar23Be12",15);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18313.8,2751.03);
   cutg->SetPoint(1,18298.5,2648.15);
   cutg->SetPoint(2,18294.7,2579.56);
   cutg->SetPoint(3,18302.3,2476.68);
   cutg->SetPoint(4,18329.2,2366.94);
   cutg->SetPoint(5,18367.6,2250.34);
   cutg->SetPoint(6,18444.3,2353.22);
   cutg->SetPoint(7,18482.7,2510.97);
   cutg->SetPoint(8,18513.4,2675.58);
   cutg->SetPoint(9,18471.2,2819.62);
   cutg->SetPoint(10,18402.1,2833.33);
   cutg->SetPoint(11,18359.9,2853.91);
   cutg->SetPoint(12,18333,2833.33);
   cutg->SetPoint(13,18333,2833.33);
   cutg->SetPoint(14,18313.8,2751.03);
   cutg->Draw("same");
}
