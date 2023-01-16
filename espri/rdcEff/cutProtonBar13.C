{
//========= Macro generated from object: ProtonBar13/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("ProtonBar13",15);
   cutg->SetVarX("sqrt(naiQPed[2][3]*naiQPed[3][3])");
   cutg->SetVarY("sqrt(plasQPed[2]*plasQPed[3])");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);

   cutg->SetMarkerStyle(20);
   cutg->SetPoint(0,110.155,2551.39);
   cutg->SetPoint(1,441.25,1921.11);
   cutg->SetPoint(2,793.368,1451.9);
   cutg->SetPoint(3,1434.54,1031.71);
   cutg->SetPoint(4,2180.81,730.571);
   cutg->SetPoint(5,2701.11,562.495);
   cutg->SetPoint(6,2065.19,450.444);
   cutg->SetPoint(7,1550.16,597.51);
   cutg->SetPoint(8,1082.42,807.605);
   cutg->SetPoint(9,646.214,1136.75);
   cutg->SetPoint(10,367.674,1591.96);
   cutg->SetPoint(11,162.71,1956.13);
   cutg->SetPoint(12,83.8775,2201.24);
   cutg->SetPoint(13,99.6439,2453.35);
   cutg->SetPoint(14,110.155,2551.39);
   cutg->Draw("");
}
