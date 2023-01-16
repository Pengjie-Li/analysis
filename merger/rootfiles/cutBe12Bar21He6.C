{
//========= Macro generated from object: Be12Bar21He6/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar21He6",11);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18271.4,966.895);
   cutg->SetPoint(1,18239.5,886.986);
   cutg->SetPoint(2,18245.8,744.292);
   cutg->SetPoint(3,18287.4,710.046);
   cutg->SetPoint(4,18332.2,698.63);
   cutg->SetPoint(5,18392.9,698.63);
   cutg->SetPoint(6,18437.7,750);
   cutg->SetPoint(7,18479.2,818.493);
   cutg->SetPoint(8,18415.3,949.772);
   cutg->SetPoint(9,18456.8,915.525);
   cutg->SetPoint(10,18271.4,966.895);
   cutg->Draw("");
}
