{
//========= Macro generated from object: Bar23Be10/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar23Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18291.7,2614.46);
   cutg->SetPoint(1,18316.7,2457.83);
   cutg->SetPoint(2,18438.9,2415.66);
   cutg->SetPoint(3,18494.4,2740.96);
   cutg->SetPoint(4,18375,2867.47);
   cutg->SetPoint(5,18300,2771.08);
   cutg->SetPoint(6,18308.3,2668.67);
   cutg->SetPoint(7,18291.7,2614.46);
   cutg->Draw("");
}
