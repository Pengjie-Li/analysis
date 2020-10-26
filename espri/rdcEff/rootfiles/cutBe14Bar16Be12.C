{
//========= Macro generated from object: Be14Bar16Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar16Be12",16);
   cutg->SetVarX("0.5*(hodTRaw[0][16]+hodTRaw[1][16])");
   cutg->SetVarY("hodBarQCal[16]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18643.9,2936.21);
   cutg->SetPoint(1,18586.4,2799.04);
   cutg->SetPoint(2,18601.7,2469.82);
   cutg->SetPoint(3,18624.7,2380.66);
   cutg->SetPoint(4,18778.3,2428.67);
   cutg->SetPoint(5,18862.7,2579.56);
   cutg->SetPoint(6,18908.8,2730.45);
   cutg->SetPoint(7,18878.1,2936.21);
   cutg->SetPoint(8,18801.3,3004.8);
   cutg->SetPoint(9,18759.1,3196.85);
   cutg->SetPoint(10,18716.9,3313.44);
   cutg->SetPoint(11,18628.6,3189.99);
   cutg->SetPoint(12,18632.4,3039.09);
   cutg->SetPoint(13,18632.4,2970.51);
   cutg->SetPoint(14,18632.4,2970.51);
   cutg->SetPoint(15,18643.9,2936.21);
   cutg->Draw("same");
}
