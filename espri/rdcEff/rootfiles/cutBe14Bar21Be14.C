{
//========= Macro generated from object: Be14Bar21Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar21Be14",11);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18697.1,3179.68);
   cutg->SetPoint(1,18687.3,2973.02);
   cutg->SetPoint(2,18710.1,2829.51);
   cutg->SetPoint(3,18772,2812.28);
   cutg->SetPoint(4,18788.3,2938.58);
   cutg->SetPoint(5,18801.4,3133.75);
   cutg->SetPoint(6,18781.8,3196.9);
   cutg->SetPoint(7,18719.9,3271.53);
   cutg->SetPoint(8,18697.1,3196.9);
   cutg->SetPoint(9,18697.1,3196.9);
   cutg->SetPoint(10,18697.1,3179.68);
   cutg->Draw("");
}
