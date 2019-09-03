{
//========= Macro generated from object: Bar21Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar21Be12",8);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18226,2525.26);
   cutg->SetPoint(1,18271,2312.86);
   cutg->SetPoint(2,18345.4,2226.75);
   cutg->SetPoint(3,18423.7,2473.59);
   cutg->SetPoint(4,18359.1,2737.66);
   cutg->SetPoint(5,18222.1,2691.73);
   cutg->SetPoint(6,18231.9,2559.7);
   cutg->SetPoint(7,18226,2525.26);
   cutg->Draw("");
}
