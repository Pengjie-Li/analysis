{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("CUTG",8);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18630.6,2949.61);
   cutg->SetPoint(1,18833,3306.2);
   cutg->SetPoint(2,18878.5,3182.17);
   cutg->SetPoint(3,18868.4,3050.39);
   cutg->SetPoint(4,18817.8,2910.85);
   cutg->SetPoint(5,18681.2,2779.07);
   cutg->SetPoint(6,18635.6,2910.85);
   cutg->SetPoint(7,18630.6,2949.61);
   cutg->Draw("");
}
