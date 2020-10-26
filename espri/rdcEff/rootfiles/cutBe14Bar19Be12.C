{
//========= Macro generated from object: Be14Bar19Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar19Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18501.9,3148.83);
   cutg->SetPoint(1,18448.2,3032.24);
   cutg->SetPoint(2,18448.2,2895.06);
   cutg->SetPoint(3,18459.7,2771.6);
   cutg->SetPoint(4,18475.1,2703.02);
   cutg->SetPoint(5,18532.6,2709.88);
   cutg->SetPoint(6,18620.9,2799.04);
   cutg->SetPoint(7,18693.8,2895.06);
   cutg->SetPoint(8,18701.5,3018.52);
   cutg->SetPoint(9,18693.8,3176.27);
   cutg->SetPoint(10,18640.1,3258.57);
   cutg->SetPoint(11,18574.8,3251.71);
   cutg->SetPoint(12,18540.3,3203.7);
   cutg->SetPoint(13,18501.9,3148.83);
   cutg->Draw("same");
}
