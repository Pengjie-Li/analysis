{
//========= Macro generated from object: Be12Bar8He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar8He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][8]+hodTRaw[1][8])");
   cutg->SetVarY("hodBarQCal[8]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18214.1,993.61);
   cutg->SetPoint(1,18038.4,857.827);
   cutg->SetPoint(2,18062.9,586.262);
   cutg->SetPoint(3,18111.9,490.415);
   cutg->SetPoint(4,18283.5,618.211);
   cutg->SetPoint(5,18406,825.879);
   cutg->SetPoint(6,18475.5,961.661);
   cutg->SetPoint(7,18352.9,1057.51);
   cutg->SetPoint(8,18263.1,1017.57);
   cutg->SetPoint(9,18263.1,1017.57);
   cutg->SetPoint(10,18214.1,993.61);
   cutg->Draw("");
}
