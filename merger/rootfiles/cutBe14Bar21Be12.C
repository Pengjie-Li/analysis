{
//========= Macro generated from object: Be14Bar21Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar21Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18374.6,2835.25);
   cutg->SetPoint(1,18374.6,2674.51);
   cutg->SetPoint(2,18374.6,2548.22);
   cutg->SetPoint(3,18426.7,2496.56);
   cutg->SetPoint(4,18482.1,2519.52);
   cutg->SetPoint(5,18537.5,2576.92);
   cutg->SetPoint(6,18566.8,2708.96);
   cutg->SetPoint(7,18504.9,2835.25);
   cutg->SetPoint(8,18459.3,2846.73);
   cutg->SetPoint(9,18416.9,2858.21);
   cutg->SetPoint(10,18390.9,2852.47);
   cutg->SetPoint(11,18381.1,2835.25);
   cutg->SetPoint(12,18374.6,2835.25);
   cutg->Draw("");
}
