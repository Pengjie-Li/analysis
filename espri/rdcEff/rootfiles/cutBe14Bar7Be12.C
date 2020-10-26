{
//========= Macro generated from object: Be14Bar7Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar7Be12",11);
   cutg->SetVarX("0.5*(hodTRaw[0][7]+hodTRaw[1][7])");
   cutg->SetVarY("hodBarQCal[7]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,19292.6,3628.94);
   cutg->SetPoint(1,19142.9,3272.29);
   cutg->SetPoint(2,19108.4,3100.82);
   cutg->SetPoint(3,19250.4,3039.09);
   cutg->SetPoint(4,19388.6,3258.57);
   cutg->SetPoint(5,19461.5,3546.64);
   cutg->SetPoint(6,19469.2,3676.95);
   cutg->SetPoint(7,19461.5,3759.26);
   cutg->SetPoint(8,19369.4,3738.68);
   cutg->SetPoint(9,19319.5,3670.1);
   cutg->SetPoint(10,19292.6,3628.94);
   cutg->Draw("same");
}
