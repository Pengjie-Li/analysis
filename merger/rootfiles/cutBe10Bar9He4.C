{
//========= Macro generated from object: Be10Bar9He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar9He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][9]+hodTRaw[1][9])");
   cutg->SetVarY("hodBarQCal[9]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18498.3,1016.85);
   cutg->SetPoint(1,18448.4,932.584);
   cutg->SetPoint(2,18451.8,808.989);
   cutg->SetPoint(3,18515,752.809);
   cutg->SetPoint(4,18574.9,747.191);
   cutg->SetPoint(5,18618.1,848.315);
   cutg->SetPoint(6,18638.1,915.73);
   cutg->SetPoint(7,18611.5,1022.47);
   cutg->SetPoint(8,18554.9,1028.09);
   cutg->SetPoint(9,18515,1016.85);
   cutg->SetPoint(10,18498.3,1011.24);
   cutg->SetPoint(11,18498.3,1016.85);
   cutg->Draw("");
}
