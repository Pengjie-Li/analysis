{
//========= Macro generated from object: Be14Bar20Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar20Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18440.5,2819.62);
   cutg->SetPoint(1,18402.1,2709.88);
   cutg->SetPoint(2,18402.1,2572.7);
   cutg->SetPoint(3,18463.5,2414.95);
   cutg->SetPoint(4,18544.1,2449.25);
   cutg->SetPoint(5,18632.4,2538.41);
   cutg->SetPoint(6,18667,2661.87);
   cutg->SetPoint(7,18647.8,2792.18);
   cutg->SetPoint(8,18574.8,2853.91);
   cutg->SetPoint(9,18517.3,2895.06);
   cutg->SetPoint(10,18478.9,2874.49);
   cutg->SetPoint(11,18478.9,2874.49);
   cutg->SetPoint(12,18440.5,2819.62);
   cutg->Draw("same");
}
