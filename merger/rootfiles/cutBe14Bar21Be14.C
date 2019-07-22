{
//========= Macro generated from object: Bar21Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar21Be14",7);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18653.7,3255.07);
   cutg->SetPoint(1,18671.4,2828.82);
   cutg->SetPoint(2,18784.8,2761.16);
   cutg->SetPoint(3,18802.4,3228.01);
   cutg->SetPoint(4,18757.1,3376.86);
   cutg->SetPoint(5,18668.9,3349.8);
   cutg->SetPoint(6,18653.7,3255.07);
   cutg->Draw("");
}
