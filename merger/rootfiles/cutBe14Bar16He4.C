{
//========= Macro generated from object: Be14Bar16He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar16He4",9);
   cutg->SetVarX("0.5*(hodTRaw[0][16]+hodTRaw[1][16])");
   cutg->SetVarY("hodBarQCal[16]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18027.2,670.886);
   cutg->SetPoint(1,18166.9,829.114);
   cutg->SetPoint(2,18242.1,765.823);
   cutg->SetPoint(3,18226,597.046);
   cutg->SetPoint(4,18102.4,533.755);
   cutg->SetPoint(5,18043.3,491.561);
   cutg->SetPoint(6,18021.8,628.692);
   cutg->SetPoint(7,18021.8,491.561);
   cutg->SetPoint(8,18027.2,670.886);
   cutg->Draw("");
}
