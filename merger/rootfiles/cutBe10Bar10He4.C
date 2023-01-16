{
//========= Macro generated from object: Be10Bar10He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar10He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18441.8,1084.27);
   cutg->SetPoint(1,18401.8,988.764);
   cutg->SetPoint(2,18391.9,882.022);
   cutg->SetPoint(3,18438.4,741.573);
   cutg->SetPoint(4,18581.5,780.899);
   cutg->SetPoint(5,18644.7,921.348);
   cutg->SetPoint(6,18654.7,1011.24);
   cutg->SetPoint(7,18568.2,1073.03);
   cutg->SetPoint(8,18498.3,1084.27);
   cutg->SetPoint(9,18465.1,1078.65);
   cutg->SetPoint(10,18445.1,1078.65);
   cutg->SetPoint(11,18441.8,1084.27);
   cutg->Draw("");
}
