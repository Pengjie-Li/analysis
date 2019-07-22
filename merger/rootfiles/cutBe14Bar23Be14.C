{
//========= Macro generated from object: Bar23Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar23Be14",7);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18568.5,2863.95);
   cutg->SetPoint(1,18644.8,3110.79);
   cutg->SetPoint(2,18725.1,2961.54);
   cutg->SetPoint(3,18732.9,2731.92);
   cutg->SetPoint(4,18611.6,2657.29);
   cutg->SetPoint(5,18582.2,2886.91);
   cutg->SetPoint(6,18568.5,2863.95);
   cutg->Draw("");
}
