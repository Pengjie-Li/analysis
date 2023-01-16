{
//========= Macro generated from object: Be12Bar27He8/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar27He8",7);
   cutg->SetVarX("0.5*(hodTRaw[0][27]+hodTRaw[1][27])");
   cutg->SetVarY("hodBarQCal[27]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1666.37,533.105);
   cutg->SetPoint(1,1749.7,533.105);
   cutg->SetPoint(2,1767.77,715.753);
   cutg->SetPoint(3,1704.52,835.616);
   cutg->SetPoint(4,1670.38,704.338);
   cutg->SetPoint(5,1689.46,852.74);
   cutg->SetPoint(6,1666.37,533.105);
   cutg->Draw("");
}
