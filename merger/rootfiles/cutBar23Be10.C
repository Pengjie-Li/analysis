{
//========= Macro generated from object: Bar23Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Bar23Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18062,2074.2);
   cutg->SetPoint(1,18132.4,2171.23);
   cutg->SetPoint(2,18140.3,2325.34);
   cutg->SetPoint(3,18114.8,2376.71);
   cutg->SetPoint(4,18071.8,2359.59);
   cutg->SetPoint(5,18026.9,2251.14);
   cutg->SetPoint(6,18069.9,2051.37);
   cutg->SetPoint(7,18062,2074.2);
   cutg->Draw("");
}
