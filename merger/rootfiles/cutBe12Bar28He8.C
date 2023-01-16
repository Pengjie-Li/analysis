{
//========= Macro generated from object: Be12Bar28He8/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar28He8",8);
   cutg->SetVarX("0.5*(hodTRaw[0][28]+hodTRaw[1][28])");
   cutg->SetVarY("hodBarQCal[28]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1620.18,504.566);
   cutg->SetPoint(1,1699.5,550.228);
   cutg->SetPoint(2,1724.6,721.461);
   cutg->SetPoint(3,1658.33,750);
   cutg->SetPoint(4,1623.19,727.169);
   cutg->SetPoint(5,1605.12,624.429);
   cutg->SetPoint(6,1611.14,675.799);
   cutg->SetPoint(7,1620.18,504.566);
   cutg->Draw("");
}
