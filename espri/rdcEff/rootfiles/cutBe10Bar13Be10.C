{
//========= Macro generated from object: Be10Bar13Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar13Be10",10);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18764.5,3106.74);
   cutg->SetPoint(1,18731.3,2994.38);
   cutg->SetPoint(2,18727.9,2803.37);
   cutg->SetPoint(3,18787.8,2769.66);
   cutg->SetPoint(4,18851,2797.75);
   cutg->SetPoint(5,18847.7,2966.29);
   cutg->SetPoint(6,18841.1,3095.51);
   cutg->SetPoint(7,18801.1,3095.51);
   cutg->SetPoint(8,18784.5,3101.12);
   cutg->SetPoint(9,18764.5,3106.74);
   cutg->Draw("");
}
