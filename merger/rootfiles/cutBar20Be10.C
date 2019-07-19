{
//========= Macro generated from object: Bar20Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Bar20Be10",9);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18144.2,2256.85);
   cutg->SetPoint(1,18171.5,2416.67);
   cutg->SetPoint(2,18222.4,2433.79);
   cutg->SetPoint(3,18263.4,2273.97);
   cutg->SetPoint(4,18253.6,2097.03);
   cutg->SetPoint(5,18193,2062.79);
   cutg->SetPoint(6,18157.8,2131.28);
   cutg->SetPoint(7,18148.1,2222.6);
   cutg->SetPoint(8,18144.2,2256.85);
   cutg->Draw("");
}
