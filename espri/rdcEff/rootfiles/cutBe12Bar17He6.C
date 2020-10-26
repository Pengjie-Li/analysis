{
//========= Macro generated from object: Be12Bar17He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar17He6",12);
   cutg->SetVarX("0.5*(hodTRaw[0][17]+hodTRaw[1][17])");
   cutg->SetVarY("hodBarQCal[17]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18442.9,894.948);
   cutg->SetPoint(1,18549,906.429);
   cutg->SetPoint(2,18606.1,992.537);
   cutg->SetPoint(3,18598,1095.87);
   cutg->SetPoint(4,18524.5,1147.53);
   cutg->SetPoint(5,18470.1,1164.75);
   cutg->SetPoint(6,18418.4,1044.2);
   cutg->SetPoint(7,18412.9,969.575);
   cutg->SetPoint(8,18429.2,894.948);
   cutg->SetPoint(9,18464.6,883.467);
   cutg->SetPoint(10,18472.8,889.208);
   cutg->SetPoint(11,18442.9,894.948);
   cutg->Draw("");
}
