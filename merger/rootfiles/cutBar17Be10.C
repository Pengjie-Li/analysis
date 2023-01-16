{
//========= Macro generated from object: Bar10Be10/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("Bar17Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][17]+hodTRaw[1][17])");
   cutg->SetVarY("hodBarQCal[17]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18234.1,2810.5);
   cutg->SetPoint(1,18327.9,2867.58);
   cutg->SetPoint(2,18367,2759.13);
   cutg->SetPoint(3,18355.3,2553.65);
   cutg->SetPoint(4,18269.3,2496.58);
   cutg->SetPoint(5,18228.2,2667.81);
   cutg->SetPoint(6,18230.2,2799.09);
   cutg->SetPoint(7,18234.1,2810.5);
   cutg->Draw("");
}
