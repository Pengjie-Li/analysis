{
//========= Macro generated from object: Bar21Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Bar21Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18122.7,2119.86);
   cutg->SetPoint(1,18228.2,2239.73);
   cutg->SetPoint(2,18191.1,2445.21);
   cutg->SetPoint(3,18118.7,2502.28);
   cutg->SetPoint(4,18091.4,2348.17);
   cutg->SetPoint(5,18095.3,2325.34);
   cutg->SetPoint(6,18112.9,2154.11);
   cutg->SetPoint(7,18122.7,2119.86);
   cutg->Draw("");
}
