{
//========= Macro generated from object: Be12Bar19Be12/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Be12Bar19Be12",15);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18374.1,2867.97);
   cutg->SetPoint(1,18345.7,2764.06);
   cutg->SetPoint(2,18345.7,2660.15);
   cutg->SetPoint(3,18370.5,2599.02);
   cutg->SetPoint(4,18398.9,2574.57);
   cutg->SetPoint(5,18445,2599.02);
   cutg->SetPoint(6,18494.7,2647.92);
   cutg->SetPoint(7,18519.5,2721.27);
   cutg->SetPoint(8,18512.4,2782.4);
   cutg->SetPoint(9,18480.5,2831.3);
   cutg->SetPoint(10,18466.3,2892.42);
   cutg->SetPoint(11,18423.7,2898.53);
   cutg->SetPoint(12,18402.4,2898.53);
   cutg->SetPoint(13,18384.7,2874.08);
   cutg->SetPoint(14,18374.1,2867.97);
   cutg->Draw("");
}
